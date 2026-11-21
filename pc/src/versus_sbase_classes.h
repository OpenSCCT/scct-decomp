// versus_sbase_classes.h -- classes of the SBase package as the Versus executable builds them
#ifndef VERSUS_SBASE_CLASSES_H
#define VERSUS_SBASE_CLASSES_H

#include "versus_build.h"
#include "unreal_actor.h"
#include "unreal_containers.h"
#include "unreal_object.h"
#include "versus_engine_classes.h"
#include "versus_ipdrv_classes.h"
#include "versus_ltcg.h"

// SBase.SBasicGamePlayObject: 0x344 bytes, 78 virtual functions
class ASBasicGamePlayObject : public AActor {
public:
    virtual ~ASBasicGamePlayObject();

    BYTE    unk_2f8[0x10];
    FString unk_308;
    BYTE    unk_314[0x30];
};

// SBase.SGamePlayObject: 0x3c4 bytes, 78 virtual functions
class ASGamePlayObject : public ASBasicGamePlayObject {
public:
    virtual ~ASGamePlayObject();

    BYTE                   unk_344[0x14];
    TArrayLtcg<UnkType_18> unk_358;
    TArrayLtcg<UnkType_18> unk_364;
    TArrayLtcg<UnkType_4>  unk_370;
    BYTE                   unk_37c[0x4];
    TArray<BYTE>           unk_380;
    TArrayLtcg<UnkType_4>  unk_38c;
    BYTE                   unk_398[0x2c];
};

// SBase.SVitre: 0x3c4 bytes, 78 virtual functions
class ASVitre : public ASGamePlayObject {
public:
    virtual ~ASVitre();
};

// SBase.SInteractObject: 0x364 bytes, 80 virtual functions
class ASInteractObject : public AActor {
public:
    virtual ~ASInteractObject();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();

    BYTE    unk_2f8[0xc];
    FString unk_304;
    BYTE    unk_310[0x54];
};

// SBase.SMineProxInteraction: 0x364 bytes, 80 virtual functions
class ASMineProxInteraction : public ASInteractObject {
public:
    virtual ~ASMineProxInteraction();
};

// SBase.SStickyCamInteraction: 0x364 bytes, 80 virtual functions
class ASStickyCamInteraction : public ASMineProxInteraction {
public:
    virtual ~ASStickyCamInteraction();
};

// SBase.SCoronaLight: 0x30c bytes, 78 virtual functions
class ASCoronaLight : public ALight {
public:
    virtual ~ASCoronaLight();
};

// SBase.SGadget: 0x350 bytes, 78 virtual functions
class ASGadget : public AInventory {
public:
    virtual ~ASGadget();

    BYTE unk_338[0x18];

    DECLARE_NATIVE(execGetUniqueIDByClass)
    INT GetUniqueIDByClass();
};

// SBase.SGadHeartBeatSensor: 0x370 bytes, 78 virtual functions
class ASGadHeartBeatSensor : public ASGadget {
public:
    virtual ~ASGadHeartBeatSensor();

    BYTE unk_350[0x20];
};

// SBase.SPoisonEmitter: 0x364 bytes, 81 virtual functions
class ASPoisonEmitter : public AEmitter {
public:
    virtual ~ASPoisonEmitter();
};

// SBase.SGadMultiMinesLauncher: 0x428 bytes, 78 virtual functions
class ASGadMultiMinesLauncher : public ASGadget {
public:
    virtual ~ASGadMultiMinesLauncher();

    BYTE unk_350[0xd8];
};

// SBase.SGadMultiPresDetectorLauncher: 0x428 bytes, 78 virtual functions
class ASGadMultiPresDetectorLauncher : public ASGadMultiMinesLauncher {
public:
    virtual ~ASGadMultiPresDetectorLauncher();
};

// SBase.SWeaponDefenseDummy: 0x318 bytes, 78 virtual functions
class ASWeaponDefenseDummy : public AActor {
public:
    virtual ~ASWeaponDefenseDummy();

    BYTE unk_2f8[0x20];
};

// SBase.SWeaponDefenseDummy_Uzi: 0x318 bytes, 78 virtual functions
class ASWeaponDefenseDummy_Uzi : public ASWeaponDefenseDummy {
public:
    virtual ~ASWeaponDefenseDummy_Uzi();
};

// SBase.SWeaponDefenseDummy_Shotgun: 0x324 bytes, 78 virtual functions
class ASWeaponDefenseDummy_Shotgun : public ASWeaponDefenseDummy {
public:
    virtual ~ASWeaponDefenseDummy_Shotgun();

    BYTE unk_318[0xc];
};

// SBase.SWeapon: 0x37c bytes, 78 virtual functions
class ASWeapon : public AInventory {
public:
    virtual ~ASWeapon();

