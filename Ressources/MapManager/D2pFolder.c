#include <stdlib.h>
#include <dirent.h>
#include "Definitions.h"

D2pFolder createD2pFolder(char* d2pFolderPath)
{
    D2pFolder this=malloc(sizeof(struct D2pFolder));
    this->d2pFolderPath=d2pFolderPath;
    this->d2pFilesCount=8; // nombre de fichiers fixé
    this->d2pFolderContent=malloc(sizeof(struct D2pFile)*this->d2pFilesCount);
    initializeD2pFolder(this);
    return this;
}

void initializeD2pFolder(D2pFolder this)
{
    DIR* folder=opendir(this->d2pFolderPath);
    struct dirent* file;
    int i=0;
    while((file=readdir(folder))!=NULL)
    {
        if(!strcmp(strrchr(file->d_name,'.'),".d2p"))
        {
            char* d2pFilePath=malloc(sizeof(this->d2pFolderPath)+file->d_namlen);
            strcpy(d2pFilePath,this->d2pFolderPath);
            strcat(d2pFilePath,file->d_name);
            this->d2pFolderContent[i++]=createD2pFile(d2pFilePath);
        }
    }
    closedir(folder);
}
