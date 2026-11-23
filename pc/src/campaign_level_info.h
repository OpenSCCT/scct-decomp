// campaign_level_info.h -- AInfo, AZoneInfo and ALevelInfo as the Campaign executable builds them
#ifndef CAMPAIGN_LEVEL_INFO_H
#define CAMPAIGN_LEVEL_INFO_H

#include "unreal_actor.h"

// Engine.Info: 0x2b4 bytes, 166 virtual functions
class AInfo : public AActor {
public:
    virtual ~AInfo();
};

// Engine.ZoneInfo: 0x3b4 bytes, 167 virtual functions
class AZoneInfo : public AInfo {
public:
    virtual ~AZoneInfo();
    virtual void VirtualSlot166();

    BYTE unk_2b4[0x100];
};

// Engine.LevelInfo: 0x880 bytes, 178 virtual functions
class ALevelInfo : public AZoneInfo {
public:
    virtual ~ALevelInfo();
    virtual void VirtualSlot167();
    virtual void VirtualSlot168();
    virtual void VirtualSlot169();
    virtual void VirtualSlot170();
    virtual void VirtualSlot171();
    virtual void VirtualSlot172();
    virtual void VirtualSlot173();
    virtual void VirtualSlot174();
    virtual void VirtualSlot175();
    virtual void VirtualSlot176();
    virtual void VirtualSlot177();

    BYTE  unk_3b4[0xf0];
    DWORD unk_4a4;              // flag word: execSpawn tests it
    BYTE  unk_4a8[0x138];
    class AController *ControllerList;  // first of the level's controllers (name invented)
    BYTE  unk_5e4[0x29c];
};

#endif // CAMPAIGN_LEVEL_INFO_H
