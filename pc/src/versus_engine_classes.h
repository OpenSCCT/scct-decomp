// versus_engine_classes.h -- classes of the Engine package as the Versus executable builds them
#ifndef VERSUS_ENGINE_CLASSES_H
#define VERSUS_ENGINE_CLASSES_H

#include "versus_build.h"
#include "unreal_actor.h"
#include "unreal_commandlet.h"
#include "unreal_containers.h"
#include "unreal_interaction.h"
#include "unreal_object.h"
#include "unreal_pawn.h"
#include "versus_core_classes.h"
#include "versus_canvas.h"
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
    BYTE unk_140[0x4af0 - 0x140];

    ALevelInfo *GetLevelInfo() const;

    UBOOL SingleLineCheck(FCheckResult &Hit, AActor *SourceActor, const FVector &End,
                          const FVector &Start, DWORD TraceFlags, const FVector &Extent);
    FCheckResult *MultiLineCheck(FMemStack &Mem, FVector End, const FVector &Start,
                                 const FVector &Extent, ALevelInfo *LevelInfo, DWORD TraceFlags,
                                 AActor *SourceActor);
};

// Engine.SImpactManager: 0x554 bytes, 78 virtual functions
class ASImpactManager : public AActor {
public:
    virtual ~ASImpactManager();

    BYTE unk_2f8[0x25c];
};

// Engine.Info: 0x2f8 bytes, 78 virtual functions
class AInfo : public AActor {
public:
    virtual ~AInfo();
};

// Engine.FileLog: 0x308 bytes, 78 virtual functions
class AFileLog : public AInfo {
public:
    virtual ~AFileLog();

    BYTE    unk_2f8[0x4];
    FString unk_2fc;
};

// Engine.GameStats: 0x300 bytes, 78 virtual functions
class AGameStats : public AInfo {
public:
    virtual ~AGameStats();

    BYTE unk_2f8[0x8];
};

// Engine.Light: 0x30c bytes, 78 virtual functions
class ALight : public AActor {
public:
    virtual ~ALight();

    BYTE unk_2f8[0x14];
};

// Engine.Note: 0x304 bytes, 78 virtual functions
class ANote : public AActor {
public:
    virtual ~ANote();

    FString unk_2f8;
};

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

    BYTE                  unk_340[0x54];
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

// Engine.Camera: 0x604 bytes, 84 virtual functions
class ACamera : public APlayerController {
public:
    virtual ~ACamera();
};

// Engine.SkyZoneInfo: 0x340 bytes, 78 virtual functions
class ASkyZoneInfo : public AZoneInfo {
public:
    virtual ~ASkyZoneInfo();
};

// Engine.Decoration: 0x32c bytes, 78 virtual functions
class ADecoration : public AActor {
public:
    virtual ~ADecoration();

    BYTE unk_2f8[0x34];
};

// Engine.Projectile: 0x324 bytes, 80 virtual functions
class AProjectile : public AActor {
public:
    virtual ~AProjectile();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();

    BYTE unk_2f8[0x2c];
};

// Engine.Effects: 0x2f8 bytes, 78 virtual functions
class AEffects : public AActor {
public:
    virtual ~AEffects();
};

// Engine.SImpactEffectBase: 0x304 bytes, 78 virtual functions
class ASImpactEffectBase : public AActor {
public:
    virtual ~ASImpactEffectBase();

    BYTE unk_2f8[0xc];
};

// Engine.Projector: 0x47c bytes, 83 virtual functions
class AProjector : public AActor {
public:
    virtual ~AProjector();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void VirtualSlot81();
    virtual void VirtualSlot82();

    BYTE unk_2f8[0x184];
};

// Engine.SBulletImpact: 0x480 bytes, 83 virtual functions
class ASBulletImpact : public AProjector {
public:
    virtual ~ASBulletImpact();

    BYTE unk_47c[0x4];
};

