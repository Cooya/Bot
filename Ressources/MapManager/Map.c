static const char* DefaultEncryptionKeyString="649ae451ca33ec53bbcbcc33becf15f4";
static const int NbCells=560;

typedef struct Map
{
    ByteArray reader;
    unsigned char* encryptionKey; // ???
    int mapVersion;
    bool encrypted;
    unsigned int encryptionVersion;
    int groundCRC;
    int zoomScale=1;
    int zoomOffsetX;
    int zoomOffsetY;
    int groundCacheCurrentlyUsed=0;
    unsigned int id;
    unsigned int relativeId;
    int mapType;
    int backgroundsCount;
    Fixture* backgroundFixtures;
    int foregroundsCount;
    Fixture* foregroundFixtures;
    int sub areaId;
    int shadowBonusOnEntities;
    unsigned int backgroundColor;
    int backgroundRed;
    int backgroundGreen;
    int backgroundBlue;
    int topNeighbourId;
    int bottomNeighbourId;
    int leftNeighbourId;
    int rightNeighbourId;
    bool useLowPassFilter;
    bool useReverb;
    int presetId;
    int cellsCount;
    int layersCount;
    bool isUsingNewMovementSystem=false;
    Layer* layers;
    CellData* cells;
    WorldPoint position;
    char* hashCode;
}* Map;

Map createMap(CompressedMap CM)
{
    Map this=createMap(sizeof(struct Map));
    ByteArray reader=initializeReader(this, CM);
    this->encryptionKey=DefaultEncryptionKeyString;
    initializeMap(this, reader, this->encryptionKey);
}

void initializeMap(unsigned char* encryptionKey)
{

}
