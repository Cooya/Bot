#include "Socket.h"
#include "Declarations.h"

#define BUFFER_SIZE_MAX 10000
#define CLIENTS_NB_MAX 10

struct Socket
{
    SOCKET socket;
    SOCKET* clients; // pour le moment c'est inutile, il ne gère pas plusieurs clients à la fois
    int clients_count;
    byte* buffer;
    int buffer_size;
    bool type; // false = client, true = serveur
};

static SOCKET initSocket(bool type, char* address, int port);

Socket createSocket(bool type, char* address, int port)
{
    Socket this=malloc(sizeof(struct Socket));
    this->socket=initSocket(type,address,port);
    this->buffer=malloc(sizeof(byte)*BUFFER_SIZE_MAX);
    this->buffer_size=0;
    this->type=type;
    if(type) // serveur
    {
        this->clients=malloc(sizeof(SOCKET)*CLIENTS_NB_MAX);
        this->clients_count=0;
    }
    return this;
}

void destroySocket(Socket this)
{
    closesocket(this->socket);
    free(this->buffer);
    if(this->type)
    {
        for(int i=0;i<this->clients_count;++i)
            closesocket(this->clients[i]);
        free(this->clients);
    }
    free(this);
}

SOCKET getSocket(Socket this)
{
    return this->socket;
}

SOCKET getClient(Socket this, int client_id)
{
    if(!this->type)
        error("getClient");
    return this->clients[client_id];
}

int getClientsCount(Socket this)
{
    if(!this->type)
        error("getClientsCount");
    return this->clients_count;
}

byte* getSBuffer(Socket this)
{
    return this->buffer;
}

int getBufferSize(Socket this)
{
    return this->buffer_size;
}

static SOCKET initSocket(bool type, char* address, int port)
{
    WSADATA WSAData;
    WSAStartup(MAKEWORD(2,0), &WSAData);
    SOCKET sock;
    SOCKADDR_IN sin;
    sin.sin_addr.s_addr = inet_addr(address);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sock = socket(AF_INET,SOCK_STREAM,0);
    bind(sock, (SOCKADDR *)&sin, sizeof(sin));
    if(type)
    {
        if (listen(sock,0)==-1)
            error("Serveur : erreur a l'ecoute du socket.");
    }
    else
    {
         if (connect(sock, (SOCKADDR *)&sin, sizeof(sin))==-1)
             error("Client : erreur a la connexion du socket.");
    }
    return sock;
}

void waitClientConnection(Socket this)
{
    if(!this->type)
        error("Erreur a la fonction waitClientConnection().");
    SOCKET client=INVALID_SOCKET;
    SOCKADDR_IN csin;
    int csin_size=sizeof(csin);
    while (client==INVALID_SOCKET)
        client=accept(this->socket, (SOCKADDR *)&csin, &csin_size);
    this->clients[this->clients_count++]=client;
}

bool receiveData(Socket this, int client_id)
{
    SOCKET client;
    if(!this->type)
        client=this->socket;
    else
        client=this->clients[client_id];
    this->buffer_size=recv(client,(char*)this->buffer,BUFFER_SIZE_MAX, 0);
    if (this->buffer_size==0)
        return false;
    return true;
}
