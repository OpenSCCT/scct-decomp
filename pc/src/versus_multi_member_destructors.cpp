// Unreal Engine 2 class destructors from the Steam Versus payload that destroy several members.
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
// Releases a member's storage; members that share a helper share one declaration.
template<unsigned Helper> void __stdcall ReleaseMember(void *member);

// Parent classes whose own destructors are matched elsewhere or remain open.
class AInfo : public UObject { public: virtual ~AInfo(); };
class AReplicationInfo : public UObject { public: virtual ~AReplicationInfo(); };
class ASBasicGamePlayObject : public UObject { public: virtual ~ASBasicGamePlayObject(); };
class ASGadget : public UObject { public: virtual ~ASGadget(); };
class ASInteractObject : public UObject { public: virtual ~ASInteractObject(); };
class ASStickyCam : public UObject { public: virtual ~ASStickyCam(); };
class ASWeapon : public UObject { public: virtual ~ASWeapon(); };
class ATeamInfo : public UObject { public: virtual ~ATeamInfo(); };
class UGUI : public UObject { public: virtual ~UGUI(); };
class UGUIButton : public UObject { public: virtual ~UGUIButton(); };
class UGUIList : public UObject { public: virtual ~UGUIList(); };
class UGUIMultiComponent : public UObject { public: virtual ~UGUIMultiComponent(); };
class UState : public UObject { public: virtual ~UState(); };

class UClass : public UState {
public:
    struct Member94 { ~Member94(); };
    struct MemberA0 { ~MemberA0(); };
    struct MemberAC { ~MemberAC(); };
    struct MemberC8 { ~MemberC8(); };
    struct MemberD4 { ~MemberD4(); };
    struct MemberE0 { ~MemberE0(); };
    struct MemberEC { ~MemberEC(); };
    struct MemberF8 { ~MemberF8(); };
    virtual ~UClass();
    InheritedData<0x94 - sizeof(UState)> UStateData;
    Member94 Field94;
    unsigned char Data95[0xb];
    MemberA0 FieldA0;
    unsigned char DataA1[0xb];
    MemberAC FieldAC;
    unsigned char DataAD[0x1b];
    MemberC8 FieldC8;
    unsigned char DataC9[0xb];
    MemberD4 FieldD4;
    unsigned char DataD5[0xb];
    MemberE0 FieldE0;
    unsigned char DataE1[0xb];
    MemberEC FieldEC;
    unsigned char DataED[0xb];
    MemberF8 FieldF8;
};
UClass::~UClass() { ConditionalDestroy(); }

class AActor : public UObject {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member1C4 { ~Member1C4(); };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    struct Member1E8 { ~Member1E8(); };
    virtual ~AActor();
    InheritedData<0x138 - sizeof(UObject)> UObjectData;
    Released0 Field138;
    unsigned char Data139[0x8b];
    Member1C4 Field1C4;
    unsigned char Data1C5[0x17];
    Released1 Field1DC;
    unsigned char Data1DD[0xb];
    Member1E8 Field1E8;
    unsigned char Data1E9[0x1b];
    Released1 Field204;
    unsigned char Data205[0xb];
    Released1 Field210;
    unsigned char Data211[0xb];
    Released1 Field21C;
    unsigned char Data21D[0x23];
    Released1 Field240;
    unsigned char Data241[0x1b];
    Released1 Field25C;
};
AActor::~AActor() { ConditionalDestroy(); }

class UPersistentData : public UObject {
public:
    struct Member28 { ~Member28(); };
    struct Member34 { ~Member34(); };
    struct Member4C { ~Member4C(); };
    virtual ~UPersistentData();
    InheritedData<0x28 - sizeof(UObject)> UObjectData;
    Member28 Field28;
    unsigned char Data29[0xb];
    Member34 Field34;
    unsigned char Data35[0x17];
    Member4C Field4C;
};
UPersistentData::~UPersistentData() { ConditionalDestroy(); }

