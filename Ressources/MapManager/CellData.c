#include "ByteArray.h"

typedef struct CellData
{
    int floor;
    int losmov;
    int speed;
    unsigned int mapChangeData;
    unsigned int moveZone;
    int arrow;
    bool los;
    bool mov;
    bool visible;
    bool farmCell;
    bool blue;
    bool red,
    bool nonWalkableDuringRP;
    bool nonWalkableDuringFight;
}* CellData;

CellData createCellData(ByteArray reader, char mapVersion)
{
    CellData this=malloc(sizeof(struct CellData));
    this->floor=ReadByte(reader)*10;
    if(this->floor!=-1280)
    {
        this->losmov=ReadByte(reader);
        this->speed=ReadByte(reader);
        this->mapChangeData=ReadByte(reader);
        int tmpBits=0;
        if(mapVersion>5)
            this->moveZone=ReadByte(reader);
        if(mapVersion>7)
        {
            tmpBits=ReadByte(reader);
            this->arrow=15&tmpBits;
        }
        this->los=(this->losmov&2)>>1==1;
        this->mov=(this->losmov&1)==1;
        this->visible=(this->losmov&64)>>6==1;
        this->farmCell=(this->losmov&32)>>5==1;
        this->blue=(this->losmov&16)>>4==1;
        this->red=(this->losmov&8)>>3==1;
        this->nonWalkableDuringRP=(this->losmov&128)>>7==1;
        this->nonWalkableDuringFight=(this->losmov&4)>>2==1;
    }
}
