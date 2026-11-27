// Native classes and network encryption key sources registered by the Engine package.
#include "versus_build.h"
#include "versus_native_class_init.h"

// The Core registrar initializes all 256 entries before Engine selects the first key.
BYTE GByteTable_10c814d8[256];
extern const BYTE GEngineKeyBytes[];
extern const ANSICHAR *GEngineCopyright;
extern TArray<const BYTE *> GEncryptionKeySources;

static const EName NAME_Engine = (EName)21;
static const EName NAME_PC_input = (EName)239;
static const DWORD NativeClassObjectFlags = 0x04084004;
extern "C" void place_UObject(void *Storage);

class UCommandlet : public UObject { public: static UClass PrivateStaticClass; };
class UPackageMap : public UObject { public: static UClass PrivateStaticClass; };
class USubsystem : public UObject { public: static UClass PrivateStaticClass; };

#define NATIVE_CLASS_MEMBERS(index) \
    enum { NativeNameIndex = index }; \
    static UClass PrivateStaticClass; \
    static void InternalConstructor(void *Storage)

#define DECLARE_ABSTRACT_ENGINE_CLASS(type, base, index) \
    class type : public base { public: enum { NativeNameIndex = index }; static UClass PrivateStaticClass; }

#define DECLARE_ENGINE_CLASS(type, base, index) \
    class type : public base { public: NATIVE_CLASS_MEMBERS(index); }

