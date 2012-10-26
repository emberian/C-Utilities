#include "TCPServer.h"

#include "Array.h"
#include "Misc.h"
#include "DataStream.h"
#include <SAL/Cryptography.h>

#define WS_HEADER_LINES 25
#define WS_MASK_BYTES 4
#define WS_CLOSE_OPCODE 0x8
#define WS_BINARY_OPCODE 0x2
#define WS_PONG_OPCODE 0xA
#define WS_PING_OPCODE 0x9
#define WS_TEXT_OPCODE 0x1
#define WS_CONTINUATION_OPCODE 0x0

static void TCPServer_WebSocket_DoHandshake(TCPServer_Client* const client, SAL_Socket* const socket);
static void TCPServer_WebSocket_OnReceive(TCPServer_Client* const client, SAL_Socket* const socket);
static void TCPServer_WebSocket_Send(TCPServer_Client* const client, const uint8* const data, const uint16 length, const uint8 opCode);
static void TCPServer_WebSocket_Close(TCPServer_Client* const client, const uint16 code);

static void TCPServer_WebSocket_DoHandshake(TCPServer_Client* const client, SAL_Socket* const socket) {
	int32 i;
	int32 lastOffset;
	int32 nextHeaderLine;
	Array* headerLines[WS_HEADER_LINES];
	Array* keyAndMagic;
	DataStream* response;
	uint8* hash;
	int8* base64;
	uint32 base64Length;
	
	client->BytesReceived = SAL_Socket_Read(socket, client->Buffer + client->BytesReceived, MESSAGE_MAXSIZE - client->BytesReceived);

	if (client->BytesReceived == 0) {
		client->Server->DisconnectCallback(client, client->State);
		TCPServer_DisconnectClient(client);
		return;
	}

	for (i = 0, lastOffset = 0, nextHeaderLine = 0; i < client->BytesReceived && nextHeaderLine < WS_HEADER_LINES; i++) {
		if (client->Buffer[i] == 13 && client->Buffer[i + 1] == 10) {
			headerLines[nextHeaderLine] = Array_NewFromExisting(client->Buffer + lastOffset, i - lastOffset);
			nextHeaderLine++;
			lastOffset = i + 2;
		}
	}
	
	keyAndMagic = Array_New(60);
	for (i = 0; i < nextHeaderLine; i++)
		if (headerLines[i] != NULL)
			if (headerLines[i]->Size >= 17 && Memory_Compare((const uint8*)"Sec-WebSocket-Key", headerLines[i]->Data, 17, 17))
				keyAndMagic = Array_NewFromExisting(headerLines[i]->Data + 19, 24);
	
	Array_Write(keyAndMagic, (const uint8*)"258EAFA5-E914-47DA-95CA-C5AB0DC85B11", 24, 36);
	hash = SAL_Cryptography_SHA1(keyAndMagic->Data, 60);
	Base64Encode(hash, 20, &base64, &base64Length);

	response = DataStream_New(97 + 4 + base64Length);
	DataStream_WriteBytes(response, (uint8*)"HTTP/1.1 101 Switching Protocols\r\nUpgrade: WebSocket\r\nConnection: Upgrade\r\nSec-WebSocket-Accept: ", 97, false);
	DataStream_WriteBytes(response, (uint8*)base64, base64Length, false);
	DataStream_WriteBytes(response, (uint8*)"\r\n\r\n", 4, false);
	
	SAL_Socket_Write(client->Socket, response->Data.Data, 97 + 4 + base64Length);
	client->WebSocketReady = true;
	client->BytesReceived = 0;
	
	DataStream_Free(response);
	Array_Free(keyAndMagic);
	Free(base64);
	Free(hash);
	
	for (i = 0; i < nextHeaderLine; i++)
		if (headerLines[i] != NULL)
			Array_Free(headerLines[i]);
}

