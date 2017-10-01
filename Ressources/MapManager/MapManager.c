#include "Definitions.h"

MapManager createMapManager(char* d2pFolderPath)
{
    MapManager this=malloc(sizeof(struct MapManager));
    this->d2pFolder=createD2pFolder(d2pFolderPath);
    this->parsedMapsList=malloc(sizeof(struct Map)*20);
    this->size=20;
    this->index=0;
    return this;
}

void extendParsedMapsList(MapManager this)
{
    this->size*=2;
    this->parsedMapsList=realloc(parsedMapsList,this->size);
}

Map getMap(MapManager this, unsigned int id)
{
    for(int i=0;i<this->index+1;i++)
        if(this->parsedMapsList[i]->id==id)
            return this->parsedMapsList[i];
    CompressedMap compressedMap=getCompressedMap(this,id);
    if(compressedMap==NULL)
        return NULL;
    Map map=createMap(compressedMap);
    if(this->index==this->size)
        extendParsedMapsList(this);
    this->parsedMapsList(this->index++)=map;
    return this->parsedMapsList[this->index-1];
}

CompressedMap getCompressedMap(MapManager this, unsigned int id)
{
    for(int i=0;i<getD2pFilesCount(this->d2pFolder);i++)
        for(int j=0;j<this->d2pFolder->d2pFolderContent[i]->compressedMapsCount;j++)
            if(this->d2pFolder->d2pFolderContent[i]->compressedMapsList[j]->id==id)
                return this->d2pFolder->d2pFolderContent[i]->compressedMapsList[j];
    printf("Identifiant de map non trouvé !");
    return NULL;
}
