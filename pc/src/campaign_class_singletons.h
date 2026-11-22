/* campaign_class_singletons.h -- the class singleton symbols and package name tables used by the
   class singleton, class cast, subclass load and class registration units */

struct RuntimeClass;

extern const unsigned short package_Core[];
extern const unsigned short package_D3DDrv[];
extern const unsigned short package_DareAudio[];
extern const unsigned short package_Echelon[];
extern const unsigned short package_EchelonAI[];
extern const unsigned short package_EchelonIngredient[];
extern const unsigned short package_EchelonMenus[];
extern const unsigned short package_Engine[];
extern const unsigned short package_WinDrv[];
extern const unsigned short package_Window[];

extern struct RuntimeClass *class_UArrayProperty;
extern struct RuntimeClass *create_UArrayProperty(const unsigned short *package);
extern void register_UArrayProperty(void);

extern struct RuntimeClass *class_UBoolProperty;
extern struct RuntimeClass *create_UBoolProperty(const unsigned short *package);
extern void register_UBoolProperty(void);

extern struct RuntimeClass *class_UByteProperty;
extern struct RuntimeClass *create_UByteProperty(const unsigned short *package);
extern void register_UByteProperty(void);

extern struct RuntimeClass *class_UClass;
extern struct RuntimeClass *create_UClass(const unsigned short *package);
extern void register_UClass(void);

extern struct RuntimeClass *class_UClassProperty;
extern struct RuntimeClass *create_UClassProperty(const unsigned short *package);
extern void register_UClassProperty(void);

extern struct RuntimeClass *class_UCommandlet;
extern struct RuntimeClass *create_UCommandlet(const unsigned short *package);
extern void register_UCommandlet(void);

extern struct RuntimeClass *class_UConst;
extern struct RuntimeClass *create_UConst(const unsigned short *package);
extern void register_UConst(void);

extern struct RuntimeClass *class_UEnum;
extern struct RuntimeClass *create_UEnum(const unsigned short *package);
extern void register_UEnum(void);

extern struct RuntimeClass *class_UExporter;
extern struct RuntimeClass *create_UExporter(const unsigned short *package);
extern void register_UExporter(void);

extern struct RuntimeClass *class_UFactory;
extern struct RuntimeClass *create_UFactory(const unsigned short *package);
extern void register_UFactory(void);

extern struct RuntimeClass *class_UField;
extern struct RuntimeClass *create_UField(const unsigned short *package);
extern void register_UField(void);

extern struct RuntimeClass *class_UFixedArrayProperty;
extern struct RuntimeClass *create_UFixedArrayProperty(const unsigned short *package);
extern void register_UFixedArrayProperty(void);

extern struct RuntimeClass *class_UFloatProperty;
extern struct RuntimeClass *create_UFloatProperty(const unsigned short *package);
extern void register_UFloatProperty(void);

extern struct RuntimeClass *class_UFunction;
extern struct RuntimeClass *create_UFunction(const unsigned short *package);
extern void register_UFunction(void);

extern struct RuntimeClass *class_UIntProperty;
extern struct RuntimeClass *create_UIntProperty(const unsigned short *package);
extern void register_UIntProperty(void);

extern struct RuntimeClass *class_ULanguage;
extern struct RuntimeClass *create_ULanguage(const unsigned short *package);
extern void register_ULanguage(void);

extern struct RuntimeClass *class_ULinker;
extern struct RuntimeClass *create_ULinker(const unsigned short *package);
extern void register_ULinker(void);

extern struct RuntimeClass *class_ULinkerLoad;
extern struct RuntimeClass *create_ULinkerLoad(const unsigned short *package);
extern void register_ULinkerLoad(void);

extern struct RuntimeClass *class_ULinkerSave;
extern struct RuntimeClass *create_ULinkerSave(const unsigned short *package);
extern void register_ULinkerSave(void);

extern struct RuntimeClass *class_UMapProperty;
extern struct RuntimeClass *create_UMapProperty(const unsigned short *package);
extern void register_UMapProperty(void);

extern struct RuntimeClass *class_UNameProperty;
extern struct RuntimeClass *create_UNameProperty(const unsigned short *package);
extern void register_UNameProperty(void);

extern struct RuntimeClass *class_UObject;
extern struct RuntimeClass *create_UObject(const unsigned short *package);
extern void register_UObject(void);

extern struct RuntimeClass *class_UObjectProperty;
extern struct RuntimeClass *create_UObjectProperty(const unsigned short *package);
extern void register_UObjectProperty(void);

extern struct RuntimeClass *class_UPackage;
extern struct RuntimeClass *create_UPackage(const unsigned short *package);
extern void register_UPackage(void);

extern struct RuntimeClass *class_UProperty;
extern struct RuntimeClass *create_UProperty(const unsigned short *package);
extern void register_UProperty(void);

extern struct RuntimeClass *class_UState;
extern struct RuntimeClass *create_UState(const unsigned short *package);
extern void register_UState(void);

extern struct RuntimeClass *class_UStrProperty;
extern struct RuntimeClass *create_UStrProperty(const unsigned short *package);
extern void register_UStrProperty(void);

extern struct RuntimeClass *class_UStruct;
extern struct RuntimeClass *create_UStruct(const unsigned short *package);
extern void register_UStruct(void);

extern struct RuntimeClass *class_UStructProperty;
extern struct RuntimeClass *create_UStructProperty(const unsigned short *package);
extern void register_UStructProperty(void);

extern struct RuntimeClass *class_USubsystem;
extern struct RuntimeClass *create_USubsystem(const unsigned short *package);
extern void register_USubsystem(void);

extern struct RuntimeClass *class_USystem;
extern struct RuntimeClass *create_USystem(const unsigned short *package);
extern void register_USystem(void);

extern struct RuntimeClass *class_UTextBuffer;
extern struct RuntimeClass *create_UTextBuffer(const unsigned short *package);
extern void register_UTextBuffer(void);

extern struct RuntimeClass *class_UTextBufferFactory;
extern struct RuntimeClass *create_UTextBufferFactory(const unsigned short *package);
extern void register_UTextBufferFactory(void);

extern struct RuntimeClass *class_UD3DRenderDevice;
extern struct RuntimeClass *create_UD3DRenderDevice(const unsigned short *package);
extern void register_UD3DRenderDevice(void);

extern struct RuntimeClass *class_UDareAudioSubsystem;
extern struct RuntimeClass *create_UDareAudioSubsystem(const unsigned short *package);
extern void register_UDareAudioSubsystem(void);

extern struct RuntimeClass *class_AE3DBeacon;
extern struct RuntimeClass *create_AE3DBeacon(const unsigned short *package);
extern void register_AE3DBeacon(void);

extern struct RuntimeClass *class_AE3DCameraTarget;
extern struct RuntimeClass *create_AE3DCameraTarget(const unsigned short *package);
extern void register_AE3DCameraTarget(void);

extern struct RuntimeClass *class_AE3DMapSystem;
extern struct RuntimeClass *create_AE3DMapSystem(const unsigned short *package);
extern void register_AE3DMapSystem(void);

extern struct RuntimeClass *class_AEAIController;
extern struct RuntimeClass *create_AEAIController(const unsigned short *package);
extern void register_AEAIController(void);

extern struct RuntimeClass *class_AEAIManager;
extern struct RuntimeClass *create_AEAIManager(const unsigned short *package);
extern void register_AEAIManager(void);

extern struct RuntimeClass *class_AEAIPawn;
extern struct RuntimeClass *create_AEAIPawn(const unsigned short *package);
extern void register_AEAIPawn(void);

extern struct RuntimeClass *class_AEAccessory;
extern struct RuntimeClass *create_AEAccessory(const unsigned short *package);
extern void register_AEAccessory(void);

extern struct RuntimeClass *class_AEAlarmPanelObject;
extern struct RuntimeClass *create_AEAlarmPanelObject(const unsigned short *package);
extern void register_AEAlarmPanelObject(void);

extern struct RuntimeClass *class_AEAmbianceSplitter;
extern struct RuntimeClass *create_AEAmbianceSplitter(const unsigned short *package);
extern void register_AEAmbianceSplitter(void);

extern struct RuntimeClass *class_AEBaseDoor;
extern struct RuntimeClass *create_AEBaseDoor(const unsigned short *package);
extern void register_AEBaseDoor(void);

extern struct RuntimeClass *class_AEChangedActorManager;
extern struct RuntimeClass *create_AEChangedActorManager(const unsigned short *package);
extern void register_AEChangedActorManager(void);

extern struct RuntimeClass *class_AECoopAltCommSync;
extern struct RuntimeClass *create_AECoopAltCommSync(const unsigned short *package);
extern void register_AECoopAltCommSync(void);

extern struct RuntimeClass *class_AECoopBlockingVolume;
extern struct RuntimeClass *create_AECoopBlockingVolume(const unsigned short *package);
extern void register_AECoopBlockingVolume(void);

extern struct RuntimeClass *class_AECoopExitInteraction;
extern struct RuntimeClass *create_AECoopExitInteraction(const unsigned short *package);
extern void register_AECoopExitInteraction(void);

extern struct RuntimeClass *class_AECoopHackRope;
extern struct RuntimeClass *create_AECoopHackRope(const unsigned short *package);
extern void register_AECoopHackRope(void);

extern struct RuntimeClass *class_AECoopInteractDispatch;
extern struct RuntimeClass *create_AECoopInteractDispatch(const unsigned short *package);
extern void register_AECoopInteractDispatch(void);

extern struct RuntimeClass *class_AECoopInteractVolume;
extern struct RuntimeClass *create_AECoopInteractVolume(const unsigned short *package);
extern void register_AECoopInteractVolume(void);

extern struct RuntimeClass *class_AECoopPlayerController;
extern struct RuntimeClass *create_AECoopPlayerController(const unsigned short *package);
extern void register_AECoopPlayerController(void);

extern struct RuntimeClass *class_AECoopRevive;
extern struct RuntimeClass *create_AECoopRevive(const unsigned short *package);
extern void register_AECoopRevive(void);

extern struct RuntimeClass *class_AECoopRplBtmFinish;
extern struct RuntimeClass *create_AECoopRplBtmFinish(const unsigned short *package);
extern void register_AECoopRplBtmFinish(void);

extern struct RuntimeClass *class_AECoopRplBtmInit;
extern struct RuntimeClass *create_AECoopRplBtmInit(const unsigned short *package);
extern void register_AECoopRplBtmInit(void);

extern struct RuntimeClass *class_AECoopShareEquipment;
extern struct RuntimeClass *create_AECoopShareEquipment(const unsigned short *package);
extern void register_AECoopShareEquipment(void);

extern struct RuntimeClass *class_AECoopSuccessVolume;
extern struct RuntimeClass *create_AECoopSuccessVolume(const unsigned short *package);
extern void register_AECoopSuccessVolume(void);

