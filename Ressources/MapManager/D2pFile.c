#include <stdio.h>
#include "ByteArray.h"
#include "Definitions.h"
#define START_POSITION_END_OFFSET 16

typedef struct CompressedMap* CompressedMap;

D2pFile createD2pFile(char* d2pFilePath)
{
    D2pFile this=malloc(sizeof(struct D2pFile));
    this->d2pFilePath=d2pFilePath;
    getFileContent(this);
    return this;
}

void getFileContent(D2pFile this)
{
    FILE* file=fopen(this->d2pFilePath,"rb");
    fseek(file,0,SEEK_END);
    long file_size=ftell(file);
    fseek(file,0,SEEK_SET);
    this->content=creerByteArray(NULL,file_size);
    fread(getBuffer(this->content),sizeof(char),file_size,file);
    fclose(file);
    setPosition(this->content, file_size-START_POSITION_END_OFFSET);
    unsigned int pos=ReadUInt(this->content);
    unsigned int nb_maps=ReadUInt(this->content);
    this->compressedMapsList=malloc(sizeof(CompressedMap)*nb_maps);
    setPosition(this->content,pos);
    for(int i=0;i<nb_maps;i++)
    {
        this->compressedMapsList[i]=createCompressedMap(this->content,this->d2pFilePath);
        if (this->compressedMapsList[i]->isInvalidMap)
            destroyInvalidCompressedMap(this->compressedMapsList[i--]);
    }
}
