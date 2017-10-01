typedef struct Fixture
{
    int fixtureId;
    int offsetX;
    int offsetY;
    int rotation;
    int xScale;
    int yScale;
    int redMultiplier;
    int greenMultiplier;
    int blueMultiplier;
    int hue;
    unsigned int alpha;
}* Fixture;

Fixture createFixture(ByteArray reader)
{
    Fixture this=malloc(sizeof(struct Fixture));
    this->fixtureId=ReadInt(reader);
    this->offsetX=ReadShort(reader);
    this->offsetY=ReadShort(reader);
    this->rotation=ReadShot(reader);
    this->xScale=ReadShort(reader);
    this->yScale=ReadShort(reader);
    this->redMultiplier=ReadByte(reader);
    this->greenMultiplier=ReadByte(reader);
    this->blueMultiplier=ReadByte(reader);
    this->hue=this->redMultiplier|this->greenMultiplier|this->blueMultiplier;
    this->alpha=ReadByte(reader);
    return this;
}