extern struct RuntimeClass *class_AECoopTeammateShoulders;
extern struct RuntimeClass *create_AECoopTeammateShoulders(const unsigned short *package);
extern void register_AECoopTeammateShoulders(void);

extern struct RuntimeClass *class_AEDoorOpener;
extern struct RuntimeClass *create_AEDoorOpener(const unsigned short *package);
extern void register_AEDoorOpener(void);

extern struct RuntimeClass *class_AEDummyActor;
extern struct RuntimeClass *create_AEDummyActor(const unsigned short *package);
extern void register_AEDummyActor(void);

extern struct RuntimeClass *class_AEDynamicLight;
extern struct RuntimeClass *create_AEDynamicLight(const unsigned short *package);
extern void register_AEDynamicLight(void);

extern struct RuntimeClass *class_AEExitInteraction;
extern struct RuntimeClass *create_AEExitInteraction(const unsigned short *package);
extern void register_AEExitInteraction(void);

extern struct RuntimeClass *class_AEFlashLight;
extern struct RuntimeClass *create_AEFlashLight(const unsigned short *package);
extern void register_AEFlashLight(void);

extern struct RuntimeClass *class_AEForegripAttach;
extern struct RuntimeClass *create_AEForegripAttach(const unsigned short *package);
extern void register_AEForegripAttach(void);

extern struct RuntimeClass *class_AEFurniture;
extern struct RuntimeClass *create_AEFurniture(const unsigned short *package);
extern void register_AEFurniture(void);

extern struct RuntimeClass *class_AEGOListener;
extern struct RuntimeClass *create_AEGOListener(const unsigned short *package);
extern void register_AEGOListener(void);

extern struct RuntimeClass *class_AEGameplayObject;
extern struct RuntimeClass *create_AEGameplayObject(const unsigned short *package);
extern void register_AEGameplayObject(void);

extern struct RuntimeClass *class_AEGameplayObjectLight;
extern struct RuntimeClass *create_AEGameplayObjectLight(const unsigned short *package);
extern void register_AEGameplayObjectLight(void);

extern struct RuntimeClass *class_AEGoggle;
extern struct RuntimeClass *create_AEGoggle(const unsigned short *package);
extern void register_AEGoggle(void);

extern struct RuntimeClass *class_AEHackingGameplay;
extern struct RuntimeClass *create_AEHackingGameplay(const unsigned short *package);
extern void register_AEHackingGameplay(void);

extern struct RuntimeClass *class_AEHandGun;
extern struct RuntimeClass *create_AEHandGun(const unsigned short *package);
extern void register_AEHandGun(void);

extern struct RuntimeClass *class_AEHelpNote;
extern struct RuntimeClass *create_AEHelpNote(const unsigned short *package);
extern void register_AEHelpNote(void);

extern struct RuntimeClass *class_AEInventoryItem;
extern struct RuntimeClass *create_AEInventoryItem(const unsigned short *package);
extern void register_AEInventoryItem(void);

extern struct RuntimeClass *class_AELaserMicVolume;
extern struct RuntimeClass *create_AELaserMicVolume(const unsigned short *package);
extern void register_AELaserMicVolume(void);

extern struct RuntimeClass *class_AELauncherAttach;
extern struct RuntimeClass *create_AELauncherAttach(const unsigned short *package);
extern void register_AELauncherAttach(void);

extern struct RuntimeClass *class_AELight;
extern struct RuntimeClass *create_AELight(const unsigned short *package);
extern void register_AELight(void);

extern struct RuntimeClass *class_AELightning;
extern struct RuntimeClass *create_AELightning(const unsigned short *package);
extern void register_AELightning(void);

extern struct RuntimeClass *class_AEMachinery;
extern struct RuntimeClass *create_AEMachinery(const unsigned short *package);
extern void register_AEMachinery(void);

extern struct RuntimeClass *class_AEMainGun;
extern struct RuntimeClass *create_AEMainGun(const unsigned short *package);
extern void register_AEMainGun(void);

extern struct RuntimeClass *class_AEMusic;
extern struct RuntimeClass *create_AEMusic(const unsigned short *package);
extern void register_AEMusic(void);

extern struct RuntimeClass *class_AEMuzzleFlash;
extern struct RuntimeClass *create_AEMuzzleFlash(const unsigned short *package);
extern void register_AEMuzzleFlash(void);

extern struct RuntimeClass *class_AENpcZoneInteraction;
extern struct RuntimeClass *create_AENpcZoneInteraction(const unsigned short *package);
extern void register_AENpcZoneInteraction(void);

extern struct RuntimeClass *class_AEObjectiveInteraction;
extern struct RuntimeClass *create_AEObjectiveInteraction(const unsigned short *package);
extern void register_AEObjectiveInteraction(void);

extern struct RuntimeClass *class_AEOcclusionZone;
extern struct RuntimeClass *create_AEOcclusionZone(const unsigned short *package);
extern void register_AEOcclusionZone(void);

extern struct RuntimeClass *class_AEOneHandedWeapon;
extern struct RuntimeClass *create_AEOneHandedWeapon(const unsigned short *package);
extern void register_AEOneHandedWeapon(void);

extern struct RuntimeClass *class_AEPattern;
extern struct RuntimeClass *create_AEPattern(const unsigned short *package);
extern void register_AEPattern(void);

extern struct RuntimeClass *class_AEPawn;
extern struct RuntimeClass *create_AEPawn(const unsigned short *package);
extern void register_AEPawn(void);

extern struct RuntimeClass *class_AEPickupInteraction;
extern struct RuntimeClass *create_AEPickupInteraction(const unsigned short *package);
extern void register_AEPickupInteraction(void);

extern struct RuntimeClass *class_AEPlayerCam;
extern struct RuntimeClass *create_AEPlayerCam(const unsigned short *package);
extern void register_AEPlayerCam(void);

extern struct RuntimeClass *class_AEPlayerController;
extern struct RuntimeClass *create_AEPlayerController(const unsigned short *package);
extern void register_AEPlayerController(void);

extern struct RuntimeClass *class_AEPlayerInfo;
extern struct RuntimeClass *create_AEPlayerInfo(const unsigned short *package);
extern void register_AEPlayerInfo(void);

extern struct RuntimeClass *class_AEPowerBox;
extern struct RuntimeClass *create_AEPowerBox(const unsigned short *package);
extern void register_AEPowerBox(void);

extern struct RuntimeClass *class_AEReflexSightAttach;
extern struct RuntimeClass *create_AEReflexSightAttach(const unsigned short *package);
extern void register_AEReflexSightAttach(void);

extern struct RuntimeClass *class_AESBSlashInteraction;
extern struct RuntimeClass *create_AESBSlashInteraction(const unsigned short *package);
extern void register_AESBSlashInteraction(void);

extern struct RuntimeClass *class_AESRA;
extern struct RuntimeClass *create_AESRA(const unsigned short *package);
extern void register_AESRA(void);

extern struct RuntimeClass *class_AEScopeAttachment;
extern struct RuntimeClass *create_AEScopeAttachment(const unsigned short *package);
extern void register_AEScopeAttachment(void);

extern struct RuntimeClass *class_AESecondaryAmmo;
extern struct RuntimeClass *create_AESecondaryAmmo(const unsigned short *package);
extern void register_AESecondaryAmmo(void);

extern struct RuntimeClass *class_AEShotgunAttach;
extern struct RuntimeClass *create_AEShotgunAttach(const unsigned short *package);
extern void register_AEShotgunAttach(void);

extern struct RuntimeClass *class_AESniperAttach;
extern struct RuntimeClass *create_AESniperAttach(const unsigned short *package);
extern void register_AESniperAttach(void);

extern struct RuntimeClass *class_AESoundVolume;
extern struct RuntimeClass *create_AESoundVolume(const unsigned short *package);
extern void register_AESoundVolume(void);

extern struct RuntimeClass *class_AESpeaker;
extern struct RuntimeClass *create_AESpeaker(const unsigned short *package);
extern void register_AESpeaker(void);

extern struct RuntimeClass *class_AESpeechDispatcher;
extern struct RuntimeClass *create_AESpeechDispatcher(const unsigned short *package);
extern void register_AESpeechDispatcher(void);

extern struct RuntimeClass *class_AESurroundAmbience;
extern struct RuntimeClass *create_AESurroundAmbience(const unsigned short *package);
extern void register_AESurroundAmbience(void);

extern struct RuntimeClass *class_AETrapMover;
extern struct RuntimeClass *create_AETrapMover(const unsigned short *package);
extern void register_AETrapMover(void);

extern struct RuntimeClass *class_AETwoHandedWeapon;
extern struct RuntimeClass *create_AETwoHandedWeapon(const unsigned short *package);
extern void register_AETwoHandedWeapon(void);

extern struct RuntimeClass *class_AEVolume;
extern struct RuntimeClass *create_AEVolume(const unsigned short *package);
extern void register_AEVolume(void);

extern struct RuntimeClass *class_AEVolumeTrigger;
extern struct RuntimeClass *create_AEVolumeTrigger(const unsigned short *package);
extern void register_AEVolumeTrigger(void);

extern struct RuntimeClass *class_AEWallHit;
extern struct RuntimeClass *create_AEWallHit(const unsigned short *package);
extern void register_AEWallHit(void);

extern struct RuntimeClass *class_AEWeapon;
extern struct RuntimeClass *create_AEWeapon(const unsigned short *package);
extern void register_AEWeapon(void);

extern struct RuntimeClass *class_AEWeaponAttachment;
extern struct RuntimeClass *create_AEWeaponAttachment(const unsigned short *package);
extern void register_AEWeaponAttachment(void);

extern struct RuntimeClass *class_AEZoneInfo;
extern struct RuntimeClass *create_AEZoneInfo(const unsigned short *package);
extern void register_AEZoneInfo(void);

extern struct RuntimeClass *class_AEchelonGameInfo;
extern struct RuntimeClass *create_AEchelonGameInfo(const unsigned short *package);
extern void register_AEchelonGameInfo(void);

extern struct RuntimeClass *class_AEchelonLevelInfo;
extern struct RuntimeClass *create_AEchelonLevelInfo(const unsigned short *package);
extern void register_AEchelonLevelInfo(void);

extern struct RuntimeClass *class_UActionComponent;
extern struct RuntimeClass *create_UActionComponent(const unsigned short *package);
extern void register_UActionComponent(void);

extern struct RuntimeClass *class_UEBarkManager;
extern struct RuntimeClass *create_UEBarkManager(const unsigned short *package);
extern void register_UEBarkManager(void);

extern struct RuntimeClass *class_UECanvas;
extern struct RuntimeClass *create_UECanvas(const unsigned short *package);
extern void register_UECanvas(void);

extern struct RuntimeClass *class_UEEEV;
extern struct RuntimeClass *create_UEEEV(const unsigned short *package);
extern void register_UEEEV(void);

extern struct RuntimeClass *class_UEEmotion;
extern struct RuntimeClass *create_UEEmotion(const unsigned short *package);
extern void register_UEEmotion(void);