class UParticleEmitter : public UObject {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member15C { ~Member15C(); };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    struct Released2 { ~Released2() { Released2 *self = this; ReleaseMember<2>(self); } };
    struct Released3 { ~Released3() { Released3 *self = this; ReleaseMember<3>(self); } };
    struct Released4 { ~Released4() { Released4 *self = this; ReleaseMember<4>(self); } };
    struct Released5 { ~Released5() { Released5 *self = this; ReleaseMember<5>(self); } };
    virtual ~UParticleEmitter();
    InheritedData<0x120 - sizeof(UObject)> UObjectData;
    Released0 Field120;
    unsigned char Data121[0x3b];
    Member15C Field15C;
    unsigned char Data15D[0xc7];
    Released1 Field224;
    unsigned char Data225[0x63];
    Released2 Field288;
    unsigned char Data289[0x23];
    Released3 Field2AC;
    unsigned char Data2AD[0x3f];
    Released4 Field2EC;
    unsigned char Data2ED[0x97];
    Released1 Field384;
    unsigned char Data385[0x1f];
    Released5 Field3A4;
};
UParticleEmitter::~UParticleEmitter() { ConditionalDestroy(); }

class AInventory : public AActor {
public:
    struct Member2F8 { ~Member2F8(); };
    struct Member304 { ~Member304(); };
    struct Member310 { ~Member310(); };
    struct Member31C { ~Member31C(); };
    virtual ~AInventory();
    InheritedData<0x2f8 - sizeof(AActor)> AActorData;
    Member2F8 Field2F8;
    unsigned char Data2F9[0xb];
    Member304 Field304;
    unsigned char Data305[0xb];
    Member310 Field310;
    unsigned char Data311[0xb];
    Member31C Field31C;
};
AInventory::~AInventory() { ConditionalDestroy(); }

