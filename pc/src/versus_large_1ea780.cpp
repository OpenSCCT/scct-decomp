// versus_large_1ea780.cpp -- class registration block at 0x10aea780: 143 native classes.
// Each call constructs one class's static UClass in place with the UClass constructor, in the
// order of the retail calls. Names come from the unit records (see the unit's identification).

#include "versus_stock_class_objects.h"

typedef unsigned long DWORD;
typedef int INT;
typedef unsigned char BYTE;

enum ENativeConstructor { EC_NativeConstructor };

// Name indices (EName). Indices whose names are not recovered keep neutral names.
enum EName
{
    NAME_Name0b4           = 0xb4,
    NAME_System            = 0x256,
};

#define RF_Native_Flags 0x4084004

struct FName
{
    INT Index;
    FName(EName N) : Index(N) {}
};

struct FGuid
{
    DWORD A, B, C, D;
    FGuid(DWORD InA, DWORD InB, DWORD InC, DWORD InD) : A(InA), B(InB), C(InC), D(InD) {}
};

class UObject;
typedef void (UObject::*StaticConstructorType)();

class UClass
{
public:
    UClass(ENativeConstructor, DWORD InSize, DWORD InClassFlags, UClass *InBaseClass,
           UClass *InWithinClass, FGuid InGuid, FName InNameString, FName InPackageName,
           FName InClassConfigName, DWORD InFlags, void (*InClassConstructor)(void *),
           StaticConstructorType InClassStaticConstructor);
    BYTE unk_0[0x118];      // size not recovered
};