    BYTE unk_338[0x44];
};

// SBase.SWeaponDefense: 0x438 bytes, 78 virtual functions
class ASWeaponDefense : public ASWeapon {
public:
    virtual ~ASWeaponDefense();

    BYTE    unk_37c[0x40];
    FString unk_3bc;
    FString unk_3c8;
    FString unk_3d4;
    BYTE    unk_3e0[0x58];

    DECLARE_NATIVE(execGetAccuracy)
    FLOAT GetAccuracy();
};

// SBase.SWeaponDefense_Uzi: 0x43c bytes, 78 virtual functions
class ASWeaponDefense_Uzi : public ASWeaponDefense {
public:
    virtual ~ASWeaponDefense_Uzi();

    BYTE unk_438[0x4];
};

// SBase.SMateInteraction: 0x368 bytes, 80 virtual functions
class ASMateInteraction : public ASInteractObject {
public:
    virtual ~ASMateInteraction();

    BYTE unk_364[0x4];
};

// SBase.SRemoveSpyBulletInteraction: 0x368 bytes, 80 virtual functions
class ASRemoveSpyBulletInteraction : public ASMateInteraction {
public:
    virtual ~ASRemoveSpyBulletInteraction();
};

// SBase.SBackPackInteraction: 0x36c bytes, 80 virtual functions
class ASBackPackInteraction : public ASMateInteraction {
public:
    virtual ~ASBackPackInteraction();

    BYTE unk_368[0x4];
};

// SBase.SHealMateInteraction: 0x374 bytes, 80 virtual functions
class ASHealMateInteraction : public ASMateInteraction {
public:
    virtual ~ASHealMateInteraction();

    BYTE unk_368[0xc];
};

// SBase.SGadBackPack: 0x37c bytes, 78 virtual functions
class ASGadBackPack : public ASGadget {
public:
    virtual ~ASGadBackPack();

    BYTE    unk_350[0x14];
    FString unk_364;
    BYTE    unk_370[0xc];
};

// SBase.SGadGasMask: 0x374 bytes, 78 virtual functions
class ASGadGasMask : public ASGadget {
public:
    virtual ~ASGadGasMask();

    FString unk_350;
    BYTE    unk_35c[0x18];
};

// SBase.SMines: 0x36c bytes, 78 virtual functions
class ASMines : public ASBasicGamePlayObject {
public:
    virtual ~ASMines();

    BYTE unk_344[0x28];
};

// SBase.SMinePiegeSpy: 0x394 bytes, 78 virtual functions
class ASMinePiegeSpy : public ASMines {
public:
    virtual ~ASMinePiegeSpy();

    BYTE unk_36c[0x28];
};

// SBase.SMinePoison: 0x39c bytes, 78 virtual functions
class ASMinePoison : public ASMinePiegeSpy {
public:
    virtual ~ASMinePoison();

    BYTE unk_394[0x8];
};

// SBase.SImpactEffectShocker: 0x304 bytes, 78 virtual functions
class ASImpactEffectShocker : public ASImpactEffectBase {
public:
    virtual ~ASImpactEffectShocker();
};

// SBase.SImpactEffectShockerMetal: 0x304 bytes, 78 virtual functions
class ASImpactEffectShockerMetal : public ASImpactEffectBase {
public:
    virtual ~ASImpactEffectShockerMetal();
};

// SBase.SWeaponDefense_Shotgun: 0x444 bytes, 78 virtual functions
class ASWeaponDefense_Shotgun : public ASWeaponDefense {
public:
    virtual ~ASWeaponDefense_Shotgun();

    BYTE unk_438[0xc];
};

// SBase.SOrientableObject: 0x3a8 bytes, 78 virtual functions
class ASOrientableObject : public ASBasicGamePlayObject {
public:
    virtual ~ASOrientableObject();

    BYTE unk_344[0x64];
};

// SBase.SStickyCam: 0x3c0 bytes, 78 virtual functions
class ASStickyCam : public ASOrientableObject {
public:
    virtual ~ASStickyCam();

    BYTE unk_3a8[0x18];
};

// SBase.SCamNetwork: 0x438 bytes, 78 virtual functions
class ASCamNetwork : public ASStickyCam {
public:
    virtual ~ASCamNetwork();

    BYTE    unk_3c0[0x8];
    FString unk_3c8;
    BYTE    unk_3d4[0x4];
    FString unk_3d8;
    BYTE    unk_3e4[0x54];
};

// SBase.SGadCamNetwork: 0x358 bytes, 78 virtual functions
class ASGadCamNetwork : public ASGadget {
public:
    virtual ~ASGadCamNetwork();

    BYTE unk_350[0x8];
};

