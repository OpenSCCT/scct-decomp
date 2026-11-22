// w3_item_0387.cpp -- AActor::SetZone and ALevelInfo::SetZone (Versus)

typedef unsigned char BYTE;
typedef short SWORD;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned __int64 QWORD;
typedef float FLOAT;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef unsigned short TCHAR;

#define INDEX_NONE (-1)

enum EName {
    NAME_None           = 0,
    ENGINE_ActorEntered = 0x141,
    ENGINE_ActorLeaving = 0x142,
    ENGINE_ZoneChange   = 0x143
};

struct FName {
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
};

struct FVector {
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};

struct FPlane : public FVector {
    FLOAT W;
    FLOAT PlaneDot(const FVector &P) const
    {
        return X * P.X + Y * P.Y + Z * P.Z - W;
    }
};

struct FGuid;
struct FFrame;
class UFunction;
class UClass;
class AActor;
class AZoneInfo;
class ALevelInfo;
class ULevel;
class UModel;

struct FPointRegion {
    AZoneInfo *Zone;
    INT        iLeaf;
    BYTE       ZoneNumber;

    FPointRegion() {}
    FPointRegion(AZoneInfo *InLevel)
        : Zone(InLevel), iLeaf(INDEX_NONE), ZoneNumber(0) {}
    FPointRegion(AZoneInfo *InLevel, INT InLeaf, BYTE InZoneNumber)
        : Zone(InLevel), iLeaf(InLeaf), ZoneNumber(InZoneNumber) {}
};

struct FStateFrame {
    BYTE  unk_00[0x1c];
    QWORD ProbeMask;
};

class FUnknown {
public:
    virtual DWORD __stdcall QueryInterface(const FGuid &RefIID, void **InterfacePtr);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

class UObject : public FUnknown {
public:
    virtual ~UObject();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0);
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void Destroy();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();

    INT          Index;
    BYTE         unk_08[0x4];
    FStateFrame *StateFrame;
    BYTE         unk_10[0xc];
    DWORD        ObjectFlags;
    BYTE         unk_20[0x4];
    UClass      *Class;

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0);
    UBOOL IsProbing(INT ProbeIndex) const
    {
        return !StateFrame || (StateFrame->ProbeMask & ((QWORD)1 << ProbeIndex));
    }
};

struct FBspNode {
    FPlane Plane;
    BYTE   unk_10[0x20];
    INT    iChild[2];
    BYTE   unk_38[0x14];
    SWORD  iLeaf[2];
    BYTE   unk_50[0x8];
    BYTE   iZone[2];
    BYTE   NumVertices;
    BYTE   NodeFlags;
};

struct FZoneProperties {
    AZoneInfo *ZoneActor;
    BYTE       unk_04[0xc];
};

template<class T> struct TArray {
    T  *Data;
    INT ArrayNum;
    INT ArrayMax;

    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
    const T &operator()(INT i) const { return Data[i]; }
};

class UModel : public UObject {
public:
    BYTE                    unk_28[0x2c];
    TArray<FBspNode>        Nodes;
    BYTE                    unk_60[0xa4];
    INT                     RootOutside;
    BYTE                    unk_108[0xc];
    TArray<FZoneProperties> Zones;

    AZoneInfo *GetZoneActor(INT iZone) const
    {
        return iZone < Zones.Num() ? Zones(iZone).ZoneActor : 0;
    }
    FPointRegion PointRegion(AZoneInfo *Zone, const FVector &Location) const;
};

class ULevel : public UObject {
public:
    BYTE    unk_28[0x114];
    UModel *Model;
};

class AActor : public UObject {
public:
    virtual ~AActor();
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
    virtual void SetZone(UBOOL bTest, UBOOL bForceRefresh);

    BYTE         unk_28[0x58];
    FVector      Location;
    BYTE         unk_8c[0x114];
    ALevelInfo  *Level;
    ULevel      *XLevel;
    BYTE         unk_1a8[0x4];
    FPointRegion Region;
    BYTE         unk_1b8[0x130];
    BITFIELD     unk_2e8_0 : 15;
    BITFIELD     bDeleteMe : 1;
    BITFIELD     unk_2e8_16 : 16;

    ULevel *GetLevel() const { return XLevel; }
    void eventZoneChange(AZoneInfo *NewZone);
};

