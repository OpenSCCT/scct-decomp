// Work item 0383: Versus RVA 0x11b4b0, ULevel::FarMoveActor.
// Compiled with VC7.0 /GL and linked with /LTCG.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef DWORD BITFIELD;
typedef float FLOAT;
typedef unsigned char BYTE;

enum EName { NAME_None = 0 };
enum ENetMode { NM_Standalone = 0, NM_DedicatedServer = 1, NM_ListenServer = 2, NM_Client = 3 };

struct FName
{
    INT Index;
    UBOOL operator==(EName N) const { return Index == (INT)N; }
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    UBOOL operator==(const FVector &V) const { return X == V.X && Y == V.Y && Z == V.Z; }
    UBOOL operator!=(const FVector &V) const { return X != V.X || Y != V.Y || Z != V.Z; }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

template<class T> class TArray
{
public:
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return Data[i]; }
};

class AActor;
class ULevel;

extern const FVector &GMath_UnitZ; // retail 0x10ccacbc

class FCollisionOctree
{
public:
    void *RootNode;
    void AddActor(AActor *Actor);               // RVA 0x1198a0
    void __stdcall RemoveActor(AActor *Actor);  // RVA 0x119a20
};

class AActor
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36(); virtual void Slot37(); virtual void Slot38(); virtual void Slot39();
    virtual void Slot40(); virtual void Slot41(); virtual void Slot42(); virtual void Slot43();
    virtual void Slot44(); virtual void Slot45(); virtual void Slot46();
    virtual void SetBase(AActor *NewBase, const FVector &NewFloor, UBOOL bNotifyActor); // slot 47 (0xbc)
    virtual void Slot48(); virtual void Slot49(); virtual void Slot50(); virtual void Slot51();
    virtual void Slot52(); virtual void Slot53(); virtual void Slot54(); virtual void Slot55();
    virtual void Slot56(); virtual void Slot57(); virtual void Slot58();
    virtual void SetZone(UBOOL bTest, UBOOL bForceRefresh);                             // slot 59 (0xec)

    BYTE Pad004[0x24 - 0x04];
    void *Class;                    // 0x24
    BYTE Pad028[0x80 - 0x28];
    FVector Location;               // 0x80
    BYTE Pad08C[0xe0 - 0x8c];
    FRotator Rotation;              // 0xe0
    BYTE Pad0EC[0x134 - 0xec];
    INT Field134;                   // 0x134
    BYTE Pad138[0x1a4 - 0x138];
    ULevel *XLevel;                 // 0x1a4
    BYTE Pad1A8[0x1e8 - 0x1a8];
    TArray<void *> OctreeNodes;     // 0x1e8
    BYTE Pad1F4[0x204 - 0x1f4];
    TArray<AActor *> Attached;      // 0x204
    BYTE Pad210[0x250 - 0x210];
    DWORD Field250;                 // 0x250
    BYTE Pad254[0x268 - 0x254];
    FLOAT CollisionRadius;          // 0x268
    FLOAT CollisionHeight;          // 0x26c
    BYTE Pad270[0x2b8 - 0x270];
    FName AttachmentBone;           // 0x2b8
    BYTE Pad2BC[0x2e8 - 0x2bc];
    BITFIELD Pad2E8Low : 11;
    BITFIELD bStatic : 1;           // 0x2e8 bit 11 (0x800)
    BITFIELD Pad2E8High : 20;
    DWORD Flags2EC;                 // 0x2ec
    BITFIELD Bit2F0_0 : 1;
    BITFIELD bCollideWhenPlacing : 1; // 0x2f0 bit 1 (0x02)
    BITFIELD Bit2F0_2 : 1;
    BITFIELD bMovable : 1;          // 0x2f0 bit 3 (0x08)
    BITFIELD Bit2F0_4 : 2;
    BITFIELD Bit2F0_6 : 1;          // 0x2f0 bit 6 (0x40)
    BITFIELD Bit2F0_7 : 5;
    BITFIELD bCollideActors : 1;    // 0x2f0 bit 12 (0x1000)
    BITFIELD bCollideWorld : 1;     // 0x2f0 bit 13 (0x2000)
    BITFIELD Bit2F0_14 : 16;
    BITFIELD bJustTeleported : 1;   // 0x2f0 bit 30 (0x40000000)
    BITFIELD Bit2F0_31 : 1;

    FVector GetCylinderExtent() const { return FVector(CollisionRadius, CollisionRadius, CollisionHeight); }
    void ClearRenderData();         // RVA 0x90de0
};