// SBase.SGadGrenLauncher: 0x354 bytes, 78 virtual functions
class ASGadGrenLauncher : public ASGadget {
public:
    virtual ~ASGadGrenLauncher();

    BYTE unk_350[0x4];
};

// SBase.SGadFlashBang: 0x354 bytes, 78 virtual functions
class ASGadFlashBang : public ASGadGrenLauncher {
public:
    virtual ~ASGadFlashBang();
};

// SBase.SGadChaffeGrenade: 0x354 bytes, 78 virtual functions
class ASGadChaffeGrenade : public ASGadGrenLauncher {
public:
    virtual ~ASGadChaffeGrenade();
};

// SBase.SGadFlareLauncher: 0x354 bytes, 78 virtual functions
class ASGadFlareLauncher : public ASGadGrenLauncher {
public:
    virtual ~ASGadFlareLauncher();
};

// SBase.SGadFragGrenade: 0x354 bytes, 78 virtual functions
class ASGadFragGrenade : public ASGadGrenLauncher {
public:
    virtual ~ASGadFragGrenade();
};

// SBase.SGadPhosphoLauncher: 0x354 bytes, 78 virtual functions
class ASGadPhosphoLauncher : public ASGadGrenLauncher {
public:
    virtual ~ASGadPhosphoLauncher();
};

// SBase.SGadSmokeGrenade: 0x354 bytes, 78 virtual functions
class ASGadSmokeGrenade : public ASGadGrenLauncher {
public:
    virtual ~ASGadSmokeGrenade();
};

// SBase.SShareObjectInteraction: 0x380 bytes, 80 virtual functions
class ASShareObjectInteraction : public ASInteractObject {
public:
    virtual ~ASShareObjectInteraction();

    FString unk_364;
    FString unk_370;
    BYTE    unk_37c[0x4];
};

// SBase.SExtincteur: 0x304 bytes, 78 virtual functions
class ASExtincteur : public AActor {
public:
    virtual ~ASExtincteur();

    BYTE unk_2f8[0xc];
};

// SBase.SAmmoStockInteraction: 0x364 bytes, 80 virtual functions
class ASAmmoStockInteraction : public ASInteractObject {
public:
    virtual ~ASAmmoStockInteraction();
};

// SBase.STazerEmitter: 0x308 bytes, 78 virtual functions
class ASTazerEmitter : public AEffects {
public:
    virtual ~ASTazerEmitter();

    BYTE unk_2f8[0x10];
};

// SBase.SDouilleEmitter: 0x364 bytes, 81 virtual functions
class ASDouilleEmitter : public AEmitter {
public:
    virtual ~ASDouilleEmitter();
};

// SBase.SFlashLight: 0x30c bytes, 78 virtual functions
class ASFlashLight : public ALight {
public:
    virtual ~ASFlashLight();
};

// SBase.SFlashLight_FragGrenade: 0x314 bytes, 78 virtual functions
class ASFlashLight_FragGrenade : public ASFlashLight {
public:
    virtual ~ASFlashLight_FragGrenade();

    BYTE unk_30c[0x8];
};

// SBase.SExtincteurEmitter: 0x364 bytes, 81 virtual functions
class ASExtincteurEmitter : public AEmitter {
public:
    virtual ~ASExtincteurEmitter();
};

// SBase.SFlareCourseEmitter: 0x364 bytes, 81 virtual functions
class ASFlareCourseEmitter : public AEmitter {
public:
    virtual ~ASFlareCourseEmitter();
};

// SBase.SFlareEmitter: 0x36c bytes, 81 virtual functions
class ASFlareEmitter : public AEmitter {
public:
    virtual ~ASFlareEmitter();

    BYTE unk_364[0x8];
};

// SBase.SGoggle: 0x33c bytes, 78 virtual functions
class ASGoggle : public AActor {
public:
    virtual ~ASGoggle();

    BYTE    unk_2f8[0x8];
    FString unk_300;
    FString unk_30c;
    FString unk_318;
    FString unk_324;
    BYTE    unk_330[0xc];
};

// SBase.SAlarm: 0x360 bytes, 78 virtual functions
class ASAlarm : public AActor {
public:
    virtual ~ASAlarm();

    TArray<UnkType_4>     unk_2f8;
    TArrayLtcg<UnkType_4> unk_304;
    TArrayLtcg<UnkType_8> unk_310;
    FString               unk_31c;
    FString               unk_328;
    FString               unk_334;
    BYTE                  unk_340[0x20];
};

// SBase.SAmbientSoundTrigger: 0x300 bytes, 78 virtual functions
class ASAmbientSoundTrigger : public ATriggers {
public:
    virtual ~ASAmbientSoundTrigger();

    BYTE unk_2f8[0x8];
};

