// Unreal Engine 2 class destructors from the Steam Versus payload.
// Each class destructor runs UObject::ConditionalDestroy() before its parent's
// destructor, as the engine's DECLARE_CLASS destructor does. Only the members these
// destructors touch are declared; VirtualSlot names stand for engine virtual methods
// whose names this translation unit does not need.
enum { INDEX_NONE = -1 };
enum EObjectFlags { RF_Destroyed = 0x00800000, RF_DebugDestroy = 0x80000000 };

class UObject {
public:
    virtual ~UObject();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    int Index;
    unsigned Reserved[5];
    unsigned ObjectFlags;
    int ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed)) {
            ObjectFlags = (ObjectFlags & ~(RF_DebugDestroy | RF_Destroyed)) | RF_Destroyed;
            Destroy();
            return 1;
        }
        return 0;
    }
};

template<unsigned Size> struct InheritedData { unsigned char Bytes[Size]; };

// Releases a member's storage; each class binds its own helper.
void __stdcall ReleaseMember(void *member);

// Parent classes whose own destructors are matched elsewhere or remain open.
class AActor : public UObject { public: virtual ~AActor(); };
class ABrush : public UObject { public: virtual ~ABrush(); };
class AInfo : public UObject { public: virtual ~AInfo(); };
class AKeypoint : public UObject { public: virtual ~AKeypoint(); };
class ALight : public UObject { public: virtual ~ALight(); };
class APawn : public UObject { public: virtual ~APawn(); };
class AReplicationInfo : public UObject { public: virtual ~AReplicationInfo(); };
class ASGadget : public UObject { public: virtual ~ASGadget(); };
class ASGamePlayObject : public UObject { public: virtual ~ASGamePlayObject(); };
class ASObjective : public UObject { public: virtual ~ASObjective(); };
class ATriggers : public UObject { public: virtual ~ATriggers(); };
class UGUIComponent : public UObject { public: virtual ~UGUIComponent(); };
class UGUIPage : public UObject { public: virtual ~UGUIPage(); };
class UGUIVertList : public UObject { public: virtual ~UGUIVertList(); };
class UInteractions : public UObject { public: virtual ~UInteractions(); };
class UModifier : public UObject { public: virtual ~UModifier(); };
class UParticleEmitter : public UObject { public: virtual ~UParticleEmitter(); };

class UGlobalTempObjects : public UObject {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UGlobalTempObjects();
    InheritedData<0x28 - sizeof(UObject)> UObjectData;
    Member Field28;
};
UGlobalTempObjects::~UGlobalTempObjects() { ConditionalDestroy(); }

class ADecorationList : public AKeypoint {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~ADecorationList();
    InheritedData<0x2f8 - sizeof(AKeypoint)> AKeypointData;
    Member Field2F8;
};
ADecorationList::~ADecorationList() { ConditionalDestroy(); }

class USparkEmitter : public UParticleEmitter {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~USparkEmitter();
    InheritedData<0x400 - sizeof(UParticleEmitter)> UParticleEmitterData;
    Member Field400;
};
USparkEmitter::~USparkEmitter() { ConditionalDestroy(); }

class ASecurity : public AInfo {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~ASecurity();
    InheritedData<0x2fc - sizeof(AInfo)> AInfoData;
    Member Field2FC;
};
ASecurity::~ASecurity() { ConditionalDestroy(); }

class AEmitter : public AActor {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~AEmitter();
    InheritedData<0x2f8 - sizeof(AActor)> AActorData;
    Member Field2F8;
};
AEmitter::~AEmitter() { ConditionalDestroy(); }

class UMaterialSequence : public UModifier {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UMaterialSequence();
    InheritedData<0x50 - sizeof(UModifier)> UModifierData;
    Member Field50;
};
UMaterialSequence::~UMaterialSequence() { ConditionalDestroy(); }

class UMaterialSwitch : public UModifier {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UMaterialSwitch();
    InheritedData<0x54 - sizeof(UModifier)> UModifierData;
    Member Field54;
};
UMaterialSwitch::~UMaterialSwitch() { ConditionalDestroy(); }

class UInteractionMaster : public UInteractions {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UInteractionMaster();
    InheritedData<0x34 - sizeof(UInteractions)> UInteractionsData;
    Member Field34;
};
UInteractionMaster::~UInteractionMaster() { ConditionalDestroy(); }

class UPolys : public UObject {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UPolys();
    InheritedData<0x28 - sizeof(UObject)> UObjectData;
    Member Field28;
};
UPolys::~UPolys() { ConditionalDestroy(); }