class ALevelInfo : public AActor
{
public:
    BYTE LevelInfoPad[0x4a8 - 0x2f4];
    BYTE NetMode;                   // 0x4a8
};

class ULevel
{
public:
    BYTE Pad0000[0x2c];
    TArray<AActor *> Actors;        // 0x2c
    BYTE Pad0038[0x3a48 - 0x38];
    FCollisionOctree *Hash;         // 0x3a48

    ALevelInfo *GetLevelInfo() { return (ALevelInfo *)Actors(0); }
    UBOOL FindSpot(const FVector &Extent, FVector &Location);                                   // RVA 0x11b1f0
    UBOOL CheckEncroachment(AActor *Actor, FVector TestLocation, FRotator TestRotation, UBOOL bTouchNotify); // RVA 0x11c8d0
    UBOOL FarMoveActor(AActor *Actor, const FVector &DestLocation, UBOOL test = 0, UBOOL bNoCheck = 0, UBOOL bAttachedMove = 0);
};

UBOOL ULevel::FarMoveActor(AActor *Actor, const FVector &DestLocation, UBOOL test, UBOOL bNoCheck, UBOOL bAttachedMove)
{
    if (Actor->bStatic || !Actor->bMovable)
        return 0;

    if (Actor->bCollideActors && Hash)
        Hash->RemoveActor(Actor);

    FVector prevLocation = Actor->Location;
    FVector newLocation = DestLocation;
    UBOOL result = 1;

    if (!bNoCheck && (Actor->bCollideWorld || (Actor->bCollideWhenPlacing && GetLevelInfo()->NetMode != NM_Client)))
        result = FindSpot(Actor->GetCylinderExtent(), newLocation);

    if (result && !test && !bNoCheck)
        result = !CheckEncroachment(Actor, newLocation, Actor->Rotation, 1);

    if (prevLocation == Actor->Location || test)
    {
        if (result)
        {
            if (!test)
            {
                Actor->bJustTeleported = 1;
                if (!bAttachedMove)
                    Actor->SetBase(0, GMath_UnitZ, 1);
                for (INT i = 0; i < Actor->Attached.Num(); i++)
                {
                    if (Actor->Attached(i) && Actor->Attached(i)->AttachmentBone == NAME_None)
                        FarMoveActor(Actor->Attached(i), newLocation + Actor->Attached(i)->Location - Actor->Location, 0, bNoCheck, 1);
                }
            }
            if (Actor->OctreeNodes.Num() > 0)
                Hash->RemoveActor(Actor);
            Actor->Location = newLocation;
        }
        if (Actor->bCollideActors && Hash)
            Hash->AddActor(Actor);
        if (result)
            Actor->SetZone(test, 0);
        if (!test)
            Actor->ClearRenderData();
    }
    return result;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);

__declspec(noinline) void AActor::ClearRenderData()
{
    Field134++;
    if (Field250)
    {
        Escape(Class);
        Escape(this);
    }
}

__declspec(noinline) void FCollisionOctree::AddActor(AActor *Actor)
{
    if (!Actor || Actor->Bit2F0_6)
        return;
    if (Actor->OctreeNodes.Num() > 0)
        RemoveActor(Actor);
    struct FBig { DWORD D[16]; };
    *(FBig *)&Actor->Pad028 = *(FBig *)Actor->Class;
    *(FBig *)&Actor->Pad1A8 = *(FBig *)Actor->XLevel;
    Escape(Actor->Class);
    Actor->Flags2EC &= 0x7fffffff;
    RemoveActor(Actor);
}

extern UBOOL __fastcall FindSpot_Helper(const FVector *Extent, ULevel *Level, FVector *Location);

__declspec(noinline) UBOOL ULevel::FindSpot(const FVector &Extent, FVector &Location)
{
    Location.X += Extent.X;
    return FindSpot_Helper(&Extent, this, &Location);
}

UBOOL Driver_11b4b0(ULevel *Level, AActor *Actor, const FVector *Dest, UBOOL Test, UBOOL bNoCheck, UBOOL bAttached)
{
    Escape((void *)&GMath_UnitZ);
    return Level->FarMoveActor(Actor, *Dest, Test, bNoCheck, bAttached);
}