// SBase.SAmmoStock: 0x344 bytes, 78 virtual functions
class ASAmmoStock : public ASBasicGamePlayObject {
public:
    virtual ~ASAmmoStock();
};

// SBase.SBasePawn: 0xb60 bytes, 84 virtual functions
class ASBasePawn : public APawn {
public:
    virtual ~ASBasePawn();

    BYTE                  unk_4b0[0x214];
    TArrayLtcg<UnkType_4> unk_6c4;
    BYTE                  unk_6d0[0x490];

    DECLARE_NATIVE(execExecuteAction)
    void ExecuteAction(INT A0);
};

// SBase.SBloodSplat: 0x488 bytes, 83 virtual functions
class ASBloodSplat : public AProjector {
public:
    virtual ~ASBloodSplat();

    BYTE unk_47c[0xc];
};

// SBase.SObjectiveTrigger: 0x3e8 bytes, 80 virtual functions
class ASObjectiveTrigger : public ASGamePlayObject {
public:
    virtual ~ASObjectiveTrigger();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();

    FString unk_3c4;
    BYTE    unk_3d0[0x18];
};

// SBase.SBombTargetObjectiveTrigger: 0x3f4 bytes, 80 virtual functions
class ASBombTargetObjectiveTrigger : public ASObjectiveTrigger {
public:
    virtual ~ASBombTargetObjectiveTrigger();

    BYTE unk_3e8[0xc];
};

// SBase.SCamera: 0x3c0 bytes, 78 virtual functions
class ASCamera : public ASBasicGamePlayObject {
public:
    virtual ~ASCamera();

    BYTE unk_344[0x7c];
};

// SBase.SChaffeEmitter: 0x364 bytes, 81 virtual functions
class ASChaffeEmitter : public AEmitter {
public:
    virtual ~ASChaffeEmitter();
};

// SBase.SComputerInteraction: 0x374 bytes, 80 virtual functions
class ASComputerInteraction : public ASInteractObject {
public:
    virtual ~ASComputerInteraction();

    BYTE    unk_364[0x4];
    FString unk_368;
};

// SBase.SComputerObjectiveTrigger: 0x41c bytes, 80 virtual functions
class ASComputerObjectiveTrigger : public ASObjectiveTrigger {
public:
    virtual ~ASComputerObjectiveTrigger();

    BYTE unk_3e8[0x34];
};

// SBase.SFireTrace: 0x314 bytes, 78 virtual functions
class ASFireTrace : public AEffects {
public:
    virtual ~ASFireTrace();

    BYTE unk_2f8[0x1c];
};

// SBase.SFlag: 0x430 bytes, 80 virtual functions
class ASFlag : public ASObjectiveTrigger {
public:
    virtual ~ASFlag();

    BYTE unk_3e8[0x48];
};

// SBase.SFlagDropZone: 0x3ec bytes, 80 virtual functions
class ASFlagDropZone : public ASObjectiveTrigger {
public:
    virtual ~ASFlagDropZone();

    BYTE unk_3e8[0x4];
};

// SBase.SFlashBang: 0x364 bytes, 81 virtual functions
class ASFlashBang : public AEmitter {
public:
    virtual ~ASFlashBang();
};

// SBase.SFragLaunchEmitter: 0x368 bytes, 81 virtual functions
class ASFragLaunchEmitter : public AEmitter {
public:
    virtual ~ASFragLaunchEmitter();

    BYTE unk_364[0x4];
};

// SBase.SGadBomb: 0x358 bytes, 78 virtual functions
class ASGadBomb : public ASGadget {
public:
    virtual ~ASGadBomb();

    BYTE unk_350[0x8];
};

// SBase.SGadNoiseEmitter: 0x360 bytes, 78 virtual functions
class ASGadNoiseEmitter : public ASGadget {
public:
    virtual ~ASGadNoiseEmitter();

    BYTE unk_350[0x10];
};

// SBase.SGadTazerLauncher: 0x368 bytes, 78 virtual functions
class ASGadTazerLauncher : public ASGadget {
public:
    virtual ~ASGadTazerLauncher();

    BYTE unk_350[0x18];
};

// SBase.SGadTorche: 0x374 bytes, 78 virtual functions
class ASGadTorche : public ASGadget {
public:
    virtual ~ASGadTorche();

    BYTE    unk_350[0xc];
    FString unk_35c;
    FString unk_368;
};

// SBase.SGadTorcheLaser: 0x3a0 bytes, 78 virtual functions
class ASGadTorcheLaser : public ASGadget {
public:
    virtual ~ASGadTorcheLaser();

    BYTE    unk_350[0x10];
    FString unk_360;
    FString unk_36c;
    BYTE    unk_378[0x28];
};

// SBase.SGoggleBeam: 0x308 bytes, 78 virtual functions
class ASGoggleBeam : public AActor {
public:
    virtual ~ASGoggleBeam();

