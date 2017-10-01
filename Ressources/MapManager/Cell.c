typedef struct Cell
{
    int cellId;
    int elementsCount;
    void** elements;
}* Cell;

Cell createCell(ByteArray reader, char mapVersion)
{
    Cell this=malloc(sizeof(struct Cell));
    this->cellId=ReadShort(reader);
    this->elementsCount=ReadShort(reader);
    this->elements=malloc(sizeof(void*)*this->elementsCount);
    for(int i=0;i<this->elementsCount;i++)
        this->elements[i]=getElementFromType(ReadByte(reader),reader,mapVersion);
    return this;
}