// Engine.PlayerStart: 0x338 bytes, 78 virtual functions
class APlayerStart : public AActor {
public:
    virtual ~APlayerStart();

    BYTE unk_2f8[0x40];
};

// Engine.Keypoint: 0x2f8 bytes, 78 virtual functions
class AKeypoint : public AActor {
public:
    virtual ~AKeypoint();
};

// Engine.Triggers: 0x2f8 bytes, 78 virtual functions
class ATriggers : public AActor {
public:
    virtual ~ATriggers();
};

// Engine.Trigger: 0x32c bytes, 78 virtual functions
class ATrigger : public ATriggers {
public:
    virtual ~ATrigger();

    BYTE    unk_2f8[0x4];
    FString unk_2fc;
    BYTE    unk_308[0x24];
};

// Engine.LocalMessage: 0x314 bytes, 78 virtual functions
class ALocalMessage : public AInfo {
public:
    virtual ~ALocalMessage();

    BYTE unk_2f8[0x1c];
};

// Engine.MotionTrackingVision: 0x328 bytes, 78 virtual functions
class AMotionTrackingVision : public AActor {
public:
    virtual ~AMotionTrackingVision();

    TArrayLtcg<UnkType_28> unk_2f8;
    BYTE                   unk_304[0x4];
    FString                unk_308;
    BYTE                   unk_314[0x14];
};

// Engine.ReplicationInfo: 0x2f8 bytes, 78 virtual functions
class AReplicationInfo : public AInfo {
public:
    virtual ~AReplicationInfo();
};

// Engine.PlayerReplicationInfo: 0x450 bytes, 78 virtual functions
class APlayerReplicationInfo : public AReplicationInfo {
public:
    virtual ~APlayerReplicationInfo();

    FString unk_2f8;
    FString unk_304;
    FString unk_310;
    FString unk_31c;
    FString unk_328;
    FString unk_334;
    FString unk_340;
    FString unk_34c;
    FString unk_358;
    FString unk_364;
    FString unk_370;
    FString unk_37c;
    FString unk_388;
    FString unk_394;
    FString unk_3a0;
    FString unk_3ac;
    FString unk_3b8;
    BYTE    unk_3c4[0x8c];
};

// Engine.InternetInfo: 0x2f8 bytes, 78 virtual functions
class AInternetInfo : public AInfo {
public:
    virtual ~AInternetInfo();
};

// Engine.GameReplicationInfo: 0x3c0 bytes, 78 virtual functions
class AGameReplicationInfo : public AReplicationInfo {
public:
    virtual ~AGameReplicationInfo();

    FString               unk_2f8;
    FString               unk_304;
    BYTE                  unk_310[0x68];
    FString               unk_378;
    FString               unk_384;
    FString               unk_390;
    FString               unk_39c;
    BYTE                  unk_3a8[0x4];
    TArrayLtcg<UnkType_4> unk_3ac;
    BYTE                  unk_3b8[0x8];
};

// Engine.LevelSummary: 0x50 bytes, 22 virtual functions
class ULevelSummary : public UObject {
public:
    virtual ~ULevelSummary();

    FString unk_28;
    FString unk_34;
    BYTE    unk_40[0x4];
    FString unk_44;
};

// Engine.Brush: 0x354 bytes, 78 virtual functions
class ABrush : public AActor {
public:
    virtual ~ABrush();

    BYTE unk_2f8[0x5c];
};

// Engine.LineOfSightTrigger: 0x314 bytes, 78 virtual functions
class ALineOfSightTrigger : public ATriggers {
public:
    virtual ~ALineOfSightTrigger();

    BYTE unk_2f8[0x1c];
};

// Engine.Volume: 0x370 bytes, 78 virtual functions
class AVolume : public ABrush {
public:
    virtual ~AVolume();

    BYTE    unk_354[0x8];
    FString unk_35c;
    BYTE    unk_368[0x8];
};

