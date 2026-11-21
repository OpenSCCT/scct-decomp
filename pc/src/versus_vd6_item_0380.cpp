// Work item 0380 (w3): Versus RVA 0x11a3d0 (959 bytes), ULevel::SpawnActor
// (Engine, UnLevAct.cpp), compiled with /GL and linked with /LTCG.

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned __int64 QWORD;

enum EName
{
    NAME_None = 0,
    NAME_PROBEMIN = 0x14c,
    NAME_PROBEMAX = 0x18c,
    NAME_GainedChild = 0x14e,
    NAME_LostChild = 0x14f,
    NAME_PreBeginPlay = 0x163,
    NAME_BeginPlay = 0x164,
    NAME_PostBeginPlay = 0x165,
    NAME_SetInitialState = 0xa3d,
    NAME_PostNetBeginPlay = 0xa3e,
};

enum EClassFlags
{
    CLASS_Abstract = 0x00000001,
};

enum EObjectFlags
{
    RF_Transactional = 0x00000001,
    RF_Dynamic       = 0x80000000,
};

enum ENetMode
{
    NM_Standalone      = 0,
    NM_DedicatedServer = 1,
    NM_ListenServer    = 2,
    NM_Client          = 3,
};

enum EDetailMode
{
    DM_Low = 0,
};

enum EPhysics
{
    PHYS_None     = 0,
    PHYS_Rotating = 3,
};

enum { INDEX_NONE = -1 };

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    INT GetIndex() const { return Index; }
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FBox
{
    FVector Min, Max;
};

template <class T> inline void Exchange(T &A, T &B)
{
    const T Temp = A;
    A = B;
    B = Temp;
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize); // RVA 0x44e0
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    INT Add(INT Count = 1) { return FArray::Add(Count, sizeof(T)); }
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR MemChunk_Tag[];
inline void *appMalloc(INT Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

struct FTaggedMemory
{
    FTaggedMemory *Next;
    INT DataSize;
    BYTE Data[1];
};

class FMemStack
{
public:
    BYTE *Top;
    BYTE *End;
    INT DefaultChunkSize;
    FTaggedMemory *TopChunk;
    static FTaggedMemory *UnusedChunks;
    BYTE *AllocateNewChunk(INT MinSize);
    BYTE *PushBytes(INT AllocSize, INT Align)
    {
        BYTE *Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
        Top = Result + AllocSize;
        if (Top > End) {
            AllocateNewChunk(AllocSize + Align);
            Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};
extern FMemStack GMem; // 0x10c8bbe0

void *operator new(unsigned int Size, FMemStack &Mem, INT Count = 1, INT Align = 8);

class FOutputDevice;
extern FOutputDevice *GError; // 0x10c71aa8

class UFunction;
class UClass;
class AActor;
class APawn;
class AZoneInfo;
class ALevelInfo;
class ULevel;

struct FStateFrame
{
    BYTE Pad00[0x20];
    QWORD ProbeMask;
};

struct FPointRegion
{
    AZoneInfo *Zone;
    INT iLeaf;
    BYTE ZoneNumber;
    FPointRegion() {}
    FPointRegion(AZoneInfo *InZone, INT InLeaf = INDEX_NONE, BYTE InZoneNumber = 0)
        : Zone(InZone), iLeaf(InLeaf), ZoneNumber(InZoneNumber) {}
};

struct FActorLink
{
    AActor *Actor;
    FActorLink *Next;
    FActorLink(AActor *InActor, FActorLink *InNext)
        : Actor(InActor), Next(InNext) {}
};

class UObject
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // +0x10
    virtual void V14(); virtual void V18(); virtual void V1C();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2C();
    virtual void V30(); virtual void V34();
    virtual void InitExecution(); // +0x38

    INT Index;               // +0x04
    UObject *HashNext;       // +0x08
    FStateFrame *StateFrame; // +0x0c
    void *_Linker;           // +0x10
    INT _LinkerIndex;        // +0x14
    UObject *Outer;          // +0x18
    DWORD ObjectFlags;       // +0x1c
    FName Name;              // +0x20
    UClass *Class;           // +0x24

    UObject *GetOuter() const { return Outer; }
    void SetFlags(DWORD NewFlags) { ObjectFlags |= NewFlags; }
    FName GetFName() const { return Name; }

    UFunction *FindFunctionChecked(FName InName, INT Global = 0);
    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }

    static UObject *StaticAllocateObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                         UObject *Template, FOutputDevice *Error, UObject *Ptr,
                                         UObject *SubobjectRoot);
    static UObject *StaticConstructObject(UClass *Class, UObject *InOuter, FName Name, DWORD SetFlags,
                                          UObject *Template, FOutputDevice *Error, UObject *SubobjectRoot);
};

