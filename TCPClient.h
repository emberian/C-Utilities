#ifndef INCLUDE_UTILITIES_TCPCLIENT
#define INCLUDE_UTILITIES_TCPCLIENT

#include "Common.h"
#include "AsyncList.h"
#include "TCPServer.h"
#include <SAL/Common.h>
#include <SAL/Thread.h>
#include <SAL/Socket.h>

/* forward declarations */
typedef struct TCPClient TCPClient;

typedef void (*TCPClient_OnServerDisconnect)(const TCPClient* const client, void* state);
typedef void (*TCPClient_OnReceive)(const TCPClient* const client, void* state, const uint8* const buffer, const uint16 length);

struct TCPClient {
	SAL_Socket* Server;
	TCPClient_OnReceive ReceiveCallback;
	TCPClient_OnServerDisconnect DisconnectCallback;
	uint8 Buffer[MESSAGE_MAXSIZE];
	uint16 BytesReceived;
	void* State;
};

public TCPClient* TCPClient_Connect(const int8* const address, const int8* const port, const TCPClient_OnReceive receiveCallback, const TCPClient_OnServerDisconnect serverDisconnectCallback, void* state);
public boolean TCPClient_Send(TCPClient* const client, const uint8* const buffer, const uint16 length);
public void TCPClient_Disconnect(TCPClient* const client);

#endif