// Engine.BlockingVolume: 0x370 bytes, 78 virtual functions
class ABlockingVolume : public AVolume {
public:
    virtual ~ABlockingVolume();
};

// Engine.TeamInfo: 0x324 bytes, 78 virtual functions
class ATeamInfo : public AReplicationInfo {
public:
    virtual ~ATeamInfo();

    FString unk_2f8;
    BYTE    unk_304[0x20];
};

// Engine.AntiPortalActor: 0x2f8 bytes, 78 virtual functions
class AAntiPortalActor : public AActor {
public:
    virtual ~AAntiPortalActor();
};

// Engine.CarriedObject: 0x30c bytes, 78 virtual functions
class ACarriedObject : public AActor {
public:
    virtual ~ACarriedObject();

    BYTE unk_2f8[0x14];
};

// Engine.Sound: 0x84 bytes, 23 virtual functions
class USound : public UObject {
public:
    virtual ~USound();
    virtual void VirtualSlot22();

    UnkType_308B00        unk_28;
    BYTE                  unk_40[0x8];
    FString               unk_48;
    BYTE                  unk_54[0x18];
    TArrayLtcg<UnkType_4> unk_6c;
    TArray<UnkType_4>     unk_78;
};

// Engine.I3DL2Listener: 0x9c bytes, 22 virtual functions
class UI3DL2Listener : public UObject {
public:
    virtual ~UI3DL2Listener();

    BYTE unk_28[0x74];
};

// Engine.ParticleEmitter: 0x3e8 bytes, 32 virtual functions
class UParticleEmitter : public UObject {
public:
    virtual ~UParticleEmitter();
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

    BYTE                          unk_28[0xf8];
    TArrayLtcg<UnkType_8>         unk_120;
    BYTE                          unk_12c[0x30];
    FString                       unk_15c;
    BYTE                          unk_168[0xbc];
    TArrayLtcg<UnkType_10>        unk_224;
    BYTE                          unk_230[0x58];
    TArrayLtcg<UnkType_8_911AA0>  unk_288;
    BYTE                          unk_294[0x18];
    TArrayLtcg<UnkType_28>        unk_2ac;
    BYTE                          unk_2b8[0x34];
    TArrayLtcg<UnkType_4>         unk_2ec;
    BYTE                          unk_2f8[0x8c];
    TArrayLtcg<UnkType_10>        unk_384;
    BYTE                          unk_390[0x14];
    TArrayLtcg<UnkType_C8_911AA0> unk_3a4;
    BYTE                          unk_3b0[0x38];
};

// Engine.BeamEmitter: 0x4f4 bytes, 33 virtual functions
class UBeamEmitter : public UParticleEmitter {
public:
    virtual ~UBeamEmitter();
    virtual void VirtualSlot32();

    BYTE                   unk_3e8[0x8];
    TArrayLtcg<UnkType_20> unk_3f0;
    BYTE                   unk_3fc[0x4c];
    TArrayLtcg<UnkType_10> unk_448;
    TArrayLtcg<UnkType_10> unk_454;
    BYTE                   unk_460[0x6c];
    TArrayLtcg<UnkType_10> unk_4cc;
    TArray<UnkType_C>      unk_4d8;
    TArrayLtcg<UnkType_4>  unk_4e4;
    BYTE                   unk_4f0[0x4];
};

// Engine.Channel: 0x58 bytes, 28 virtual functions
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

// Engine.CheatManager: 0x28 bytes, 22 virtual functions
class UCheatManager : public UObject {
public:
    virtual ~UCheatManager();
};

// Engine.PlayerInput: 0x7c bytes, 22 virtual functions
class UPlayerInput : public UObject {
public:
    virtual ~UPlayerInput();

    BYTE unk_28[0x54];
};

// Engine.ServerCommandlet: 0x1dc bytes, 23 virtual functions
class UServerCommandlet : public UCommandlet {
public:
    virtual ~UServerCommandlet();
};