DECLARE_ENGINE_CLASS(AActor, UObject, 0x260);
DECLARE_ENGINE_CLASS(UAnimNotify, UObject, 0x7dd);
DECLARE_ENGINE_CLASS(UAnimation, UObject, 0x26886);
DECLARE_ENGINE_CLASS(UCanvas, UObject, 0xcd);
DECLARE_ABSTRACT_ENGINE_CLASS(UChannel, UObject, 0x268a9);
DECLARE_ENGINE_CLASS(UCheatManager, UObject, 0x471);
class UClient : public UObject {
public:
    NATIVE_CLASS_MEMBERS(0x263);
    void StaticConstructor();
};
DECLARE_ENGINE_CLASS(UFont, UObject, 0x2689c);
DECLARE_ENGINE_CLASS(UGlobalTempObjects, UObject, 0x2a9eb);
DECLARE_ENGINE_CLASS(UI3DL2Listener, UObject, 0x478);
DECLARE_ENGINE_CLASS(UInteractions, UObject, 0x7d5);
DECLARE_ENGINE_CLASS(ULANErrorHandler, UObject, 0x7eb);
DECLARE_ABSTRACT_ENGINE_CLASS(ULevelBase, UObject, 0x2a9ea);
DECLARE_ENGINE_CLASS(ULevelSummary, UObject, 0x483);
DECLARE_ENGINE_CLASS(UMatchInfo, UObject, 0x48985);
DECLARE_ABSTRACT_ENGINE_CLASS(UMaterial, UObject, 0x26879);
DECLARE_ENGINE_CLASS(UMeshAnimation, UObject, 0x26887);
DECLARE_ENGINE_CLASS(UMeshObject, UObject, 0x433);
DECLARE_ENGINE_CLASS(UPalette, UObject, 0x2687a);
DECLARE_ENGINE_CLASS(UParticleEmitter, UObject, 0x7da);
DECLARE_ABSTRACT_ENGINE_CLASS(UPendingLevel, UObject, 0x26892);
DECLARE_ENGINE_CLASS(UPersistentData, UObject, 0xcb45e);
DECLARE_ABSTRACT_ENGINE_CLASS(UPlayer, UObject, 0x2682d);
DECLARE_ENGINE_CLASS(UPlayerInput, UObject, 0xa3);
DECLARE_ENGINE_CLASS(UPolys, UObject, 0x2689b);
DECLARE_ENGINE_CLASS(UPrimitive, UObject, 0x26857);
DECLARE_ABSTRACT_ENGINE_CLASS(URenderResource, UObject, 0x2a9df);
DECLARE_ENGINE_CLASS(USound, UObject, 0x22d);
DECLARE_ENGINE_CLASS(UStaticMeshInstance, UObject, 0x2687b);
DECLARE_ENGINE_CLASS(AAntiPortalActor, AActor, 0x47b);
DECLARE_ENGINE_CLASS(ABrush, AActor, 0x480);
DECLARE_ENGINE_CLASS(ACarriedObject, AActor, 0x47a);
DECLARE_ENGINE_CLASS(AController, AActor, 0x8b6);
DECLARE_ENGINE_CLASS(ADecoVolumeObject, AActor, 0x7e9);
DECLARE_ENGINE_CLASS(ADecoration, AActor, 0x489);
DECLARE_ENGINE_CLASS(AERainVolume, AActor, 0xb3841);
DECLARE_ENGINE_CLASS(AESoftBodyActor, AActor, 0x8b0);
DECLARE_ENGINE_CLASS(AEffects, AActor, 0x115bf);
DECLARE_ENGINE_CLASS(AEmitter, AActor, 0x443);
DECLARE_ENGINE_CLASS(AHUD, AActor, 0x8b7);
DECLARE_ENGINE_CLASS(AInfo, AActor, 0x8b5);
DECLARE_ENGINE_CLASS(AInventory, AActor, 0x8b1);
DECLARE_ENGINE_CLASS(AKeypoint, AActor, 0x7d0);
DECLARE_ENGINE_CLASS(ALight, AActor, 0x48f);
DECLARE_ENGINE_CLASS(AMotionTrackingVision, AActor, 0x486);
DECLARE_ENGINE_CLASS(AMover, AActor, 0x446);
DECLARE_ENGINE_CLASS(ANote, AActor, 0x48e);
DECLARE_ENGINE_CLASS(APawn, AActor, 0x262);
DECLARE_ENGINE_CLASS(APlayerStart, AActor, 0x487);
DECLARE_ENGINE_CLASS(AProjectile, AActor, 0x488);
DECLARE_ENGINE_CLASS(AProjector, AActor, 0x7db);
DECLARE_ENGINE_CLASS(ASImpactEffectBase, AActor, 0x2afca);
DECLARE_ENGINE_CLASS(ASImpactManager, AActor, 0xcec75);
DECLARE_ENGINE_CLASS(ASLogManager, AActor, 0x7ea);
DECLARE_ENGINE_CLASS(AStaticMeshActor, AActor, 0x7ec);
DECLARE_ENGINE_CLASS(ATriggers, AActor, 0x482);
class UActorChannel : public UChannel {
public:
    NATIVE_CLASS_MEMBERS(0x2a9ed);
    void StaticConstructor();
};
DECLARE_ENGINE_CLASS(UAnimNotify_DestroyEffect, UAnimNotify, 0x7e0);
DECLARE_ENGINE_CLASS(UAnimNotify_Effect, UAnimNotify, 0x7df);
DECLARE_ENGINE_CLASS(UAnimNotify_Script, UAnimNotify, 0x7e3);
DECLARE_ENGINE_CLASS(UAnimNotify_Scripted, UAnimNotify, 0x7de);
DECLARE_ENGINE_CLASS(UAnimNotify_Sound, UAnimNotify, 0x7e1);
DECLARE_ENGINE_CLASS(UAnimNotify_StopSound, UAnimNotify, 0x7e2);
DECLARE_ABSTRACT_ENGINE_CLASS(UAudioSubsystem, USubsystem, 0x26853);
DECLARE_ENGINE_CLASS(UBeamEmitter, UParticleEmitter, 0x477);
DECLARE_ENGINE_CLASS(UCombiner, UMaterial, 0x45f);
class UControlChannel : public UChannel {
public:
    NATIVE_CLASS_MEMBERS(0x2a9ef);
    void StaticConstructor();
};
DECLARE_ENGINE_CLASS(UConvexVolume, UPrimitive, 0x268a7);
DECLARE_ENGINE_CLASS(UEMFChannelTextures, UMaterial, 0x44b);
DECLARE_ENGINE_CLASS(UERainPrimitive, UPrimitive, 0x447);
DECLARE_ENGINE_CLASS(UESoftBody, UPrimitive, 0x26856);
DECLARE_ENGINE_CLASS(UEchelonLightingMaterial, UMaterial, 0x462);
DECLARE_ABSTRACT_ENGINE_CLASS(UEngine, USubsystem, 0x15);
DECLARE_ENGINE_CLASS(UIndexBuffer, URenderResource, 0x2688a);
class UInput : public USubsystem {
public:
    NATIVE_CLASS_MEMBERS(0x289);
    static FName StaticConfigName() { return NAME_PC_input; }
};
DECLARE_ENGINE_CLASS(UInteraction, UInteractions, 0x7d3);
DECLARE_ENGINE_CLASS(UInteractionMaster, UInteractions, 0x469);
DECLARE_ENGINE_CLASS(ULevel, ULevelBase, 0x26899);
DECLARE_ABSTRACT_ENGINE_CLASS(UMatchmakingSubsystem, USubsystem, 0x2682a);
DECLARE_ABSTRACT_ENGINE_CLASS(UMenuManagerSubsystem, USubsystem, 0x2a9f1);
DECLARE_ENGINE_CLASS(UMesh, UPrimitive, 0x7d6);
DECLARE_ENGINE_CLASS(UMeshEmitter, UParticleEmitter, 0x448);
DECLARE_ENGINE_CLASS(UMeshInstance, UPrimitive, 0x26873);
DECLARE_ENGINE_CLASS(UModel, UPrimitive, 0x26895);
DECLARE_ENGINE_CLASS(UModifier, UMaterial, 0x44a);
DECLARE_ABSTRACT_ENGINE_CLASS(UNetConnection, UPlayer, 0x26870);
class UNetDriver : public USubsystem {
public:
    NATIVE_CLASS_MEMBERS(0x2685d);
    void StaticConstructor();
};
DECLARE_ENGINE_CLASS(UNetPendingLevel, UPendingLevel, 0x2a9e5);
DECLARE_ENGINE_CLASS(UPackageMapLevel, UPackageMap, 0x2a9e6);
DECLARE_ENGINE_CLASS(UProjectorPrimitive, UPrimitive, 0x2a9e4);
class URenderDevice : public USubsystem {
public:
    NATIVE_CLASS_MEMBERS(0x2689f);
    void StaticConstructor();
};
DECLARE_ABSTRACT_ENGINE_CLASS(URenderedMaterial, UMaterial, 0x26878);
DECLARE_ABSTRACT_ENGINE_CLASS(USaveGameDevice, USubsystem, 0x26898);
class UServerCommandlet : public UCommandlet {
public:
    NATIVE_CLASS_MEMBERS(0x2a9ec);
    void StaticConstructor();
};
DECLARE_ENGINE_CLASS(USkinVertexBuffer, URenderResource, 0x2a9de);
DECLARE_ENGINE_CLASS(USparkEmitter, UParticleEmitter, 0x7e4);
DECLARE_ENGINE_CLASS(USpriteEmitter, UParticleEmitter, 0x7e5);
class UStaticMesh : public UPrimitive {
public:
    NATIVE_CLASS_MEMBERS(0x92);
    void StaticConstructor();
};
DECLARE_ENGINE_CLASS(UTrailEmitter, UParticleEmitter, 0x7e7);
DECLARE_ABSTRACT_ENGINE_CLASS(UVertexStreamBase, URenderResource, 0x2a9e0);
DECLARE_ABSTRACT_ENGINE_CLASS(UViewport, UPlayer, 0x2682c);
DECLARE_ENGINE_CLASS(ADecorationList, AKeypoint, 0x7e8);
DECLARE_ENGINE_CLASS(AFileLog, AInfo, 0x492);
DECLARE_ENGINE_CLASS(AGameInfo, AInfo, 0x48c);
DECLARE_ENGINE_CLASS(AGameStats, AInfo, 0x491);
DECLARE_ENGINE_CLASS(AInternetInfo, AInfo, 0x8b3);
DECLARE_ENGINE_CLASS(ALineOfSightTrigger, ATriggers, 0x481);
DECLARE_ENGINE_CLASS(ALocalMessage, AInfo, 0x2afbe);
DECLARE_ENGINE_CLASS(AMoverRotating, AMover, 0x7d849);
DECLARE_ENGINE_CLASS(APlayerController, AController, 0x261);
DECLARE_ENGINE_CLASS(AReplicationInfo, AInfo, 0x47d);
DECLARE_ENGINE_CLASS(ASBulletImpact, AProjector, 0x2afc8);
DECLARE_ENGINE_CLASS(ASecurity, AInfo, 0x431);
DECLARE_ENGINE_CLASS(AShadowProjector, AProjector, 0x7dc);
DECLARE_ENGINE_CLASS(ATrigger, ATriggers, 0x132);
DECLARE_ENGINE_CLASS(AVolume, ABrush, 0x47f);
DECLARE_ENGINE_CLASS(AZoneInfo, AInfo, 0x48b);
DECLARE_ENGINE_CLASS(UBaseGUIController, UInteraction, 0x7d4);
DECLARE_ABSTRACT_ENGINE_CLASS(UBitmapMaterial, URenderedMaterial, 0x26877);
DECLARE_ENGINE_CLASS(UColorModifier, UModifier, 0x463);
DECLARE_ENGINE_CLASS(UConsole, UInteraction, 0x252);
DECLARE_ENGINE_CLASS(UConstantMaterial, URenderedMaterial, 0x45d);
DECLARE_ENGINE_CLASS(UEMFTextureModifier, UModifier, 0x44c);
DECLARE_ENGINE_CLASS(UFinalBlend, UModifier, 0x450);
DECLARE_ENGINE_CLASS(UFlicFlocEmitter, USpriteEmitter, 0xba542);
DECLARE_ENGINE_CLASS(UGameEngine, UEngine, 0xc4);
DECLARE_ENGINE_CLASS(UHeatTextureModifier, UModifier, 0x44d);
DECLARE_ENGINE_CLASS(ULitSpecularMaterial, URenderedMaterial, 0x460);
DECLARE_ENGINE_CLASS(ULodMesh, UMesh, 0x2a9d8);
DECLARE_ENGINE_CLASS(ULodMeshInstance, UMeshInstance, 0x2a9d6);
DECLARE_ENGINE_CLASS(UMagmaInteraction, UInteraction, 0xcc052);
DECLARE_ENGINE_CLASS(UMaterialSequence, UModifier, 0x44e);
DECLARE_ENGINE_CLASS(UMaterialSwitch, UModifier, 0x44f);
DECLARE_ENGINE_CLASS(UNullRenderDevice, URenderDevice, 0x2a9f0);
DECLARE_ENGINE_CLASS(UOpacityModifier, UModifier, 0x449);
DECLARE_ENGINE_CLASS(UParticleMaterial, URenderedMaterial, 0x442);
DECLARE_ENGINE_CLASS(UProjectorMaterial, URenderedMaterial, 0x43c);
DECLARE_ENGINE_CLASS(UShader, URenderedMaterial, 0x461);
DECLARE_ENGINE_CLASS(USpecialVisionTextureModifier, UModifier, 0xb384d);
DECLARE_ENGINE_CLASS(UTexCoordMaterial, URenderedMaterial, 0x2a9e8);
DECLARE_ENGINE_CLASS(UTexModifier, UModifier, 0x453);
DECLARE_ENGINE_CLASS(UVertexBuffer, UVertexStreamBase, 0x2688b);
DECLARE_ENGINE_CLASS(UVertexColor, URenderedMaterial, 0x451);
DECLARE_ENGINE_CLASS(UVertexStreamPosNormTex, UVertexStreamBase, 0x2a9e1);
DECLARE_ENGINE_CLASS(UVertexStreamUV, UVertexStreamBase, 0x2a9e2);
DECLARE_ENGINE_CLASS(UVertexStreamVECTOR, UVertexStreamBase, 0x2a9e3);
DECLARE_ENGINE_CLASS(ABlockingVolume, AVolume, 0x47e);
DECLARE_ENGINE_CLASS(ACamera, APlayerController, 0xa2);
DECLARE_ENGINE_CLASS(AGameReplicationInfo, AReplicationInfo, 0x484);
DECLARE_ENGINE_CLASS(ALevelInfo, AZoneInfo, 0x48d);
DECLARE_ENGINE_CLASS(APlayerReplicationInfo, AReplicationInfo, 0x485);
DECLARE_ENGINE_CLASS(ASkyZoneInfo, AZoneInfo, 0x48a);
DECLARE_ENGINE_CLASS(ATeamInfo, AReplicationInfo, 0x47c);
DECLARE_ENGINE_CLASS(UConstantColor, UConstantMaterial, 0x45e);
DECLARE_ENGINE_CLASS(UFadeColor, UConstantMaterial, 0x45c);
DECLARE_ENGINE_CLASS(UProxyBitmapMaterial, UBitmapMaterial, 0x2a9e9);
DECLARE_ENGINE_CLASS(UScriptedTexture, UBitmapMaterial, 0x432);
DECLARE_ENGINE_CLASS(UShadowBitmapMaterial, UBitmapMaterial, 0x430);
DECLARE_ENGINE_CLASS(USkeletalMesh, ULodMesh, 0x26885);
DECLARE_ENGINE_CLASS(USkeletalMeshInstance, ULodMeshInstance, 0x2a9dd);
DECLARE_ENGINE_CLASS(UTexCoordSource, UTexModifier, 0x452);
DECLARE_ENGINE_CLASS(UTexEnvMap, UTexModifier, 0x455);
DECLARE_ENGINE_CLASS(UTexFriendlyPanner, UTexModifier, 0xb384e);
DECLARE_ENGINE_CLASS(UTexMatrix, UTexModifier, 0x454);
DECLARE_ENGINE_CLASS(UTexOscillator, UTexModifier, 0x456);
DECLARE_ENGINE_CLASS(UTexPanner, UTexModifier, 0x45a);
DECLARE_ENGINE_CLASS(UTexRotator, UTexModifier, 0x458);
DECLARE_ENGINE_CLASS(UTexScaler, UTexModifier, 0x459);
DECLARE_ENGINE_CLASS(UTexture, UBitmapMaterial, 0x22c);
DECLARE_ENGINE_CLASS(UVertMesh, ULodMesh, 0x2a9d7);
DECLARE_ENGINE_CLASS(UVertMeshInstance, ULodMeshInstance, 0x2a9d5);
DECLARE_ENGINE_CLASS(UCubemap, UTexture, 0x26876);
DECLARE_ENGINE_CLASS(UTexOscillatorTriggered, UTexOscillator, 0x457);
DECLARE_ENGINE_CLASS(UTexPannerTriggered, UTexPanner, 0x45b);

