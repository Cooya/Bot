#include "ByteArray.h"
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 15000

struct ByteArray
{
    unsigned char* buffer;
    int position;
};

ByteArray creerByteArray(unsigned char* buffer, int taille_buffer)
{
    ByteArray this=malloc(sizeof(struct ByteArray));
    if (buffer!=NULL)
    {
        this->buffer=malloc(sizeof(char)*taille_buffer);
        for(int i=0;i<taille_buffer;i++)
            this->buffer[i]=buffer[i];
    }
    else
        if(taille_buffer!=0)
            this->buffer=malloc(sizeof(char)*taille_buffer);
        else
            this->buffer=malloc(sizeof(char)*MAX_SIZE);
    this->position=0;
    return this;
}

void detruireByteArray(ByteArray this)
{
    free(this->buffer);
    free(this);
}

void reset(ByteArray this)
{
    free(this->buffer);
    this->buffer=malloc(sizeof(char)*8192);
}

void printBuffer(ByteArray this)
{
    int j=this->position;
    for(int i=0;i<j;i++)
        writeIntoLog("%X ",this->buffer[i]);
    writeIntoLog("\n\n");
}

void writeBuffer(ByteArray this, char* buffer, int taille_buffer)
{
    for(int i=0;i<taille_buffer;i++)
        writeByte(this,buffer[i]);
    writeNullChar(this);
}

void rewriteBuffer(ByteArray this, int position) // nécessite d'avoir la position à la fin du buffer
{
    int size=getPosition(this);
    setPosition(this,0);
    writeBuffer(this,&this->buffer[position],size-position);
}

void setPosition(ByteArray this, int pos)
{
    this->position=pos;
}

int getPosition(ByteArray this)
{
    return this->position;
}

void setBuffer(ByteArray this, unsigned char* buffer)
{
    free(this->buffer);
    this->buffer=buffer;
    setPosition(this,0);
}

unsigned char* getBuffer(ByteArray this)
{
    return this->buffer;
}

int bytesAvailable(ByteArray this)
{
    return strlen(this->buffer) - this->position;
}

signed short ReadShort(ByteArray this)
{
    signed short s = this->buffer[this->position] * 256 + this->buffer[this->position + 1];
    this->position += 2;
    return s;
}

unsigned short ReadUShort(ByteArray this)
{
    unsigned short s = (unsigned char)this->buffer[this->position] * 256 + (unsigned char)this->buffer[this->position + 1];
    this->position += 2;
    return s;
}

unsigned char ReadByte(ByteArray this)
{
    char s = this->buffer[this->position];
    this->position++;
    return s;
}

unsigned char* ReadBytes(ByteArray this,int len)
{
    char*  s = malloc(sizeof(char)*(len+1));
    int i;
    for(i = 0; i < len; i++)
    {
        s[i] = this->buffer[this->position + i];
    }
    s[i] = '\0';
    this->position += len;
    return s;
}

signed int ReadInt(ByteArray this)
{
    signed int i =
    this->buffer[this->position] * 16777216 +
    this->buffer[this->position + 1] * 65536 +
    this->buffer[this->position + 2] * 256 +
    this->buffer[this->position + 3];
    this->position += 4;
    return i;
}

unsigned int ReadUInt(ByteArray this)
{
    unsigned int i =
    (unsigned char)this->buffer[this->position] * 16777216 +
    (unsigned char)this->buffer[this->position + 1] * 65536 +
    (unsigned char)this->buffer[this->position + 2] * 256 +
    (unsigned char)this->buffer[this->position + 3];
    this->position += 4;
    return i;
}

char* ReadUTF(ByteArray this)
{
    unsigned short len = ReadUShort(this);
    char*  s = malloc(sizeof(char)*(len+1));
    int i;
    for(i = 0; i < len; i++)
    {
        s[i] = this->buffer[this->position + i];
    }
    s[i] = '\0';
    this->position += len;
    return s;
}

bool ReadBool(ByteArray this)
{
    return ReadByte(this) == 1 ? true : false;
}

short swapShort(short s)
{
    return (s >> 8) | (s << 8);
}

int swapInt(int i)
{
    return (i >> 24) | ((i << 8) & 0x00FF0000) | ((i >> 8) & 0x0000FF00) | (i << 24);
}

long swapLong(long l)
{
    return (l >> 56) | ((l << 40) & 0x00FF000000000000) | ((l << 24) & 0x0000FF0000000000) | ((l << 8) & 0x000000FF00000000) | ((l >> 8) & 0x00000000FF000000) | ((l >> 24) & 0x0000000000FF0000) | ((l >> 40) & 0x000000000000FF00) | (l << 56);
}

double swapDouble(double d)
{
    int* p = (int*)&d;
    int tmp = p[0];
    p[0] = swapInt(p[1]);
    p[1] = swapInt(tmp);
    return d;
}

void writeNullChar(ByteArray this)
{
    this->buffer[this->position]='\0';
}

void writeByte(ByteArray this, unsigned char b)
{
    this->buffer[this->position]=b;
    this->position++;
}

void writeBytes(ByteArray this, unsigned char* bs, int len)
{
    int i=0;
    for(;i<len;i++)
        this->buffer[this->position+i]=bs[i];
    this->position+=i;
}

void writeShort(ByteArray this, short s)
{
   s=swapShort(s);
   memcpy(this->buffer + this->position, &s, sizeof(s));
   this->position+=sizeof(s);
}

void writeUShort(ByteArray this, unsigned short s)
{
    s=swapShort(s);
    memcpy(this->buffer + this->position, &s, sizeof(s));
    this->position+=sizeof(s);
}

void writeInt(ByteArray this, int i)
{
    i = swapInt(i);
    memcpy(this->buffer + this->position, &i, sizeof(i));
    this->position += sizeof(i);
}

void writeUInt(ByteArray this, unsigned int i)
{
    i = swapInt(i);
    memcpy(this->buffer + this->position, &i, sizeof(i));
    this->position += sizeof(i);
}

void writeLong(ByteArray this, long l)
{
    l = swapLong(l);
    memcpy(this->buffer + this->position, &l, sizeof(l));
    this->position += sizeof(l);
}

void writeULong(ByteArray this, unsigned long l)
{
    l = swapLong(l);
    memcpy(this->buffer + this->position, &l, sizeof(l));
    this->position += sizeof(l);
}

void writeDouble(ByteArray this, double d)
{
    d = swapDouble(d);
    memcpy(this->buffer + this->position, &d, sizeof(d));
    this->position += sizeof(d);
}

void writeUTF(ByteArray this, char* str)
{
    int len = strlen(str);
    writeShort(this,(unsigned short)len);
    int i=0;
    for(;i < len; i++)
        this->buffer[this->position + i] = str[i];
    this->position += i;
}

void writeUTFBytes(ByteArray this, char* str)
{
    int len = strlen(str);
    int i=0;
    for(;i < len; i++)
        this->buffer[this->position + i] = str[i];
    this->position += i;
}

void writeBool(ByteArray this, bool b)
{
    if (b)
        writeByte(this, 1);
    else
        writeByte(this, 0);
}

int getStringLength(char* str)
{
    int i=0;
    while(str[i]!='\0')
        i++;
    return i;
}