// Engine.GlobalTempObjects: 0x34 bytes, 22 virtual functions
class UGlobalTempObjects : public UObject {
public:
    virtual ~UGlobalTempObjects();

    TArrayLtcg<UnkType_4> unk_28;
};

// Engine.Polys: 0x38 bytes, 22 virtual functions
class UPolys : public UObject {
public:
    virtual ~UPolys();

    TArrayLtcg<UnkType_E4> unk_28;
    BYTE                   unk_34[0x4];
};

// Engine.InteractionMaster: 0x44 bytes, 22 virtual functions
class UInteractionMaster : public UInteractions {
public:
    virtual ~UInteractionMaster();

    BYTE                  unk_28[0xc];
    TArrayLtcg<UnkType_4> unk_34;
    BYTE                  unk_40[0x4];
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

// Engine.MeshInstance: 0x50 bytes, 71 virtual functions
class UMeshInstance : public UPrimitive {
public:
    virtual ~UMeshInstance();
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
};

// Engine.LodMeshInstance: 0x78 bytes, 72 virtual functions
class ULodMeshInstance : public UMeshInstance {
public:
    virtual ~ULodMeshInstance();
    virtual void VirtualSlot71();

    BYTE unk_50[0x28];
};

#include "versus_material.h"

// Engine.RenderedMaterial: 0x4c bytes, 35 virtual functions
class URenderedMaterial : public UMaterial {
public:
    virtual ~URenderedMaterial();
};

// Engine.BitmapMaterial: 0x64 bytes, 37 virtual functions
class UBitmapMaterial : public URenderedMaterial {
public:
    virtual ~UBitmapMaterial();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();

    BYTE unk_4c[0x18];
};

// Engine.ProxyBitmapMaterial: 0x68 bytes, 37 virtual functions
class UProxyBitmapMaterial : public UBitmapMaterial {
public:
    virtual ~UProxyBitmapMaterial();

    BYTE unk_64[0x4];
};

// Engine.TexCoordMaterial: 0x54 bytes, 35 virtual functions
class UTexCoordMaterial : public URenderedMaterial {
public:
    virtual ~UTexCoordMaterial();

    BYTE unk_4c[0x8];
};

// Engine.Modifier: 0x50 bytes, 35 virtual functions
class UModifier : public UMaterial {
public:
    virtual ~UModifier();

    BYTE unk_4c[0x4];
};

// Engine.ColorModifier: 0x58 bytes, 35 virtual functions
class UColorModifier : public UModifier {
public:
    virtual ~UColorModifier();

    BYTE unk_50[0x8];
};

// Engine.EchelonLightingMaterial: 0x58 bytes, 35 virtual functions
class UEchelonLightingMaterial : public UMaterial {
public:
    virtual ~UEchelonLightingMaterial();

    BYTE unk_4c[0xc];
};

// Engine.Shader: 0x74 bytes, 35 virtual functions
class UShader : public URenderedMaterial {
public:
    virtual ~UShader();

    BYTE unk_4c[0x28];
};

// Engine.LitSpecularMaterial: 0x64 bytes, 35 virtual functions
class ULitSpecularMaterial : public URenderedMaterial {
public:
    virtual ~ULitSpecularMaterial();

    BYTE unk_4c[0x18];
};

// Engine.Combiner: 0x60 bytes, 35 virtual functions
class UCombiner : public UMaterial {
public:
    virtual ~UCombiner();

    BYTE unk_4c[0x14];
};

// Engine.ConstantMaterial: 0x4c bytes, 36 virtual functions
class UConstantMaterial : public URenderedMaterial {
public:
    virtual ~UConstantMaterial();
    virtual void VirtualSlot35();
};

// Engine.ConstantColor: 0x50 bytes, 36 virtual functions
class UConstantColor : public UConstantMaterial {
public:
    virtual ~UConstantColor();