class UField : public UObject
{
public:
    UField *SuperField; // +0x28
};

class UStruct : public UField
{
public:
    UBOOL IsChildOf(const UStruct *SomeBase) const
    {
        for (const UStruct *Struct = this; Struct; Struct = (const UStruct *)Struct->SuperField)
            if (Struct == SomeBase)
                return 1;
        return 0;
    }
};

class UClass : public UStruct
{
public:
    BYTE Pad2C[0x88 - 0x2c];
    DWORD ClassFlags;                       // +0x88
    BYTE Pad8C[0xac - 0x8c];
    TArray<BYTE> Defaults;                  // +0xac
    BYTE PadB8[0x104 - 0xb8];
    void (*ClassConstructor)(void *);       // +0x104

    AActor *GetDefaultActor() { return (AActor *)Defaults.Data; }
};

class FCollisionHashBase
{
public:
    void AddActor(AActor *Actor);
    void __stdcall RemoveActor(AActor *Actor);
};

class AActor : public UObject
{
public:
    virtual void V3C();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4C();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5C();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6C();
    virtual void V70(); virtual void V74(); virtual void V78(); virtual void V7C();
    virtual void V80(); virtual void V84();
    virtual void Spawned(); // +0x88
    virtual void V8C();
    virtual void V90(); virtual void V94(); virtual void V98(); virtual void V9C();
    virtual void VA0(); virtual void VA4(); virtual void VA8(); virtual void VAC();
    virtual void VB0(); virtual void VB4(); virtual void VB8(); virtual void VBC();
    virtual void VC0(); virtual void VC4(); virtual void VC8(); virtual void VCC();
    virtual void VD0(); virtual void VD4(); virtual void VD8(); virtual void VDC();
    virtual void VE0(); virtual void VE4(); virtual void VE8();
    virtual void SetZone(UBOOL bTest, UBOOL bForceRefresh); // +0xec
    virtual void VF0(); virtual void VF4();
    virtual void PostBeginPlay(); // +0xf8

    BYTE Pad28[0x80 - 0x28];
    FVector Location;           // +0x80
    BYTE Pad8C[0xc8 - 0x8c];
    FBox OctreeBox;             // +0xc8
    FRotator Rotation;          // +0xe0
    BYTE PadEC[0x104 - 0xec];
    AActor *Owner;              // +0x104
    AActor *Base;               // +0x108
    BYTE Pad10C[0x134 - 0x10c];
    INT RenderRevision;         // +0x134
    BYTE Pad138[0x194 - 0x138];
    APawn *Instigator;          // +0x194
    BYTE Pad198[0x1a0 - 0x198];
    ALevelInfo *Level;          // +0x1a0
    ULevel *XLevel;             // +0x1a4
    DWORD Pad1A8;               // +0x1a8
    FPointRegion Region;        // +0x1ac
    BYTE Pad1B8[0x1c4 - 0x1b8];
    INT *LeavesData;            // +0x1c4
    INT LeavesNum;              // +0x1c8
    BYTE Pad1CC[0x238 - 0x1cc];
    void *MeshInstance;         // +0x238
    BYTE Pad23C[0x250 - 0x23c];
    DWORD RenderDataFlag;       // +0x250
    BYTE Pad254[0x268 - 0x254];
    FLOAT CollisionRadius;      // +0x268
    FLOAT CollisionHeight;      // +0x26c
    BYTE Pad270[0x2bc - 0x270];
    FName Tag;                  // +0x2bc
    BYTE Pad2C0[0x2d8 - 0x2c0];
    BYTE Physics;               // +0x2d8
    BYTE Pad2D9[0x2dd - 0x2d9];
    BYTE Role;                  // +0x2dd
    BYTE RemoteRole;            // +0x2de
    BYTE Pad2DF[0x2e8 - 0x2df];

