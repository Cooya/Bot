#include "ByteArray.h"

typedef struct SoundElement
{
    int soundId;
    int baseVolume;
    int fullVolumeDistance;
    int nullVolumeDistance;
    int minDelayBetweenLoops;
    int maxDelayBetweenLoops;
}* SoundElement;

SoundElement createSoundElement(ByteArray reader)
{
    SoundElement this=malloc(sizeof(struct SoundElement));
    this->soundId=ReadInt(reader);
    this->baseVolume=ReadShort(reader);
    this->fullVolumeDistance=ReadInt(reader);
    this->nullVolumeDistance=ReadInt(reader);
    this->minDelayBetweenLoops=ReadShort(reader);
    this->maxDelayBetweenLoops=ReadShort(reader);
    return this;
}

