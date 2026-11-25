// campaign_engine_classes.h -- engine classes the Campaign units use: level, audio, collision queries
#ifndef CAMPAIGN_ENGINE_CLASSES_H
#define CAMPAIGN_ENGINE_CLASSES_H

#include "unreal_actor.h"
#include "unreal_containers.h"
#include "unreal_subsystem.h"

// The result of a collision query; a linked list when a query returns several hits.
struct FCheckResult {
    FCheckResult     *Next;
    AActor           *Actor;
    FVector           Location;
    FVector           Normal;
    class UPrimitive *Primitive;
    FLOAT             Time;         // 0..1 along the trace
    INT               Item;
    class UMaterial  *Material;
    FName             BoneName;

    FCheckResult(FLOAT InTime = 0.0f, FCheckResult *InNext = 0)
        : Next(InNext), Actor(0), Location(0, 0, 0), Normal(0, 0, 0), Primitive(0),
          Time(InTime), Item(-1), Material(0), BoneName(NAME_None) {}
};

// The level's spatial index of colliding actors: 10 virtual functions (the count of the
// implementation ULevel creates).
class FCollisionHashBase {
public:
    virtual ~FCollisionHashBase();
    virtual void Tick();
    virtual void AddActor(AActor *Actor);
    virtual void RemoveActor(AActor *Actor);
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
};

// Engine.AudioSubsystem: 0x2c bytes, 105 virtual functions
class UAudioSubsystem : public USubsystem {
public:
    virtual ~UAudioSubsystem();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual UBOOL StopSound(AActor *Actor, class USound *Sound, FLOAT FadeTime, INT Slot);
    virtual class UViewport *GetViewport();
    virtual void VirtualSlot30();
    virtual UBOOL PlaySound(AActor *Actor, class USound *Sound, BYTE Slot, FLOAT Volume, INT Option4,
                            FLOAT Option5, FLOAT Option6);
    virtual UBOOL IsPlaying(AActor *Actor, class USound *Sound);
    virtual UBOOL IsPlayingAnyActor(AActor *Actor);
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void ChangeSoundVolume(AActor *Actor, class USound *Sound, FLOAT Volume, INT Slot);
    virtual void VirtualSlot37();
    virtual INT StopAllVoicesActor(AActor *Actor, INT Option2);
    virtual void StopAllSoundsType(BYTE Type);
    virtual void StopAllSounds();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual FLOAT GetSoundPosition(AActor *Actor, class USound *Sound);
    virtual void SetVolumeLineValue(INT Line, FLOAT Value);
    virtual FLOAT GetVolumeLineValue(INT Line);
    virtual void VirtualSlot48();
    virtual void AddSoundRequest(AActor *Actor, class USound *Sound, BYTE Slot, FLOAT Value1,
                                 FLOAT Value2, INT Flags);
    virtual void FlushRequests(AActor *Actor);
    // The effect is passed as a full word (an enumeration, most likely); the script passes a byte.
    virtual void SetReverbEffect(INT Effect, AActor *Actor);
    virtual void VerifyOcclusion();
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
    virtual void SetLaserMicSession(INT Option1);
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void StartFadeOut(FLOAT Option1);
    virtual void VirtualSlot74();
    virtual UBOOL IsGameOver();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void NotifyAudioEndConversation(AActor *Actor);
    virtual UBOOL IsAConversationPlaying(AActor *Actor);
    virtual void VirtualSlot82();
    virtual void AddMaskingFadeOut(AActor *Actor);
    virtual void VirtualSlot84();
    virtual void VirtualSlot85();
    virtual void VirtualSlot86();
    virtual void VirtualSlot87();
    virtual void VirtualSlot88();
    virtual void VirtualSlot89();
    virtual void VirtualSlot90();
    virtual void VirtualSlot91();
    virtual void VirtualSlot92();
    virtual void VirtualSlot93();
    virtual void VirtualSlot94();
    virtual void VirtualSlot95();
    virtual void VirtualSlot96();
    virtual void VirtualSlot97();
    virtual void VirtualSlot98();
    virtual void VirtualSlot99();
    virtual void VirtualSlot100();
    virtual void VirtualSlot101();
    virtual void VirtualSlot102();
    virtual void VirtualSlot103();
    virtual void VirtualSlot104();
};

// Engine.Engine: 0x17c bytes, 56 virtual functions
class UEngine : public USubsystem {
public:
    virtual ~UEngine();
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

    BYTE             unk_2c[0x1c];
    UAudioSubsystem *Audio;
    BYTE             unk_4c[0x130];
};

// Engine.GameEngine: 0x1e0 bytes. Engine.u lists both level object properties.
class UGameEngine : public UEngine {
public:
    class ULevel *GLevel;
    class ULevel *GEntry;
    BYTE          unk_184[0x5c];
};

// Engine.LevelBase: 0x80 bytes, 24 virtual functions
class ULevelBase : public UObject {
public:
    virtual ~ULevelBase();

    TArray<AActor *> Actors;    // element 0 is the ALevelInfo
    BYTE             unk_34[0x4];
    UEngine         *Engine;
    BYTE             unk_3c[0x44];
};

// Engine.Level: 0x3ad0 bytes, 58 virtual functions
// The engine packs its classes to 4 bytes, which puts TimeSeconds at 0xc4.
#pragma pack(push, 4)
class ULevel : public ULevelBase {
public:
    virtual ~ULevel();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual UBOOL MoveActor(AActor *Actor, FVector Delta, FRotator NewRotation, FCheckResult &Hit,
                            UBOOL bTest = 0, UBOOL bIgnorePawns = 0, UBOOL bIgnoreBases = 0,
                            UBOOL bNoFail = 0);
    virtual UBOOL FarMoveActor(AActor *Actor, FVector DestLocation, UBOOL bTest = 0, UBOOL bNoCheck = 0,
                               UBOOL bAttachedMove = 0);
    virtual UBOOL DestroyActor(AActor *ThisActor, UBOOL bNetForce = 0);
    virtual void VirtualSlot36();
    virtual AActor *SpawnActor(class UClass *Class, FName InName, FVector Location, FRotator Rotation,
                               AActor *Template = 0, UBOOL bNoCollisionFail = 0,
                               UBOOL bRemoteOwned = 0, AActor *Owner = 0,
                               class APawn *Instigator = 0);
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
    virtual UBOOL SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                                  const FVector &Start, DWORD TraceFlags, FVector Extent,
                                  INT Option7, INT Option8);
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();

    BYTE                unk_80[0x44];
    DOUBLE              TimeSeconds;    // game time; execPlayerCanSeeMe subtracts from it (name
                                        // invented). 4-aligned: see the pack around the class
    BYTE                unk_cc[0x3944];
    FCollisionHashBase *Hash;
    BYTE                unk_3a14[0xbc];

    class ALevelInfo *GetLevelInfo() { return (class ALevelInfo *)Actors(0); }
};
#pragma pack(pop)

#endif // CAMPAIGN_ENGINE_CLASSES_H