    BYTE unk_2f8[0x10];
};

// SBase.SGPOControl: 0x310 bytes, 78 virtual functions
class ASGPOControl : public AActor {
public:
    virtual ~ASGPOControl();

    BYTE    unk_2f8[0x4];
    FString unk_2fc;
    BYTE    unk_308[0x8];
};

// SBase.SGrenadeExplosion: 0x364 bytes, 81 virtual functions
class ASGrenadeExplosion : public AEmitter {
public:
    virtual ~ASGrenadeExplosion();
};

// SBase.SInteractionManager: 0x340 bytes, 78 virtual functions
class ASInteractionManager : public AActor {
public:
    virtual ~ASInteractionManager();

    BYTE unk_2f8[0x48];
};

// SBase.SInterrupteur: 0x37c bytes, 78 virtual functions
class ASInterrupteur : public ASBasicGamePlayObject {
public:
    virtual ~ASInterrupteur();

    BYTE    unk_344[0x1c];
    FString unk_360;
    BYTE    unk_36c[0x10];
};

// SBase.SLANClientLink: 0x358 bytes, 78 virtual functions
class ASLANClientLink : public AUdpLink {
public:
    virtual ~ASLANClientLink();

    BYTE unk_32c[0x2c];
};

// SBase.SLaserBeam: 0x2fc bytes, 78 virtual functions
class ASLaserBeam : public AEffects {
public:
    virtual ~ASLaserBeam();

    BYTE unk_2f8[0x4];
};

// SBase.SLaserBeam_MineLaser: 0x308 bytes, 78 virtual functions
class ASLaserBeam_MineLaser : public ASLaserBeam {
public:
    virtual ~ASLaserBeam_MineLaser();

    BYTE unk_2fc[0xc];
};

// SBase.SLaserProjector: 0x47c bytes, 83 virtual functions
class ASLaserProjector : public AProjector {
public:
    virtual ~ASLaserProjector();
};

// SBase.SLaserTrigger: 0x388 bytes, 78 virtual functions
class ASLaserTrigger : public ASBasicGamePlayObject {
public:
    virtual ~ASLaserTrigger();

    BYTE unk_344[0x44];
};

// SBase.SLeaveInteraction: 0x364 bytes, 80 virtual functions
class ASLeaveInteraction : public ASInteractObject {
public:
    virtual ~ASLeaveInteraction();
};

// SBase.SMatchInfo: 0xc4 bytes, 22 virtual functions
class USMatchInfo : public UMatchInfo {
public:
    virtual ~USMatchInfo();

    BYTE unk_90[0x34];
};

// SBase.SMineLaser: 0x3e8 bytes, 78 virtual functions
class ASMineLaser : public ASMines {
public:
    virtual ~ASMineLaser();

    BYTE unk_36c[0x7c];
};

// SBase.SMineProx: 0x3b8 bytes, 78 virtual functions
class ASMineProx : public ASMines {
public:
    virtual ~ASMineProx();

    BYTE unk_36c[0x4c];
};

// SBase.SObjective: 0x35c bytes, 79 virtual functions
class ASObjective : public AActor {
public:
    virtual ~ASObjective();
    virtual void VirtualSlot78();

    TArrayLtcg<UnkType_4> unk_2f8;
    TArrayLtcg<UnkType_4> unk_304;
    BYTE                  unk_310[0x4];
    FString               unk_314;
    FString               unk_320;
    FString               unk_32c;
    BYTE                  unk_338[0x24];
};

// SBase.SMission: 0x388 bytes, 79 virtual functions
class ASMission : public ASObjective {
public:
    virtual ~ASMission();

    TArrayLtcg<UnkType_4> unk_35c;
    BYTE                  unk_368[0x20];
};

// SBase.SMotionTrackingVision: 0x348 bytes, 78 virtual functions
class ASMotionTrackingVision : public AMotionTrackingVision {
public:
    virtual ~ASMotionTrackingVision();

    BYTE unk_328[0x20];
};

// SBase.SMuzzleFlash: 0x2fc bytes, 78 virtual functions
class ASMuzzleFlash : public AActor {
public:
    virtual ~ASMuzzleFlash();

    BYTE unk_2f8[0x4];
};

// SBase.SMuzzleSticky: 0x300 bytes, 78 virtual functions
class ASMuzzleSticky : public ASMuzzleFlash {
public:
    virtual ~ASMuzzleSticky();

    BYTE unk_2fc[0x4];
};

// SBase.SNoiseEmitter: 0x394 bytes, 78 virtual functions
class ASNoiseEmitter : public ASBasicGamePlayObject {
public:
    virtual ~ASNoiseEmitter();

    BYTE unk_344[0x50];
};

