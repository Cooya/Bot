#ifndef SOCKET_H
#define SOCKET_H

#include <stdbool.h>
#include <winsock2.h>

typedef struct Socket* Socket;

extern Socket   createSocket(bool, char*, int);
extern void     destroySocket(Socket);
extern SOCKET   getSocket(Socket);
extern SOCKET   getClient(Socket, int);
extern int      getClientsCount(Socket);
extern byte*    getSBuffer(Socket);
extern int      getBufferSize(Socket);

extern void     waitClientConnection(Socket);
extern bool     receiveData(Socket, int);

#endif
