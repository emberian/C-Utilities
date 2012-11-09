#ifndef INCLUDE_UTILITIES_SERVER
#define INCLUDE_UTILITIES_SERVER

#include "Common.h"
#include "AsyncLinkedList.h"
#include <SAL/Common.h>
#include <SAL/Thread.h>
#include <SAL/Socket.h>

#define MESSAGE_LENGTHBYTES 2
#define MESSAGE_MAXSIZE 65536 + MESSAGE_LENGTHBYTES

/* forward declarations */
typedef struct TCPServer TCPServer;
typedef struct TCPServer_Client TCPServer_Client;

typedef void* (*TCPServer_OnConnect)(TCPServer_Client* client, uint8 clientAddress[SAL_Socket_AddressLength]); /* return a pointer to a state object passed in to OnReceive */
typedef void (*TCPServer_OnDisconnect)(TCPServer_Client* client, void* state);
typedef void (*TCPServer_OnReceive)(TCPServer_Client* client, void* state, uint8* buffer, uint16 length);

struct TCPServer {
	SAL_Socket* Listener;
	SAL_Thread AcceptWorker;
	AsyncLinkedList ClientList;
	boolean IsWebSocket;
	boolean Active;
	TCPServer_OnReceive ReceiveCallback;
	TCPServer_OnConnect ConnectCallback;
	TCPServer_OnDisconnect DisconnectCallback;
};

struct TCPServer_Client {
	SAL_Socket* Socket;
	void* State;
	boolean WebSocketReady;
	boolean WebSocketCloseSent;
	TCPServer* Server;
	uint8 Buffer[MESSAGE_MAXSIZE];
	uint16 BytesReceived;
	uint32 MessageLength; //for websockets only
};

export TCPServer* TCPServer_Listen(int8* port, boolean isWebSocket, TCPServer_OnConnect connectCallback, TCPServer_OnReceive receiveCallback, TCPServer_OnDisconnect disconnectCallback);
export boolean TCPServer_Send(TCPServer_Client* client, uint8* buffer, uint16 length);
export void TCPServer_DisconnectClient(TCPServer_Client* client);
export void TCPServer_Shutdown(TCPServer* server);

#endif