class ATeamInfo : public AReplicationInfo {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ATeamInfo();
    InheritedData<0x2f8 - sizeof(AReplicationInfo)> AReplicationInfoData;
    Member Field2F8;
};
ATeamInfo::~ATeamInfo() { ConditionalDestroy(); }

class AVolume : public ABrush {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~AVolume();
    InheritedData<0x35c - sizeof(ABrush)> ABrushData;
    Member Field35C;
};
AVolume::~AVolume() { ConditionalDestroy(); }

class AController : public AActor {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~AController();
    InheritedData<0x374 - sizeof(AActor)> AActorData;
    Member Field374;
};
AController::~AController() { ConditionalDestroy(); }

class ATrigger : public ATriggers {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ATrigger();
    InheritedData<0x2fc - sizeof(ATriggers)> ATriggersData;
    Member Field2FC;
};
ATrigger::~ATrigger() { ConditionalDestroy(); }

class ANote : public AActor {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ANote();
    InheritedData<0x2f8 - sizeof(AActor)> AActorData;
    Member Field2F8;
};
ANote::~ANote() { ConditionalDestroy(); }

class AFileLog : public AInfo {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~AFileLog();
    InheritedData<0x2fc - sizeof(AInfo)> AInfoData;
    Member Field2FC;
};
AFileLog::~AFileLog() { ConditionalDestroy(); }

class UPalette : public UObject {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UPalette();
    InheritedData<0x28 - sizeof(UObject)> UObjectData;
    Member Field28;
};
UPalette::~UPalette() { ConditionalDestroy(); }

class UGUIMultiComponent : public UGUIComponent {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UGUIMultiComponent();
    InheritedData<0x190 - sizeof(UGUIComponent)> UGUIComponentData;
    Member Field190;
};
UGUIMultiComponent::~UGUIMultiComponent() { ConditionalDestroy(); }

class UGUIPageWaitLaunch : public UGUIPage {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~UGUIPageWaitLaunch();
    InheritedData<0x2e0 - sizeof(UGUIPage)> UGUIPageData;
    Member Field2E0;
};
UGUIPageWaitLaunch::~UGUIPageWaitLaunch() { ConditionalDestroy(); }

class UGUIList : public UGUIVertList {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~UGUIList();
    InheritedData<0x1d4 - sizeof(UGUIVertList)> UGUIVertListData;
    Member Field1D4;
};
UGUIList::~UGUIList() { ConditionalDestroy(); }

class UGUISlider : public UGUIComponent {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~UGUISlider();
    InheritedData<0x198 - sizeof(UGUIComponent)> UGUIComponentData;
    Member Field198;
};
UGUISlider::~UGUISlider() { ConditionalDestroy(); }

class UGUITitleBar : public UGUIComponent {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~UGUITitleBar();
    InheritedData<0x190 - sizeof(UGUIComponent)> UGUIComponentData;
    Member Field190;
};
UGUITitleBar::~UGUITitleBar() { ConditionalDestroy(); }

class UGUIComboBox : public UGUIMultiComponent {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~UGUIComboBox();
    InheritedData<0x1ac - sizeof(UGUIMultiComponent)> UGUIMultiComponentData;
    Member Field1AC;
};
UGUIComboBox::~UGUIComboBox() { ConditionalDestroy(); }

class UGUIButton : public UGUIComponent {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~UGUIButton();
    InheritedData<0x194 - sizeof(UGUIComponent)> UGUIComponentData;
    Member Field194;
};
UGUIButton::~UGUIButton() { ConditionalDestroy(); }

class UGUINumericEdit : public UGUIMultiComponent {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~UGUINumericEdit();
    InheritedData<0x1a0 - sizeof(UGUIMultiComponent)> UGUIMultiComponentData;
    Member Field1A0;
};
UGUINumericEdit::~UGUINumericEdit() { ConditionalDestroy(); }

class UGUICheckBox : public UGUIComponent {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~UGUICheckBox();
    InheritedData<0x198 - sizeof(UGUIComponent)> UGUIComponentData;
    Member Field198;
};
UGUICheckBox::~UGUICheckBox() { ConditionalDestroy(); }

class ASInteractObject : public AActor {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASInteractObject();
    InheritedData<0x304 - sizeof(AActor)> AActorData;
    Member Field304;
};
ASInteractObject::~ASInteractObject() { ConditionalDestroy(); }

