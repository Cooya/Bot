#include "ByteArray.h"

static short getLenOfSize(int size)
{
    if(size > 65535)
        return 3;
    else if(size > 255)
        return 2;
    else if(size > 0)
        return 1;
    else
        return 0;
}

static short getHeader(short id, short lenofsize)
{
    return id << 2 | lenofsize;
}

void writeHeader(ByteArray packet, short id, int size)
{
    short lenofsize=getLenOfSize(size);
    writeShort(packet,getHeader(id,lenofsize));
    switch(lenofsize)
    {
        case 0 : break;
        case 1 : writeByte(packet,size); break;
        case 2 : writeShort(packet,size); break;
        case 3 : writeByte(packet,size>>16&255); writeShort(packet,size&65535); break;
    }
}