    BYTE unk_4c[0x4];
};

// Engine.FadeColor: 0x60 bytes, 36 virtual functions
class UFadeColor : public UConstantMaterial {
public:
    virtual ~UFadeColor();

    BYTE unk_4c[0x14];
};

// Engine.TexModifier: 0x58 bytes, 36 virtual functions
class UTexModifier : public UModifier {
public:
    virtual ~UTexModifier();
    virtual void VirtualSlot35();

    BYTE unk_50[0x8];
};

// Engine.TexPanner: 0xa8 bytes, 36 virtual functions
class UTexPanner : public UTexModifier {
public:
    virtual ~UTexPanner();

    BYTE unk_58[0x50];
};

// Engine.TexPannerTriggered: 0xb8 bytes, 36 virtual functions
class UTexPannerTriggered : public UTexPanner {
public:
    virtual ~UTexPannerTriggered();

    BYTE unk_a8[0x10];
};

// Engine.TexFriendlyPanner: 0xac bytes, 36 virtual functions
class UTexFriendlyPanner : public UTexModifier {
public:
    virtual ~UTexFriendlyPanner();

    BYTE unk_58[0x54];
};

// Engine.TexScaler: 0xa8 bytes, 36 virtual functions
class UTexScaler : public UTexModifier {
public:
    virtual ~UTexScaler();

    BYTE unk_58[0x50];
};

// Engine.TexRotator: 0xd8 bytes, 36 virtual functions
class UTexRotator : public UTexModifier {
public:
    virtual ~UTexRotator();

    BYTE unk_58[0x80];
};

// Engine.TexOscillator: 0xcc bytes, 36 virtual functions
class UTexOscillator : public UTexModifier {
public:
    virtual ~UTexOscillator();

    BYTE unk_58[0x74];
};

// Engine.TexOscillatorTriggered: 0xdc bytes, 36 virtual functions
class UTexOscillatorTriggered : public UTexOscillator {
public:
    virtual ~UTexOscillatorTriggered();

    BYTE unk_cc[0x10];
};

// Engine.TexEnvMap: 0x5c bytes, 36 virtual functions
class UTexEnvMap : public UTexModifier {
public:
    virtual ~UTexEnvMap();

    BYTE unk_58[0x4];
};

// Engine.TexMatrix: 0x98 bytes, 36 virtual functions
class UTexMatrix : public UTexModifier {
public:
    virtual ~UTexMatrix();

    BYTE unk_58[0x40];
};

// Engine.TexCoordSource: 0x5c bytes, 36 virtual functions
class UTexCoordSource : public UTexModifier {
public:
    virtual ~UTexCoordSource();

    BYTE unk_58[0x4];
};

// Engine.VertexColor: 0x4c bytes, 35 virtual functions
class UVertexColor : public URenderedMaterial {
public:
    virtual ~UVertexColor();
};

// Engine.FinalBlend: 0x5c bytes, 35 virtual functions
class UFinalBlend : public UModifier {
public:
    virtual ~UFinalBlend();

    BYTE unk_50[0xc];
};

// Engine.MaterialSwitch: 0x60 bytes, 35 virtual functions
class UMaterialSwitch : public UModifier {
public:
    virtual ~UMaterialSwitch();

    BYTE                  unk_50[0x4];
    TArrayLtcg<UnkType_4> unk_54;
};

// Engine.MaterialSequence: 0x70 bytes, 35 virtual functions
class UMaterialSequence : public UModifier {
public:
    virtual ~UMaterialSequence();

    TArrayLtcg<UnkType_C> unk_50;
    BYTE                  unk_5c[0x14];
};

// Engine.HeatTextureModifier: 0x5c bytes, 35 virtual functions
class UHeatTextureModifier : public UModifier {
public:
    virtual ~UHeatTextureModifier();