static void TCPServer_WebSocket_OnReceive(TCPServer_Client* const client, SAL_Socket* const socket) {
    uint8 bytes[2];
    uint8 FIN;
    uint8 RSV1;
    uint8 RSV2;
    uint8 RSV3;
    uint16 opCode;
    uint8 mask;
    uint16 length;
	uint32 i;
	uint32 received;
	uint8 headerEnd;
	uint8 maskBuffer[WS_MASK_BYTES];
	uint8* payloadBuffer;
	uint8* dataBuffer; //used for websocket's framing. The unmasked data from the current frame is copied to the start of Client.Buffer. Client.MessageLength is then used to point to the end of the data copied to the start of Client.Buffer.

	if (client->WebSocketReady == false) {
		TCPServer_WebSocket_DoHandshake(client, socket);
		return;
	}

	dataBuffer = client->Buffer + client->MessageLength;
	received = SAL_Socket_Read(client->Socket, dataBuffer + client->BytesReceived, MESSAGE_MAXSIZE - client->BytesReceived - client->MessageLength);
	client->BytesReceived += received;
	
	if (client->BytesReceived == 0) {
		client->Server->DisconnectCallback(client, client->State);
		TCPServer_DisconnectClient(client);
		return;
	}

	while (client->BytesReceived > 0) {
		if (client->BytesReceived >= 2) {
			bytes[0] = dataBuffer[0];
			bytes[1] = dataBuffer[1];

			headerEnd = 2;
		
			FIN = bytes[0] >> 7 & 0x1;
			RSV1 = bytes[0] >> 6 & 0x1;
			RSV2 = bytes[0] >> 5 & 0x1;
			RSV3 = bytes[0] >> 4 & 0x1;
			opCode = bytes[0] & 0xF;

			mask = bytes[1] >> 7 & 0x1;
			length = bytes[1] & 0x7F;

			if (mask == false || RSV1 || RSV2 || RSV3) {
				TCPServer_WebSocket_Close(client, 1002);
				return;
			}

			if (length == 126) {
				if (client->BytesReceived < 4)
					return;
				length = SAL_Socket_NetworkToHostShort((uint16)*dataBuffer + 2);
				headerEnd += 2;
			}
			else if (length == 127) { //we don't support messages this big
				TCPServer_WebSocket_Close(client, 1009);
				return;	
			}

			switch (opCode) { //ping is handled by the application, not websocket
				case WS_TEXT_OPCODE: 
					TCPServer_WebSocket_Close(client, 1003);
					return;
				case WS_CLOSE_OPCODE: 
					TCPServer_WebSocket_Close(client, 1000);
					return;
				case WS_PONG_OPCODE:
					headerEnd += mask ? WS_MASK_BYTES : 0;
					client->BytesReceived -= headerEnd;
					dataBuffer = client->Buffer + headerEnd;
					continue;
				case WS_PING_OPCODE: 
					if (length <= 125) {
						bytes[0] = 128 | WS_PONG_OPCODE;  
						SAL_Socket_Write(client->Socket, bytes, 2);
						SAL_Socket_Write(client->Socket, dataBuffer + headerEnd, length + 4);
						headerEnd += mask ? WS_MASK_BYTES : 0;
						client->BytesReceived -= headerEnd;
						dataBuffer = client->Buffer + headerEnd;
						continue;
					}
					else {
						TCPServer_WebSocket_Close(client, 1009);
						return;
					}
				case WS_CONTINUATION_OPCODE:
				case WS_BINARY_OPCODE:  
					Memory_BlockCopy(dataBuffer + headerEnd, maskBuffer, WS_MASK_BYTES);
					headerEnd += WS_MASK_BYTES;
					payloadBuffer = dataBuffer + headerEnd;
					
					client->BytesReceived -= length + headerEnd;
					for (i = 0; i < length; i++)
						dataBuffer[i] = payloadBuffer[i] ^ maskBuffer[i % WS_MASK_BYTES];

					if (FIN) {
						if (*(uint16*)client->Buffer == client->MessageLength + length - MESSAGE_LENGTHBYTES) {
							client->Server->ReceiveCallback(client, client->State, client->Buffer + MESSAGE_LENGTHBYTES, client->MessageLength + length - MESSAGE_LENGTHBYTES);
						}
						Memory_BlockCopy(client->Buffer + length + headerEnd, client->Buffer, client->BytesReceived);
						dataBuffer = client->Buffer;
						client->MessageLength = 0;
					}
					else {
						client->MessageLength += length;
						dataBuffer = client->Buffer + client->MessageLength;
						Memory_BlockCopy(payloadBuffer + length, dataBuffer, client->BytesReceived);
					}
					continue;
				default:
					TCPServer_WebSocket_Close(client, 1002);
					return;
			}
		}
	}
}

