#include "ByteArray.h"

typedef struct Layer
{
    int layerId;
    int cellsCount;
    Cell* cells;
}* Layer;

Layer createLayer(ByteArray reader, char mapVersion)
{
    Layer this=malloc(sizeof(struct Layer));
    this->layerId=ReadInt(reader);
    this->cellsCount=ReadShort(reader);
    for(int i=0;i<this->cellsCount;i++)
        this->cells[i]=createCell(reader,mapVersion);
    return this;
}