// SBase.SPawnAttaque: 0xba4 bytes, 84 virtual functions
class ASPawnAttaque : public ASBasePawn {
public:
    virtual ~ASPawnAttaque();

    BYTE unk_b60[0x44];
};

// SBase.SPAWNDEFENSE: 0xb80 bytes, 84 virtual functions
class ASPAWNDEFENSE : public ASBasePawn {
public:
    virtual ~ASPAWNDEFENSE();

    BYTE unk_b60[0x20];
};

// SBase.SPhosphoEmitter: 0x37c bytes, 81 virtual functions
class ASPhosphoEmitter : public AEmitter {
public:
    virtual ~ASPhosphoEmitter();

    BYTE unk_364[0x18];
};

// SBase.SPickupInteraction: 0x368 bytes, 80 virtual functions
class ASPickupInteraction : public ASInteractObject {
public:
    virtual ~ASPickupInteraction();

    BYTE unk_364[0x4];
};

// SBase.SPlayerCam: 0x18f0 bytes, 78 virtual functions
class ASPlayerCam : public AActor {
public:
    virtual ~ASPlayerCam();

    BYTE unk_2f8[0x15f8];
};

// SBase.SProjGrenade: 0x354 bytes, 81 virtual functions
class ASProjGrenade : public AProjectile {
public:
    virtual ~ASProjGrenade();
    virtual void VirtualSlot80();

    BYTE unk_324[0x30];
};

// SBase.SProjChaffe: 0x36c bytes, 82 virtual functions
class ASProjChaffe : public ASProjGrenade {
public:
    virtual ~ASProjChaffe();
    virtual void VirtualSlot81();

    BYTE unk_354[0x18];
};

// SBase.SProjFlare: 0x35c bytes, 81 virtual functions
class ASProjFlare : public ASProjGrenade {
public:
    virtual ~ASProjFlare();

    BYTE unk_354[0x8];
};

// SBase.SProjFlashBang: 0x35c bytes, 81 virtual functions
class ASProjFlashBang : public ASProjGrenade {
public:
    virtual ~ASProjFlashBang();

    BYTE unk_354[0x8];
};

// SBase.SProjFrag: 0x36c bytes, 81 virtual functions
class ASProjFrag : public ASProjGrenade {
public:
    virtual ~ASProjFrag();

    BYTE unk_354[0x18];
};

// SBase.SProjMarqueurSpy: 0x358 bytes, 78 virtual functions
class ASProjMarqueurSpy : public ASBasicGamePlayObject {
public:
    virtual ~ASProjMarqueurSpy();

    BYTE                  unk_344[0x8];
    TArrayLtcg<UnkType_4> unk_34c;
};

// SBase.SProjPhospho: 0x368 bytes, 81 virtual functions
class ASProjPhospho : public ASProjGrenade {
public:
    virtual ~ASProjPhospho();

    BYTE unk_354[0x14];
};

// SBase.SProjSmoke: 0x368 bytes, 81 virtual functions
class ASProjSmoke : public ASProjGrenade {
public:
    virtual ~ASProjSmoke();

    BYTE unk_354[0x14];
};

// SBase.SRJ45Checker: 0x2fc bytes, 78 virtual functions
class ASRJ45Checker : public AActor {
public:
    virtual ~ASRJ45Checker();

    BYTE unk_2f8[0x4];
};

// SBase.SSavedMove: 0x310 bytes, 78 virtual functions
class ASSavedMove : public AInfo {
public:
    virtual ~ASSavedMove();

    BYTE unk_2f8[0x18];
};

// SBase.SSmokeEmitter: 0x380 bytes, 81 virtual functions
class ASSmokeEmitter : public AEmitter {
public:
    virtual ~ASSmokeEmitter();

    BYTE unk_364[0x1c];
};

// SBase.SSmokeLaunchEmitter: 0x364 bytes, 81 virtual functions
class ASSmokeLaunchEmitter : public AEmitter {
public:
    virtual ~ASSmokeLaunchEmitter();
};

// SBase.SSpyBulletLauncher: 0x368 bytes, 78 virtual functions
class ASSpyBulletLauncher : public ASGadget {
public:
    virtual ~ASSpyBulletLauncher();

    BYTE    unk_350[0xc];
    FString unk_35c;
};

// SBase.SStickyCamEmitter: 0x390 bytes, 81 virtual functions
class ASStickyCamEmitter : public AEmitter {
public:
    virtual ~ASStickyCamEmitter();

    BYTE unk_364[0x2c];
};

// SBase.STriggerInteraction: 0x380 bytes, 80 virtual functions
class ASTriggerInteraction : public ASInteractObject {
public:
    virtual ~ASTriggerInteraction();

    BYTE unk_364[0x1c];
};