extern struct RuntimeClass *class_UEGlobalMissionManager;
extern struct RuntimeClass *create_UEGlobalMissionManager(const unsigned short *package);
extern void register_UEGlobalMissionManager(void);

extern struct RuntimeClass *class_UEGoal;
extern struct RuntimeClass *create_UEGoal(const unsigned short *package);
extern void register_UEGoal(void);

extern struct RuntimeClass *class_UEGoalList;
extern struct RuntimeClass *create_UEGoalList(const unsigned short *package);
extern void register_UEGoalList(void);

extern struct RuntimeClass *class_UEHollywoodManager;
extern struct RuntimeClass *create_UEHollywoodManager(const unsigned short *package);
extern void register_UEHollywoodManager(void);

extern struct RuntimeClass *class_UEInventory;
extern struct RuntimeClass *create_UEInventory(const unsigned short *package);
extern void register_UEInventory(void);

extern struct RuntimeClass *class_UEMissionManager;
extern struct RuntimeClass *create_UEMissionManager(const unsigned short *package);
extern void register_UEMissionManager(void);

extern struct RuntimeClass *class_UERandomSoundEvent;
extern struct RuntimeClass *create_UERandomSoundEvent(const unsigned short *package);
extern void register_UERandomSoundEvent(void);

extern struct RuntimeClass *class_UESRAManager;
extern struct RuntimeClass *create_UESRAManager(const unsigned short *package);
extern void register_UESRAManager(void);

extern struct RuntimeClass *class_UESearchManager;
extern struct RuntimeClass *create_UESearchManager(const unsigned short *package);
extern void register_UESearchManager(void);

extern struct RuntimeClass *class_UETextureManager;
extern struct RuntimeClass *create_UETextureManager(const unsigned short *package);
extern void register_UETextureManager(void);

extern struct RuntimeClass *class_UETrainingData;
extern struct RuntimeClass *create_UETrainingData(const unsigned short *package);
extern void register_UETrainingData(void);

extern struct RuntimeClass *class_UETransitionController;
extern struct RuntimeClass *create_UETransitionController(const unsigned short *package);
extern void register_UETransitionController(void);

extern struct RuntimeClass *class_UEchelonCinInfo;
extern struct RuntimeClass *create_UEchelonCinInfo(const unsigned short *package);
extern void register_UEchelonCinInfo(void);

extern struct RuntimeClass *class_UExplosionComponent;
extern struct RuntimeClass *create_UExplosionComponent(const unsigned short *package);
extern void register_UExplosionComponent(void);

extern struct RuntimeClass *class_ABaseCivilian;
extern struct RuntimeClass *create_ABaseCivilian(const unsigned short *package);
extern void register_ABaseCivilian(void);

extern struct RuntimeClass *class_ABasePattern;
extern struct RuntimeClass *create_ABasePattern(const unsigned short *package);
extern void register_ABasePattern(void);

extern struct RuntimeClass *class_ABaseSoldier;
extern struct RuntimeClass *create_ABaseSoldier(const unsigned short *package);
extern void register_ABaseSoldier(void);

extern struct RuntimeClass *class_ABaseUAV;
extern struct RuntimeClass *create_ABaseUAV(const unsigned short *package);
extern void register_ABaseUAV(void);

extern struct RuntimeClass *class_AESRAElectrostatic;
extern struct RuntimeClass *create_AESRAElectrostatic(const unsigned short *package);
extern void register_AESRAElectrostatic(void);

extern struct RuntimeClass *class_AESRAKickable;
extern struct RuntimeClass *create_AESRAKickable(const unsigned short *package);
extern void register_AESRAKickable(void);

extern struct RuntimeClass *class_AESRAPickable;
extern struct RuntimeClass *create_AESRAPickable(const unsigned short *package);
extern void register_AESRAPickable(void);

extern struct RuntimeClass *class_AEAlarmLight;
extern struct RuntimeClass *create_AEAlarmLight(const unsigned short *package);
extern void register_AEAlarmLight(void);

extern struct RuntimeClass *class_AEAnimatedObject;
extern struct RuntimeClass *create_AEAnimatedObject(const unsigned short *package);
extern void register_AEAnimatedObject(void);

extern struct RuntimeClass *class_AEBaseCam;
extern struct RuntimeClass *create_AEBaseCam(const unsigned short *package);
extern void register_AEBaseCam(void);

extern struct RuntimeClass *class_AEBaseTurret;
extern struct RuntimeClass *create_AEBaseTurret(const unsigned short *package);
extern void register_AEBaseTurret(void);

extern struct RuntimeClass *class_AEBed;
extern struct RuntimeClass *create_AEBed(const unsigned short *package);
extern void register_AEBed(void);

extern struct RuntimeClass *class_AECar;
extern struct RuntimeClass *create_AECar(const unsigned short *package);
extern void register_AECar(void);

extern struct RuntimeClass *class_AECeilingCamera;
extern struct RuntimeClass *create_AECeilingCamera(const unsigned short *package);
extern void register_AECeilingCamera(void);

extern struct RuntimeClass *class_AEChair;
extern struct RuntimeClass *create_AEChair(const unsigned short *package);
extern void register_AEChair(void);

extern struct RuntimeClass *class_AEChargeInteraction;
extern struct RuntimeClass *create_AEChargeInteraction(const unsigned short *package);
extern void register_AEChargeInteraction(void);

extern struct RuntimeClass *class_AECommInteraction;
extern struct RuntimeClass *create_AECommInteraction(const unsigned short *package);
extern void register_AECommInteraction(void);

extern struct RuntimeClass *class_AEComputerIntHckCoop;
extern struct RuntimeClass *create_AEComputerIntHckCoop(const unsigned short *package);
extern void register_AEComputerIntHckCoop(void);

extern struct RuntimeClass *class_AEComputerInteraction;
extern struct RuntimeClass *create_AEComputerInteraction(const unsigned short *package);
extern void register_AEComputerInteraction(void);

extern struct RuntimeClass *class_AEComputerKbrd;
extern struct RuntimeClass *create_AEComputerKbrd(const unsigned short *package);
extern void register_AEComputerKbrd(void);

extern struct RuntimeClass *class_AEComputerSystem;
extern struct RuntimeClass *create_AEComputerSystem(const unsigned short *package);
extern void register_AEComputerSystem(void);

extern struct RuntimeClass *class_AEConveyor;
extern struct RuntimeClass *create_AEConveyor(const unsigned short *package);
extern void register_AEConveyor(void);

extern struct RuntimeClass *class_AECoopRetinalScannerInt;
extern struct RuntimeClass *create_AECoopRetinalScannerInt(const unsigned short *package);
extern void register_AECoopRetinalScannerInt(void);

extern struct RuntimeClass *class_AECraneController;
extern struct RuntimeClass *create_AECraneController(const unsigned short *package);
extern void register_AECraneController(void);

extern struct RuntimeClass *class_AECraneControllerStick;
extern struct RuntimeClass *create_AECraneControllerStick(const unsigned short *package);
extern void register_AECraneControllerStick(void);

extern struct RuntimeClass *class_AECraneInteraction;
extern struct RuntimeClass *create_AECraneInteraction(const unsigned short *package);
extern void register_AECraneInteraction(void);

extern struct RuntimeClass *class_AECruiseMissile;
extern struct RuntimeClass *create_AECruiseMissile(const unsigned short *package);
extern void register_AECruiseMissile(void);

extern struct RuntimeClass *class_AECruiseMissileHead;
extern struct RuntimeClass *create_AECruiseMissileHead(const unsigned short *package);
extern void register_AECruiseMissileHead(void);

extern struct RuntimeClass *class_AECryoBloodVial;
extern struct RuntimeClass *create_AECryoBloodVial(const unsigned short *package);
extern void register_AECryoBloodVial(void);

extern struct RuntimeClass *class_AECryoTank;
extern struct RuntimeClass *create_AECryoTank(const unsigned short *package);
extern void register_AECryoTank(void);

extern struct RuntimeClass *class_AECryoTankInteraction;
extern struct RuntimeClass *create_AECryoTankInteraction(const unsigned short *package);
extern void register_AECryoTankInteraction(void);

extern struct RuntimeClass *class_AECryoTankSide;
extern struct RuntimeClass *create_AECryoTankSide(const unsigned short *package);
extern void register_AECryoTankSide(void);

extern struct RuntimeClass *class_AEDetonator;
extern struct RuntimeClass *create_AEDetonator(const unsigned short *package);
extern void register_AEDetonator(void);

extern struct RuntimeClass *class_AEDetonatorInteraction;
extern struct RuntimeClass *create_AEDetonatorInteraction(const unsigned short *package);
extern void register_AEDetonatorInteraction(void);

extern struct RuntimeClass *class_AEDoorInteraction;
extern struct RuntimeClass *create_AEDoorInteraction(const unsigned short *package);
extern void register_AEDoorInteraction(void);

extern struct RuntimeClass *class_AEDualLock;
extern struct RuntimeClass *create_AEDualLock(const unsigned short *package);
extern void register_AEDualLock(void);

extern struct RuntimeClass *class_AEElectroChromaticGlass;
extern struct RuntimeClass *create_AEElectroChromaticGlass(const unsigned short *package);
extern void register_AEElectroChromaticGlass(void);

extern struct RuntimeClass *class_AEElectroChromaticTrigger;
extern struct RuntimeClass *create_AEElectroChromaticTrigger(const unsigned short *package);
extern void register_AEElectroChromaticTrigger(void);

extern struct RuntimeClass *class_AEElevatorButton;
extern struct RuntimeClass *create_AEElevatorButton(const unsigned short *package);
extern void register_AEElevatorButton(void);

extern struct RuntimeClass *class_AEElevatorInteraction;
extern struct RuntimeClass *create_AEElevatorInteraction(const unsigned short *package);
extern void register_AEElevatorInteraction(void);

extern struct RuntimeClass *class_AEElevatorPanel;
extern struct RuntimeClass *create_AEElevatorPanel(const unsigned short *package);
extern void register_AEElevatorPanel(void);

extern struct RuntimeClass *class_AEEmergencyLight;
extern struct RuntimeClass *create_AEEmergencyLight(const unsigned short *package);
extern void register_AEEmergencyLight(void);

extern struct RuntimeClass *class_AEFireDoor;
extern struct RuntimeClass *create_AEFireDoor(const unsigned short *package);
extern void register_AEFireDoor(void);

extern struct RuntimeClass *class_AEFireVolume;
extern struct RuntimeClass *create_AEFireVolume(const unsigned short *package);
extern void register_AEFireVolume(void);

extern struct RuntimeClass *class_AEFlare;
extern struct RuntimeClass *create_AEFlare(const unsigned short *package);
extern void register_AEFlare(void);

extern struct RuntimeClass *class_AEFlashGrenade;
extern struct RuntimeClass *create_AEFlashGrenade(const unsigned short *package);
extern void register_AEFlashGrenade(void);

