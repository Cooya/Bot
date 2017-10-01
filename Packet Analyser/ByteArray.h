#ifndef BYTEARRAY_H
#define BYTEARRAY_H

#include <stdbool.h>

typedef struct ByteArray* ByteArray;

extern ByteArray       creerByteArray(char*,int);
extern void            detruireByteArray(ByteArray);
extern void            reset(ByteArray);

extern void            setPosition(ByteArray,int);
extern int             getPosition(ByteArray);
extern char*           getBuffer(ByteArray);
extern int             bytesAvailable(ByteArray);

extern signed short    ReadShort(ByteArray);
extern unsigned short  ReadUShort(ByteArray);
extern char            ReadByte(ByteArray);
extern char*           ReadBytes(ByteArray,int);
extern signed int      ReadInt(ByteArray);
extern unsigned int    ReadUInt(ByteArray);
extern double          ReadDouble(ByteArray);
extern char*           ReadUTF(ByteArray);
extern bool            ReadBool(ByteArray);

extern short           swapShort(short);
extern int             swapInt(int);
extern long            swapLong(long);
extern double          swapDouble(double);

extern void            writeByte(ByteArray, char);
extern void            writeBytes(ByteArray, char*, int);
extern void            writeShort(ByteArray, short);
extern void            writeUShort(ByteArray, unsigned short);
extern void            writeInt(ByteArray, int);
extern void            writeUInt(ByteArray, unsigned int);
extern void            writeLong(ByteArray, long);
extern void            writeULong(ByteArray, unsigned long);
extern void            writeDouble(ByteArray, double);
extern void            writeUTF(ByteArray, char*);
extern void            writeBool(ByteArray, bool);

#endif