// SBase.STriggerLight: 0x32c bytes, 78 virtual functions
class ASTriggerLight : public ALight {
public:
    virtual ~ASTriggerLight();

    TArrayLtcg<UnkType_4> unk_30c;
    BYTE                  unk_318[0x14];
};

// SBase.SVolumetricSensor: 0x37c bytes, 78 virtual functions
class ASVolumetricSensor : public ASBasicGamePlayObject {
public:
    virtual ~ASVolumetricSensor();

    TArrayLtcg<UnkType_4> unk_344;
    BYTE                  unk_350[0x2c];
};

// SBase.SWeaponAttaque: 0x3b0 bytes, 78 virtual functions
class ASWeaponAttaque : public ASWeapon {
public:
    virtual ~ASWeaponAttaque();

    BYTE unk_37c[0x34];
};

// SBase.SPlayerProfile: 0xe4 bytes, 22 virtual functions
class USPlayerProfile : public UObject {
public:
    virtual ~USPlayerProfile();

    BYTE            unk_28[0x2c];
    FString         unk_54;
    FString         unk_60;
    FString         unk_6c;
    BYTE            unk_78[0x60];
    TArray<FString> unk_d8;
};

// SBase.SXBoxLiveRef: 0xb8 bytes, 22 virtual functions
class USXBoxLiveRef : public UObject {
public:
    virtual ~USXBoxLiveRef();

    BYTE                       unk_28[0x1c];
    FString                    unk_44;
    FString                    unk_50;
    TArrayLtcg<UnkType_179000> unk_5c;
    BYTE                       unk_68[0x50];

    DECLARE_NATIVE(execGetUserName)
    DECLARE_NATIVE(execGetLobbyName)
    DECLARE_NATIVE(execMatchQueryGetMapAmateur)
    DECLARE_NATIVE(execMatchQueryGetGameMode)
    DECLARE_NATIVE(execMatchQueryIsLadderGame)
    DECLARE_NATIVE(execMatchQueryGetGameLevel)
    DECLARE_NATIVE(execMatchQueryGetGameState)
    DECLARE_NATIVE(execMatchQueryGetTimeRemaining)
    DECLARE_NATIVE(execMatchQueryIsSpyAvailable)
    DECLARE_NATIVE(execMatchQueryIsSentryAvailable)
    DECLARE_NATIVE(execMatchQueryGetNumSlotsUsed)
    DECLARE_NATIVE(execMatchQueryGetMaxPlayers)
    DECLARE_NATIVE(execMatchQueryGetNbrPlayers)
    DECLARE_NATIVE(execMatchQueryGetbGamesInARowPlaying)
    DECLARE_NATIVE(execMatchQueryGetNumSlotsFree)
    DECLARE_NATIVE(execMatchQueryGetPrivateSlotsFree)
    DECLARE_NATIVE(execMatchQueryGetPublicSlotsFree)
    DECLARE_NATIVE(execMatchQueryGetPrivateSlotsUsed)
    DECLARE_NATIVE(execMatchQueryGetPublicSlotsUsed)
    DECLARE_NATIVE(execMatchQueryIsPunkBusterEnabled)
    DECLARE_NATIVE(execMatchQueryIsLocked)
    DECLARE_NATIVE(execMatchQueryGetCompatibilityVersion)
    DECLARE_NATIVE(execActivateCdKey)
    DECLARE_NATIVE(execGetResultPlayerName)
    DECLARE_NATIVE(execMatchSetServerName)
    DECLARE_NATIVE(execMatchSetServerPassword)
    DECLARE_NATIVE(execMatchSetMapName)
    DECLARE_NATIVE(execMatchSetMapPublicName)
    DECLARE_NATIVE(execBlackListGetName)
    DECLARE_NATIVE(execBLIgnorePlayer)
    DECLARE_NATIVE(execBLUnIgnorePlayer)
    DECLARE_NATIVE(execAddFriend)
    DECLARE_NATIVE(execGetFriendName)
    DECLARE_NATIVE(execGetInvitePassword)
    DECLARE_NATIVE(execGetFriendGameTitle)
    DECLARE_NATIVE(execGetInviteSenderName)
    DECLARE_NATIVE(execRecentPlayerGetName)
    DECLARE_NATIVE(execDownloadContent)
    DECLARE_NATIVE(execLadderDyn_GetPlayerScore)
    DECLARE_NATIVE(execLadderDyn_GetPlayerLevel)
    DECLARE_NATIVE(execMatchQueryIsTutoratMode)
    DECLARE_NATIVE(execMatchQueryIsAlternateMode)
    DECLARE_NATIVE(execMatchQueryIsDedicatedServerMode)
};

// SBase.STeamInfo: 0x378 bytes, 78 virtual functions
class ASTeamInfo : public ATeamInfo {
public:
    virtual ~ASTeamInfo();