    BYTE unk_50[0xc];
};

// Engine.EMFTextureModifier: 0x58 bytes, 35 virtual functions
class UEMFTextureModifier : public UModifier {
public:
    virtual ~UEMFTextureModifier();

    BYTE unk_50[0x8];
};

// Engine.SpecialVisionTextureModifier: 0x60 bytes, 35 virtual functions
class USpecialVisionTextureModifier : public UModifier {
public:
    virtual ~USpecialVisionTextureModifier();

    BYTE unk_50[0x10];
};

// Engine.OpacityModifier: 0x58 bytes, 35 virtual functions
class UOpacityModifier : public UModifier {
public:
    virtual ~UOpacityModifier();

    BYTE unk_50[0x8];
};

// Engine.Mesh: 0x54 bytes, 31 virtual functions
class UMesh : public UPrimitive {
public:
    virtual ~UMesh();
    virtual void VirtualSlot30();

    BYTE unk_50[0x4];
};

// Engine.MeshEmitter: 0x3fc bytes, 32 virtual functions
class UMeshEmitter : public UParticleEmitter {
public:
    virtual ~UMeshEmitter();

    BYTE unk_3e8[0x14];
};

// Engine.Mover: 0x4e8 bytes, 80 virtual functions
class AMover : public AActor {
public:
    virtual ~AMover();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();

    BYTE                   unk_2f8[0x140];
    TArrayLtcg<UnkType_1C> unk_438;
    BYTE                   unk_444[0x64];
    TArrayLtcg<UnkType_4>  unk_4a8;
    BYTE                   unk_4b4[0x34];
};

// Engine.MoverRotating: 0x500 bytes, 80 virtual functions
class AMoverRotating : public AMover {
public:
    virtual ~AMoverRotating();

    BYTE unk_4e8[0x18];
};

// Engine.PackageMapLevel: 0x74 bytes, 32 virtual functions
class UPackageMapLevel : public UPackageMap {
public:
    virtual ~UPackageMapLevel();

    BYTE unk_70[0x4];
};

// Engine.Emitter: 0x364 bytes, 81 virtual functions
class AEmitter : public AActor {
public:
    virtual ~AEmitter();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();

    TArrayLtcg<UnkType_4> unk_2f8;
    BYTE                  unk_304[0x60];
};

// Engine.ParticleMaterial: 0x2dc bytes, 35 virtual functions
class UParticleMaterial : public URenderedMaterial {
public:
    virtual ~UParticleMaterial();

    BYTE unk_4c[0x290];
};

// Engine.ProjectorPrimitive: 0x50 bytes, 30 virtual functions
class UProjectorPrimitive : public UPrimitive {
public:
    virtual ~UProjectorPrimitive();
};

// Engine.ShadowProjector: 0x498 bytes, 83 virtual functions
class AShadowProjector : public AProjector {
public:
    virtual ~AShadowProjector();

    BYTE unk_47c[0x1c];
};

// Engine.ProjectorMaterial: 0xe0 bytes, 35 virtual functions
class UProjectorMaterial : public URenderedMaterial {
public:
    virtual ~UProjectorMaterial();

    BYTE unk_4c[0x94];
};

// Engine.RenderResource: 0x2c bytes, 22 virtual functions
class URenderResource : public UObject {
public:
    virtual ~URenderResource();

    BYTE unk_28[0x4];
};

// Engine.VertexStreamBase: 0x38 bytes, 24 virtual functions
class UVertexStreamBase : public URenderResource {
public:
    virtual ~UVertexStreamBase();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();

    BYTE unk_2c[0xc];
};

// Engine.MatchInfo: 0x90 bytes, 22 virtual functions
class UMatchInfo : public UObject {
public:
    virtual ~UMatchInfo();