extern struct RuntimeClass *class_AEFragGrenade;
extern struct RuntimeClass *create_AEFragGrenade(const unsigned short *package);
extern void register_AEFragGrenade(void);

extern struct RuntimeClass *class_AEGameplayObjectDisplay;
extern struct RuntimeClass *create_AEGameplayObjectDisplay(const unsigned short *package);
extern void register_AEGameplayObjectDisplay(void);

extern struct RuntimeClass *class_AEGameplayObjectPickup;
extern struct RuntimeClass *create_AEGameplayObjectPickup(const unsigned short *package);
extern void register_AEGameplayObjectPickup(void);

extern struct RuntimeClass *class_AEGazGrenade;
extern struct RuntimeClass *create_AEGazGrenade(const unsigned short *package);
extern void register_AEGazGrenade(void);

extern struct RuntimeClass *class_AEGenerator;
extern struct RuntimeClass *create_AEGenerator(const unsigned short *package);
extern void register_AEGenerator(void);

extern struct RuntimeClass *class_AEGeneratorInteraction;
extern struct RuntimeClass *create_AEGeneratorInteraction(const unsigned short *package);
extern void register_AEGeneratorInteraction(void);

extern struct RuntimeClass *class_AEGlass;
extern struct RuntimeClass *create_AEGlass(const unsigned short *package);
extern void register_AEGlass(void);

extern struct RuntimeClass *class_AEHackingInteraction;
extern struct RuntimeClass *create_AEHackingInteraction(const unsigned short *package);
extern void register_AEHackingInteraction(void);

extern struct RuntimeClass *class_AEHandCuffs;
extern struct RuntimeClass *create_AEHandCuffs(const unsigned short *package);
extern void register_AEHandCuffs(void);

extern struct RuntimeClass *class_AEHandCuffsInteraction;
extern struct RuntimeClass *create_AEHandCuffsInteraction(const unsigned short *package);
extern void register_AEHandCuffsInteraction(void);

extern struct RuntimeClass *class_AEHelicopter;
extern struct RuntimeClass *create_AEHelicopter(const unsigned short *package);
extern void register_AEHelicopter(void);

extern struct RuntimeClass *class_AEIFVTank;
extern struct RuntimeClass *create_AEIFVTank(const unsigned short *package);
extern void register_AEIFVTank(void);

extern struct RuntimeClass *class_AEIRSensor;
extern struct RuntimeClass *create_AEIRSensor(const unsigned short *package);
extern void register_AEIRSensor(void);

extern struct RuntimeClass *class_AEKeyButton;
extern struct RuntimeClass *create_AEKeyButton(const unsigned short *package);
extern void register_AEKeyButton(void);

extern struct RuntimeClass *class_AEKeyPad;
extern struct RuntimeClass *create_AEKeyPad(const unsigned short *package);
extern void register_AEKeyPad(void);

extern struct RuntimeClass *class_AEKeyPadInteraction;
extern struct RuntimeClass *create_AEKeyPadInteraction(const unsigned short *package);
extern void register_AEKeyPadInteraction(void);

extern struct RuntimeClass *class_AEKeyPadInteractionHanged;
extern struct RuntimeClass *create_AEKeyPadInteractionHanged(const unsigned short *package);
extern void register_AEKeyPadInteractionHanged(void);

extern struct RuntimeClass *class_AEKnob;
extern struct RuntimeClass *create_AEKnob(const unsigned short *package);
extern void register_AEKnob(void);

extern struct RuntimeClass *class_AEMedKit;
extern struct RuntimeClass *create_AEMedKit(const unsigned short *package);
extern void register_AEMedKit(void);

extern struct RuntimeClass *class_AEMedKitInteraction;
extern struct RuntimeClass *create_AEMedKitInteraction(const unsigned short *package);
extern void register_AEMedKitInteraction(void);

extern struct RuntimeClass *class_AEMissileInteraction;
extern struct RuntimeClass *create_AEMissileInteraction(const unsigned short *package);
extern void register_AEMissileInteraction(void);

extern struct RuntimeClass *class_AEMobileTurret;
extern struct RuntimeClass *create_AEMobileTurret(const unsigned short *package);
extern void register_AEMobileTurret(void);

extern struct RuntimeClass *class_AEMope;
extern struct RuntimeClass *create_AEMope(const unsigned short *package);
extern void register_AEMope(void);

extern struct RuntimeClass *class_AEMotionSensor;
extern struct RuntimeClass *create_AEMotionSensor(const unsigned short *package);
extern void register_AEMotionSensor(void);

extern struct RuntimeClass *class_AEPickLockInteraction;
extern struct RuntimeClass *create_AEPickLockInteraction(const unsigned short *package);
extern void register_AEPickLockInteraction(void);

extern struct RuntimeClass *class_AEPickLockSystem;
extern struct RuntimeClass *create_AEPickLockSystem(const unsigned short *package);
extern void register_AEPickLockSystem(void);

extern struct RuntimeClass *class_AEPlaceableCharge;
extern struct RuntimeClass *create_AEPlaceableCharge(const unsigned short *package);
extern void register_AEPlaceableCharge(void);

extern struct RuntimeClass *class_AEPopObjectInteraction;
extern struct RuntimeClass *create_AEPopObjectInteraction(const unsigned short *package);
extern void register_AEPopObjectInteraction(void);

extern struct RuntimeClass *class_AEProjectorScreen;
extern struct RuntimeClass *create_AEProjectorScreen(const unsigned short *package);
extern void register_AEProjectorScreen(void);

extern struct RuntimeClass *class_AEPuddle;
extern struct RuntimeClass *create_AEPuddle(const unsigned short *package);
extern void register_AEPuddle(void);

extern struct RuntimeClass *class_AERetinalScanner;
extern struct RuntimeClass *create_AERetinalScanner(const unsigned short *package);
extern void register_AERetinalScanner(void);

extern struct RuntimeClass *class_AERetinalScannerInteraction;
extern struct RuntimeClass *create_AERetinalScannerInteraction(const unsigned short *package);
extern void register_AERetinalScannerInteraction(void);

extern struct RuntimeClass *class_AERingAirfoilRound;
extern struct RuntimeClass *create_AERingAirfoilRound(const unsigned short *package);
extern void register_AERingAirfoilRound(void);

extern struct RuntimeClass *class_AESBChainActor;
extern struct RuntimeClass *create_AESBChainActor(const unsigned short *package);
extern void register_AESBChainActor(void);

extern struct RuntimeClass *class_AESBCustomActor;
extern struct RuntimeClass *create_AESBCustomActor(const unsigned short *package);
extern void register_AESBCustomActor(void);

extern struct RuntimeClass *class_AESBPatchActor;
extern struct RuntimeClass *create_AESBPatchActor(const unsigned short *package);
extern void register_AESBPatchActor(void);

extern struct RuntimeClass *class_AESBRopeActor;
extern struct RuntimeClass *create_AESBRopeActor(const unsigned short *package);
extern void register_AESBRopeActor(void);

extern struct RuntimeClass *class_AESBRopeClimbActor;
extern struct RuntimeClass *create_AESBRopeClimbActor(const unsigned short *package);
extern void register_AESBRopeClimbActor(void);

extern struct RuntimeClass *class_AESBStripDoorActor;
extern struct RuntimeClass *create_AESBStripDoorActor(const unsigned short *package);
extern void register_AESBStripDoorActor(void);

extern struct RuntimeClass *class_AEScalingActor;
extern struct RuntimeClass *create_AEScalingActor(const unsigned short *package);
extern void register_AEScalingActor(void);

extern struct RuntimeClass *class_AESensor;
extern struct RuntimeClass *create_AESensor(const unsigned short *package);
extern void register_AESensor(void);

extern struct RuntimeClass *class_AEShoulderChargeInteraction;
extern struct RuntimeClass *create_AEShoulderChargeInteraction(const unsigned short *package);
extern void register_AEShoulderChargeInteraction(void);

extern struct RuntimeClass *class_AEShutterInteraction;
extern struct RuntimeClass *create_AEShutterInteraction(const unsigned short *package);
extern void register_AEShutterInteraction(void);

extern struct RuntimeClass *class_AESlidingDoor;
extern struct RuntimeClass *create_AESlidingDoor(const unsigned short *package);
extern void register_AESlidingDoor(void);

extern struct RuntimeClass *class_AESlidingDoorInteraction;
extern struct RuntimeClass *create_AESlidingDoorInteraction(const unsigned short *package);
extern void register_AESlidingDoorInteraction(void);

extern struct RuntimeClass *class_AESmokeGrenade;
extern struct RuntimeClass *create_AESmokeGrenade(const unsigned short *package);
extern void register_AESmokeGrenade(void);

extern struct RuntimeClass *class_AESprinkler;
extern struct RuntimeClass *create_AESprinkler(const unsigned short *package);
extern void register_AESprinkler(void);

extern struct RuntimeClass *class_AEStickyCamera;
extern struct RuntimeClass *create_AEStickyCamera(const unsigned short *package);
extern void register_AEStickyCamera(void);

extern struct RuntimeClass *class_AEStickyShocker;
extern struct RuntimeClass *create_AEStickyShocker(const unsigned short *package);
extern void register_AEStickyShocker(void);

extern struct RuntimeClass *class_AESwingingDoor;
extern struct RuntimeClass *create_AESwingingDoor(const unsigned short *package);
extern void register_AESwingingDoor(void);

extern struct RuntimeClass *class_AESwitchObject;
extern struct RuntimeClass *create_AESwitchObject(const unsigned short *package);
extern void register_AESwitchObject(void);

extern struct RuntimeClass *class_AETelemetricDevice;
extern struct RuntimeClass *create_AETelemetricDevice(const unsigned short *package);
extern void register_AETelemetricDevice(void);

extern struct RuntimeClass *class_AETelemetricLockInteraction;
extern struct RuntimeClass *create_AETelemetricLockInteraction(const unsigned short *package);
extern void register_AETelemetricLockInteraction(void);

extern struct RuntimeClass *class_AETracer;
extern struct RuntimeClass *create_AETracer(const unsigned short *package);
extern void register_AETracer(void);

extern struct RuntimeClass *class_AETrapInteraction;
extern struct RuntimeClass *create_AETrapInteraction(const unsigned short *package);
extern void register_AETrapInteraction(void);

extern struct RuntimeClass *class_AETurret;
extern struct RuntimeClass *create_AETurret(const unsigned short *package);
extern void register_AETurret(void);

extern struct RuntimeClass *class_AETurretConsole;
extern struct RuntimeClass *create_AETurretConsole(const unsigned short *package);
extern void register_AETurretConsole(void);

extern struct RuntimeClass *class_AETurretInteraction;
extern struct RuntimeClass *create_AETurretInteraction(const unsigned short *package);
extern void register_AETurretInteraction(void);

extern struct RuntimeClass *class_AEUAVDrone;
extern struct RuntimeClass *create_AEUAVDrone(const unsigned short *package);
extern void register_AEUAVDrone(void);

