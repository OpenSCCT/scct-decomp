// unreal_actor.h -- AActor
#ifndef UNREAL_ACTOR_H
#define UNREAL_ACTOR_H

#include "unreal_containers.h"
#include "unreal_object.h"

#ifdef SCCT_VERSUS
#include "versus_ltcg.h"

// Engine.Actor: 0x2f8 bytes, 78 virtual functions
class AActor : public UObject {
public:
    virtual ~AActor();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
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
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();

    BYTE                  unk_28[0x110];
    TArrayLtcg<UnkType_8> unk_138;
    BYTE                  unk_144[0x80];
    TArray<UnkType_4>     unk_1c4;
    BYTE                  unk_1d0[0xc];
    TArrayLtcg<UnkType_4> unk_1dc;
    TArray<UnkType_4>     unk_1e8;
    BYTE                  unk_1f4[0x10];
    TArrayLtcg<UnkType_4> unk_204;
    TArrayLtcg<UnkType_4> unk_210;
    TArrayLtcg<UnkType_4> unk_21c;
    BYTE                  unk_228[0x18];
    TArrayLtcg<UnkType_4> unk_240;
    BYTE                  unk_24c[0x10];
    TArrayLtcg<UnkType_4> unk_25c;
    BYTE                  unk_268[0x90];
};

#endif // SCCT_VERSUS

#endif // UNREAL_ACTOR_H