    FString unk_28;
    FString unk_34;
    FString unk_40;
    FString unk_4c;
    BYTE    unk_58[0x8];
    FString unk_60;
    FString unk_6c;
    FString unk_78;
    FString unk_84;
};

// Engine.MeshObject: 0x28 bytes, 22 virtual functions
class UMeshObject : public UObject {
public:
    virtual ~UMeshObject();
};

// Engine.ScriptedTexture: 0x78 bytes, 37 virtual functions
class UScriptedTexture : public UBitmapMaterial {
public:
    virtual ~UScriptedTexture();

    BYTE unk_64[0x14];
};

// Engine.ShadowBitmapMaterial: 0x94 bytes, 37 virtual functions
class UShadowBitmapMaterial : public UBitmapMaterial {
public:
    virtual ~UShadowBitmapMaterial();

    BYTE unk_64[0x30];
};

// Engine.Animation: 0x28 bytes, 22 virtual functions
class UAnimation : public UObject {
public:
    virtual ~UAnimation();
};

// Engine.AnimNotify: 0x2c bytes, 23 virtual functions
class UAnimNotify : public UObject {
public:
    virtual ~UAnimNotify();
    virtual void VirtualSlot22();

    BYTE unk_28[0x4];
};

// Engine.AnimNotify_Effect: 0x68 bytes, 23 virtual functions
class UAnimNotify_Effect : public UAnimNotify {
public:
    virtual ~UAnimNotify_Effect();

    BYTE unk_2c[0x3c];
};

// Engine.AnimNotify_DestroyEffect: 0x34 bytes, 23 virtual functions
class UAnimNotify_DestroyEffect : public UAnimNotify {
public:
    virtual ~UAnimNotify_DestroyEffect();

    BYTE unk_2c[0x8];
};

// Engine.AnimNotify_Sound: 0x3c bytes, 23 virtual functions
class UAnimNotify_Sound : public UAnimNotify {
public:
    virtual ~UAnimNotify_Sound();

    BYTE unk_2c[0x10];
};

// Engine.AnimNotify_StopSound: 0x30 bytes, 23 virtual functions
class UAnimNotify_StopSound : public UAnimNotify {
public:
    virtual ~UAnimNotify_StopSound();

    BYTE unk_2c[0x4];
};

// Engine.AnimNotify_Script: 0x30 bytes, 23 virtual functions
class UAnimNotify_Script : public UAnimNotify {
public:
    virtual ~UAnimNotify_Script();

    BYTE unk_2c[0x4];
};

// Engine.AnimNotify_Scripted: 0x2c bytes, 23 virtual functions
class UAnimNotify_Scripted : public UAnimNotify {
public:
    virtual ~UAnimNotify_Scripted();
};

// Engine.SparkEmitter: 0x424 bytes, 32 virtual functions
class USparkEmitter : public UParticleEmitter {
public:
    virtual ~USparkEmitter();

    BYTE                   unk_3e8[0x18];
    TArrayLtcg<UnkType_20> unk_400;
    BYTE                   unk_40c[0x18];
};

// Engine.SpriteEmitter: 0x408 bytes, 33 virtual functions
class USpriteEmitter : public UParticleEmitter {
public:
    virtual ~USpriteEmitter();
    virtual void VirtualSlot32();

    BYTE unk_3e8[0x20];
};

// Engine.StaticMeshActor: 0x2fc bytes, 78 virtual functions
class AStaticMeshActor : public AActor {
public:
    virtual ~AStaticMeshActor();

    BYTE unk_2f8[0x4];
};

// Engine.Texture: 0xc0 bytes, 46 virtual functions
class UTexture : public UBitmapMaterial {
public:
    virtual ~UTexture();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();

    BYTE unk_64[0x5c];
};

// Engine.Palette: 0x3c bytes, 22 virtual functions
class UPalette : public UObject {
public:
    virtual ~UPalette();

    TArrayLtcg<UnkType_4> unk_28;
    BYTE                  unk_34[0x8];
};

// Engine.Cubemap: 0xdc bytes, 46 virtual functions
class UCubemap : public UTexture {
public:
    virtual ~UCubemap();

