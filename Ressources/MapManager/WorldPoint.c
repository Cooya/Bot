typedef struct WorldPoint
{
    unsigned int mapId;
    unsigned int worldId;
    int x;
    int y;
}* WorldPoint;

WorldPoint createWorldPoint(unsigned int mapId)
{
    WorldPoint this=malloc(sizeof(struct WorldPoint));
    this->mapId=mapId;
    this->worldId=(this->mapId&1073479680)>>18;
    this->x=(int)(this->mapId>>9&511);
    this->y=(int)(this->mapId&511);
    if((this->x&256)==256)
        this->x=-(this->x&255);
    if((this->y&256)==256)
        this->y=-(this->y&255);
    return this;
}
