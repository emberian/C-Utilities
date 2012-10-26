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

typedef void* (*TCPServer_OnConnect)(const TCPServer_Client* const client, uint8 clientAddress[SAL_Socket_AddressLength]); /* return a pointer to a state object passed in to OnReceive */
typedef void (*TCPServer_OnDisconnect)(const TCPServer_Client* const client, const void* state);
typedef void (*TCPServer_OnReceive)(const TCPServer_Client* const client, const void* state, const uint8* const buffer, const uint16 length);

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

public TCPServer* TCPServer_Listen(const int8* const port, const boolean isWebSocket, const TCPServer_OnConnect connectCallback, const TCPServer_OnReceive receiveCallback, const TCPServer_OnDisconnect disconnectCallback);
public boolean TCPServer_Send(TCPServer_Client* const client, const uint8* const buffer, const uint16 length);
public void TCPServer_DisconnectClient(TCPServer_Client* const client);
public void TCPServer_Shutdown(TCPServer* const server);

#endif
