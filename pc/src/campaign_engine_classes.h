// campaign_engine_classes.h -- engine classes only the Campaign units use so far
#ifndef CAMPAIGN_ENGINE_CLASSES_H
#define CAMPAIGN_ENGINE_CLASSES_H

#include "unreal_actor.h"
#include "unreal_class.h"
#include "unreal_containers.h"
#include "unreal_pawn.h"
#include "unreal_script.h"
#include "unreal_subsystem.h"

class UViewport;
class ALevelInfo;

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
    virtual UViewport *GetViewport();
    virtual void VirtualSlot30();
    virtual UBOOL PlaySound(AActor *Actor, class USound *Sound, BYTE Slot, FLOAT Volume, INT Option4,
                            FLOAT Option5, FLOAT Option6);
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void ChangeSoundVolume(AActor *Actor, class USound *Sound, FLOAT Volume, INT Slot);
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
    virtual void AddSoundRequest(AActor *Actor, class USound *Sound, BYTE Slot, FLOAT Value1,
                                 FLOAT Value2, INT Flags);
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
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void VirtualSlot81();
    virtual void VirtualSlot82();
    virtual void VirtualSlot83();
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
    virtual AActor *SpawnActor(UClass *Class, FName InName, FVector Location, FRotator Rotation,
                               AActor *Template = 0, UBOOL bNoCollisionFail = 0,
                               UBOOL bRemoteOwned = 0, AActor *Owner = 0, APawn *Instigator = 0);
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

    BYTE                unk_80[0x3990];
    FCollisionHashBase *Hash;
    BYTE                unk_3a14[0xbc];

    ALevelInfo *GetLevelInfo() { return (ALevelInfo *)Actors(0); }
};

// Engine.Primitive: 0x54 bytes, 32 virtual functions
class UPrimitive : public UObject {
public:
    virtual ~UPrimitive();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();

    BYTE unk_28[0x2c];
};

// Engine.Mesh: 0x5c bytes, 34 virtual functions
class UMesh : public UPrimitive {
public:
    virtual ~UMesh();
    virtual void VirtualSlot32();
    virtual class UMeshInstance *MeshGetInstance(const AActor *Owner);

    BYTE unk_54[0x8];
};

// Engine.LodMesh: 0x118 bytes, 34 virtual functions
class ULodMesh : public UMesh {
public:
    virtual ~ULodMesh();

    BYTE unk_5c[0xbc];
};

// A bone of a skeletal mesh's reference skeleton: 0x40 bytes.
struct FMeshBone {
    FName Name;
    BYTE  unk_4[0x3c];
};

// Engine.SkeletalMesh: 0x3e0 bytes, 34 virtual functions
class USkeletalMesh : public ULodMesh {
public:
    virtual ~USkeletalMesh();

    BYTE              unk_118[0x30];
    TArray<FMeshBone> RefSkeleton;
    BYTE              unk_154[0x25c];
    TArray<FName>     TagAliases;
    TArray<FName>     TagNames;
    BYTE              unk_3c8[0x18];

    DECLARE_LAZY_CLASS(USkeletalMesh)
};

// Engine.MeshInstance: 0x54 bytes, 79 virtual functions
class UMeshInstance : public UPrimitive {
public:
    virtual ~UMeshInstance();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual UMesh *GetMesh();
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
    virtual FName GetActiveAnimSequence(INT Channel);
    virtual FLOAT GetActiveAnimRate(INT Channel);
    virtual FLOAT GetActiveAnimFrame(INT Channel);
    virtual FLOAT GetActiveAnimBlend(INT Channel);
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();
    virtual void VirtualSlot78();
};

// Engine.LodMeshInstance: 0x78 bytes, 80 virtual functions
class ULodMeshInstance : public UMeshInstance {
public:
    virtual ~ULodMeshInstance();
    virtual void VirtualSlot79();

    BYTE unk_54[0x24];
};

