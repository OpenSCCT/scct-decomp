// campaign_player.h -- UPlayer and UViewport as the Campaign executable builds them
#ifndef CAMPAIGN_PLAYER_H
#define CAMPAIGN_PLAYER_H

#include "unreal_object.h"
#include "unreal_script.h"
#include "unreal_subsystem.h"

// Engine.Player: 0x58 bytes, 29 virtual functions, the FOutputDevice vtable at 0x28 and the
// FExec vtable at 0x2c
class UPlayer : public UObject, public FOutputDevice, public FExec {
public:
    virtual ~UPlayer();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();

    class APlayerController *Actor;     // the controller this player drives
    BYTE                     unk_34[0x24];
};

// Engine.Viewport: 0x1f0 bytes, 71 virtual functions
class UViewport : public UPlayer {
public:
    virtual ~UViewport();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    virtual void VirtualSlot62();
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();

    BYTE unk_58[0x198];
};

#endif // CAMPAIGN_PLAYER_H