    DWORD Bits2E8_0 : 11;       // +0x2e8
    DWORD bStatic : 1;          // 0x00000800
    DWORD Bits2E8_12 : 2;
    DWORD bNoDelete : 1;        // 0x00004000
    DWORD bDeleteMe : 1;        // 0x00008000
    DWORD bTicked : 1;          // 0x00010000
    DWORD Bits2E8_17 : 3;
    DWORD bHighDetail : 1;      // 0x00100000
    DWORD Bits2E8_21 : 11;

    DWORD Flags2EC;             // +0x2ec

    DWORD Bits2F0_0 : 1;        // +0x2f0
    DWORD bCollideWhenPlacing : 1; // 0x00000002
    DWORD Bits2F0_2 : 3;
    DWORD bBlockActors : 1;     // 0x00000020
    DWORD Bits2F0_6 : 6;
    DWORD bCollideActors : 1;   // 0x00001000
    DWORD bCollideWorld : 1;    // 0x00002000
    DWORD Bits2F0_14 : 18;

    static UClass PrivateStaticClass; // 0x10cc52a8
    static UClass *StaticClass() { return &PrivateStaticClass; }

    FVector GetCylinderExtent() const;

    void SetOwner(AActor *NewOwner);
    void ClearRenderData();
    void FindBase();

    void eventPreBeginPlay();
    void eventBeginPlay();
    void eventPostBeginPlay();
    void eventSetInitialState();
    void eventPostNetBeginPlay();

    void eventLostChild(AActor *Other)
    {
        if (IsProbing(NAME_LostChild)) {
            struct { AActor *Other; } Parms;
            Parms.Other = Other;
            ProcessEvent(FindFunctionChecked(NAME_LostChild), &Parms);
        }
    }
    void eventGainedChild(AActor *Other)
    {
        if (IsProbing(NAME_GainedChild)) {
            struct { AActor *Other; } Parms;
            Parms.Other = Other;
            ProcessEvent(FindFunctionChecked(NAME_GainedChild), &Parms);
        }
    }
};

class AZoneInfo : public AActor {};

class ALevelInfo : public AZoneInfo
{
public:
    BYTE Pad2F4[0x434 - 0x2f4];
    DWORD Bits434_0 : 3;        // +0x434
    DWORD bDropDetail : 1;      // 0x08
    DWORD Bits434_4 : 28;
    BYTE DetailMode;            // +0x438
    BYTE Pad439[0x4a8 - 0x439];
    BYTE NetMode;               // +0x4a8
};

class ULevel : public UObject
{
public:
    DWORD Pad28;                        // +0x28 (FNetworkNotify vptr)
    TArray<AActor *> Actors;            // +0x2c
    BYTE Pad38[0x3a48 - 0x38];
    FCollisionHashBase *Hash;           // +0x3a48
    DWORD Pad3A4C;                      // +0x3a4c
    FActorLink *NewlySpawned;           // +0x3a50
    UBOOL InTick;                       // +0x3a54
    UBOOL Ticked;                       // +0x3a58

    ALevelInfo *GetLevelInfo() const { return (ALevelInfo *)Actors(0); }

    UBOOL FindSpot(const FVector &Extent, FVector &Location);
    UBOOL ActorTest_f5080(AActor *Actor);
    void SortActor_f50f0(AActor *Actor);
    UBOOL CheckEncroachment(AActor *Actor, FVector TestLocation, FRotator TestRotation, UBOOL bTouchNotify);
    UBOOL __stdcall DestroyActor(AActor *Actor, UBOOL bNetForce = 0);

    AActor *SpawnActor(
        UClass *Class,
        FName InName,
        const FVector &Location,
        const FRotator &Rotation,
        AActor *Template,
        UBOOL bNoCollisionFail,
        UBOOL bRemoteOwned,
        AActor *Owner,
        APawn *Instigator
    );
};