// A per-bone scale of a skeletal mesh instance: 0x3c bytes.
struct FBoneScaler {
    INT   Bone;
    FName Name;
    FLOAT ScaleUniform;
    BYTE  unk_c[0x30];
};

// Engine.SkeletalMeshInstance: 0x39c bytes, 80 virtual functions
class USkeletalMeshInstance : public ULodMeshInstance {
public:
    virtual ~USkeletalMeshInstance();

    BYTE                unk_78[0x24];
    TArray<FBoneScaler> Scalers;
    BYTE                unk_a8[0x2f4];

    UBOOL SetBoneScale(INT Slot, FLOAT BoneScale, FName BoneName);
    void SetBoneDirection(FName BoneName, FRotator BoneTurn, FVector BoneTrans, FLOAT Alpha, INT Space);
    INT MatchRefBone(FName BoneName);
    FRotator GetBoneRotation(INT BoneIdx, INT Space);
    FCoords GetBoneCoords(INT BoneIdx, INT Space);
    void SetBoneLocation(FName BoneName, FVector BoneTrans, FLOAT Alpha, FLOAT BlendTime, INT Space);
    void SetBoneRotation(FName BoneName, FRotator BoneTurn, INT Space, FLOAT Alpha, FLOAT BlendTime,
                         INT bAdditive, INT bExtra);
};

// Engine.Material: 0x48 bytes, 53 virtual functions
class UMaterial : public UObject {
public:
    virtual ~UMaterial();
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

    BYTE     unk_28[0xc];
    UObject *unk_34;            // what DrawTile draws when it is given no source
    BYTE     unk_38[0x10];

    void DrawTile(class UCanvas *Canvas, UObject *InSource, FLOAT XL, FLOAT YL, FLOAT U, FLOAT V, FLOAT UL,
                  FLOAT VL);
};

// Engine.Canvas: 0xa0 bytes, 45 virtual functions
class UCanvas : public UObject {
public:
    virtual ~UCanvas();
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
    virtual void SetDrawColor(BYTE R, BYTE G, BYTE B, BYTE A);
    virtual void DrawText(const TCHAR *Text, UBOOL CR);
    virtual void TextSize(const TCHAR *Text, FLOAT *XL, FLOAT *YL);

    BYTE   unk_28[0x28];
    FLOAT  CurX, CurY;          // pen position
    BYTE   unk_58[0xc];
    FColor Color;               // draw colour
    BYTE   unk_68[0x38];

    DECLARE_NATIVE(execDrawText)
    DECLARE_NATIVE(execTextSize)
    DECLARE_NATIVE(execSetDrawColor)
};

// Echelon.ECanvas: 0xb0 bytes, 45 virtual functions
class UECanvas : public UCanvas {
public:
    virtual ~UECanvas();

    BYTE unk_a0[0x10];

    void DrawLine(INT X, INT Y, INT XL, INT YL, const FColor &InColor, INT Alpha, UMaterial *Material);
    void DrawRectangle(INT X, INT Y, INT XL, INT YL, INT Thickness, const FColor &Color, INT Alpha,
                       UMaterial *Material);

    DECLARE_NATIVE(execBeginScene)
    DECLARE_NATIVE(execDrawActorPortal)
    DECLARE_NATIVE(execDrawCameraPortal)
    DECLARE_NATIVE(execCreateDepthMask)
    DECLARE_NATIVE(execDrawRectangle)
    DECLARE_NATIVE(execDrawLine)
};

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

    APlayerController *Actor;   // the controller this player drives
    BYTE               unk_34[0x24];
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
    BYTE  unk_4a8[0x3d8];
};

// Echelon.EGameplayColl: 0x2b4 bytes, 166 virtual functions
class AEGameplayColl : public AActor {
public:
    virtual ~AEGameplayColl();

    DECLARE_LAZY_CLASS(AEGameplayColl)
};

#endif // CAMPAIGN_ENGINE_CLASSES_H