extern struct RuntimeClass *class_AEVentInteraction;
extern struct RuntimeClass *create_AEVentInteraction(const unsigned short *package);
extern void register_AEVentInteraction(void);

extern struct RuntimeClass *class_AEWallMine;
extern struct RuntimeClass *create_AEWallMine(const unsigned short *package);
extern void register_AEWallMine(void);

extern struct RuntimeClass *class_AEvent;
extern struct RuntimeClass *create_AEvent(const unsigned short *package);
extern void register_AEvent(void);

extern struct RuntimeClass *class_UComputerAccessComponent;
extern struct RuntimeClass *create_UComputerAccessComponent(const unsigned short *package);
extern void register_UComputerAccessComponent(void);

extern struct RuntimeClass *class_UComputerEmail;
extern struct RuntimeClass *create_UComputerEmail(const unsigned short *package);
extern void register_UComputerEmail(void);

extern struct RuntimeClass *class_UComputerFile;
extern struct RuntimeClass *create_UComputerFile(const unsigned short *package);
extern void register_UComputerFile(void);

extern struct RuntimeClass *class_UComputerImage;
extern struct RuntimeClass *create_UComputerImage(const unsigned short *package);
extern void register_UComputerImage(void);

extern struct RuntimeClass *class_UComputerMusic;
extern struct RuntimeClass *create_UComputerMusic(const unsigned short *package);
extern void register_UComputerMusic(void);

extern struct RuntimeClass *class_UComputerObjectControl;
extern struct RuntimeClass *create_UComputerObjectControl(const unsigned short *package);
extern void register_UComputerObjectControl(void);

extern struct RuntimeClass *class_UComputerTrigger;
extern struct RuntimeClass *create_UComputerTrigger(const unsigned short *package);
extern void register_UComputerTrigger(void);

extern struct RuntimeClass *class_UComputerUpload;
extern struct RuntimeClass *create_UComputerUpload(const unsigned short *package);
extern void register_UComputerUpload(void);

extern struct RuntimeClass *class_UESBChain;
extern struct RuntimeClass *create_UESBChain(const unsigned short *package);
extern void register_UESBChain(void);

extern struct RuntimeClass *class_UESBCustom;
extern struct RuntimeClass *create_UESBCustom(const unsigned short *package);
extern void register_UESBCustom(void);

extern struct RuntimeClass *class_UESBPatch;
extern struct RuntimeClass *create_UESBPatch(const unsigned short *package);
extern void register_UESBPatch(void);

extern struct RuntimeClass *class_UESBRope;
extern struct RuntimeClass *create_UESBRope(const unsigned short *package);
extern void register_UESBRope(void);

extern struct RuntimeClass *class_UESBRopeClimb;
extern struct RuntimeClass *create_UESBRopeClimb(const unsigned short *package);
extern void register_UESBRopeClimb(void);

extern struct RuntimeClass *class_UESBStripDoor;
extern struct RuntimeClass *create_UESBStripDoor(const unsigned short *package);
extern void register_UESBStripDoor(void);

extern struct RuntimeClass *class_USCMagmaInteractionMPGame;
extern struct RuntimeClass *create_USCMagmaInteractionMPGame(const unsigned short *package);
extern void register_USCMagmaInteractionMPGame(void);

extern struct RuntimeClass *class_USCMagmaInteractionPREGame;
extern struct RuntimeClass *create_USCMagmaInteractionPREGame(const unsigned short *package);
extern void register_USCMagmaInteractionPREGame(void);

extern struct RuntimeClass *class_USCMagmaInteractionSPGame;
extern struct RuntimeClass *create_USCMagmaInteractionSPGame(const unsigned short *package);
extern void register_USCMagmaInteractionSPGame(void);

extern struct RuntimeClass *class_AAIController;
extern struct RuntimeClass *create_AAIController(const unsigned short *package);
extern void register_AAIController(void);

extern struct RuntimeClass *class_AActor;
extern struct RuntimeClass *create_AActor(const unsigned short *package);
extern void register_AActor(void);

extern struct RuntimeClass *class_AAntiPortalActor;
extern struct RuntimeClass *create_AAntiPortalActor(const unsigned short *package);
extern void register_AAntiPortalActor(void);

extern struct RuntimeClass *class_ABrush;
extern struct RuntimeClass *create_ABrush(const unsigned short *package);
extern void register_ABrush(void);

extern struct RuntimeClass *class_ACamera;
extern struct RuntimeClass *create_ACamera(const unsigned short *package);
extern void register_ACamera(void);

extern struct RuntimeClass *class_ACollisionMeshActor;
extern struct RuntimeClass *create_ACollisionMeshActor(const unsigned short *package);
extern void register_ACollisionMeshActor(void);

extern struct RuntimeClass *class_AController;
extern struct RuntimeClass *create_AController(const unsigned short *package);
extern void register_AController(void);

extern struct RuntimeClass *class_ACubemapSampleInfo;
extern struct RuntimeClass *create_ACubemapSampleInfo(const unsigned short *package);
extern void register_ACubemapSampleInfo(void);

extern struct RuntimeClass *class_ADefaultPhysicsVolume;
extern struct RuntimeClass *create_ADefaultPhysicsVolume(const unsigned short *package);
extern void register_ADefaultPhysicsVolume(void);

extern struct RuntimeClass *class_AEAIVolume;
extern struct RuntimeClass *create_AEAIVolume(const unsigned short *package);
extern void register_AEAIVolume(void);

extern struct RuntimeClass *class_AEAIZone;
extern struct RuntimeClass *create_AEAIZone(const unsigned short *package);
extern void register_AEAIZone(void);

extern struct RuntimeClass *class_AECoopInteractObject;
extern struct RuntimeClass *create_AECoopInteractObject(const unsigned short *package);
extern void register_AECoopInteractObject(void);

extern struct RuntimeClass *class_AEGameplayColl;
extern struct RuntimeClass *create_AEGameplayColl(const unsigned short *package);
extern void register_AEGameplayColl(void);

extern struct RuntimeClass *class_AEHkBallAndSocketConstraint;
extern struct RuntimeClass *create_AEHkBallAndSocketConstraint(const unsigned short *package);
extern void register_AEHkBallAndSocketConstraint(void);

extern struct RuntimeClass *class_AEHkConstraint;
extern struct RuntimeClass *create_AEHkConstraint(const unsigned short *package);
extern void register_AEHkConstraint(void);

extern struct RuntimeClass *class_AEHkHingeConstraint;
extern struct RuntimeClass *create_AEHkHingeConstraint(const unsigned short *package);
extern void register_AEHkHingeConstraint(void);

extern struct RuntimeClass *class_AEHkMotor;
extern struct RuntimeClass *create_AEHkMotor(const unsigned short *package);
extern void register_AEHkMotor(void);

extern struct RuntimeClass *class_AEHkPrismaticConstraint;
extern struct RuntimeClass *create_AEHkPrismaticConstraint(const unsigned short *package);
extern void register_AEHkPrismaticConstraint(void);

extern struct RuntimeClass *class_AEHkStiffSpringConstraint;
extern struct RuntimeClass *create_AEHkStiffSpringConstraint(const unsigned short *package);
extern void register_AEHkStiffSpringConstraint(void);

extern struct RuntimeClass *class_AEHkSystem;
extern struct RuntimeClass *create_AEHkSystem(const unsigned short *package);
extern void register_AEHkSystem(void);

extern struct RuntimeClass *class_AEInfoPoint;
extern struct RuntimeClass *create_AEInfoPoint(const unsigned short *package);
extern void register_AEInfoPoint(void);

extern struct RuntimeClass *class_AEInteractObject;
extern struct RuntimeClass *create_AEInteractObject(const unsigned short *package);
extern void register_AEInteractObject(void);

extern struct RuntimeClass *class_AEInteractiveWaterInfo;
extern struct RuntimeClass *create_AEInteractiveWaterInfo(const unsigned short *package);
extern void register_AEInteractiveWaterInfo(void);

extern struct RuntimeClass *class_AEOceanInfo;
extern struct RuntimeClass *create_AEOceanInfo(const unsigned short *package);
extern void register_AEOceanInfo(void);

extern struct RuntimeClass *class_AEOceanWaterInfo;
extern struct RuntimeClass *create_AEOceanWaterInfo(const unsigned short *package);
extern void register_AEOceanWaterInfo(void);

extern struct RuntimeClass *class_AERainVolume;
extern struct RuntimeClass *create_AERainVolume(const unsigned short *package);
extern void register_AERainVolume(void);

extern struct RuntimeClass *class_AERopeActor;
extern struct RuntimeClass *create_AERopeActor(const unsigned short *package);
extern void register_AERopeActor(void);

extern struct RuntimeClass *class_AESoftBodyActor;
extern struct RuntimeClass *create_AESoftBodyActor(const unsigned short *package);
extern void register_AESoftBodyActor(void);

extern struct RuntimeClass *class_AEVariable;
extern struct RuntimeClass *create_AEVariable(const unsigned short *package);
extern void register_AEVariable(void);

extern struct RuntimeClass *class_AEVirtualWaterPlane;
extern struct RuntimeClass *create_AEVirtualWaterPlane(const unsigned short *package);
extern void register_AEVirtualWaterPlane(void);

extern struct RuntimeClass *class_AEmitter;
extern struct RuntimeClass *create_AEmitter(const unsigned short *package);
extern void register_AEmitter(void);

extern struct RuntimeClass *class_AGameInfo;
extern struct RuntimeClass *create_AGameInfo(const unsigned short *package);
extern void register_AGameInfo(void);

extern struct RuntimeClass *class_AHUD;
extern struct RuntimeClass *create_AHUD(const unsigned short *package);
extern void register_AHUD(void);

extern struct RuntimeClass *class_AInfo;
extern struct RuntimeClass *create_AInfo(const unsigned short *package);
extern void register_AInfo(void);

extern struct RuntimeClass *class_AKeypoint;
extern struct RuntimeClass *create_AKeypoint(const unsigned short *package);
extern void register_AKeypoint(void);

extern struct RuntimeClass *class_ALevelInfo;
extern struct RuntimeClass *create_ALevelInfo(const unsigned short *package);
extern void register_ALevelInfo(void);

extern struct RuntimeClass *class_ALight;
extern struct RuntimeClass *create_ALight(const unsigned short *package);
extern void register_ALight(void);

extern struct RuntimeClass *class_AMover;
extern struct RuntimeClass *create_AMover(const unsigned short *package);
extern void register_AMover(void);

extern struct RuntimeClass *class_ANavMeshActor;
extern struct RuntimeClass *create_ANavMeshActor(const unsigned short *package);
extern void register_ANavMeshActor(void);

extern struct RuntimeClass *class_ANavigationPoint;
extern struct RuntimeClass *create_ANavigationPoint(const unsigned short *package);
extern void register_ANavigationPoint(void);

