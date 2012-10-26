#include "TCPServer.h"

static void ClientSocketReadCallback(SAL_Socket* socket, void* const state) {
	TCPServer* server;
	TCPServer_Client* client;
	uint32 received;
	uint32 excess;
	uint32 messageLength;

	client = (TCPServer_Client*)state;
	server = client->Server;

	if (server->IsWebSocket) {
		return;
	}

	received = SAL_Socket_Read(socket, client->Buffer + client->BytesReceived, MESSAGE_MAXSIZE - client->BytesReceived);
	client->BytesReceived += received;

	if (received == 0) {
		server->DisconnectCallback(client, client->State);
		TCPServer_DisconnectClient(client);
		return;
	}

	if (received > MESSAGE_LENGTHBYTES) {
		messageLength = *(uint16*)client->Buffer;
		excess = received - MESSAGE_LENGTHBYTES - messageLength;

		while (excess >= 0 && messageLength != 0) {
			server->ReceiveCallback(client, client->State, client->Buffer + MESSAGE_LENGTHBYTES, messageLength);
			
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

static SAL_Thread_Start(AcceptWorkerRun) {
	TCPServer* server;
	SAL_Socket* acceptedSocket;
	TCPServer_Client* newClient;

	server = (TCPServer*)startupArgument;
	server->Active = true;

	while (server->Active) {
		acceptedSocket = SAL_Socket_Accept(server->Listener);

		if (acceptedSocket) {
			newClient = Allocate(TCPServer_Client);
			newClient->Server = server;
			newClient->State = server->ConnectCallback(newClient, acceptedSocket->RemoteEndpointAddress);
			newClient->Socket = acceptedSocket;
			newClient->BytesReceived = 0;

			AsyncList_Append(&server->ClientList, newClient);

			SAL_Socket_SetReadCallback(acceptedSocket, ClientSocketReadCallback, newClient);
		}
	}

	return 0;
}



TCPServer* TCPServer_Listen(const int8* const port, const boolean isWebSocket, const TCPServer_OnConnect connectCallback, const TCPServer_OnReceive receiveCallback, const TCPServer_OnDisconnect disconnectCallback) {
	TCPServer* server;

	server = Allocate(TCPServer);
	server->IsWebSocket = isWebSocket;
	server->ReceiveCallback = receiveCallback;
	server->DisconnectCallback = disconnectCallback;
	server->ConnectCallback = connectCallback;
	server->Active = false;
	
	server->Listener = SAL_Socket_Listen(port, SAL_Socket_Families_IPAny, SAL_Socket_Types_TCP);
	if (server->Listener) {
		AsyncList_Initialize(&server->ClientList, Memory_Free);
		server->AcceptWorker = SAL_Thread_Create(AcceptWorkerRun, server);
	}
	else {
		Free(server);
		server = NULL;
	}

	return server;
}

void TCPServer_Send(const TCPServer_Client* const client, const uint8* const buffer, const uint16 length) {
	assert(client != NULL);
	assert(client->Server != NULL);

	if (client->Server->Active)
		SAL_Socket_Write(client->Socket, buffer, length);
}

void TCPServer_DisconnectClient(TCPServer_Client* const client) {
	assert(client != NULL);
	assert(client->Server != NULL);
	assert(client->Server->Active == true);
	
	if (client->Server->Active) {
		SAL_Socket_Close(client->Socket);
		Free(client);
	}
}

void TCPServer_Shutdown(TCPServer* const server) {
	TCPServer_Client* client;

	assert(server != NULL);
	assert(server->Active == true);

	server->Active = false;
	server->IsWebSocket = false;
	server->ReceiveCallback = NULL;
	server->DisconnectCallback = NULL;
	server->ConnectCallback = NULL;
	
	AsyncList_ForEach(client, &server->ClientList, TCPServer_Client*) {
		SAL_Socket_Close(client->Socket);
	}
	
	SAL_Socket_Close(server->Listener);
	SAL_Thread_Join(server->AcceptWorker);
	AsyncList_Uninitialize(&server->ClientList);

	Free(server);
}
