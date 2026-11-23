// campaign_native_classes.h -- engine classes that Campaign script natives take: sound, brush, volume
#ifndef CAMPAIGN_NATIVE_CLASSES_H
#define CAMPAIGN_NATIVE_CLASSES_H

#include "unreal_object.h"
#include "unreal_actor.h"

// Engine.Sound: 0x54 bytes
class USound : public UObject {
public:
    virtual ~USound();
    virtual FLOAT GetDuration();    // named after AActor::execGetSoundDuration, its caller

    BYTE unk_28[0x2c];
};

// Engine.Brush: 0x340 bytes
class ABrush : public AActor {
public:
    virtual ~ABrush();

    BYTE unk_2b4[0x8c];
};

// Engine.Volume: 0x358 bytes
class AVolume : public ABrush {
public:
    virtual ~AVolume();

    BYTE unk_340[0x18];

    UBOOL Encompasses(FVector Point);

    DECLARE_NATIVE(execEncompasses)
};

#endif // CAMPAIGN_NATIVE_CLASSES_H