#undef DECLARE_ABSTRACT_ENGINE_CLASS
#undef DECLARE_ENGINE_CLASS
#undef NATIVE_CLASS_MEMBERS

#define REGISTER_WITH_CONSTRUCTOR(type, size, flags, base, within, package, staticOwner, constructor) \
    type::PrivateStaticClass.InitNative(EC_NativeConstructor, size, flags, \
        &base::PrivateStaticClass, &within::PrivateStaticClass, FGuid(0, 0, 0, 0), \
        (EName)type::NativeNameIndex, package, type::StaticConfigName(), NativeClassObjectFlags, \
        constructor, (StaticConstructorType)&staticOwner::StaticConstructor)

#define REGISTER_ENGINE_CLASS(type, size, flags, base, within, package, staticOwner) \
    REGISTER_WITH_CONSTRUCTOR(type, size, flags, base, within, package, staticOwner, type::InternalConstructor)

// Abstract Engine classes share the placement callback that constructs the base UObject.
#define REGISTER_ABSTRACT_ENGINE_CLASS(type, size, flags, base, within, package, staticOwner) \
    REGISTER_WITH_CONSTRUCTOR(type, size, flags, base, within, package, staticOwner, place_UObject)

void RegisterEngineClasses()
{
    const EName Package = NAME_Engine;

    REGISTER_ENGINE_CLASS(ASImpactManager, 0x554, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AFileLog, 0x308, 0x0, AInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AGameStats, 0x300, 0x0, AInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UNullRenderDevice, 0xfc, 0x4, URenderDevice, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AActor, 0x2f8, 0x800, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ALight, 0x30c, 0x800, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ANote, 0x304, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ALevelInfo, 0x55c, 0x804, AZoneInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AGameInfo, 0x4a4, 0x4, AInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ACamera, 0x604, 0x0, APlayerController, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AZoneInfo, 0x340, 0x800, AInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ASkyZoneInfo, 0x340, 0x0, AZoneInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ADecoration, 0x32c, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AProjectile, 0x324, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AEffects, 0x2f8, 0x800, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ASImpactEffectBase, 0x304, 0x800, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ASBulletImpact, 0x480, 0x800, AProjector, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(APlayerStart, 0x338, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AKeypoint, 0x2f8, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ATriggers, 0x2f8, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ATrigger, 0x32c, 0x0, ATriggers, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AHUD, 0x49c, 0x8, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AInfo, 0x2f8, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ALocalMessage, 0x314, 0x0, AInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AMotionTrackingVision, 0x328, 0xc, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AReplicationInfo, 0x2f8, 0x0, AInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(APlayerReplicationInfo, 0x450, 0x800, AReplicationInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AInternetInfo, 0x2f8, 0x8, AInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AGameReplicationInfo, 0x3c0, 0x804, AReplicationInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ULevelSummary, 0x50, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AController, 0x3c4, 0x800, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(APlayerController, 0x604, 0x800, AController, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ABrush, 0x354, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ALineOfSightTrigger, 0x314, 0x0, ATriggers, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AVolume, 0x370, 0x0, ABrush, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ABlockingVolume, 0x370, 0x0, AVolume, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ATeamInfo, 0x324, 0x800, AReplicationInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AAntiPortalActor, 0x2f8, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ACarriedObject, 0x30c, 0x800, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(USound, 0x84, 0x40, UObject, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UAudioSubsystem, 0x2c, 0x5, USubsystem, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UI3DL2Listener, 0x9c, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UBeamEmitter, 0x4f4, 0x0, UParticleEmitter, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UViewport, 0x190, 0x9, UPlayer, UClient, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UClient, 0xa8, 0x5, UObject, UObject, Package, UClient);
    REGISTER_ENGINE_CLASS(UCanvas, 0x80, 0x8, UObject, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UChannel, 0x58, 0x9, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UControlChannel, 0x5c, 0x8, UChannel, UObject, Package, UControlChannel);
    REGISTER_ENGINE_CLASS(UActorChannel, 0xa4, 0x8, UChannel, UObject, Package, UActorChannel);
    REGISTER_ABSTRACT_ENGINE_CLASS(UNetConnection, 0x49e0, 0xd, UPlayer, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UCheatManager, 0x28, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UPlayerInput, 0x7c, 0xc, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UConvexVolume, 0x80, 0x0, UPrimitive, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UEngine, 0x130, 0xd, USubsystem, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(URenderDevice, 0xb0, 0x5, USubsystem, UObject, Package, URenderDevice);
    REGISTER_ENGINE_CLASS(UServerCommandlet, 0x1dc, 0x8, UCommandlet, UObject, Package, UServerCommandlet);
    REGISTER_ENGINE_CLASS(UGlobalTempObjects, 0x34, 0x8, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UFont, 0x5c, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UPolys, 0x38, 0x80, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UGameEngine, 0x188, 0xc, UEngine, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UInput, 0x1b5c, 0xc, USubsystem, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UInteraction, 0x34, 0x0, UInteractions, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UConsole, 0x1ec, 0x0, UInteraction, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UBaseGUIController, 0xc50, 0x0, UInteraction, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UInteractions, 0x28, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UInteractionMaster, 0x44, 0x8, UInteractions, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(ULevelBase, 0x13c, 0x1, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ULevel, 0x4af0, 0x0, ULevelBase, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ULodMeshInstance, 0x78, 0x8, UMeshInstance, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ULodMesh, 0xf4, 0x40, UMesh, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UMatchmakingSubsystem, 0x30, 0x5, USubsystem, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(USaveGameDevice, 0x138, 0x1, USubsystem, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UMaterial, 0x4c, 0x1, UObject, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UBitmapMaterial, 0x64, 0x1, URenderedMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UProxyBitmapMaterial, 0x68, 0x0, UBitmapMaterial, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(URenderedMaterial, 0x4c, 0x1, UMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexCoordMaterial, 0x54, 0x0, URenderedMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UColorModifier, 0x58, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UEchelonLightingMaterial, 0x58, 0x0, UMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UShader, 0x74, 0x0, URenderedMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ULitSpecularMaterial, 0x64, 0x0, URenderedMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UCombiner, 0x60, 0x0, UMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UConstantMaterial, 0x4c, 0x0, URenderedMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UConstantColor, 0x50, 0x0, UConstantMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UFadeColor, 0x60, 0x0, UConstantMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UModifier, 0x50, 0x0, UMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexModifier, 0x58, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexPannerTriggered, 0xb8, 0x0, UTexPanner, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexPanner, 0xa8, 0x0, UTexModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexFriendlyPanner, 0xac, 0x0, UTexModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexScaler, 0xa8, 0x0, UTexModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexRotator, 0xd8, 0x0, UTexModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexOscillatorTriggered, 0xdc, 0x0, UTexOscillator, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexOscillator, 0xcc, 0x0, UTexModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexEnvMap, 0x5c, 0x0, UTexModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexMatrix, 0x98, 0x0, UTexModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexCoordSource, 0x5c, 0x0, UTexModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UVertexColor, 0x4c, 0x0, URenderedMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UFinalBlend, 0x5c, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMaterialSwitch, 0x60, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMaterialSequence, 0x70, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UHeatTextureModifier, 0x5c, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UEMFTextureModifier, 0x58, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(USpecialVisionTextureModifier, 0x60, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UEMFChannelTextures, 0x58, 0x0, UMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UOpacityModifier, 0x58, 0x0, UModifier, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMeshInstance, 0x50, 0x0, UPrimitive, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMesh, 0x54, 0x0, UPrimitive, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMeshEmitter, 0x3fc, 0x0, UParticleEmitter, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UModel, 0x120, 0x0, UPrimitive, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AMover, 0x4e8, 0x800, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AMoverRotating, 0x500, 0x800, AMover, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UPackageMapLevel, 0x74, 0x8, UPackageMap, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UNetDriver, 0x51c, 0xd, USubsystem, UObject, Package, UNetDriver);
    REGISTER_ENGINE_CLASS(UParticleEmitter, 0x3e8, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AEmitter, 0x364, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UParticleMaterial, 0x2dc, 0x0, URenderedMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(APawn, 0x4b0, 0x804, AActor, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UPendingLevel, 0x154, 0x1, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UNetPendingLevel, 0x154, 0x8, UPendingLevel, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UPlayer, 0x68, 0xd, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UPrimitive, 0x50, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UProjectorPrimitive, 0x50, 0x0, UPrimitive, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AProjector, 0x47c, 0x800, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AShadowProjector, 0x498, 0x0, AProjector, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UProjectorMaterial, 0xe0, 0x0, URenderedMaterial, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(URenderResource, 0x2c, 0x1, UObject, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UVertexStreamBase, 0x38, 0x1, URenderResource, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UVertexStreamVECTOR, 0x44, 0x0, UVertexStreamBase, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMatchInfo, 0x90, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UVertexStreamUV, 0x44, 0x0, UVertexStreamBase, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UVertexStreamPosNormTex, 0x44, 0x0, UVertexStreamBase, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UVertexBuffer, 0x44, 0x0, UVertexStreamBase, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UIndexBuffer, 0x38, 0x0, URenderResource, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(USkinVertexBuffer, 0x38, 0x0, URenderResource, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMeshObject, 0x28, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UScriptedTexture, 0x78, 0x0, UBitmapMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ASecurity, 0x314, 0x0, AInfo, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UShadowBitmapMaterial, 0x94, 0x0, UBitmapMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMeshAnimation, 0x54, 0x40, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UAnimation, 0x28, 0x40, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(USkeletalMesh, 0x2f0, 0x40, ULodMesh, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(USkeletalMeshInstance, 0x36c, 0x8, ULodMeshInstance, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UAnimNotify, 0x2c, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UAnimNotify_Effect, 0x68, 0x0, UAnimNotify, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UAnimNotify_DestroyEffect, 0x34, 0x0, UAnimNotify, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UAnimNotify_Sound, 0x3c, 0x0, UAnimNotify, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UAnimNotify_StopSound, 0x30, 0x0, UAnimNotify, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UAnimNotify_Script, 0x30, 0x0, UAnimNotify, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UAnimNotify_Scripted, 0x2c, 0x0, UAnimNotify, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(USparkEmitter, 0x424, 0x0, UParticleEmitter, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(USpriteEmitter, 0x408, 0x0, UParticleEmitter, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UStaticMesh, 0x1a0, 0x2040, UPrimitive, UObject, Package, UStaticMesh);
    REGISTER_ENGINE_CLASS(UStaticMeshInstance, 0x50, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AStaticMeshActor, 0x2fc, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTexture, 0xc0, 0x40, UBitmapMaterial, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UPalette, 0x3c, 0x40, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UCubemap, 0xdc, 0x40, UTexture, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UTrailEmitter, 0x424, 0x0, UParticleEmitter, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UVertMesh, 0x220, 0x0, ULodMesh, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UVertMeshInstance, 0x138, 0x0, ULodMeshInstance, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ADecorationList, 0x304, 0x0, AKeypoint, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ADecoVolumeObject, 0x2f8, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AESoftBodyActor, 0x394, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UESoftBody, 0x15c, 0x0, UPrimitive, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ASLogManager, 0x354, 0x4, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AInventory, 0x338, 0x804, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(ULANErrorHandler, 0x38, 0x0, UObject, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(AERainVolume, 0x340, 0x0, AActor, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UERainPrimitive, 0x90, 0x40, UPrimitive, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UMagmaInteraction, 0x38, 0x8, UInteraction, UObject, Package, UObject);
    REGISTER_ABSTRACT_ENGINE_CLASS(UMenuManagerSubsystem, 0x2c, 0x5, USubsystem, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UFlicFlocEmitter, 0x424, 0x0, USpriteEmitter, UObject, Package, UObject);
    REGISTER_ENGINE_CLASS(UPersistentData, 0x7c, 0x8, UObject, UObject, Package, UObject);

    GEncryptionKeySources.Empty(16);
    GEncryptionKeySources.AddUniqueItem(GByteTable_10c814d8 + 39);
    GEncryptionKeySources.AddUniqueItem(GEngineKeyBytes);
    GEncryptionKeySources.AddUniqueItem(reinterpret_cast<const BYTE *>(GEngineCopyright));
}

#undef REGISTER_ABSTRACT_ENGINE_CLASS
#undef REGISTER_WITH_CONSTRUCTOR
#undef REGISTER_ENGINE_CLASS
