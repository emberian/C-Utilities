#include "TCPClient.h"

static void ClientReadCallback(SAL_Socket* socket, void* state) {
	TCPClient* client;
	uint32 received;
	uint32 excess;
	uint32 messageLength;

	client = (TCPClient*)state;

	received = SAL_Socket_Read(socket, client->Buffer + client->BytesReceived, MESSAGE_MAXSIZE - client->BytesReceived);
	client->BytesReceived += received;

	if (received == 0) {
		client->DisconnectCallback(client, client->State);
		TCPClient_Disconnect(client);
		return;
	}

	if (received > MESSAGE_LENGTHBYTES) {
		messageLength = *(uint16*)client->Buffer;
		excess = received - MESSAGE_LENGTHBYTES - messageLength;

		while (excess >= 0 && messageLength != 0) {
			client->ReceiveCallback(client, client->State, client->Buffer + MESSAGE_LENGTHBYTES, messageLength);
			
			if (excess > 0) {
				Memory_BlockCopy(client->Buffer + client->BytesReceived - excess, client->Buffer, excess);
				client->BytesReceived = excess;
				if (excess > MESSAGE_LENGTHBYTES) {
					messageLength = *(uint16*)client->Buffer;
					excess -= MESSAGE_LENGTHBYTES + messageLength;
				}
				else {
					messageLength = 0;
				}
			}
			else {
				client->BytesReceived = 0;
				messageLength = 0;
			}
		}
		if (messageLength == 0)
			client->BytesReceived = 0;
	}
}




TCPClient* TCPClient_Connect(int8* address, int8* port, TCPClient_OnReceive receiveCallback, TCPClient_OnServerDisconnect serverDisconnectCallback, void* state) {
	TCPClient* client;

	client = Allocate(TCPClient);
	client->ReceiveCallback = receiveCallback;
	client->DisconnectCallback = serverDisconnectCallback;
	client->State = state;
	client->BytesReceived = 0;
	
	client->Server = SAL_Socket_Connect(address, port, SAL_Socket_Families_IPAny, SAL_Socket_Types_TCP);
	if (client->Server) {
		SAL_Socket_SetReadCallback(client->Server, ClientReadCallback, client);
	}
	else {
		Free(client);
		client = NULL;
	}

	return client;
}

boolean TCPClient_Send(TCPClient* client, uint8* buffer, uint16 length) {
	assert(client != NULL);
	assert(client->Server != NULL);
	assert(buffer != NULL);

	if (SAL_Socket_EnsureWrite(client->Server, buffer, length, 10) != length) {
		TCPClient_Disconnect(client);
		return false;
	}

	return true;
}

void TCPClient_Disconnect(TCPClient* client) {
	assert(client != NULL);
	assert(client->Server != NULL);

	SAL_Socket_Close(client->Server);
	Free(client);
}