class ASBasicGamePlayObject : public AActor {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASBasicGamePlayObject();
    InheritedData<0x308 - sizeof(AActor)> AActorData;
    Member Field308;
};
ASBasicGamePlayObject::~ASBasicGamePlayObject() { ConditionalDestroy(); }

class ASObjectiveTrigger : public ASGamePlayObject {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASObjectiveTrigger();
    InheritedData<0x3c4 - sizeof(ASGamePlayObject)> ASGamePlayObjectData;
    Member Field3C4;
};
ASObjectiveTrigger::~ASObjectiveTrigger() { ConditionalDestroy(); }

class ASBombTargetInteraction : public ASInteractObject {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASBombTargetInteraction();
    InheritedData<0x364 - sizeof(ASInteractObject)> ASInteractObjectData;
    Member Field364;
};
ASBombTargetInteraction::~ASBombTargetInteraction() { ConditionalDestroy(); }

class ASVolumetricSensor : public ASBasicGamePlayObject {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~ASVolumetricSensor();
    InheritedData<0x344 - sizeof(ASBasicGamePlayObject)> ASBasicGamePlayObjectData;
    Member Field344;
};
ASVolumetricSensor::~ASVolumetricSensor() { ConditionalDestroy(); }

class ASTriggerLight : public ALight {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~ASTriggerLight();
    InheritedData<0x30c - sizeof(ALight)> ALightData;
    Member Field30C;
};
ASTriggerLight::~ASTriggerLight() { ConditionalDestroy(); }

class ASSpyBulletLauncher : public ASGadget {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASSpyBulletLauncher();
    InheritedData<0x35c - sizeof(ASGadget)> ASGadgetData;
    Member Field35C;
};
ASSpyBulletLauncher::~ASSpyBulletLauncher() { ConditionalDestroy(); }

class ASProjMarqueurSpy : public ASBasicGamePlayObject {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~ASProjMarqueurSpy();
    InheritedData<0x34c - sizeof(ASBasicGamePlayObject)> ASBasicGamePlayObjectData;
    Member Field34C;
};
ASProjMarqueurSpy::~ASProjMarqueurSpy() { ConditionalDestroy(); }

class ASBasePawn : public APawn {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~ASBasePawn();
    InheritedData<0x6c4 - sizeof(APawn)> APawnData;
    Member Field6C4;
};
ASBasePawn::~ASBasePawn() { ConditionalDestroy(); }

class ASMission : public ASObjective {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~ASMission();
    InheritedData<0x35c - sizeof(ASObjective)> ASObjectiveData;
    Member Field35C;
};
ASMission::~ASMission() { ConditionalDestroy(); }

class ASInterrupteur : public ASBasicGamePlayObject {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASInterrupteur();
    InheritedData<0x360 - sizeof(ASBasicGamePlayObject)> ASBasicGamePlayObjectData;
    Member Field360;
};
ASInterrupteur::~ASInterrupteur() { ConditionalDestroy(); }

class ASGPOControl : public AActor {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASGPOControl();
    InheritedData<0x2fc - sizeof(AActor)> AActorData;
    Member Field2FC;
};
ASGPOControl::~ASGPOControl() { ConditionalDestroy(); }

class ASGadStickyCam : public ASGadget {
public:
    struct Member { ~Member() { ReleaseMember(this); } };  // released through a helper
    virtual ~ASGadStickyCam();
    InheritedData<0x358 - sizeof(ASGadget)> ASGadgetData;
    Member Field358;
};
ASGadStickyCam::~ASGadStickyCam() { ConditionalDestroy(); }

class ASComputerInteraction : public ASInteractObject {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASComputerInteraction();
    InheritedData<0x368 - sizeof(ASInteractObject)> ASInteractObjectData;
    Member Field368;
};
ASComputerInteraction::~ASComputerInteraction() { ConditionalDestroy(); }

class ASGadGasMask : public ASGadget {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASGadGasMask();
    InheritedData<0x350 - sizeof(ASGadget)> ASGadgetData;
    Member Field350;
};
ASGadGasMask::~ASGadGasMask() { ConditionalDestroy(); }

class ASGadBackPack : public ASGadget {
public:
    struct Member { ~Member(); };  // destroyed by an out-of-line destructor
    virtual ~ASGadBackPack();
    InheritedData<0x364 - sizeof(ASGadget)> ASGadgetData;
    Member Field364;
};
ASGadBackPack::~ASGadBackPack() { ConditionalDestroy(); }