extern struct RuntimeClass *class_ANote;
extern struct RuntimeClass *create_ANote(const unsigned short *package);
extern void register_ANote(void);

extern struct RuntimeClass *class_APathNode;
extern struct RuntimeClass *create_APathNode(const unsigned short *package);
extern void register_APathNode(void);

extern struct RuntimeClass *class_APawn;
extern struct RuntimeClass *create_APawn(const unsigned short *package);
extern void register_APawn(void);

extern struct RuntimeClass *class_APhysicsVolume;
extern struct RuntimeClass *create_APhysicsVolume(const unsigned short *package);
extern void register_APhysicsVolume(void);

extern struct RuntimeClass *class_APlayerController;
extern struct RuntimeClass *create_APlayerController(const unsigned short *package);
extern void register_APlayerController(void);

extern struct RuntimeClass *class_APlayerStart;
extern struct RuntimeClass *create_APlayerStart(const unsigned short *package);
extern void register_APlayerStart(void);

extern struct RuntimeClass *class_AProjector;
extern struct RuntimeClass *create_AProjector(const unsigned short *package);
extern void register_AProjector(void);

extern struct RuntimeClass *class_AReflectionReferInfo;
extern struct RuntimeClass *create_AReflectionReferInfo(const unsigned short *package);
extern void register_AReflectionReferInfo(void);

extern struct RuntimeClass *class_AScout;
extern struct RuntimeClass *create_AScout(const unsigned short *package);
extern void register_AScout(void);

extern struct RuntimeClass *class_ASkyZoneInfo;
extern struct RuntimeClass *create_ASkyZoneInfo(const unsigned short *package);
extern void register_ASkyZoneInfo(void);

extern struct RuntimeClass *class_ASpecialVolume;
extern struct RuntimeClass *create_ASpecialVolume(const unsigned short *package);
extern void register_ASpecialVolume(void);

extern struct RuntimeClass *class_AStaticMeshActor;
extern struct RuntimeClass *create_AStaticMeshActor(const unsigned short *package);
extern void register_AStaticMeshActor(void);

extern struct RuntimeClass *class_ATerrainInfo;
extern struct RuntimeClass *create_ATerrainInfo(const unsigned short *package);
extern void register_ATerrainInfo(void);

extern struct RuntimeClass *class_ATrigger;
extern struct RuntimeClass *create_ATrigger(const unsigned short *package);
extern void register_ATrigger(void);

extern struct RuntimeClass *class_ATriggers;
extern struct RuntimeClass *create_ATriggers(const unsigned short *package);
extern void register_ATriggers(void);

extern struct RuntimeClass *class_AVolume;
extern struct RuntimeClass *create_AVolume(const unsigned short *package);
extern void register_AVolume(void);

extern struct RuntimeClass *class_AWindEmitter;
extern struct RuntimeClass *create_AWindEmitter(const unsigned short *package);
extern void register_AWindEmitter(void);

extern struct RuntimeClass *class_AZoneInfo;
extern struct RuntimeClass *create_AZoneInfo(const unsigned short *package);
extern void register_AZoneInfo(void);

extern struct RuntimeClass *class_PatchTemplate;
extern struct RuntimeClass *create_PatchTemplate(const unsigned short *package);
extern void register_PatchTemplate(void);

extern struct RuntimeClass *class_UAnimInfo;
extern struct RuntimeClass *create_UAnimInfo(const unsigned short *package);
extern void register_UAnimInfo(void);

extern struct RuntimeClass *class_UAnimNotify;
extern struct RuntimeClass *create_UAnimNotify(const unsigned short *package);
extern void register_UAnimNotify(void);

extern struct RuntimeClass *class_UAnimNotify_Script;
extern struct RuntimeClass *create_UAnimNotify_Script(const unsigned short *package);
extern void register_UAnimNotify_Script(void);

extern struct RuntimeClass *class_UAnimNotify_Sound;
extern struct RuntimeClass *create_UAnimNotify_Sound(const unsigned short *package);
extern void register_UAnimNotify_Sound(void);

extern struct RuntimeClass *class_UAnimation;
extern struct RuntimeClass *create_UAnimation(const unsigned short *package);
extern void register_UAnimation(void);

extern struct RuntimeClass *class_UAudioSubsystem;
extern struct RuntimeClass *create_UAudioSubsystem(const unsigned short *package);
extern void register_UAudioSubsystem(void);

extern struct RuntimeClass *class_UBeamEmitter;
extern struct RuntimeClass *create_UBeamEmitter(const unsigned short *package);
extern void register_UBeamEmitter(void);

extern struct RuntimeClass *class_UBitmapMaterial;
extern struct RuntimeClass *create_UBitmapMaterial(const unsigned short *package);
extern void register_UBitmapMaterial(void);

extern struct RuntimeClass *class_UCanvas;
extern struct RuntimeClass *create_UCanvas(const unsigned short *package);
extern void register_UCanvas(void);

extern struct RuntimeClass *class_UCheatManager;
extern struct RuntimeClass *create_UCheatManager(const unsigned short *package);
extern void register_UCheatManager(void);

extern struct RuntimeClass *class_UCleanerShader;
extern struct RuntimeClass *create_UCleanerShader(const unsigned short *package);
extern void register_UCleanerShader(void);

extern struct RuntimeClass *class_UClient;
extern struct RuntimeClass *create_UClient(const unsigned short *package);
extern void register_UClient(void);

extern struct RuntimeClass *class_UColorModifier;
extern struct RuntimeClass *create_UColorModifier(const unsigned short *package);
extern void register_UColorModifier(void);

extern struct RuntimeClass *class_UCombiner;
extern struct RuntimeClass *create_UCombiner(const unsigned short *package);
extern void register_UCombiner(void);

extern struct RuntimeClass *class_UConsole;
extern struct RuntimeClass *create_UConsole(const unsigned short *package);
extern void register_UConsole(void);

extern struct RuntimeClass *class_UConstantColor;
extern struct RuntimeClass *create_UConstantColor(const unsigned short *package);
extern void register_UConstantColor(void);

extern struct RuntimeClass *class_UConstantMaterial;
extern struct RuntimeClass *create_UConstantMaterial(const unsigned short *package);
extern void register_UConstantMaterial(void);

extern struct RuntimeClass *class_UConvexVolume;
extern struct RuntimeClass *create_UConvexVolume(const unsigned short *package);
extern void register_UConvexVolume(void);

extern struct RuntimeClass *class_UCubemap;
extern struct RuntimeClass *create_UCubemap(const unsigned short *package);
extern void register_UCubemap(void);

extern struct RuntimeClass *class_UDecalTextureCollection;
extern struct RuntimeClass *create_UDecalTextureCollection(const unsigned short *package);
extern void register_UDecalTextureCollection(void);

extern struct RuntimeClass *class_UEAdInfoObject;
extern struct RuntimeClass *create_UEAdInfoObject(const unsigned short *package);
extern void register_UEAdInfoObject(void);

extern struct RuntimeClass *class_UECinInfo;
extern struct RuntimeClass *create_UECinInfo(const unsigned short *package);
extern void register_UECinInfo(void);

extern struct RuntimeClass *class_UEGlow;
extern struct RuntimeClass *create_UEGlow(const unsigned short *package);
extern void register_UEGlow(void);

extern struct RuntimeClass *class_UEHkObject;
extern struct RuntimeClass *create_UEHkObject(const unsigned short *package);
extern void register_UEHkObject(void);

extern struct RuntimeClass *class_UEHkRigidBody;
extern struct RuntimeClass *create_UEHkRigidBody(const unsigned short *package);
extern void register_UEHkRigidBody(void);

extern struct RuntimeClass *class_UEHkSkeletalSystem;
extern struct RuntimeClass *create_UEHkSkeletalSystem(const unsigned short *package);
extern void register_UEHkSkeletalSystem(void);

extern struct RuntimeClass *class_UEInteractionManager;
extern struct RuntimeClass *create_UEInteractionManager(const unsigned short *package);
extern void register_UEInteractionManager(void);

extern struct RuntimeClass *class_UEListNode;
extern struct RuntimeClass *create_UEListNode(const unsigned short *package);
extern void register_UEListNode(void);

extern struct RuntimeClass *class_UENavMesh;
extern struct RuntimeClass *create_UENavMesh(const unsigned short *package);
extern void register_UENavMesh(void);

extern struct RuntimeClass *class_UEOceanPrimitive;
extern struct RuntimeClass *create_UEOceanPrimitive(const unsigned short *package);
extern void register_UEOceanPrimitive(void);

extern struct RuntimeClass *class_UEPCGameOptions;
extern struct RuntimeClass *create_UEPCGameOptions(const unsigned short *package);
extern void register_UEPCGameOptions(void);

extern struct RuntimeClass *class_UEPatrolInfo;
extern struct RuntimeClass *create_UEPatrolInfo(const unsigned short *package);
extern void register_UEPatrolInfo(void);

extern struct RuntimeClass *class_UEPixelShader;
extern struct RuntimeClass *create_UEPixelShader(const unsigned short *package);
extern void register_UEPixelShader(void);

extern struct RuntimeClass *class_UERainMaterial;
extern struct RuntimeClass *create_UERainMaterial(const unsigned short *package);
extern void register_UERainMaterial(void);

extern struct RuntimeClass *class_UERainPrimitive;
extern struct RuntimeClass *create_UERainPrimitive(const unsigned short *package);
extern void register_UERainPrimitive(void);

extern struct RuntimeClass *class_UERope;
extern struct RuntimeClass *create_UERope(const unsigned short *package);
extern void register_UERope(void);

extern struct RuntimeClass *class_UERumble;
extern struct RuntimeClass *create_UERumble(const unsigned short *package);
extern void register_UERumble(void);

extern struct RuntimeClass *class_UESList;
extern struct RuntimeClass *create_UESList(const unsigned short *package);
extern void register_UESList(void);

extern struct RuntimeClass *class_UESoftBody;
extern struct RuntimeClass *create_UESoftBody(const unsigned short *package);
extern void register_UESoftBody(void);

extern struct RuntimeClass *class_UEVirtualWaterPrimitive;
extern struct RuntimeClass *create_UEVirtualWaterPrimitive(const unsigned short *package);
extern void register_UEVirtualWaterPrimitive(void);

extern struct RuntimeClass *class_UEWaterPatch;
extern struct RuntimeClass *create_UEWaterPatch(const unsigned short *package);
extern void register_UEWaterPatch(void);

extern struct RuntimeClass *class_UEWaterPrimitive;
extern struct RuntimeClass *create_UEWaterPrimitive(const unsigned short *package);
extern void register_UEWaterPrimitive(void);

extern struct RuntimeClass *class_UEWaterWaveSource;
extern struct RuntimeClass *create_UEWaterWaveSource(const unsigned short *package);
extern void register_UEWaterWaveSource(void);

extern struct RuntimeClass *class_UEchelonEnums;
extern struct RuntimeClass *create_UEchelonEnums(const unsigned short *package);
extern void register_UEchelonEnums(void);