    TArray<UnkType_4>     unk_324;
    TArray<FString>       unk_330;
    TArrayLtcg<UnkType_4> unk_33c;
    TArray<FString>       unk_348;
    TArrayLtcg<UnkType_4> unk_354;
    BYTE                  unk_360[0x4];
    TArrayLtcg<UnkType_4> unk_364;
    BYTE                  unk_370[0x8];
};

// SBase.SFlashGen: 0x328 bytes, 78 virtual functions
class ASFlashGen : public ALight {
public:
    virtual ~ASFlashGen();

    BYTE unk_30c[0x1c];
};

// SBase.SInfirmary: 0x350 bytes, 78 virtual functions
class ASInfirmary : public ASBasicGamePlayObject {
public:
    virtual ~ASInfirmary();

    BYTE unk_344[0xc];
};

// SBase.SLift: 0x510 bytes, 80 virtual functions
class ASLift : public AMover {
public:
    virtual ~ASLift();

    TArrayLtcg<UnkType_4>      unk_4e8;
    TArrayLtcg<UnkType_1EEFB0> unk_4f4;
    BYTE                       unk_500[0x10];
};

// SBase.SLiftDoor: 0x4e8 bytes, 80 virtual functions
class ASLiftDoor : public AMover {
public:
    virtual ~ASLiftDoor();
};

// SBase.SMagicEvent: 0x318 bytes, 78 virtual functions
class ASMagicEvent : public AActor {
public:
    virtual ~ASMagicEvent();

    TArrayLtcg<UnkType_1EECB0> unk_2f8;
    TArrayLtcg<UnkType_18>     unk_304;
    BYTE                       unk_310[0x8];
};

// SBase.SProjoFixe: 0x3bc bytes, 78 virtual functions
class ASProjoFixe : public ASOrientableObject {
public:
    virtual ~ASProjoFixe();

    BYTE unk_3a8[0x14];
};

// SBase.SAnimatedMesh: 0x32c bytes, 78 virtual functions
class ASAnimatedMesh : public AActor {
public:
    virtual ~ASAnimatedMesh();

    BYTE                  unk_2f8[0xc];
    TArray<UnkType_4>     unk_304;
    TArray<UnkType_4>     unk_310;
    TArrayLtcg<UnkType_8> unk_31c;
    BYTE                  unk_328[0x4];
};

// SBase.SMapSettings: 0x80 bytes, 22 virtual functions
class USMapSettings : public UObject {
public:
    virtual ~USMapSettings();

    FString                    unk_28;
    FString                    unk_34;
    FString                    unk_40;
    FString                    unk_4c;
    FString                    unk_58;
    BYTE                       unk_64[0x4];
    TArrayLtcg<UnkType_20>     unk_68;
    TArrayLtcg<UnkType_1EE640> unk_74;
};

// SBase.SBombTargetInteraction: 0x374 bytes, 80 virtual functions
class ASBombTargetInteraction : public ASInteractObject {
public:
    virtual ~ASBombTargetInteraction();

    FString unk_364;
    BYTE    unk_370[0x4];
};

// SBase.SSprinkler: 0x35c bytes, 78 virtual functions
class ASSprinkler : public ASBasicGamePlayObject {
public:
    virtual ~ASSprinkler();

    BYTE unk_344[0x18];
};

// SBase.SFlaque: 0x348 bytes, 78 virtual functions
class ASFlaque : public ASBasicGamePlayObject {
public:
    virtual ~ASFlaque();

    BYTE unk_344[0x4];
};

// SBase.SDisk: 0x408 bytes, 80 virtual functions
class ASDisk : public ASObjectiveTrigger {
public:
    virtual ~ASDisk();

    BYTE unk_3e8[0x20];
};

// SBase.SDamageVolume: 0x38c bytes, 78 virtual functions
class ASDamageVolume : public AVolume {
public:
    virtual ~ASDamageVolume();

    BYTE unk_370[0x1c];
};

// SBase.SNotifyNoise: 0x304 bytes, 78 virtual functions
class ASNotifyNoise : public AActor {
public:
    virtual ~ASNotifyNoise();

    BYTE unk_2f8[0xc];
};

// SBase.SPresDetector: 0x394 bytes, 79 virtual functions
class ASPresDetector : public ASMines {
public:
    virtual ~ASPresDetector();
    virtual void VirtualSlot78();

    BYTE unk_36c[0x28];
};

// SBase.SFlagDropZoneInteraction: 0x368 bytes, 80 virtual functions
class ASFlagDropZoneInteraction : public ASInteractObject {
public:
    virtual ~ASFlagDropZoneInteraction();

    BYTE unk_364[0x4];
};

#endif // VERSUS_SBASE_CLASSES_H
