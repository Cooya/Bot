#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <stdbool.h>

typedef struct ByteArray* ByteArray;
typedef unsigned char byte;

extern ByteArray       creerByteArray(unsigned char*,int);
extern void            detruireByteArray(ByteArray);
extern void            reset(ByteArray);

extern void            printBuffer(ByteArray);
extern void            rewriteBuffer(ByteArray, int);

extern void            setPosition(ByteArray,int);
extern int             getPosition(ByteArray);
extern void            setBuffer(ByteArray, unsigned char* buffer);
extern unsigned char*  getBuffer(ByteArray);
extern int             bytesAvailable(ByteArray);

extern signed short    ReadShort(ByteArray);
extern unsigned short  ReadUShort(ByteArray);
extern unsigned char   ReadByte(ByteArray);
extern unsigned char*  ReadBytes(ByteArray,int);
extern signed int      ReadInt(ByteArray);
extern unsigned int    ReadUInt(ByteArray);
extern char*           ReadUTF(ByteArray);
extern bool            ReadBool(ByteArray);

extern short           swapShort(short);
extern int             swapInt(int);
extern long            swapLong(long);
extern double          swapDouble(double);

extern void            writeNullChar(ByteArray);
extern void            writeByte(ByteArray, unsigned char);
extern void            writeBytes(ByteArray, unsigned char*, int);
extern void            writeShort(ByteArray, short);
extern void            writeUShort(ByteArray, unsigned short);
extern void            writeInt(ByteArray, int);
extern void            writeUInt(ByteArray, unsigned int);
extern void            writeLong(ByteArray, long);
extern void            writeULong(ByteArray, unsigned long);
extern void            writeDouble(ByteArray, double);
extern void            writeUTF(ByteArray, char*);
extern void            writeUTFBytes(ByteArray, char*);
extern void            writeBool(ByteArray, bool);
extern void            writeBuffer(ByteArray, char*, int);

extern int             getStringLength(char*);

#endif