extern struct RuntimeClass *class_UEngine;
extern struct RuntimeClass *create_UEngine(const unsigned short *package);
extern void register_UEngine(void);

extern struct RuntimeClass *class_UFadeColor;
extern struct RuntimeClass *create_UFadeColor(const unsigned short *package);
extern void register_UFadeColor(void);

extern struct RuntimeClass *class_UFinalBlend;
extern struct RuntimeClass *create_UFinalBlend(const unsigned short *package);
extern void register_UFinalBlend(void);

extern struct RuntimeClass *class_UFont;
extern struct RuntimeClass *create_UFont(const unsigned short *package);
extern void register_UFont(void);

extern struct RuntimeClass *class_UGameEngine;
extern struct RuntimeClass *create_UGameEngine(const unsigned short *package);
extern void register_UGameEngine(void);

extern struct RuntimeClass *class_UGlobalInteractionManager;
extern struct RuntimeClass *create_UGlobalInteractionManager(const unsigned short *package);
extern void register_UGlobalInteractionManager(void);

extern struct RuntimeClass *class_UGlobalTempObjects;
extern struct RuntimeClass *create_UGlobalTempObjects(const unsigned short *package);
extern void register_UGlobalTempObjects(void);

extern struct RuntimeClass *class_UHkLevelData;
extern struct RuntimeClass *create_UHkLevelData(const unsigned short *package);
extern void register_UHkLevelData(void);

extern struct RuntimeClass *class_UIndexBuffer;
extern struct RuntimeClass *create_UIndexBuffer(const unsigned short *package);
extern void register_UIndexBuffer(void);

extern struct RuntimeClass *class_UInput;
extern struct RuntimeClass *create_UInput(const unsigned short *package);
extern void register_UInput(void);

extern struct RuntimeClass *class_UInteraction;
extern struct RuntimeClass *create_UInteraction(const unsigned short *package);
extern void register_UInteraction(void);

extern struct RuntimeClass *class_UInteractionMaster;
extern struct RuntimeClass *create_UInteractionMaster(const unsigned short *package);
extern void register_UInteractionMaster(void);

extern struct RuntimeClass *class_UInteractions;
extern struct RuntimeClass *create_UInteractions(const unsigned short *package);
extern void register_UInteractions(void);

extern struct RuntimeClass *class_UKeyboardManager;
extern struct RuntimeClass *create_UKeyboardManager(const unsigned short *package);
extern void register_UKeyboardManager(void);

extern struct RuntimeClass *class_ULevel;
extern struct RuntimeClass *create_ULevel(const unsigned short *package);
extern void register_ULevel(void);

extern struct RuntimeClass *class_ULevelBase;
extern struct RuntimeClass *create_ULevelBase(const unsigned short *package);
extern void register_ULevelBase(void);

extern struct RuntimeClass *class_ULevelSummary;
extern struct RuntimeClass *create_ULevelSummary(const unsigned short *package);
extern void register_ULevelSummary(void);

extern struct RuntimeClass *class_ULodMesh;
extern struct RuntimeClass *create_ULodMesh(const unsigned short *package);
extern void register_ULodMesh(void);

extern struct RuntimeClass *class_ULodMeshInstance;
extern struct RuntimeClass *create_ULodMeshInstance(const unsigned short *package);
extern void register_ULodMeshInstance(void);

extern struct RuntimeClass *class_UMaterial;
extern struct RuntimeClass *create_UMaterial(const unsigned short *package);
extern void register_UMaterial(void);

extern struct RuntimeClass *class_UMesh;
extern struct RuntimeClass *create_UMesh(const unsigned short *package);
extern void register_UMesh(void);

extern struct RuntimeClass *class_UMeshAnimation;
extern struct RuntimeClass *create_UMeshAnimation(const unsigned short *package);
extern void register_UMeshAnimation(void);

extern struct RuntimeClass *class_UMeshEmitter;
extern struct RuntimeClass *create_UMeshEmitter(const unsigned short *package);
extern void register_UMeshEmitter(void);

extern struct RuntimeClass *class_UMeshInstance;
extern struct RuntimeClass *create_UMeshInstance(const unsigned short *package);
extern void register_UMeshInstance(void);

extern struct RuntimeClass *class_UModel;
extern struct RuntimeClass *create_UModel(const unsigned short *package);
extern void register_UModel(void);

extern struct RuntimeClass *class_UModifier;
extern struct RuntimeClass *create_UModifier(const unsigned short *package);
extern void register_UModifier(void);

extern struct RuntimeClass *class_UOceanPatchSet;
extern struct RuntimeClass *create_UOceanPatchSet(const unsigned short *package);
extern void register_UOceanPatchSet(void);

extern struct RuntimeClass *class_UPalette;
extern struct RuntimeClass *create_UPalette(const unsigned short *package);
extern void register_UPalette(void);

extern struct RuntimeClass *class_UParticleEmitter;
extern struct RuntimeClass *create_UParticleEmitter(const unsigned short *package);
extern void register_UParticleEmitter(void);

extern struct RuntimeClass *class_UParticleMaterial;
extern struct RuntimeClass *create_UParticleMaterial(const unsigned short *package);
extern void register_UParticleMaterial(void);

extern struct RuntimeClass *class_UPixelShaderMaterial;
extern struct RuntimeClass *create_UPixelShaderMaterial(const unsigned short *package);
extern void register_UPixelShaderMaterial(void);

extern struct RuntimeClass *class_UPlayer;
extern struct RuntimeClass *create_UPlayer(const unsigned short *package);
extern void register_UPlayer(void);

extern struct RuntimeClass *class_UPlayerInput;
extern struct RuntimeClass *create_UPlayerInput(const unsigned short *package);
extern void register_UPlayerInput(void);

extern struct RuntimeClass *class_UPolys;
extern struct RuntimeClass *create_UPolys(const unsigned short *package);
extern void register_UPolys(void);

extern struct RuntimeClass *class_UPrimitive;
extern struct RuntimeClass *create_UPrimitive(const unsigned short *package);
extern void register_UPrimitive(void);

extern struct RuntimeClass *class_UProceduralShader;
extern struct RuntimeClass *create_UProceduralShader(const unsigned short *package);
extern void register_UProceduralShader(void);

extern struct RuntimeClass *class_UProceduralTexture;
extern struct RuntimeClass *create_UProceduralTexture(const unsigned short *package);
extern void register_UProceduralTexture(void);

extern struct RuntimeClass *class_UProjectorPrimitive;
extern struct RuntimeClass *create_UProjectorPrimitive(const unsigned short *package);
extern void register_UProjectorPrimitive(void);

extern struct RuntimeClass *class_UProjectorRenderInfo;
extern struct RuntimeClass *create_UProjectorRenderInfo(const unsigned short *package);
extern void register_UProjectorRenderInfo(void);

extern struct RuntimeClass *class_UProxyBitmapMaterial;
extern struct RuntimeClass *create_UProxyBitmapMaterial(const unsigned short *package);
extern void register_UProxyBitmapMaterial(void);

extern struct RuntimeClass *class_URainDropMaterial;
extern struct RuntimeClass *create_URainDropMaterial(const unsigned short *package);
extern void register_URainDropMaterial(void);

extern struct RuntimeClass *class_URainDropShader;
extern struct RuntimeClass *create_URainDropShader(const unsigned short *package);
extern void register_URainDropShader(void);

extern struct RuntimeClass *class_UReachSpec;
extern struct RuntimeClass *create_UReachSpec(const unsigned short *package);
extern void register_UReachSpec(void);

extern struct RuntimeClass *class_URenderDevice;
extern struct RuntimeClass *create_URenderDevice(const unsigned short *package);
extern void register_URenderDevice(void);

extern struct RuntimeClass *class_URenderResource;
extern struct RuntimeClass *create_URenderResource(const unsigned short *package);
extern void register_URenderResource(void);

extern struct RuntimeClass *class_URenderedMaterial;
extern struct RuntimeClass *create_URenderedMaterial(const unsigned short *package);
extern void register_URenderedMaterial(void);

extern struct RuntimeClass *class_URotationComponent;
extern struct RuntimeClass *create_URotationComponent(const unsigned short *package);
extern void register_URotationComponent(void);

extern struct RuntimeClass *class_USCMagmaInteraction;
extern struct RuntimeClass *create_USCMagmaInteraction(const unsigned short *package);
extern void register_USCMagmaInteraction(void);

extern struct RuntimeClass *class_USCX_ALL_unlit_material;
extern struct RuntimeClass *create_USCX_ALL_unlit_material(const unsigned short *package);
extern void register_USCX_ALL_unlit_material(void);

extern struct RuntimeClass *class_USCX_BSP_basic_material;
extern struct RuntimeClass *create_USCX_BSP_basic_material(const unsigned short *package);
extern void register_USCX_BSP_basic_material(void);

extern struct RuntimeClass *class_USCX_CHR_basic_material;
extern struct RuntimeClass *create_USCX_CHR_basic_material(const unsigned short *package);
extern void register_USCX_CHR_basic_material(void);

extern struct RuntimeClass *class_USCX_STM_basic_material;
extern struct RuntimeClass *create_USCX_STM_basic_material(const unsigned short *package);
extern void register_USCX_STM_basic_material(void);

extern struct RuntimeClass *class_USCX_basic_material;
extern struct RuntimeClass *create_USCX_basic_material(const unsigned short *package);
extern void register_USCX_basic_material(void);

extern struct RuntimeClass *class_USCX_canvas_material;
extern struct RuntimeClass *create_USCX_canvas_material(const unsigned short *package);
extern void register_USCX_canvas_material(void);

extern struct RuntimeClass *class_USCX_combine_material;
extern struct RuntimeClass *create_USCX_combine_material(const unsigned short *package);
extern void register_USCX_combine_material(void);

extern struct RuntimeClass *class_USCX_decal_material;
extern struct RuntimeClass *create_USCX_decal_material(const unsigned short *package);
extern void register_USCX_decal_material(void);

extern struct RuntimeClass *class_USCX_depth_material;
extern struct RuntimeClass *create_USCX_depth_material(const unsigned short *package);
extern void register_USCX_depth_material(void);

extern struct RuntimeClass *class_USCX_eev_material;
extern struct RuntimeClass *create_USCX_eev_material(const unsigned short *package);
extern void register_USCX_eev_material(void);

extern struct RuntimeClass *class_USCX_glass_material;
extern struct RuntimeClass *create_USCX_glass_material(const unsigned short *package);
extern void register_USCX_glass_material(void);

extern struct RuntimeClass *class_USCX_glow_material;
extern struct RuntimeClass *create_USCX_glow_material(const unsigned short *package);
extern void register_USCX_glow_material(void);

extern struct RuntimeClass *class_USCX_gui_material;
extern struct RuntimeClass *create_USCX_gui_material(const unsigned short *package);
extern void register_USCX_gui_material(void);

