#ifndef VERSUS_NET_CHANNEL_H
#define VERSUS_NET_CHANNEL_H

// Network objects used by native property replication.
#if !defined(VERSUS_PAWN_ACTION_EVENTS_H)
#include "unreal_object.h"
#endif

// Core.PackageMap: 0x70 bytes.
class UPackageMap : public UObject {
public:
    virtual ~UPackageMap();
    virtual UBOOL CanSerializeObject(UObject *Object);
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();

    BYTE unk_28[0x48];
};

// Engine.Channel: 0x58 bytes.
class UChannel : public UObject {
public:
    virtual ~UChannel();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();

    BYTE unk_28[0x30];
};

// Engine.ActorChannel: 0xa4 bytes.
class UActorChannel : public UChannel {
public:
    virtual ~UActorChannel();
    BYTE unk_58[0x7e - 0x58];
    BYTE bActorMustStayDirty;
    BYTE unk_7f[0xa4 - 0x7f];
};

#endif
