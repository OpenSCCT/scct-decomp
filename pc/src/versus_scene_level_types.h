#ifndef VERSUS_SCENE_LEVEL_TYPES_H
#define VERSUS_SCENE_LEVEL_TYPES_H

#include "versus_ltcg.h"

struct FCheckResult;
class FMemStack;
class ALevelInfo;
class UModel;

template<class T> class TTransArray : public TArray<T> {
public:
    UObject *Owner;

    const T &operator()(INT Index) const { return ((const T *)Data)[Index]; }
};

// Engine.LevelBase uses UObject as its primary base and FNetworkNotify as its
// secondary interface; its registration gives a total size of 0x13c.
class FNetworkNotify {
public:
    virtual INT NotifyAcceptingConnection() = 0;
};

class ULevelBase : public UObject, public FNetworkNotify {
public:
    virtual INT NotifyAcceptingConnection();
    TTransArray<AActor *> Actors;
    BYTE unk_3c[0x13c - 0x3c];
};

// Engine.Level derives from LevelBase and is 0x4af0 bytes in the registration.
class ULevel : public ULevelBase {
public:
    UModel *Model;
    BYTE unk_140[0x4ae0 - 0x140];
    INT unk_4ae0;
    BYTE unk_4ae4[0x4af0 - 0x4ae4];

    ALevelInfo *GetLevelInfo() const;
    void BuildRenderData();

    UBOOL SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                          const FVector &Start, DWORD TraceFlags, const FVector &Extent);
    FCheckResult *MultiLineCheck(FMemStack &Mem, FVector End, const FVector &Start,
                                 const FVector &Extent, ALevelInfo *LevelInfo, DWORD TraceFlags,
                                 AActor *SourceActor);
};

#include "versus_info.h"

// Engine.ZoneInfo: 0x340 bytes, 78 virtual functions
class AZoneInfo : public AInfo {
public:
    virtual ~AZoneInfo();

    BYTE                  unk_2f8[0xc];
    FString               unk_304;
    BYTE                  unk_310[0x24];
    TArrayLtcg<UnkType_4> unk_334;
};

// Engine.LevelInfo: 0x55c bytes, 78 virtual functions
class ALevelInfo : public AZoneInfo {
public:
    virtual ~ALevelInfo();

    BYTE                  unk_340[4];
    class UTexture       *pThermalTexture_A;
    BYTE                  unk_348[0x394 - 0x348];
    TArrayLtcg<UnkType_8> unk_394;
    BYTE                  unk_3a0[0x40];
    FString               unk_3e0;
    FString               unk_3ec;
    FString               unk_3f8;
    FString               unk_404;
    BYTE                  unk_410[0xc];
    FString               unk_41c;
    FString               unk_428;
    BYTE                  unk_434[0x78];
    FString               unk_4ac;
    FString               unk_4b8;
    FString               unk_4c4;
    FString               unk_4d0;
    BYTE                  unk_4dc[0x1c];
    TArray<UnkType_4>     unk_4f8;
    BYTE                  unk_504[0x14];
    FString               unk_518;
    BYTE                  unk_524[0x10];
    TArrayLtcg<UnkType_4> unk_534;
    TArrayLtcg<UnkType_4> unk_540;
    BYTE                  unk_54c[0x10];
};

// Engine.Primitive: 0x50 bytes, 30 virtual functions
class UPrimitive : public UObject {
public:
    virtual ~UPrimitive();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();

    BYTE unk_28[0x28];
};

#endif