class UObject
{
public:
    static UClass PrivateStaticClass;
    static FName StaticConfigName() { return NAME_System; }
    void StaticConstructor();
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

// Registered placement callbacks (InClassConstructor): matched units by their symbols,
// unmatched ones as FUN_<VA>.
extern "C" void place_ASFlagDropZoneInteraction(void *Storage);
extern "C" void place_ASPresDetector(void *Storage);
extern "C" void place_ASNotifyNoise(void *Storage);
extern "C" void place_ASDamageVolume(void *Storage);
extern "C" void place_ASDisk(void *Storage);
extern "C" void place_ASFlaque(void *Storage);
extern "C" void place_ASSprinkler(void *Storage);
extern "C" void place_ASBombTargetInteraction(void *Storage);
extern "C" void place_USMapSettings(void *Storage);
extern "C" void place_ASAnimatedMesh(void *Storage);
extern "C" void place_ASProjoFixe(void *Storage);
extern "C" void FUN_10aee920(void);
extern "C" void place_ASMagicEvent(void *Storage);
extern "C" void place_ASLiftDoor(void *Storage);
extern "C" void place_ASLift(void *Storage);
extern "C" void place_ASInfirmary(void *Storage);
extern "C" void FUN_10aef0d0(void);
extern "C" void place_ASFlashGen(void *Storage);
extern "C" void place_ASTeamInfo(void *Storage);
extern "C" void place_USXBoxLiveRef(void *Storage);
extern "C" void place_USPlayerProfile(void *Storage);
extern "C" void place_ASWeaponDefense(void *Storage);
extern "C" void place_ASWeaponAttaque(void *Storage);
extern "C" void place_ASWeapon(void *Storage);
extern "C" void place_ASWeaponDefenseDummy(void *Storage);
extern "C" void place_ASVolumetricSensor(void *Storage);
extern "C" void place_ASTriggerLight(void *Storage);
extern "C" void place_ASTriggerInteraction(void *Storage);
extern "C" void place_ASStickyCamEmitter(void *Storage);
extern "C" void place_ASSpyBulletLauncher(void *Storage);
extern "C" void place_ASSmokeLaunchEmitter(void *Storage);
extern "C" void place_ASSmokeEmitter(void *Storage);
extern "C" void place_ASSavedMove(void *Storage);
extern "C" void place_ASRJ45Checker(void *Storage);
extern "C" void place_ASProjSmoke(void *Storage);
extern "C" void place_ASProjPhospho(void *Storage);
extern "C" void place_ASProjMarqueurSpy(void *Storage);
extern "C" void place_ASProjGrenade(void *Storage);
extern "C" void place_ASProjFrag(void *Storage);
extern "C" void place_ASProjFlashBang(void *Storage);
extern "C" void place_ASProjFlare(void *Storage);
extern "C" void place_ASProjChaffe(void *Storage);
extern "C" void FUN_10af0730(void);
extern "C" void place_ASPlayerCam(void *Storage);
extern "C" void place_ASPickupInteraction(void *Storage);
extern "C" void place_ASPhosphoEmitter(void *Storage);
extern "C" void place_ASPAWNDEFENSE(void *Storage);
extern "C" void place_ASPawnAttaque(void *Storage);
extern "C" void place_ASOrientableObject(void *Storage);
extern "C" void place_ASObjectiveTrigger(void *Storage);
extern "C" void place_ASObjective(void *Storage);
extern "C" void place_ASNoiseEmitter(void *Storage);
extern "C" void place_ASMuzzleSticky(void *Storage);
extern "C" void place_ASMuzzleFlash(void *Storage);
extern "C" void place_ASMotionTrackingVision(void *Storage);
extern "C" void place_ASMission(void *Storage);
extern "C" void place_ASMines(void *Storage);
extern "C" void place_ASMineProx(void *Storage);
extern "C" void place_ASMineLaser(void *Storage);
extern "C" void place_USMatchInfo(void *Storage);
extern "C" void place_ASLeaveInteraction(void *Storage);
extern "C" void place_ASLaserTrigger(void *Storage);
extern "C" void place_ASLaserProjector(void *Storage);
extern "C" void place_ASLaserBeam_MineLaser(void *Storage);
extern "C" void place_ASLaserBeam(void *Storage);
extern "C" void FUN_10af1950(void);
extern "C" void FUN_10af1a70(void);
extern "C" void place_ASInterrupteur(void *Storage);
extern "C" void place_ASInteractObject(void *Storage);
extern "C" void place_ASInteractionManager(void *Storage);
extern "C" void FUN_10af1d10(void);
extern "C" void place_ASGrenadeExplosion(void *Storage);
extern "C" void place_ASGPOControl(void *Storage);
extern "C" void place_ASGoggleBeam(void *Storage);
extern "C" void place_ASGamePlayObject(void *Storage);
extern "C" void place_ASBasicGamePlayObject(void *Storage);
extern "C" void place_ASGameMessages(void *Storage);
extern "C" void FUN_10af2790(void);
extern "C" void place_ASGadTorcheLaser(void *Storage);
extern "C" void place_ASGadTorche(void *Storage);
extern "C" void place_ASGadTazerLauncher(void *Storage);
extern "C" void FUN_10af2b10(void);
extern "C" void place_ASGadNoiseEmitter(void *Storage);
extern "C" void FUN_10af2d30(void);
extern "C" void place_ASGadGrenLauncher(void *Storage);
extern "C" void place_ASGadget(void *Storage);
extern "C" void place_ASGadBomb(void *Storage);
extern "C" void place_ASFragLaunchEmitter(void *Storage);
extern "C" void place_ASFlashBang(void *Storage);
extern "C" void place_ASFlagDropZone(void *Storage);
extern "C" void place_ASFlag(void *Storage);
extern "C" void place_ASFireTrace(void *Storage);
extern "C" void place_ASComputerObjectiveTrigger(void *Storage);
extern "C" void place_ASComputerInteraction(void *Storage);
extern "C" void place_ASChaffeEmitter(void *Storage);
extern "C" void place_ASCamera(void *Storage);
extern "C" void place_ASBombTargetObjectiveTrigger(void *Storage);
extern "C" void place_ASBloodSplat(void *Storage);
extern "C" void place_ASBasePawn(void *Storage);
extern "C" void place_ASAmmoStock(void *Storage);
extern "C" void place_ASAmbientSoundTrigger(void *Storage);
extern "C" void place_ASAlarm(void *Storage);
extern "C" void place_ASGoggle(void *Storage);
extern "C" void place_ASFlareEmitter(void *Storage);
extern "C" void place_ASFlareCourseEmitter(void *Storage);
extern "C" void place_ASExtincteurEmitter(void *Storage);
extern "C" void place_ASFlashLight(void *Storage);
extern "C" void place_ASFlashLight_FragGrenade(void *Storage);
extern "C" void place_ASDouilleEmitter(void *Storage);
extern "C" void place_ASTazerEmitter(void *Storage);
extern "C" void place_ASMinePiegeSpy(void *Storage);
extern "C" void place_ASAmmoStockInteraction(void *Storage);
extern "C" void place_ASMineProxInteraction(void *Storage);
extern "C" void place_ASExtincteur(void *Storage);
extern "C" void place_ASShareObjectInteraction(void *Storage);
extern "C" void place_ASGadSmokeGrenade(void *Storage);
extern "C" void place_ASGadPhosphoLauncher(void *Storage);
extern "C" void place_ASGadFragGrenade(void *Storage);
extern "C" void place_ASGadFlareLauncher(void *Storage);
extern "C" void place_ASGadChaffeGrenade(void *Storage);
extern "C" void place_ASGadFlashBang(void *Storage);
extern "C" void place_ASGadCamNetwork(void *Storage);
extern "C" void place_ASCamNetwork(void *Storage);
extern "C" void place_ASStickyCam(void *Storage);
extern "C" void place_ASWeaponDefense_Shotgun(void *Storage);
extern "C" void place_ASImpactEffectShockerMetal(void *Storage);
extern "C" void place_ASImpactEffectShocker(void *Storage);
extern "C" void place_ASMinePoison(void *Storage);
extern "C" void place_ASGadGasMask(void *Storage);
extern "C" void place_ASGadBackPack(void *Storage);
extern "C" void place_ASMateInteraction(void *Storage);
extern "C" void place_ASHealMateInteraction(void *Storage);
extern "C" void place_ASBackPackInteraction(void *Storage);
extern "C" void place_ASRemoveSpyBulletInteraction(void *Storage);
extern "C" void place_ASWeaponDefense_Uzi(void *Storage);
extern "C" void place_ASWeaponDefenseDummy_Shotgun(void *Storage);
extern "C" void place_ASWeaponDefenseDummy_Uzi(void *Storage);
extern "C" void FUN_10af5700(void);
extern "C" void place_ASPoisonEmitter(void *Storage);
extern "C" void place_ASGadHeartBeatSensor(void *Storage);
extern "C" void place_ASCoronaLight(void *Storage);
extern "C" void place_ASStickyCamInteraction(void *Storage);
extern "C" void place_ASVitre(void *Storage);

// Function placeholder: registers the block's classes.
class UnkType_10aea780
{
public:
    void FUN_10aea780();
};

// FUN_10aea780: constructs the static UClass of each of the 143 classes, in address order.
void UnkType_10aea780::FUN_10aea780()
{
    new(&ASVitre_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3c4, 0x0,
        (UClass *)&ASGamePlayObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xfa7cb, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASVitre,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASStickyCamInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&ASMineProxInteraction_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0xfa7c7, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASStickyCamInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASCoronaLight_PrivateStaticClass) UClass(EC_NativeConstructor, 0x30c, 0x0,
        (UClass *)&ALight_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xde180, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASCoronaLight,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadHeartBeatSensor_PrivateStaticClass) UClass(EC_NativeConstructor, 0x370, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xe6cc8, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadHeartBeatSensor,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASPoisonEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xe4305, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASPoisonEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10ca0838) UClass(EC_NativeConstructor, 0x428, 0x4,
        (UClass *)&DAT_10c9d5e8, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xe42e8, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10af5700,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASWeaponDefenseDummy_Uzi_PrivateStaticClass) UClass(EC_NativeConstructor, 0x318, 0x0,
        (UClass *)&ASWeaponDefenseDummy_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xdd3b9, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASWeaponDefenseDummy_Uzi,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASWeaponDefenseDummy_Shotgun_PrivateStaticClass) UClass(EC_NativeConstructor, 0x324,
        0x800, (UClass *)&ASWeaponDefenseDummy_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0xdd3b8, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASWeaponDefenseDummy_Shotgun,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASWeaponDefense_Uzi_PrivateStaticClass) UClass(EC_NativeConstructor, 0x43c, 0x4,
        (UClass *)&ASWeaponDefense_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xdd3ba, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASWeaponDefense_Uzi,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASRemoveSpyBulletInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x0,
        (UClass *)&ASMateInteraction_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd5298, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASRemoveSpyBulletInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASBackPackInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x36c, 0x0,
        (UClass *)&ASMateInteraction_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd5267, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASBackPackInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASHealMateInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x374, 0x0,
        (UClass *)&ASMateInteraction_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd5281, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASHealMateInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMateInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x800,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd5268, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMateInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadBackPack_PrivateStaticClass) UClass(EC_NativeConstructor, 0x37c, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd0835, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadBackPack,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadGasMask_PrivateStaticClass) UClass(EC_NativeConstructor, 0x374, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd0837, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadGasMask,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMinePoison_PrivateStaticClass) UClass(EC_NativeConstructor, 0x39c, 0x0,
        (UClass *)&ASMinePiegeSpy_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd0850, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMinePoison,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASImpactEffectShocker_PrivateStaticClass) UClass(EC_NativeConstructor, 0x304, 0x0,
        (UClass *)&ASImpactEffectBase_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd0847, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASImpactEffectShocker,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASImpactEffectShockerMetal_PrivateStaticClass) UClass(EC_NativeConstructor, 0x304, 0x0,
        (UClass *)&ASImpactEffectBase_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd0848, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASImpactEffectShockerMetal,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASWeaponDefense_Shotgun_PrivateStaticClass) UClass(EC_NativeConstructor, 0x444, 0x4,
        (UClass *)&ASWeaponDefense_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xc73e3, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASWeaponDefense_Shotgun,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASStickyCam_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3c0, 0x800,
        (UClass *)&ASOrientableObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xbef3c, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASStickyCam,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASCamNetwork_PrivateStaticClass) UClass(EC_NativeConstructor, 0x438, 0x800,
        (UClass *)&ASStickyCam_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xbef3b, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASCamNetwork,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadCamNetwork_PrivateStaticClass) UClass(EC_NativeConstructor, 0x358, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xbef49, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadCamNetwork,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadFlashBang_PrivateStaticClass) UClass(EC_NativeConstructor, 0x354, 0x4,
        (UClass *)&ASGadGrenLauncher_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xacc69, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadFlashBang,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadChaffeGrenade_PrivateStaticClass) UClass(EC_NativeConstructor, 0x354, 0x4,
        (UClass *)&ASGadGrenLauncher_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xacc67, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadChaffeGrenade,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadFlareLauncher_PrivateStaticClass) UClass(EC_NativeConstructor, 0x354, 0x4,
        (UClass *)&ASGadGrenLauncher_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xacc68, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadFlareLauncher,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadFragGrenade_PrivateStaticClass) UClass(EC_NativeConstructor, 0x354, 0x4,
        (UClass *)&ASGadGrenLauncher_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xacc6a, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadFragGrenade,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadPhosphoLauncher_PrivateStaticClass) UClass(EC_NativeConstructor, 0x354, 0x4,
        (UClass *)&ASGadGrenLauncher_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xacc6d, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadPhosphoLauncher,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadSmokeGrenade_PrivateStaticClass) UClass(EC_NativeConstructor, 0x354, 0x4,
        (UClass *)&ASGadGrenLauncher_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xacc6f, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadSmokeGrenade,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASShareObjectInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x380, 0x0,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xbd1cb, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASShareObjectInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASExtincteur_PrivateStaticClass) UClass(EC_NativeConstructor, 0x304, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xb96be, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASExtincteur,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMineProxInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x71463, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMineProxInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASAmmoStockInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x6b8a6, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASAmmoStockInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMinePiegeSpy_PrivateStaticClass) UClass(EC_NativeConstructor, 0x394, 0x800,
        (UClass *)&ASMines_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x5585b, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMinePiegeSpy,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASTazerEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x308, 0x800,
        (UClass *)&AEffects_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x4aaa4, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASTazerEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASDouilleEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2edfc, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASDouilleEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlashLight_FragGrenade_PrivateStaticClass) UClass(EC_NativeConstructor, 0x314, 0x0,
        (UClass *)&ASFlashLight_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2ee08, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlashLight_FragGrenade,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlashLight_PrivateStaticClass) UClass(EC_NativeConstructor, 0x30c, 0x0,
        (UClass *)&ALight_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2ee07, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlashLight,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASExtincteurEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2ee03, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASExtincteurEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlareCourseEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2ee05, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlareCourseEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlareEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x36c, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2ea2a, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlareEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGoggle_PrivateStaticClass) UClass(EC_NativeConstructor, 0x33c, 0x0,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x184, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASGoggle, (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASAlarm_PrivateStaticClass) UClass(EC_NativeConstructor, 0x360, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x267, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASAlarm, (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASAmbientSoundTrigger_PrivateStaticClass) UClass(EC_NativeConstructor, 0x300, 0x800,
        (UClass *)&ATriggers_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2edf8, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASAmbientSoundTrigger,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASAmmoStock_PrivateStaticClass) UClass(EC_NativeConstructor, 0x344, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x33d20, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASAmmoStock,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASBasePawn_PrivateStaticClass) UClass(EC_NativeConstructor, 0xb60, 0x804,
        (UClass *)&APawn_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cd8, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASBasePawn,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASBloodSplat_PrivateStaticClass) UClass(EC_NativeConstructor, 0x488, 0x800,
        (UClass *)&AProjector_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bed9, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASBloodSplat,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASBombTargetObjectiveTrigger_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3f4,
        0x800, (UClass *)&ASObjectiveTrigger_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x2bedb, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASBombTargetObjectiveTrigger,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASCamera_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3c0, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x2bedc, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASCamera,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASChaffeEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cd9, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASChaffeEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASComputerInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x374, 0x800,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bedd, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASComputerInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASComputerObjectiveTrigger_PrivateStaticClass) UClass(EC_NativeConstructor, 0x41c, 0x800,
        (UClass *)&ASObjectiveTrigger_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bede, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASComputerObjectiveTrigger,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFireTrace_PrivateStaticClass) UClass(EC_NativeConstructor, 0x314, 0x800,
        (UClass *)&AEffects_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x12ba4, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFireTrace,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlag_PrivateStaticClass) UClass(EC_NativeConstructor, 0x430, 0x800,
        (UClass *)&ASObjectiveTrigger_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x1be5f, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlag,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlagDropZone_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3ec, 0x800,
        (UClass *)&ASObjectiveTrigger_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d2a, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlagDropZone,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlashBang_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x12c03, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlashBang,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFragLaunchEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cd5, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFragLaunchEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadBomb_PrivateStaticClass) UClass(EC_NativeConstructor, 0x358, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bef1, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadBomb,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadget_PrivateStaticClass) UClass(EC_NativeConstructor, 0x350, 0x804,
        (UClass *)&AInventory_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ce8, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadget,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadGrenLauncher_PrivateStaticClass) UClass(EC_NativeConstructor, 0x354, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2e785, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadGrenLauncher,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10c9d5e8) UClass(EC_NativeConstructor, 0x428, 0x804,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2befc, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10af2d30,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadNoiseEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x360, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d34, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadNoiseEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10c9d818) UClass(EC_NativeConstructor, 0x38c, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d38, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10af2b10,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadTazerLauncher_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d39, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadTazerLauncher,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadTorche_PrivateStaticClass) UClass(EC_NativeConstructor, 0x374, 0x804,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xe8, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASGadTorche, (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGadTorcheLaser_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3a0, 0x804,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ce7, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGadTorcheLaser,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10c9f488) UClass(EC_NativeConstructor, 0x4d4, 0x4,
        (UClass *)&DAT_10cc5708, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd0, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&FUN_10af2790, (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGameMessages_PrivateStaticClass) UClass(EC_NativeConstructor, 0x548, 0x0,
        (UClass *)&ALocalMessage_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d3a, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGameMessages,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASBasicGamePlayObject_PrivateStaticClass) UClass(EC_NativeConstructor, 0x344, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x7ee, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASBasicGamePlayObject,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGamePlayObject_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3c4, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x266, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASGamePlayObject,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGoggleBeam_PrivateStaticClass) UClass(EC_NativeConstructor, 0x308, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bf04, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGoggleBeam,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGPOControl_PrivateStaticClass) UClass(EC_NativeConstructor, 0x310, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x5e4c4, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGPOControl,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASGrenadeExplosion_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cd4, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASGrenadeExplosion,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10c9ff78) UClass(EC_NativeConstructor, 0x898, 0x8,
        (UClass *)&DAT_10cc61f8, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x1a7d, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10af1d10,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASInteractionManager_PrivateStaticClass) UClass(EC_NativeConstructor, 0x340, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d4c, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASInteractionManager,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASInteractObject_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2beb1, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASInteractObject,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASInterrupteur_PrivateStaticClass) UClass(EC_NativeConstructor, 0x37c, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x33d4d, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASInterrupteur,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10c9cd20) UClass(EC_NativeConstructor, 0x358, 0x8,
        (UClass *)&DAT_10ca27f0, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ce6, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10af1a70,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10c9ce38) UClass(EC_NativeConstructor, 0x368, 0x8,
        (UClass *)&DAT_10ca27f0, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ce3, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10af1950,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASLaserBeam_PrivateStaticClass) UClass(EC_NativeConstructor, 0x2fc, 0x800,
        (UClass *)&AEffects_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xec, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASLaserBeam, (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASLaserBeam_MineLaser_PrivateStaticClass) UClass(EC_NativeConstructor, 0x308, 0x800,
        (UClass *)&ASLaserBeam_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x12c2c, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASLaserBeam_MineLaser,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASLaserProjector_PrivateStaticClass) UClass(EC_NativeConstructor, 0x47c, 0x0,
        (UClass *)&AProjector_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x3cc, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASLaserProjector,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASLaserTrigger_PrivateStaticClass) UClass(EC_NativeConstructor, 0x388, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x1288f, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASLaserTrigger,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASLeaveInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x362e7, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASLeaveInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&USMatchInfo_PrivateStaticClass) UClass(EC_NativeConstructor, 0xc4, 0x0,
        (UClass *)&UMatchInfo_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x49889, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_USMatchInfo,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMineLaser_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3e8, 0x800,
        (UClass *)&ASMines_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x12b9d, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMineLaser,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMineProx_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3b8, 0x800,
        (UClass *)&ASMines_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2ea22, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMineProx,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMines_PrivateStaticClass) UClass(EC_NativeConstructor, 0x36c, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x12c33, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASMines,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMission_PrivateStaticClass) UClass(EC_NativeConstructor, 0x388, 0x800,
        (UClass *)&ASObjective_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bf27, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMission,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMotionTrackingVision_PrivateStaticClass) UClass(EC_NativeConstructor, 0x348, 0xc,
        (UClass *)&AMotionTrackingVision_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x26828, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASMotionTrackingVision,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMuzzleFlash_PrivateStaticClass) UClass(EC_NativeConstructor, 0x2fc, 0x0,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bf2a, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMuzzleFlash,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMuzzleSticky_PrivateStaticClass) UClass(EC_NativeConstructor, 0x300, 0x0,
        (UClass *)&ASMuzzleFlash_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x3cd, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASMuzzleSticky,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASNoiseEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x394, 0x0,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x33d5b, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASNoiseEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASObjective_PrivateStaticClass) UClass(EC_NativeConstructor, 0x35c, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8161, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASObjective,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASObjectiveTrigger_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3e8, 0x800,
        (UClass *)&ASGamePlayObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x8c0, NAME_Name0b4, UObject::StaticConfigName(), RF_Native_Flags,
        (void (*)(void *))&place_ASObjectiveTrigger,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASOrientableObject_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3a8, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x33d5c, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASOrientableObject,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASPawnAttaque_PrivateStaticClass) UClass(EC_NativeConstructor, 0xba4, 0x804,
        (UClass *)&ASBasePawn_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cee, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASPawnAttaque,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASPAWNDEFENSE_PrivateStaticClass) UClass(EC_NativeConstructor, 0xb80, 0x804,
        (UClass *)&ASBasePawn_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cd7, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASPAWNDEFENSE,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASPhosphoEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x37c, 0x800,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cda, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASPhosphoEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASPickupInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x800,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d5d, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASPickupInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASPlayerCam_PrivateStaticClass) UClass(EC_NativeConstructor, 0x18f0, 0x0,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ced, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASPlayerCam,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10c9cf58) UClass(EC_NativeConstructor, 0xc70, 0x800,
        (UClass *)&DAT_10cc6ce8, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cec, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10af0730,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjChaffe_PrivateStaticClass) UClass(EC_NativeConstructor, 0x36c, 0x0,
        (UClass *)&ASProjGrenade_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cdf, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASProjChaffe,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjFlare_PrivateStaticClass) UClass(EC_NativeConstructor, 0x35c, 0x0,
        (UClass *)&ASProjGrenade_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ce0, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASProjFlare,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjFlashBang_PrivateStaticClass) UClass(EC_NativeConstructor, 0x35c, 0x0,
        (UClass *)&ASProjGrenade_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cde, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASProjFlashBang,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjFrag_PrivateStaticClass) UClass(EC_NativeConstructor, 0x36c, 0x0,
        (UClass *)&ASProjGrenade_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ce1, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASProjFrag,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjGrenade_PrivateStaticClass) UClass(EC_NativeConstructor, 0x354, 0x800,
        (UClass *)&AProjectile_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cdd, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASProjGrenade,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjMarqueurSpy_PrivateStaticClass) UClass(EC_NativeConstructor, 0x358, 0x0,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x33d60, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASProjMarqueurSpy,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjPhospho_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x0,
        (UClass *)&ASProjGrenade_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cdc, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASProjPhospho,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjSmoke_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x0,
        (UClass *)&ASProjGrenade_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ce2, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASProjSmoke,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASRJ45Checker_PrivateStaticClass) UClass(EC_NativeConstructor, 0x2fc, 0x0,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x64c37, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASRJ45Checker,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASSavedMove_PrivateStaticClass) UClass(EC_NativeConstructor, 0x310, 0x0,
        (UClass *)&AInfo_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xf4cf, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASSavedMove,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASSmokeEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x380, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cdb, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASSmokeEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASSmokeLaunchEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x364, 0x0,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cd6, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASSmokeLaunchEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASSpyBulletLauncher_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x4,
        (UClass *)&ASGadget_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d6d, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASSpyBulletLauncher,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASStickyCamEmitter_PrivateStaticClass) UClass(EC_NativeConstructor, 0x390, 0x800,
        (UClass *)&AEmitter_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d6f, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASStickyCamEmitter,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASTriggerInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x380, 0x800,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d74, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASTriggerInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASTriggerLight_PrivateStaticClass) UClass(EC_NativeConstructor, 0x32c, 0x800,
        (UClass *)&ALight_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cd2, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASTriggerLight,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASVolumetricSensor_PrivateStaticClass) UClass(EC_NativeConstructor, 0x37c, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x2bf54, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASVolumetricSensor,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASWeaponDefenseDummy_PrivateStaticClass) UClass(EC_NativeConstructor, 0x318, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x33d7e, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASWeaponDefenseDummy,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASWeapon_PrivateStaticClass) UClass(EC_NativeConstructor, 0x37c, 0x804,
        (UClass *)&AInventory_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bf55, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASWeapon,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASWeaponAttaque_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3b0, 0x804,
        (UClass *)&ASWeapon_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2bf56, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASWeaponAttaque,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASWeaponDefense_PrivateStaticClass) UClass(EC_NativeConstructor, 0x438, 0x4,
        (UClass *)&ASWeapon_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x2e70f, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASWeaponDefense,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&USPlayerProfile_PrivateStaticClass) UClass(EC_NativeConstructor, 0xe4, 0x4,
        (UClass *)&UObject::PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9cea, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_USPlayerProfile,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&USXBoxLiveRef_PrivateStaticClass) UClass(EC_NativeConstructor, 0xb8, 0x0,
        (UClass *)&UObject::PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x9ceb, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_USXBoxLiveRef,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASTeamInfo_PrivateStaticClass) UClass(EC_NativeConstructor, 0x378, 0x800,
        (UClass *)&ATeamInfo_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x58d18, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASTeamInfo,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlashGen_PrivateStaticClass) UClass(EC_NativeConstructor, 0x328, 0x800,
        (UClass *)&ALight_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x58fe1, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlashGen,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10ca02c0) UClass(EC_NativeConstructor, 0x330, 0x0,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x59003, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10aef0d0,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASInfirmary_PrivateStaticClass) UClass(EC_NativeConstructor, 0x350, 0x0,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0x62022, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASInfirmary,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASLift_PrivateStaticClass) UClass(EC_NativeConstructor, 0x510, 0x800,
        (UClass *)&AMover_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xb7947, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASLift,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASLiftDoor_PrivateStaticClass) UClass(EC_NativeConstructor, 0x4e8, 0x800,
        (UClass *)&AMover_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xb7948, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASLiftDoor,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASMagicEvent_PrivateStaticClass) UClass(EC_NativeConstructor, 0x318, 0x0,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xbd1be, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASMagicEvent,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&DAT_10c9c000) UClass(EC_NativeConstructor, 0x1b8, 0x8,
        (UClass *)&UPersistentData_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xcadcf, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&FUN_10aee920,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASProjoFixe_PrivateStaticClass) UClass(EC_NativeConstructor, 0x3bc, 0x800,
        (UClass *)&ASOrientableObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x592dc, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASProjoFixe,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASAnimatedMesh_PrivateStaticClass) UClass(EC_NativeConstructor, 0x32c, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xbb42d, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASAnimatedMesh,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&USMapSettings_PrivateStaticClass) UClass(EC_NativeConstructor, 0x80, 0x0,
        (UClass *)&UObject::PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xc9c5d, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_USMapSettings,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASBombTargetInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x374, 0x800,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xcd440, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASBombTargetInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASSprinkler_PrivateStaticClass) UClass(EC_NativeConstructor, 0x35c, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0xcd47c, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASSprinkler,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlaque_PrivateStaticClass) UClass(EC_NativeConstructor, 0x348, 0x800,
        (UClass *)&ASBasicGamePlayObject_PrivateStaticClass,
        (UClass *)&UObject::PrivateStaticClass, FGuid(0, 0, 0, 0), (EName)0xd0832, NAME_Name0b4,
        UObject::StaticConfigName(), RF_Native_Flags, (void (*)(void *))&place_ASFlaque,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASDisk_PrivateStaticClass) UClass(EC_NativeConstructor, 0x408, 0x800,
        (UClass *)&ASObjectiveTrigger_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd0828, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASDisk,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASDamageVolume_PrivateStaticClass) UClass(EC_NativeConstructor, 0x38c, 0x0,
        (UClass *)&AVolume_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xd0826, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASDamageVolume,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASNotifyNoise_PrivateStaticClass) UClass(EC_NativeConstructor, 0x304, 0x800,
        (UClass *)&AActor_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xe558d, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASNotifyNoise,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASPresDetector_PrivateStaticClass) UClass(EC_NativeConstructor, 0x394, 0x4,
        (UClass *)&ASMines_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0xf681f, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASPresDetector,
        (StaticConstructorType)&UObject::StaticConstructor);
    new(&ASFlagDropZoneInteraction_PrivateStaticClass) UClass(EC_NativeConstructor, 0x368, 0x800,
        (UClass *)&ASInteractObject_PrivateStaticClass, (UClass *)&UObject::PrivateStaticClass,
        FGuid(0, 0, 0, 0), (EName)0x12321f, NAME_Name0b4, UObject::StaticConfigName(),
        RF_Native_Flags, (void (*)(void *))&place_ASFlagDropZoneInteraction,
        (StaticConstructorType)&UObject::StaticConstructor);
}