    BYTE unk_c0[0x1c];
};

// Engine.TrailEmitter: 0x424 bytes, 32 virtual functions
class UTrailEmitter : public UParticleEmitter {
public:
    virtual ~UTrailEmitter();

    BYTE                   unk_3e8[0x10];
    TArrayLtcg<UnkType_1C> unk_3f8;
    TArrayLtcg<UnkType_14> unk_404;
    BYTE                   unk_410[0x14];
};

// Engine.DecorationList: 0x304 bytes, 78 virtual functions
class ADecorationList : public AKeypoint {
public:
    virtual ~ADecorationList();

    TArrayLtcg<UnkType_24> unk_2f8;
};

// Engine.DecoVolumeObject: 0x2f8 bytes, 78 virtual functions
class ADecoVolumeObject : public AActor {
public:
    virtual ~ADecoVolumeObject();
};

// Engine.ESoftBodyActor: 0x394 bytes, 80 virtual functions
class AESoftBodyActor : public AActor {
public:
    virtual ~AESoftBodyActor();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();

    BYTE                   unk_2f8[0x4];
    TArrayLtcg<UnkType_10> unk_2fc;
    TArrayLtcg<UnkType_10> unk_308;
    TArrayLtcg<UnkType_18> unk_314;
    TArrayLtcg<UnkType_10> unk_320;
    BYTE                   unk_32c[0x68];
};

// Engine.ESoftBody: 0x15c bytes, 58 virtual functions
class UESoftBody : public UPrimitive {
public:
    virtual ~UESoftBody();
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

    BYTE unk_50[0x10c];
};

// Engine.SLogManager: 0x354 bytes, 78 virtual functions
class ASLogManager : public AActor {
public:
    virtual ~ASLogManager();

    FString                    unk_2f8;
    FString                    unk_304;
    BYTE                       unk_310[0x8];
    TArrayLtcg<UnkType_9A3370> unk_318;
    TArray<UnkType_4>          unk_324;
    TArrayLtcg<UnkType_4>      unk_330;
    TArray<FString>            unk_33c;
    TArrayLtcg<UnkType_8>      unk_348;
};

// Engine.Inventory: 0x338 bytes, 78 virtual functions
class AInventory : public AActor {
public:
    virtual ~AInventory();

    FString unk_2f8;
    FString unk_304;
    FString unk_310;
    FString unk_31c;
    BYTE    unk_328[0x10];
};

// Engine.LANErrorHandler: 0x38 bytes, 22 virtual functions
class ULANErrorHandler : public UObject {
public:
    virtual ~ULANErrorHandler();

    BYTE unk_28[0x10];
};

// Engine.ERainVolume: 0x340 bytes, 78 virtual functions
class AERainVolume : public AActor {
public:
    virtual ~AERainVolume();

    BYTE unk_2f8[0x48];
};

// Engine.MagmaInteraction: 0x38 bytes, 34 virtual functions
class UMagmaInteraction : public UInteraction {
public:
    virtual ~UMagmaInteraction();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();

    BYTE unk_34[0x4];
};

// Engine.FlicFlocEmitter: 0x424 bytes, 33 virtual functions
class UFlicFlocEmitter : public USpriteEmitter {
public:
    virtual ~UFlicFlocEmitter();

    BYTE unk_408[0x1c];
};

// Engine.PersistentData: 0x7c bytes, 22 virtual functions
class UPersistentData : public UObject {
public:
    virtual ~UPersistentData();

    TArray<FString> unk_28;
    FString         unk_34;
    BYTE            unk_40[0xc];
    TArray<FString> unk_4c;
    BYTE            unk_58[0x24];
};

inline ALevelInfo *ULevel::GetLevelInfo() const
{
    return static_cast<ALevelInfo *>(Actors(0));
}

#endif // VERSUS_ENGINE_CLASSES_H
