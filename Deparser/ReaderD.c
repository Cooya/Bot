#include <stdlib.h>
#include "ByteArray.h"

ByteArray DEPOSIT_BUFFER;

struct Paquet
{
    int id;
    int size;
    int lenofsize;
    unsigned char* content;
    bool complete;
} P;

static ByteArray createDepositBuffer(char* buffer, int taille_buffer);
static void addToDepositBuffer(ByteArray this, char* buffer, int taille_buffer);
static void setDepositBuffer(ByteArray this, int position);
static bool deparseBuffer(char* buffer, int buffer_size);
static char* modifyBuffer(char* buffer, int* buffer_size, bool direction);

void handleBuffer(char* buffer, int buffer_size, bool direction)
{
    while(buffer_size!=0)
    {
        if (DEPOSIT_BUFFER==NULL)
        {
            if(deparseBuffer(buffer,buffer_size))
                buffer=modifyBuffer(buffer,&buffer_size,direction);
            else
            {
                //writeIntoLog("Creation du depot et ajout de %d octets dans le depot.\n\n",buffer_size);
                DEPOSIT_BUFFER=createDepositBuffer(buffer,buffer_size);
                break;
            }
        }
        else
        {
            if (P.complete==false)
            {
                //writeIntoLog("Ajout de %d octets dans le depot. ",buffer_size);
                addToDepositBuffer(DEPOSIT_BUFFER,buffer,buffer_size);
                buffer_size=getPosition(DEPOSIT_BUFFER);
                //writeIntoLog("Nouvelle taille du depot : %d octets.\n\n",buffer_size);
            }
            buffer=getBuffer(DEPOSIT_BUFFER);
            if(deparseBuffer(buffer,buffer_size))
            {
                buffer=modifyBuffer(buffer,&buffer_size,direction);
                if (buffer_size!=0)
                    setDepositBuffer(DEPOSIT_BUFFER,2+P.lenofsize+P.size);
            }
            else
                break;
        }
        if (buffer_size==0 && DEPOSIT_BUFFER!=NULL)
        {
            //writeIntoLog("Destruction du depot.\n\n");
            detruireByteArray(DEPOSIT_BUFFER);
            DEPOSIT_BUFFER=NULL;
        }
    }
}

static ByteArray createDepositBuffer(char* buffer, int buffer_size)
{
    ByteArray this=creerByteArray(NULL,0);
    writeBuffer(this,buffer,buffer_size);
    return this;
}

static void addToDepositBuffer(ByteArray this, char* buffer, int buffer_size)
{
    writeBuffer(this,buffer,buffer_size);
}

static void setDepositBuffer(ByteArray this, int position)
{
    rewriteBuffer(this,position);
}

static bool deparseBuffer(char* buffer, int buffer_size)
{
    unsigned short header = (unsigned char)buffer[0] << 8 | (unsigned char)buffer[1];
    P.id = header >> 2;
    if (P.id==0)
    {
        writeIntoLog("Erreur de deparsing !\n");
        exit(0);
    }
    P.lenofsize = header & 3;
    if(P.lenofsize == 0)
        P.size = 0;
    else if(P.lenofsize  == 1)
        P.size = (unsigned char)buffer[2];
    else if(P.lenofsize == 2)
        P.size = ((unsigned char)buffer[2]<<8|(unsigned char)buffer[3]);
    else //P.lenofsize = 3
        P.size = (((unsigned char)buffer[2]<<16|(unsigned char)buffer[3]<<8)|(unsigned char)buffer[4]);
    if (P.size>(buffer_size-P.lenofsize-2))
    {
        P.complete=false;
        return false;
    }
    P.complete=true;
    return true;
}

static char* modifyBuffer(char* buffer, int* buffer_size, bool direction)
{
    if(direction)
        writeIntoLog("Envoi du paquet %d (%s)\n",P.id,printPacketName(P.id));
    else
        writeIntoLog("Reception du paquet %d (%s)\n",P.id,printPacketName(P.id));
    writeIntoLog("Longueur de la taille : %d\n",P.lenofsize);
    writeIntoLog("Taille : %d octets\n\n",P.size);
    P.content=&buffer[2+P.lenofsize];
    *buffer_size-=(2+P.lenofsize+P.size);
    return &buffer[2+P.lenofsize+P.size];
}
