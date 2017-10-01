#include "ByteArray.h"

static const unsigned int CELL_HALF_WIDTH=43;
static const float CELL_HALF_HEIGHT=21,5;

typedef struct GraphicalElement
{
    unsigned int elementId;
    int hue1;
    int hue2;
    int hue3;
    int shadow1;
    int shadow2;
    int shadow3;
    int offsetX;
    int offsetY;
    int pixelOffsetX;
    int pixelOffsetY;
    int altitude;
    unsigned int identifier;
}* GraphicalElement;

GraphicalElement createGraphicalElement(ByteArray reader, char mapVersion)
{
    GraphicalElement this=malloc(sizeof(struct GraphicalElement));
    this->elementid=ReadUInt(reader);
    this->hue1=ReadByte(reader);
    this->hue2=ReadByte(reader);
    this->hue3=ReadByte(reader);
    this->shadow1=ReadByte(reader);
    this->shadow2=ReadByte(reader);
    this->shadow3=ReadByte(reader);
    if(mapVersion <=4)
    {
        this->offsetX=ReadByte(reader);
        this->offsetY=ReadByte(reader);
        this->pixelOffsetX=(int)(this->offsetX*CELL_HALF_WIDTH);
        this->pixelOffsetY=(int)(this->offsetY*CELL_HALF_HEIGHT);
    }
    else
    {
        this->pixelOffsetX=ReadShort(reader);
        this->pixelOffsetY=ReadShort(reader);
        this->offsetX=(int)(this->pixelOffsetX/CELL_HALF_WIDTH);
        this->offsetY=(int)(this->pixelOffsetY/CELL_HALF_HEIGHT);
    }
    this->altitude=ReadByte(reader);
    this->identifier=ReadUInt(reader);
    return this;
}