static void TCPServer_WebSocket_Send(TCPServer_Client* const client, const uint8* const data, const uint16 length, const uint8 opCode) {
	uint8 bytes[2];
	uint16 networkLength;

	bytes[0] = 128 | opCode;

	if (length <= 125) {
		bytes[1] = (uint8)length;
		networkLength = 0;
	}
	else if (length <= 65536) {
		bytes[1] = 126;
		networkLength = SAL_Socket_HostToNetworkShort(length);
	}
	else {
		TCPServer_WebSocket_Close(client, 1004);
		return;	
	}

	SAL_Socket_Write(client->Socket, bytes, 2);
	if (networkLength)
		SAL_Socket_Write(client->Socket, (uint8*)&networkLength, 2);
	SAL_Socket_Write(client->Socket, data, length); 
}

static void TCPServer_WebSocket_Close(TCPServer_Client* const client, const uint16 code) {
	TCPServer_WebSocket_Send(client, (uint8*)&code, sizeof(uint16), WS_CLOSE_OPCODE);

	client->WebSocketCloseSent = true;

	if (client->Server->IsWebSocket)
		TCPServer_DisconnectClient(client);
}

static void TCPServer_ClientSocketReadCallback(SAL_Socket* socket, void* const state) {
	TCPServer* server;
	TCPServer_Client* client;
	uint32 received;
	uint32 excess;
	uint32 messageLength;

	client = (TCPServer_Client*)state;
	server = client->Server;

	if (server->IsWebSocket) {
		TCPServer_WebSocket_OnReceive(client, socket);
		return;
	}

	received = SAL_Socket_Read(socket, client->Buffer + client->BytesReceived, MESSAGE_MAXSIZE - client->BytesReceived);
	client->BytesReceived += received;

	if (received == 0) {
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

static SAL_Thread_Start(TCPServer_AcceptWorkerRun) {
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
			newClient->MessageLength = 0;
			newClient->WebSocketReady = false;	
			newClient->WebSocketCloseSent = false;
			
			AsyncLinkedList_Append(&server->ClientList, newClient);
			
			SAL_Socket_SetReadCallback(acceptedSocket, TCPServer_ClientSocketReadCallback, newClient);
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
		AsyncLinkedList_Initialize(&server->ClientList, NULL);
		server->AcceptWorker = SAL_Thread_Create(TCPServer_AcceptWorkerRun, server);
	}
	else {
		Free(server);
		server = NULL;
	}

	return server;
}

void TCPServer_Send(TCPServer_Client* const client, const uint8* const buffer, const uint16 length) {
	assert(client != NULL);
	assert(client->Server != NULL);
	
	if (client->Server->Active) {
		if (client->Server->IsWebSocket) {
			TCPServer_WebSocket_Send(client, buffer, length, WS_BINARY_OPCODE);
		}
		else {
			SAL_Socket_Write(client->Socket, buffer, length);
		}
	}
}

void TCPServer_DisconnectClient(TCPServer_Client* const client) {
	assert(client != NULL);
	assert(client->Server != NULL);
	
	if (!client->WebSocketCloseSent)
		TCPServer_WebSocket_Close(client, 1001);
		
	client->Server->DisconnectCallback(client, client->State);
	SAL_Socket_Close(client->Socket);
	AsyncLinkedList_Remove(&client->Server->ClientList, client);

	Free(client);
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
	
	AsyncLinkedList_ForEach(client, &server->ClientList, TCPServer_Client*) {
		TCPServer_DisconnectClient(client);
	}
	
	SAL_Socket_Close(server->Listener);
	SAL_Thread_Join(server->AcceptWorker);
	AsyncLinkedList_Uninitialize(&server->ClientList);

	Free(server);
}