extern struct RuntimeClass *class_USCX_particle_material;
extern struct RuntimeClass *create_USCX_particle_material(const unsigned short *package);
extern void register_USCX_particle_material(void);

extern struct RuntimeClass *class_USCX_rain_material;
extern struct RuntimeClass *create_USCX_rain_material(const unsigned short *package);
extern void register_USCX_rain_material(void);

extern struct RuntimeClass *class_USCX_reflection_material;
extern struct RuntimeClass *create_USCX_reflection_material(const unsigned short *package);
extern void register_USCX_reflection_material(void);

extern struct RuntimeClass *class_USCX_skin_material;
extern struct RuntimeClass *create_USCX_skin_material(const unsigned short *package);
extern void register_USCX_skin_material(void);

extern struct RuntimeClass *class_USCX_state_material;
extern struct RuntimeClass *create_USCX_state_material(const unsigned short *package);
extern void register_USCX_state_material(void);

extern struct RuntimeClass *class_USCX_thermalvision_material;
extern struct RuntimeClass *create_USCX_thermalvision_material(const unsigned short *package);
extern void register_USCX_thermalvision_material(void);

extern struct RuntimeClass *class_USCX_unlit_material;
extern struct RuntimeClass *create_USCX_unlit_material(const unsigned short *package);
extern void register_USCX_unlit_material(void);

extern struct RuntimeClass *class_USCX_volumetric_material;
extern struct RuntimeClass *create_USCX_volumetric_material(const unsigned short *package);
extern void register_USCX_volumetric_material(void);

extern struct RuntimeClass *class_USCX_water_material;
extern struct RuntimeClass *create_USCX_water_material(const unsigned short *package);
extern void register_USCX_water_material(void);

extern struct RuntimeClass *class_USMStreamer;
extern struct RuntimeClass *create_USMStreamer(const unsigned short *package);
extern void register_USMStreamer(void);

extern struct RuntimeClass *class_UServerCommandlet;
extern struct RuntimeClass *create_UServerCommandlet(const unsigned short *package);
extern void register_UServerCommandlet(void);

extern struct RuntimeClass *class_UShader;
extern struct RuntimeClass *create_UShader(const unsigned short *package);
extern void register_UShader(void);

extern struct RuntimeClass *class_USkeletalMesh;
extern struct RuntimeClass *create_USkeletalMesh(const unsigned short *package);
extern void register_USkeletalMesh(void);

extern struct RuntimeClass *class_USkeletalMeshInstance;
extern struct RuntimeClass *create_USkeletalMeshInstance(const unsigned short *package);
extern void register_USkeletalMeshInstance(void);

extern struct RuntimeClass *class_USound;
extern struct RuntimeClass *create_USound(const unsigned short *package);
extern void register_USound(void);

extern struct RuntimeClass *class_USparkEmitter;
extern struct RuntimeClass *create_USparkEmitter(const unsigned short *package);
extern void register_USparkEmitter(void);

extern struct RuntimeClass *class_USpriteEmitter;
extern struct RuntimeClass *create_USpriteEmitter(const unsigned short *package);
extern void register_USpriteEmitter(void);

extern struct RuntimeClass *class_UStaticMesh;
extern struct RuntimeClass *create_UStaticMesh(const unsigned short *package);
extern void register_UStaticMesh(void);

extern struct RuntimeClass *class_UStaticMeshInstance;
extern struct RuntimeClass *create_UStaticMeshInstance(const unsigned short *package);
extern void register_UStaticMeshInstance(void);

extern struct RuntimeClass *class_UStreamer;
extern struct RuntimeClass *create_UStreamer(const unsigned short *package);
extern void register_UStreamer(void);

extern struct RuntimeClass *class_UTerrainPrimitive;
extern struct RuntimeClass *create_UTerrainPrimitive(const unsigned short *package);
extern void register_UTerrainPrimitive(void);

extern struct RuntimeClass *class_UTerrainSector;
extern struct RuntimeClass *create_UTerrainSector(const unsigned short *package);
extern void register_UTerrainSector(void);

extern struct RuntimeClass *class_UTexCoordMaterial;
extern struct RuntimeClass *create_UTexCoordMaterial(const unsigned short *package);
extern void register_UTexCoordMaterial(void);

extern struct RuntimeClass *class_UTexEnvMap;
extern struct RuntimeClass *create_UTexEnvMap(const unsigned short *package);
extern void register_UTexEnvMap(void);

extern struct RuntimeClass *class_UTexMatrix;
extern struct RuntimeClass *create_UTexMatrix(const unsigned short *package);
extern void register_UTexMatrix(void);

extern struct RuntimeClass *class_UTexModifier;
extern struct RuntimeClass *create_UTexModifier(const unsigned short *package);
extern void register_UTexModifier(void);

extern struct RuntimeClass *class_UTexOscillator;
extern struct RuntimeClass *create_UTexOscillator(const unsigned short *package);
extern void register_UTexOscillator(void);

extern struct RuntimeClass *class_UTexPanner;
extern struct RuntimeClass *create_UTexPanner(const unsigned short *package);
extern void register_UTexPanner(void);

extern struct RuntimeClass *class_UTexRotator;
extern struct RuntimeClass *create_UTexRotator(const unsigned short *package);
extern void register_UTexRotator(void);

extern struct RuntimeClass *class_UTexScaler;
extern struct RuntimeClass *create_UTexScaler(const unsigned short *package);
extern void register_UTexScaler(void);

extern struct RuntimeClass *class_UTexTransform;
extern struct RuntimeClass *create_UTexTransform(const unsigned short *package);
extern void register_UTexTransform(void);

extern struct RuntimeClass *class_UTexTransformBasic;
extern struct RuntimeClass *create_UTexTransformBasic(const unsigned short *package);
extern void register_UTexTransformBasic(void);

extern struct RuntimeClass *class_UTexTransformOscillator;
extern struct RuntimeClass *create_UTexTransformOscillator(const unsigned short *package);
extern void register_UTexTransformOscillator(void);

extern struct RuntimeClass *class_UTexture;
extern struct RuntimeClass *create_UTexture(const unsigned short *package);
extern void register_UTexture(void);

extern struct RuntimeClass *class_UTextureFactory;
extern struct RuntimeClass *create_UTextureFactory(const unsigned short *package);
extern void register_UTextureFactory(void);

extern struct RuntimeClass *class_UTextureStreamer;
extern struct RuntimeClass *create_UTextureStreamer(const unsigned short *package);
extern void register_UTextureStreamer(void);

extern struct RuntimeClass *class_UUbiAccountManager;
extern struct RuntimeClass *create_UUbiAccountManager(const unsigned short *package);
extern void register_UUbiAccountManager(void);

extern struct RuntimeClass *class_UVertexBuffer;
extern struct RuntimeClass *create_UVertexBuffer(const unsigned short *package);
extern void register_UVertexBuffer(void);

extern struct RuntimeClass *class_UVertexStreamBase;
extern struct RuntimeClass *create_UVertexStreamBase(const unsigned short *package);
extern void register_UVertexStreamBase(void);

extern struct RuntimeClass *class_UVertexStreamCOLOR;
extern struct RuntimeClass *create_UVertexStreamCOLOR(const unsigned short *package);
extern void register_UVertexStreamCOLOR(void);

extern struct RuntimeClass *class_UVertexStreamPosNormTex;
extern struct RuntimeClass *create_UVertexStreamPosNormTex(const unsigned short *package);
extern void register_UVertexStreamPosNormTex(void);

extern struct RuntimeClass *class_UVertexStreamUV;
extern struct RuntimeClass *create_UVertexStreamUV(const unsigned short *package);
extern void register_UVertexStreamUV(void);

extern struct RuntimeClass *class_UVertexStreamVECTOR;
extern struct RuntimeClass *create_UVertexStreamVECTOR(const unsigned short *package);
extern void register_UVertexStreamVECTOR(void);

extern struct RuntimeClass *class_UViewport;
extern struct RuntimeClass *create_UViewport(const unsigned short *package);
extern void register_UViewport(void);

extern struct RuntimeClass *class_UVolumeTexture;
extern struct RuntimeClass *create_UVolumeTexture(const unsigned short *package);
extern void register_UVolumeTexture(void);

extern struct RuntimeClass *class_UWeather;
extern struct RuntimeClass *create_UWeather(const unsigned short *package);
extern void register_UWeather(void);

extern struct RuntimeClass *class_UWindMaker;
extern struct RuntimeClass *create_UWindMaker(const unsigned short *package);
extern void register_UWindMaker(void);

extern struct RuntimeClass *class_UnNetZ;
extern struct RuntimeClass *create_UnNetZ(const unsigned short *package);
extern void register_UnNetZ(void);

extern struct RuntimeClass *class_UWinJoystickMgr;
extern struct RuntimeClass *create_UWinJoystickMgr(const unsigned short *package);
extern void register_UWinJoystickMgr(void);

extern struct RuntimeClass *class_UWindowsClient;
extern struct RuntimeClass *create_UWindowsClient(const unsigned short *package);
extern void register_UWindowsClient(void);

extern struct RuntimeClass *class_UWindowsViewport;
extern struct RuntimeClass *create_UWindowsViewport(const unsigned short *package);
extern void register_UWindowsViewport(void);

extern struct RuntimeClass *class_UWindowManager;
extern struct RuntimeClass *create_UWindowManager(const unsigned short *package);
extern void register_UWindowManager(void);

extern struct RuntimeClass *class_Descriptor_08F4A0;
extern struct RuntimeClass *create_Descriptor_08F4A0(const unsigned short *package);
extern void register_Descriptor_08F4A0(void);

extern struct RuntimeClass *class_Descriptor_097FB0;
extern struct RuntimeClass *create_Descriptor_097FB0(const unsigned short *package);
extern void register_Descriptor_097FB0(void);

extern struct RuntimeClass *class_Descriptor_0980C0;
extern struct RuntimeClass *create_Descriptor_0980C0(const unsigned short *package);
extern void register_Descriptor_0980C0(void);

extern struct RuntimeClass *class_Descriptor_0A1570;
extern struct RuntimeClass *create_Descriptor_0A1570(const unsigned short *package);
extern void register_Descriptor_0A1570(void);

extern struct RuntimeClass *class_Descriptor_0C6390;
extern struct RuntimeClass *create_Descriptor_0C6390(const unsigned short *package);
extern void register_Descriptor_0C6390(void);

extern struct RuntimeClass *class_Descriptor_16E710;
extern struct RuntimeClass *create_Descriptor_16E710(const unsigned short *package);
extern void register_Descriptor_16E710(void);

extern struct RuntimeClass *class_Descriptor_2EEE50;
extern struct RuntimeClass *create_Descriptor_2EEE50(const unsigned short *package);
extern void register_Descriptor_2EEE50(void);

extern struct RuntimeClass *class_Descriptor_3E7ED0;
extern struct RuntimeClass *create_Descriptor_3E7ED0(const unsigned short *package);
extern void register_Descriptor_3E7ED0(void);
