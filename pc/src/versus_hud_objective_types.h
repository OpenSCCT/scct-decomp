#ifndef VERSUS_HUD_OBJECTIVE_TYPES_H
#define VERSUS_HUD_OBJECTIVE_TYPES_H

#include "versus_sbase_interaction_types.h"

// The Engine.HUD registration records a 0x49c-byte actor.
class AHUD : public AActor {
public:
    BYTE Unknown2f8[0x3e0 - 0x2f8];
    APlayerController *PlayerOwner;
    BYTE Unknown3e4[0x49c - 0x3e4];
};

// SBase.SHud registers 0x898 bytes. Its three reflected arrays occur consecutively.
class ASHud : public AHUD {
public:
    BYTE Unknown49c[0x500 - 0x49c];
    TArray<AActor *> ActorToDraw;
    TArray<class UTexRotator *> TexRotObj;
    TArray<ASAlarm *> AlarmsList;
    BYTE Unknown524[0x5b8 - 0x524];
    FString sTutoMap;
    BYTE Unknown5c4[0x898 - 0x5c4];

    INT FindActiveAlarm();
};

#endif
