void* getElementFromType(int type, ByteArray reader, char mapVersion)
{
    switch(type)
    {
        case 2  : return createGraphicalElement(reader,mapVersion);
        case 33 : return createSoundElement(reader);
        default : printf("Erreur de type !");
    }
}