// RVA 0x11a3d0
AActor *ULevel::SpawnActor(
    UClass *Class,
    FName InName,
    const FVector &InLocation,
    const FRotator &Rotation,
    AActor *Template,
    UBOOL bNoCollisionFail,
    UBOOL bRemoteOwned,
    AActor *Owner,
    APawn *Instigator
)
{
    if (!Class)
        return 0;
    if (Class->ClassFlags & CLASS_Abstract)
        return 0;
    if (!Class->IsChildOf(AActor::StaticClass()))
        return 0;
    AActor *Default = Class->GetDefaultActor();
    if (Default->bStatic || Default->bNoDelete)
        return 0;
    if (Default->bHighDetail &&
        (GetLevelInfo()->DetailMode == DM_Low || GetLevelInfo()->bDropDetail || GetLevelInfo()->NetMode == NM_DedicatedServer))
        return 0;

    if (!Template)
        Template = Default;

    FVector Location = InLocation;

    if ((Template->bCollideWorld || (Template->bCollideWhenPlacing && (GetLevelInfo()->NetMode != NM_Client))) && !bNoCollisionFail)
    {
        if (!FindSpot(Template->GetCylinderExtent(), Location))
            return 0;
    }

    INT iActor = Actors.Add();
    AActor *Actor = (AActor *)UObject::StaticConstructObject(Class, GetOuter(), InName, 0, Template, GError, 0);
    Actors(iActor) = Actor;
    SortActor_f50f0(Actor);

    Actor->SetFlags(RF_Transactional | RF_Dynamic);
    Actor->Tag = Class->GetFName();
    Actor->Region = FPointRegion(GetLevelInfo());
    Actor->Level = GetLevelInfo();
    Actor->bTicked = !Ticked;
    Actor->XLevel = this;

    if (bRemoteOwned)
        Exchange(Actor->RemoteRole, Actor->Role);

    if (Actor->MeshInstance)
        Actor->MeshInstance = 0;

    Actor->Location = Location;
    Actor->Rotation = Rotation;

    if (Actor->bCollideActors && Hash)
        Hash->AddActor(Actor);

    Actor->SetOwner(Owner);
    Actor->Instigator = Instigator;
    Actor->InitExecution();
    Actor->Spawned();
    Actor->eventPreBeginPlay();
    if (Actor->bDeleteMe)
        return 0;
    Actor->eventBeginPlay();
    if (Actor->bDeleteMe)
        return 0;

    Actor->SetZone(iActor == 0, 1);
    Actor->ClearRenderData();

    if (!bNoCollisionFail)
    {
        if (Actor->bCollideActors && Hash)
            Hash->RemoveActor(Actor);
        if (CheckEncroachment(Actor, Actor->Location, Actor->Rotation, 1))
        {
            DestroyActor(Actor);
            return 0;
        }
        if (Actor->bCollideActors && Hash)
            Hash->AddActor(Actor);
    }

    Actor->eventPostBeginPlay();
    if (Actor->bDeleteMe)
        return 0;
    Actor->PostBeginPlay();
    Actor->eventSetInitialState();

    if (!Actor->Base && Actor->bCollideWorld && Actor->bBlockActors &&
        (Actor->Physics == PHYS_None || Actor->Physics == PHYS_Rotating))
        Actor->FindBase();

    if (InTick)
        NewlySpawned = new(GMem) FActorLink(Actor, NewlySpawned);

    if (!bRemoteOwned)
        Actor->eventPostNetBeginPlay();

    return Actor;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit. Stand-in bodies for
// whole-program callees so the linker gives them retail's register conventions.
void Escape(void *);
void UnnamedUse(AActor *Actor, INT Index);
FBox *UnnamedBox(AActor *Actor, FBox *Out);
FBox *UnnamedExpand(FBox *In, FBox *Out, FLOAT By);
void UnnamedInsert(FCollisionHashBase *Hash, AActor *Actor, INT X);
UBOOL UnnamedSpotCheck(ULevel *Level, AActor *Info, const FVector *Extent, FVector *Loc, INT Step);
void UnnamedSortHelper(ULevel *Level, AActor *Actor, INT Slot);
void UnnamedFindBaseHelper(AActor *Actor, FLOAT Z);

extern const FVector *GZeroVec_Standin;

__declspec(noinline) UBOOL ULevel::FindSpot(const FVector &Extent, FVector &Location)
{
    FVector *Loc = &Location;
    const FVector *Ext = &Extent;
    ULevel *Lev = this;
    FVector Start = *Loc;
    INT Best = 0;
    if (!UnnamedSpotCheck(Lev, Lev->GetLevelInfo(), Ext, Loc, Best))
        return 1;
    if (Ext->X == GZeroVec_Standin->X && Ext->Y == GZeroVec_Standin->Y && Ext->Z == GZeroVec_Standin->Z)
        return 0;
    for (INT i = 1; i <= 4; i++) {
        FVector Try = Start;
        Try.X += Ext->X * (FLOAT)i;
        Try.Y += Ext->Y * (FLOAT)i;
        if (!UnnamedSpotCheck(Lev, Lev->GetLevelInfo(), Ext, &Try, i)) {
            *Loc = Try;
            Loc = &Start;
            Ext = GZeroVec_Standin;
            Lev = (ULevel *)Lev->Outer;
            Best++;
            if (Best > 1)
                return 1;
        }
    }
    Escape(&Start);
    return Best != 0;
}

__declspec(noinline) UObject *UObject::StaticConstructObject(UClass *InClass, UObject *InOuter, FName InName, DWORD SetFlags,
                                                             UObject *InTemplate, FOutputDevice *Error, UObject *SubobjectRoot)
{
    UObject *Result = StaticAllocateObject(InClass, InOuter, InName, SetFlags, InTemplate, Error, 0, SubobjectRoot);
    if (Result)
        (*InClass->ClassConstructor)(Result);
    return Result;
}

FVector AActor::GetCylinderExtent() const
{
    return FVector(CollisionRadius, CollisionRadius, CollisionHeight);
}

__declspec(noinline) UBOOL ULevel::ActorTest_f5080(AActor *Actor)
{
    if (!Actor)
        return 0;
    if (Actor == Actors(0) || Actor->bStatic || Actor->bNoDelete)
        return 1;
    return Actor->Role != 0;
}

extern UClass *GActorListClassA_Standin;
extern UClass *GActorListClassB_Standin;

__declspec(noinline) void ULevel::SortActor_f50f0(AActor *Actor)
{
    ULevel *Lev = this;
    for (INT i = 0; i < 2; i++) {
        if (Lev->ActorTest_f5080(Actor))
            Lev->Actors(Lev->Actors.Add()) = Actor;
        if (GActorListClassA_Standin && (Actor->Class == GActorListClassA_Standin || Actor->Class->ClassFlags % GActorListClassA_Standin->ClassFlags == 0)) {
            UnnamedSortHelper(Lev, Actor, 1);
            return;
        }
        if (GActorListClassB_Standin && (Actor->Class == GActorListClassB_Standin || Actor->Class->ClassFlags % GActorListClassB_Standin->ClassFlags == 0)) {
            UnnamedSortHelper(Lev, Actor, 2);
            return;
        }
        Escape(&Actor);
        Lev = (ULevel *)Lev->Outer;
    }
    UnnamedSortHelper(Lev, Actor, 3);
}

__declspec(noinline) void FCollisionHashBase::AddActor(AActor *Actor)
{
    FBox Tmp, Tmp2;
    if (!Actor || Actor->bDeleteMe)
        return;
    if (Actor->RenderRevision > 0)
        RemoveActor(Actor);
    Actor->OctreeBox = *UnnamedBox(Actor, &Tmp);
    Actor->OctreeBox = *UnnamedExpand(&Actor->OctreeBox, &Tmp2, 4.2f);
    for (INT i = 0; i < Actor->LeavesNum; i++)
        UnnamedInsert(this, Actor, Actor->LeavesData[i]);
}

__declspec(noinline) void AActor::SetOwner(AActor *NewOwner)
{
    if (Owner != 0)
        Owner->eventLostChild(this);
    Owner = NewOwner;
    if (Owner != 0)
        Owner->eventGainedChild(this);
    Flags2EC |= 4;
}

__declspec(noinline) void AActor::eventPreBeginPlay()
{
    if (IsProbing(FName(NAME_PreBeginPlay)))
        ProcessEvent(FindFunctionChecked(FName(NAME_PreBeginPlay)), 0);
}

__declspec(noinline) void AActor::eventBeginPlay()
{
    if (IsProbing(FName(NAME_BeginPlay)))
        ProcessEvent(FindFunctionChecked(FName(NAME_BeginPlay)), 0);
}

__declspec(noinline) void AActor::eventPostBeginPlay()
{
    if (IsProbing(FName(NAME_PostBeginPlay)))
        ProcessEvent(FindFunctionChecked(FName(NAME_PostBeginPlay)), 0);
}

__declspec(noinline) void AActor::eventSetInitialState()
{
    ProcessEvent(FindFunctionChecked(FName(NAME_SetInitialState)), 0);
}

__declspec(noinline) void AActor::eventPostNetBeginPlay()
{
    ProcessEvent(FindFunctionChecked(FName(NAME_PostNetBeginPlay)), 0);
}

__declspec(noinline) void AActor::ClearRenderData()
{
    RenderRevision++;
    if (RenderDataFlag)
        for (INT i = 0; i < LeavesNum; i++)
            UnnamedUse(this, LeavesData[i]);
}

__declspec(noinline) void AActor::FindBase()
{
    UnnamedFindBaseHelper(this, Location.Z);
    if (Base)
        UnnamedFindBaseHelper(Base, Location.X);
    UnnamedFindBaseHelper(this, Location.Y);
}

__declspec(noinline) BYTE *FMemStack::AllocateNewChunk(INT MinSize)
{
    FTaggedMemory *Chunk = 0;
    for (FTaggedMemory **Link = &UnusedChunks; *Link; Link = &(*Link)->Next) {
        if ((*Link)->DataSize >= MinSize) {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk) {
        INT DataSize = Max(MinSize, DefaultChunkSize - (INT)sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)appMalloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

__declspec(noinline) void *operator new(unsigned int Size, FMemStack &Mem, INT Count, INT Align)
{
    return Mem.PushBytes(Size * Count, Align);
}

__declspec(noinline) void Driver_Aux(ULevel **Levels, UClass **Classes, FName N, AActor **Tpls, FVector *Locs, const FRotator *Rots, INT Count)
{
    Escape(&GError);
    Escape(&GMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    Escape(&AActor::PrivateStaticClass);
    Escape(&GZeroVec_Standin);
    Escape(&GActorListClassA_Standin);
    Escape(&GActorListClassB_Standin);
    for (INT i = 0; i < Count; i++) {
        Escape(UObject::StaticConstructObject(Classes[i], Levels[i], N, i, Tpls[i], GError, 0));
        Escape(operator new(8 + i, GMem, i + 1, 8));
        Levels[i]->SortActor_f50f0(Tpls[i]);
        Levels[i]->FindSpot(Locs[i], Locs[i + 1]);
        Escape(Levels[i]->SpawnActor(Classes[i], FName(NAME_None), Locs[i], Rots[i], 0, 0, 0, 0, 0));
        Escape(Levels[i]->SpawnActor(Classes[i], N, Locs[i], Rots[i], Tpls[i], 1, 1, Tpls[i], 0));
    }
}

AActor *Driver_11a3d0(ULevel *L, UClass *C, FName N, const FVector *Loc, const FRotator *Rot,
                      AActor *Tpl, UBOOL bNoFail, UBOOL bRemote, AActor *Owner, APawn *Inst)
{
    if (bNoFail == 0x11111111) {
        L->SortActor_f50f0(Tpl);
        return 0;
    }
    if (bNoFail == 0x12345678) {
        ULevel *Ls[2] = { L, L };
        UClass *Cs[2] = { C, C };
        AActor *Ts[2] = { Tpl, Owner };
        FVector Vs[3] = { *Loc, *Loc, *Loc };
        Driver_Aux(Ls, Cs, N, Ts, Vs, Rot, 2);
        return 0;
    }
    return L->SpawnActor(C, N, *Loc, *Rot, Tpl, bNoFail, bRemote, Owner, Inst);
}
