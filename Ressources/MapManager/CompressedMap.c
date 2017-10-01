#include <stdbool.h>
#include <stdlib.h>
#include "ByteArray.h"
#include "Definitions.h"

static void readMapInformations(CompressedMap this, ByteArray content)
{
    this->indexName=ReadUTF(content);
    if(this->indexName=="link" || this->indexName=="")
    {
        this->isInvalidMap=true;
        return;
    }
    this->offset=ReadUInt(content)+2;
    this->bytesCount=ReadUInt(content);
}

CompressedMap createCompressedMap(ByteArray content, char* d2pFilePath)
{
    CompressedMap this=malloc(sizeof(struct CompressedMap));
    this->d2pFilePath=d2pFilePath;
    this->isInvalidMap=false;
    readMapInformations(this,content);
    return this;
}

void destroyInvalidCompressedMap(CompressedMap this)
{
    free(this->d2pFilePath);
    free(this->indexName);
    free(this);
}