class AInfo : public AActor {
public:
    virtual ~AInfo();
};

class AZoneInfo : public AInfo {
public:
    virtual ~AZoneInfo();

    void eventActorEntered(AActor *Other);
    void eventActorLeaving(AActor *Other);
};

class ALevelInfo : public AZoneInfo {
public:
    virtual ~ALevelInfo();
    virtual void SetZone(UBOOL bTest, UBOOL bForceRefresh);
};

// AActor::SetZone -- updates the actor's BSP zone region and fires zone transition events.
void AActor::SetZone(UBOOL bTest, UBOOL bForceRefresh)
{
    if (bDeleteMe)
        return;

    if (bForceRefresh)
        Region = FPointRegion(Level);

    FPointRegion NewRegion = GetLevel()->Model->PointRegion(Level, Location);
    if (NewRegion.Zone != Region.Zone) {
        if (!bTest) {
            Region.Zone->eventActorLeaving(this);
            eventZoneChange(NewRegion.Zone);
        }
        Region = NewRegion;
        if (!bTest)
            Region.Zone->eventActorEntered(this);
    } else {
        Region = NewRegion;
    }
}

// ALevelInfo::SetZone -- keeps LevelInfo's region bound to itself.
void ALevelInfo::SetZone(UBOOL bTest, UBOOL bForceRefresh)
{
    if (bDeleteMe)
        return;

    Region = FPointRegion(Level);
}

// AZoneInfo::eventActorEntered (0x11da40) -- script event dispatched when an actor enters a zone.
void AZoneInfo::eventActorEntered(AActor *Other)
{
    struct { AActor *Other; } Parms;
    if (IsProbing(21)) {
        Parms.Other = Other;
        ProcessEvent(FindFunctionChecked(ENGINE_ActorEntered), &Parms);
    }
}

// AActor::eventZoneChange (0x11da90) -- script event dispatched when an actor changes zones.
void AActor::eventZoneChange(AZoneInfo *NewZone)
{
    struct { AZoneInfo *NewZone; } Parms;
    if (IsProbing(23)) {
        Parms.NewZone = NewZone;
        ProcessEvent(FindFunctionChecked(ENGINE_ZoneChange), &Parms);
    }
}

// AZoneInfo::eventActorLeaving (0x11dae0) -- script event dispatched when an actor leaves a zone.
void AZoneInfo::eventActorLeaving(AActor *Other)
{
    struct { AActor *Other; } Parms;
    if (IsProbing(22)) {
        Parms.Other = Other;
        ProcessEvent(FindFunctionChecked(ENGINE_ActorLeaving), &Parms);
    }
}

// UModel::PointRegion (0x143370) -- finds the BSP leaf and zone containing Location.
FPointRegion UModel::PointRegion(AZoneInfo *Zone, const FVector &Location) const
{
    if (!Nodes.Num())
        return FPointRegion(Zone);

    INT iNode = 0;
    INT Outside = RootOutside;
    INT iPrevNode;
    INT IsFront;
    do {
        const FBspNode &Node = Nodes(iNode);
        IsFront = Node.Plane.PlaneDot(Location) >= 0.0f;
        if (IsFront)
            Outside = Outside || (Node.NumVertices > 0 && !(Node.NodeFlags & 0x21));
        else
            Outside = Outside && (Node.NumVertices == 0 || (Node.NodeFlags & 0x21));
        iPrevNode = iNode;
        iNode = Node.iChild[IsFront];
    } while (iNode != INDEX_NONE);

    const FBspNode &PrevNode = Nodes(iPrevNode);
    INT iLeaf = PrevNode.iLeaf[IsFront];
    BYTE ZoneNumber = Zones.Num() ? PrevNode.iZone[IsFront] : 0;
    AZoneInfo *ResultZone = GetZoneActor(ZoneNumber) ? GetZoneActor(ZoneNumber) : Zone;
    return FPointRegion(ResultZone, iLeaf, ZoneNumber);
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_11d700(AActor *A, AZoneInfo *Z, UModel *M, const FVector &V)
{
    AActor ActorInstance;
    Escape(&ActorInstance);
    A->eventZoneChange(Z);
    Z->eventActorEntered(A);
    Z->eventActorLeaving(A);
    FPointRegion R = M->PointRegion(Z, V);
    Escape(&R);
}