class ASLogManager : public AActor {
public:
    struct Member2F8 { ~Member2F8(); };
    struct Member304 { ~Member304(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member324 { ~Member324(); };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    struct Member33C { ~Member33C(); };
    struct Released2 { ~Released2() { Released2 *self = this; ReleaseMember<2>(self); } };
    virtual ~ASLogManager();
    InheritedData<0x2f8 - sizeof(AActor)> AActorData;
    Member2F8 Field2F8;
    unsigned char Data2F9[0xb];
    Member304 Field304;
    unsigned char Data305[0x13];
    Released0 Field318;
    unsigned char Data319[0xb];
    Member324 Field324;
    unsigned char Data325[0xb];
    Released1 Field330;
    unsigned char Data331[0xb];
    Member33C Field33C;
    unsigned char Data33D[0xb];
    Released2 Field348;
};
ASLogManager::~ASLogManager() { ConditionalDestroy(); }

class AESoftBodyActor : public AActor {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    virtual ~AESoftBodyActor();
    InheritedData<0x2fc - sizeof(AActor)> AActorData;
    Released0 Field2FC;
    unsigned char Data2FD[0xb];
    Released0 Field308;
    unsigned char Data309[0xb];
    Released1 Field314;
    unsigned char Data315[0xb];
    Released0 Field320;
};
AESoftBodyActor::~AESoftBodyActor() { ConditionalDestroy(); }

class UTrailEmitter : public UParticleEmitter {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    virtual ~UTrailEmitter();
    InheritedData<0x3f8 - sizeof(UParticleEmitter)> UParticleEmitterData;
    Released0 Field3F8;
    unsigned char Data3F9[0xb];
    Released1 Field404;
};
UTrailEmitter::~UTrailEmitter() { ConditionalDestroy(); }

class UMatchInfo : public UObject {
public:
    struct Member28 { ~Member28(); };
    struct Member34 { ~Member34(); };
    struct Member40 { ~Member40(); };
    struct Member4C { ~Member4C(); };
    struct Member60 { ~Member60(); };
    struct Member6C { ~Member6C(); };
    struct Member78 { ~Member78(); };
    struct Member84 { ~Member84(); };
    virtual ~UMatchInfo();
    InheritedData<0x28 - sizeof(UObject)> UObjectData;
    Member28 Field28;
    unsigned char Data29[0xb];
    Member34 Field34;
    unsigned char Data35[0xb];
    Member40 Field40;
    unsigned char Data41[0xb];
    Member4C Field4C;
    unsigned char Data4D[0x13];
    Member60 Field60;
    unsigned char Data61[0xb];
    Member6C Field6C;
    unsigned char Data6D[0xb];
    Member78 Field78;
    unsigned char Data79[0xb];
    Member84 Field84;
};
UMatchInfo::~UMatchInfo() { ConditionalDestroy(); }

class APawn : public AActor {
public:
    struct Member448 { ~Member448(); };
    struct Member454 { ~Member454(); };
    struct Member490 { ~Member490(); };
    virtual ~APawn();
    InheritedData<0x448 - sizeof(AActor)> AActorData;
    Member448 Field448;
    unsigned char Data449[0xb];
    Member454 Field454;
    unsigned char Data455[0x3b];
    Member490 Field490;
};
APawn::~APawn() { ConditionalDestroy(); }

class AMover : public AActor {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    virtual ~AMover();
    InheritedData<0x438 - sizeof(AActor)> AActorData;
    Released0 Field438;
    unsigned char Data439[0x6f];
    Released1 Field4A8;
};
AMover::~AMover() { ConditionalDestroy(); }

class UBeamEmitter : public UParticleEmitter {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    struct Member4D8 { ~Member4D8(); };
    struct Released2 { ~Released2() { Released2 *self = this; ReleaseMember<2>(self); } };
    virtual ~UBeamEmitter();
    InheritedData<0x3f0 - sizeof(UParticleEmitter)> UParticleEmitterData;
    Released0 Field3F0;
    unsigned char Data3F1[0x57];
    Released1 Field448;
    unsigned char Data449[0xb];
    Released1 Field454;
    unsigned char Data455[0x77];
    Released1 Field4CC;
    unsigned char Data4CD[0xb];
    Member4D8 Field4D8;
    unsigned char Data4D9[0xb];
    Released2 Field4E4;
};
UBeamEmitter::~UBeamEmitter() { ConditionalDestroy(); }

class USound : public UObject {
public:
    struct Member28 { ~Member28(); };
    struct Member48 { ~Member48(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member78 { ~Member78(); };
    virtual ~USound();
    InheritedData<0x28 - sizeof(UObject)> UObjectData;
    Member28 Field28;
    unsigned char Data29[0x1f];
    Member48 Field48;
    unsigned char Data49[0x23];
    Released0 Field6C;
    unsigned char Data6D[0xb];
    Member78 Field78;
};
USound::~USound() { ConditionalDestroy(); }

class ULevelSummary : public UObject {
public:
    struct Member28 { ~Member28(); };
    struct Member34 { ~Member34(); };
    struct Member44 { ~Member44(); };
    virtual ~ULevelSummary();
    InheritedData<0x28 - sizeof(UObject)> UObjectData;
    Member28 Field28;
    unsigned char Data29[0xb];
    Member34 Field34;
    unsigned char Data35[0xf];
    Member44 Field44;
};
ULevelSummary::~ULevelSummary() { ConditionalDestroy(); }

class AGameReplicationInfo : public AReplicationInfo {
public:
    struct Member2F8 { ~Member2F8(); };
    struct Member304 { ~Member304(); };
    struct Member378 { ~Member378(); };
    struct Member384 { ~Member384(); };
    struct Member390 { ~Member390(); };
    struct Member39C { ~Member39C(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    virtual ~AGameReplicationInfo();
    InheritedData<0x2f8 - sizeof(AReplicationInfo)> AReplicationInfoData;
    Member2F8 Field2F8;
    unsigned char Data2F9[0xb];
    Member304 Field304;
    unsigned char Data305[0x73];
    Member378 Field378;
    unsigned char Data379[0xb];
    Member384 Field384;
    unsigned char Data385[0xb];
    Member390 Field390;
    unsigned char Data391[0xb];
    Member39C Field39C;
    unsigned char Data39D[0xf];
    Released0 Field3AC;
};
AGameReplicationInfo::~AGameReplicationInfo() { ConditionalDestroy(); }

class APlayerReplicationInfo : public AReplicationInfo {
public:
    struct Member2F8 { ~Member2F8(); };
    struct Member304 { ~Member304(); };
    struct Member310 { ~Member310(); };
    struct Member31C { ~Member31C(); };
    struct Member328 { ~Member328(); };
    struct Member334 { ~Member334(); };
    struct Member340 { ~Member340(); };
    struct Member34C { ~Member34C(); };
    struct Member358 { ~Member358(); };
    struct Member364 { ~Member364(); };
    struct Member370 { ~Member370(); };
    struct Member37C { ~Member37C(); };
    struct Member388 { ~Member388(); };
    struct Member394 { ~Member394(); };
    struct Member3A0 { ~Member3A0(); };
    struct Member3AC { ~Member3AC(); };
    struct Member3B8 { ~Member3B8(); };
    virtual ~APlayerReplicationInfo();
    InheritedData<0x2f8 - sizeof(AReplicationInfo)> AReplicationInfoData;
    Member2F8 Field2F8;
    unsigned char Data2F9[0xb];
    Member304 Field304;
    unsigned char Data305[0xb];
    Member310 Field310;
    unsigned char Data311[0xb];
    Member31C Field31C;
    unsigned char Data31D[0xb];
    Member328 Field328;
    unsigned char Data329[0xb];
    Member334 Field334;
    unsigned char Data335[0xb];
    Member340 Field340;
    unsigned char Data341[0xb];
    Member34C Field34C;
    unsigned char Data34D[0xb];
    Member358 Field358;
    unsigned char Data359[0xb];
    Member364 Field364;
    unsigned char Data365[0xb];
    Member370 Field370;
    unsigned char Data371[0xb];
    Member37C Field37C;
    unsigned char Data37D[0xb];
    Member388 Field388;
    unsigned char Data389[0xb];
    Member394 Field394;
    unsigned char Data395[0xb];
    Member3A0 Field3A0;
    unsigned char Data3A1[0xb];
    Member3AC Field3AC;
    unsigned char Data3AD[0xb];
    Member3B8 Field3B8;
};
APlayerReplicationInfo::~APlayerReplicationInfo() { ConditionalDestroy(); }

class AMotionTrackingVision : public AActor {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member308 { ~Member308(); };
    virtual ~AMotionTrackingVision();
    InheritedData<0x2f8 - sizeof(AActor)> AActorData;
    Released0 Field2F8;
    unsigned char Data2F9[0xf];
    Member308 Field308;
};
AMotionTrackingVision::~AMotionTrackingVision() { ConditionalDestroy(); }

class AZoneInfo : public AInfo {
public:
    struct Member304 { ~Member304(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    virtual ~AZoneInfo();
    InheritedData<0x304 - sizeof(AInfo)> AInfoData;
    Member304 Field304;
    unsigned char Data305[0x2f];
    Released0 Field334;
};
AZoneInfo::~AZoneInfo() { ConditionalDestroy(); }

class ALevelInfo : public AZoneInfo {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member3E0 { ~Member3E0(); };
    struct Member3EC { ~Member3EC(); };
    struct Member3F8 { ~Member3F8(); };
    struct Member404 { ~Member404(); };
    struct Member41C { ~Member41C(); };
    struct Member428 { ~Member428(); };
    struct Member4AC { ~Member4AC(); };
    struct Member4B8 { ~Member4B8(); };
    struct Member4C4 { ~Member4C4(); };
    struct Member4D0 { ~Member4D0(); };
    struct Member4F8 { ~Member4F8(); };
    struct Member518 { ~Member518(); };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    virtual ~ALevelInfo();
    InheritedData<0x394 - sizeof(AZoneInfo)> AZoneInfoData;
    Released0 Field394;
    unsigned char Data395[0x4b];
    Member3E0 Field3E0;
    unsigned char Data3E1[0xb];
    Member3EC Field3EC;
    unsigned char Data3ED[0xb];
    Member3F8 Field3F8;
    unsigned char Data3F9[0xb];
    Member404 Field404;
    unsigned char Data405[0x17];
    Member41C Field41C;
    unsigned char Data41D[0xb];
    Member428 Field428;
    unsigned char Data429[0x83];
    Member4AC Field4AC;
    unsigned char Data4AD[0xb];
    Member4B8 Field4B8;
    unsigned char Data4B9[0xb];
    Member4C4 Field4C4;
    unsigned char Data4C5[0xb];
    Member4D0 Field4D0;
    unsigned char Data4D1[0x27];
    Member4F8 Field4F8;
    unsigned char Data4F9[0x1f];
    Member518 Field518;
    unsigned char Data519[0x1b];
    Released1 Field534;
    unsigned char Data535[0xb];
    Released1 Field540;
};
ALevelInfo::~ALevelInfo() { ConditionalDestroy(); }

class UGUIComponent : public UGUI {
public:
    struct Member34 { ~Member34(); };
    struct Member40 { ~Member40(); };
    struct Member64 { ~Member64(); };
    virtual ~UGUIComponent();
    InheritedData<0x34 - sizeof(UGUI)> UGUIData;
    Member34 Field34;
    unsigned char Data35[0xb];
    Member40 Field40;
    unsigned char Data41[0x23];
    Member64 Field64;
};
UGUIComponent::~UGUIComponent() { ConditionalDestroy(); }

class UGUIMenuOption : public UGUIMultiComponent {
public:
    struct Member1AC { ~Member1AC(); };
    struct Member1B8 { ~Member1B8(); };
    struct Member1C8 { ~Member1C8(); };
    virtual ~UGUIMenuOption();
    InheritedData<0x1ac - sizeof(UGUIMultiComponent)> UGUIMultiComponentData;
    Member1AC Field1AC;
    unsigned char Data1AD[0xb];
    Member1B8 Field1B8;
    unsigned char Data1B9[0xf];
    Member1C8 Field1C8;
};
UGUIMenuOption::~UGUIMenuOption() { ConditionalDestroy(); }

class UGUIPage : public UGUIMultiComponent {
public:
    struct Member1B8 { ~Member1B8(); };
    struct Member1C4 { ~Member1C4(); };
    struct Member1D0 { ~Member1D0(); };
    struct Member1DC { ~Member1DC(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member280 { ~Member280(); };
    virtual ~UGUIPage();
    InheritedData<0x1b8 - sizeof(UGUIMultiComponent)> UGUIMultiComponentData;
    Member1B8 Field1B8;
    unsigned char Data1B9[0xb];
    Member1C4 Field1C4;
    unsigned char Data1C5[0xb];
    Member1D0 Field1D0;
    unsigned char Data1D1[0xb];
    Member1DC Field1DC;
    unsigned char Data1DD[0x1f];
    Released0 Field1FC;
    unsigned char Data1FD[0x83];
    Member280 Field280;
};
UGUIPage::~UGUIPage() { ConditionalDestroy(); }

class UGUIChatBox : public UGUIMultiComponent {
public:
    struct Member1B4 { ~Member1B4(); };
    struct Member1C0 { ~Member1C0(); };
    struct Member1CC { ~Member1CC(); };
    struct Member1D8 { ~Member1D8(); };
    struct Member1E4 { ~Member1E4(); };
    virtual ~UGUIChatBox();
    InheritedData<0x1b4 - sizeof(UGUIMultiComponent)> UGUIMultiComponentData;
    Member1B4 Field1B4;
    unsigned char Data1B5[0xb];
    Member1C0 Field1C0;
    unsigned char Data1C1[0xb];
    Member1CC Field1CC;
    unsigned char Data1CD[0xb];
    Member1D8 Field1D8;
    unsigned char Data1D9[0xb];
    Member1E4 Field1E4;
};
UGUIChatBox::~UGUIChatBox() { ConditionalDestroy(); }

class UGUIMultiPageLabel : public UGUIComponent {
public:
    struct Member190 { ~Member190(); };
    struct Member19C { ~Member19C(); };
    virtual ~UGUIMultiPageLabel();
    InheritedData<0x190 - sizeof(UGUIComponent)> UGUIComponentData;
    Member190 Field190;
    unsigned char Data191[0xb];
    Member19C Field19C;
};
UGUIMultiPageLabel::~UGUIMultiPageLabel() { ConditionalDestroy(); }

class UGUIProgressBar : public UGUIComponent {
public:
    struct Member1B0 { ~Member1B0(); };
    struct Member1BC { ~Member1BC(); };
    struct Member1C8 { ~Member1C8(); };
    virtual ~UGUIProgressBar();
    InheritedData<0x1b0 - sizeof(UGUIComponent)> UGUIComponentData;
    Member1B0 Field1B0;
    unsigned char Data1B1[0xb];
    Member1BC Field1BC;
    unsigned char Data1BD[0xb];
    Member1C8 Field1C8;
};
UGUIProgressBar::~UGUIProgressBar() { ConditionalDestroy(); }

class UGUIScrollText : public UGUIList {
public:
    struct Member1EC { ~Member1EC(); };
    struct Member1F8 { ~Member1F8(); };
    struct Member21C { ~Member21C(); };
    virtual ~UGUIScrollText();
    InheritedData<0x1ec - sizeof(UGUIList)> UGUIListData;
    Member1EC Field1EC;
    unsigned char Data1ED[0xb];
    Member1F8 Field1F8;
    unsigned char Data1F9[0x23];
    Member21C Field21C;
};
UGUIScrollText::~UGUIScrollText() { ConditionalDestroy(); }

class UGUITabControl : public UGUIMultiComponent {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member1B4 { ~Member1B4(); };
    virtual ~UGUITabControl();
    InheritedData<0x1a4 - sizeof(UGUIMultiComponent)> UGUIMultiComponentData;
    Released0 Field1A4;
    unsigned char Data1A5[0xf];
    Member1B4 Field1B4;
};
UGUITabControl::~UGUITabControl() { ConditionalDestroy(); }

class UGUIEditBox : public UGUIButton {
public:
    struct Member1B0 { ~Member1B0(); };
    struct Member1BC { ~Member1BC(); };
    virtual ~UGUIEditBox();
    InheritedData<0x1b0 - sizeof(UGUIButton)> UGUIButtonData;
    Member1B0 Field1B0;
    unsigned char Data1B1[0xb];
    Member1BC Field1BC;
};
UGUIEditBox::~UGUIEditBox() { ConditionalDestroy(); }

class UGUILabel : public UGUIComponent {
public:
    struct Member190 { ~Member190(); };
    struct Member1AC { ~Member1AC(); };
    virtual ~UGUILabel();
    InheritedData<0x190 - sizeof(UGUIComponent)> UGUIComponentData;
    Member190 Field190;
    unsigned char Data191[0x1b];
    Member1AC Field1AC;
};
UGUILabel::~UGUILabel() { ConditionalDestroy(); }

class UGUIFont : public UGUI {
public:
    struct Member2C { ~Member2C(); };
    struct Member3C { ~Member3C(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    virtual ~UGUIFont();
    InheritedData<0x2c - sizeof(UGUI)> UGUIData;
    Member2C Field2C;
    unsigned char Data2D[0xf];
    Member3C Field3C;
    unsigned char Data3D[0xb];
    Released0 Field48;
};
UGUIFont::~UGUIFont() { ConditionalDestroy(); }

class ASGamePlayObject : public ASBasicGamePlayObject {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    struct Member380 { ~Member380(); };
    virtual ~ASGamePlayObject();
    InheritedData<0x358 - sizeof(ASBasicGamePlayObject)> ASBasicGamePlayObjectData;
    Released0 Field358;
    unsigned char Data359[0xb];
    Released0 Field364;
    unsigned char Data365[0xb];
    Released1 Field370;
    unsigned char Data371[0xf];
    Member380 Field380;
    unsigned char Data381[0xb];
    Released1 Field38C;
};
ASGamePlayObject::~ASGamePlayObject() { ConditionalDestroy(); }

class USMapSettings : public UObject {
public:
    struct Member28 { ~Member28(); };
    struct Member34 { ~Member34(); };
    struct Member40 { ~Member40(); };
    struct Member4C { ~Member4C(); };
    struct Member58 { ~Member58(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    virtual ~USMapSettings();
    InheritedData<0x28 - sizeof(UObject)> UObjectData;
    Member28 Field28;
    unsigned char Data29[0xb];
    Member34 Field34;
    unsigned char Data35[0xb];
    Member40 Field40;
    unsigned char Data41[0xb];
    Member4C Field4C;
    unsigned char Data4D[0xb];
    Member58 Field58;
    unsigned char Data59[0xf];
    Released0 Field68;
    unsigned char Data69[0xb];
    Released1 Field74;
};
USMapSettings::~USMapSettings() { ConditionalDestroy(); }

class ASAnimatedMesh : public AActor {
public:
    struct Member304 { ~Member304(); };
    struct Member310 { ~Member310(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    virtual ~ASAnimatedMesh();
    InheritedData<0x304 - sizeof(AActor)> AActorData;
    Member304 Field304;
    unsigned char Data305[0xb];
    Member310 Field310;
    unsigned char Data311[0xb];
    Released0 Field31C;
};
ASAnimatedMesh::~ASAnimatedMesh() { ConditionalDestroy(); }

class ASMagicEvent : public AActor {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    virtual ~ASMagicEvent();
    InheritedData<0x2f8 - sizeof(AActor)> AActorData;
    Released0 Field2F8;
    unsigned char Data2F9[0xb];
    Released1 Field304;
};
ASMagicEvent::~ASMagicEvent() { ConditionalDestroy(); }

class ASLift : public AMover {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    virtual ~ASLift();
    InheritedData<0x4e8 - sizeof(AMover)> AMoverData;
    Released0 Field4E8;
    unsigned char Data4E9[0xb];
    Released1 Field4F4;
};
ASLift::~ASLift() { ConditionalDestroy(); }

class ASTeamInfo : public ATeamInfo {
public:
    struct Member324 { ~Member324(); };
    struct Member330 { ~Member330(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member348 { ~Member348(); };
    virtual ~ASTeamInfo();
    InheritedData<0x324 - sizeof(ATeamInfo)> ATeamInfoData;
    Member324 Field324;
    unsigned char Data325[0xb];
    Member330 Field330;
    unsigned char Data331[0xb];
    Released0 Field33C;
    unsigned char Data33D[0xb];
    Member348 Field348;
    unsigned char Data349[0xb];
    Released0 Field354;
    unsigned char Data355[0xf];
    Released0 Field364;
};
ASTeamInfo::~ASTeamInfo() { ConditionalDestroy(); }

class USXBoxLiveRef : public UObject {
public:
    struct Member44 { ~Member44(); };
    struct Member50 { ~Member50(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    virtual ~USXBoxLiveRef();
    InheritedData<0x44 - sizeof(UObject)> UObjectData;
    Member44 Field44;
    unsigned char Data45[0xb];
    Member50 Field50;
    unsigned char Data51[0xb];
    Released0 Field5C;
};
USXBoxLiveRef::~USXBoxLiveRef() { ConditionalDestroy(); }

class USPlayerProfile : public UObject {
public:
    struct Member54 { ~Member54(); };
    struct Member60 { ~Member60(); };
    struct Member6C { ~Member6C(); };
    struct MemberD8 { ~MemberD8(); };
    virtual ~USPlayerProfile();
    InheritedData<0x54 - sizeof(UObject)> UObjectData;
    Member54 Field54;
    unsigned char Data55[0xb];
    Member60 Field60;
    unsigned char Data61[0xb];
    Member6C Field6C;
    unsigned char Data6D[0x6b];
    MemberD8 FieldD8;
};
USPlayerProfile::~USPlayerProfile() { ConditionalDestroy(); }

class ASWeaponDefense : public ASWeapon {
public:
    struct Member3BC { ~Member3BC(); };
    struct Member3C8 { ~Member3C8(); };
    struct Member3D4 { ~Member3D4(); };
    virtual ~ASWeaponDefense();
    InheritedData<0x3bc - sizeof(ASWeapon)> ASWeaponData;
    Member3BC Field3BC;
    unsigned char Data3BD[0xb];
    Member3C8 Field3C8;
    unsigned char Data3C9[0xb];
    Member3D4 Field3D4;
};
ASWeaponDefense::~ASWeaponDefense() { ConditionalDestroy(); }

class ASObjective : public AActor {
public:
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Member314 { ~Member314(); };
    struct Member320 { ~Member320(); };
    struct Member32C { ~Member32C(); };
    virtual ~ASObjective();
    InheritedData<0x2f8 - sizeof(AActor)> AActorData;
    Released0 Field2F8;
    unsigned char Data2F9[0xb];
    Released0 Field304;
    unsigned char Data305[0xf];
    Member314 Field314;
    unsigned char Data315[0xb];
    Member320 Field320;
    unsigned char Data321[0xb];
    Member32C Field32C;
};
ASObjective::~ASObjective() { ConditionalDestroy(); }

class ASGadTorcheLaser : public ASGadget {
public:
    struct Member360 { ~Member360(); };
    struct Member36C { ~Member36C(); };
    virtual ~ASGadTorcheLaser();
    InheritedData<0x360 - sizeof(ASGadget)> ASGadgetData;
    Member360 Field360;
    unsigned char Data361[0xb];
    Member36C Field36C;
};
ASGadTorcheLaser::~ASGadTorcheLaser() { ConditionalDestroy(); }

class ASGadTorche : public ASGadget {
public:
    struct Member35C { ~Member35C(); };
    struct Member368 { ~Member368(); };
    virtual ~ASGadTorche();
    InheritedData<0x35c - sizeof(ASGadget)> ASGadgetData;
    Member35C Field35C;
    unsigned char Data35D[0xb];
    Member368 Field368;
};
ASGadTorche::~ASGadTorche() { ConditionalDestroy(); }

class ASAlarm : public AActor {
public:
    struct Member2F8 { ~Member2F8(); };
    struct Released0 { ~Released0() { Released0 *self = this; ReleaseMember<0>(self); } };
    struct Released1 { ~Released1() { Released1 *self = this; ReleaseMember<1>(self); } };
    struct Member31C { ~Member31C(); };
    struct Member328 { ~Member328(); };
    struct Member334 { ~Member334(); };
    virtual ~ASAlarm();
    InheritedData<0x2f8 - sizeof(AActor)> AActorData;
    Member2F8 Field2F8;
    unsigned char Data2F9[0xb];
    Released0 Field304;
    unsigned char Data305[0xb];
    Released1 Field310;
    unsigned char Data311[0xb];
    Member31C Field31C;
    unsigned char Data31D[0xb];
    Member328 Field328;
    unsigned char Data329[0xb];
    Member334 Field334;
};
ASAlarm::~ASAlarm() { ConditionalDestroy(); }

class ASGoggle : public AActor {
public:
    struct Member300 { ~Member300(); };
    struct Member30C { ~Member30C(); };
    struct Member318 { ~Member318(); };
    struct Member324 { ~Member324(); };
    virtual ~ASGoggle();
    InheritedData<0x300 - sizeof(AActor)> AActorData;
    Member300 Field300;
    unsigned char Data301[0xb];
    Member30C Field30C;
    unsigned char Data30D[0xb];
    Member318 Field318;
    unsigned char Data319[0xb];
    Member324 Field324;
};
ASGoggle::~ASGoggle() { ConditionalDestroy(); }

class ASShareObjectInteraction : public ASInteractObject {
public:
    struct Member364 { ~Member364(); };
    struct Member370 { ~Member370(); };
    virtual ~ASShareObjectInteraction();
    InheritedData<0x364 - sizeof(ASInteractObject)> ASInteractObjectData;
    Member364 Field364;
    unsigned char Data365[0xb];
    Member370 Field370;
};
ASShareObjectInteraction::~ASShareObjectInteraction() { ConditionalDestroy(); }

class ASCamNetwork : public ASStickyCam {
public:
    struct Member3C8 { ~Member3C8(); };
    struct Member3D8 { ~Member3D8(); };
    virtual ~ASCamNetwork();
    InheritedData<0x3c8 - sizeof(ASStickyCam)> ASStickyCamData;
    Member3C8 Field3C8;
    unsigned char Data3C9[0xf];
    Member3D8 Field3D8;
};
ASCamNetwork::~ASCamNetwork() { ConditionalDestroy(); }
