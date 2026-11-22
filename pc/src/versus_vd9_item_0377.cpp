// Work item 0377: Versus RVA 0x119860 and 0x1198a0. LTCG (VC7.0 /GL, /LTCG).
// 0x119860 allocates "FCollisionOctree::RootNode", so the class is taken as
// Unreal's FCollisionOctree (fields beyond the root node are unnamed).
typedef unsigned short TCHAR;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef int INT;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int Size, const TCHAR *Tag)
{
    return GMalloc->Malloc(Size, Tag);
}

// Octree node: 16 bytes, constructor is the published clear_4_words (0x1183b0).
struct FOctreeNode {
    FOctreeNode();
    void *Children;
    INT Pad[3];
};

class FCollisionOctree {
public:
    __declspec(noinline) FCollisionOctree();
    FOctreeNode *RootNode;    // +0x00
    DWORD OctreeTag;          // +0x04
    INT Pad08[24];
    FLOAT Value68;            // +0x68
    INT Pad6c[2];
    INT Value74;              // +0x74
};

FCollisionOctree::FCollisionOctree()
{
    Value68 = 1.0f;
    Value74 = 0;
    OctreeTag = 0x1fffffff;
    RootNode = new(L"FCollisionOctree::RootNode") FOctreeNode();
}


// ---------------------------------------------------------------------------
// RVA 0x1198a0: FCollisionOctree::AddActor (actor in EBX, octree on the stack).
// The world-bounds test and the RemoveActor/filter structure follow Unreal
// Engine 2's FCollisionOctree::AddActor.

#define WORLD_MAX       524288.0
#define HALF_WORLD_MAX  (WORLD_MAX * 0.5)

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT S) const { return FVector(X * S, Y * S, Z * S); }
};

__declspec(dllimport) extern const FVector GMath_Zero;   // 0x10ccacc0
__declspec(dllimport) extern const FVector GMath_UnitX;  // 0x10ccacc4

template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// SCCT's FBox has no IsValid flag (24 bytes, copied with rep movsd 6).
// Definitions copied from item 0307 so LTCG gives the callees their retail
// conventions; they are not part of this item's match.
struct FBox
{
    FVector Min, Max;
    FBox(const FVector &InMin, const FVector &InMax);
    FBox &operator+=(const FVector &Other);
    FBox ExpandBy(FLOAT W) const;                                       // 0x81a70
    void GetCenterAndExtents(FVector &Center, FVector &Extents) const;  // 0x92880
};

__declspec(noinline) FBox &FBox::operator+=(const FVector &Other)
{
    if (Min.X - Max.X != 1.f)
    {
        Min.X = ::Min(Min.X, Other.X); Min.Y = ::Min(Min.Y, Other.Y); Min.Z = ::Min(Min.Z, Other.Z);
        Max.X = ::Max(Max.X, Other.X); Max.Y = ::Max(Max.Y, Other.Y); Max.Z = ::Max(Max.Z, Other.Z);
    }
    else
    {
        Min = Max = Other;
    }
    return *this;
}
__declspec(noinline) FBox::FBox(const FVector &InMin, const FVector &InMax)
    : Min(InMin), Max(InMax)
{
    Min = GMath_UnitX;
    Max = GMath_Zero;
    *this += InMin;
    *this += InMax;
}
__declspec(noinline) FBox FBox::ExpandBy(FLOAT W) const
{
    return FBox(Min - FVector(W, W, W), Max + FVector(W, W, W));
}
__declspec(noinline) void FBox::GetCenterAndExtents(FVector &Center, FVector &Extents) const
{
    Extents = (Max - Min) * 0.5f;
    Center = Min + Extents;
}

class AActor;

class UPrimitive {
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25();
    virtual FBox GetCollisionBoundingBox(const AActor *Owner) const;  // +0x68
};

// Neutral: an object reached from the actor at +0x1a4; its +0x2c points at a
// pointer to something with a flag word at +0x434.
struct UnnamedFlags_434 { char Pad[0x434]; DWORD Flags; };
struct UnnamedRef_1a4 { char Pad[0x2c]; UnnamedFlags_434 **Target; };

class AActor {
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
    virtual UPrimitive *GetPrimitive();                                // +0xb0

    char Pad04[0x64];
    FVector OctreeBoxCenter;    // +0x68
    FVector OctreeBoxRadii;     // +0x74
    char Pad80[0x48];
    FBox OctreeBox;             // +0xc8
    char PadE0[0xc4];
    UnnamedRef_1a4 *Ref1a4;     // +0x1a4
    char Pad1a8[0x40];
    void *OctreeNodesData;      // +0x1e8
    INT OctreeNodesNum;         // +0x1ec
    char Pad1f0[0xf8];
    DWORD Bits2e8_0 : 15;
    DWORD bSkipOctree : 1;      // +0x2e8 bit 15 (neutral name)
    DWORD Bits2e8_16 : 15;
    DWORD bWasSNFiltered : 1;   // +0x2e8 bit 31
    DWORD Pad2ec;
    DWORD Bits2f0_0 : 6;
    DWORD bNoOctree : 1;        // +0x2f0 bit 6 (neutral name)
};

struct FPlane { FLOAT X, Y, Z, W; };
extern FPlane RootNodeBox;      // 0x10c73c9c

class FCollisionOctree;
class FOctreeNodeFilter {
public:
    void SingleNodeFilter(AActor *Actor, FCollisionOctree *Octree, const FPlane *Box); // 0x1184c0
    void MultiNodeFilter(AActor *Actor, FCollisionOctree *Octree, const FPlane *Box);  // 0x118530
};

class FCollisionOctreeA {
public:
    FOctreeNodeFilter *RootNode;
    __declspec(noinline) void AddActor(AActor *Actor);
    __declspec(noinline) void RemoveActor(AActor *Actor);            // 0x119a20
};

void FCollisionOctreeA::AddActor(AActor *Actor)
{
    if (!Actor || Actor->bSkipOctree || Actor->bNoOctree)
        return;

    // If the actor is already in the octree, remove it before re-adding it.
    if (Actor->OctreeNodesNum > 0)
        RemoveActor(Actor);

    Actor->OctreeBox = Actor->GetPrimitive()->GetCollisionBoundingBox(Actor);
    Actor->OctreeBox = Actor->OctreeBox.ExpandBy(4.2f);
    Actor->OctreeBox.GetCenterAndExtents(Actor->OctreeBoxCenter, Actor->OctreeBoxRadii);

    // Only add actors inside the world.
    if (!(Actor->OctreeBox.Max.X < -HALF_WORLD_MAX || Actor->OctreeBox.Min.X > HALF_WORLD_MAX ||
          Actor->OctreeBox.Max.Y < -HALF_WORLD_MAX || Actor->OctreeBox.Min.Y > HALF_WORLD_MAX ||
          Actor->OctreeBox.Max.Z < -HALF_WORLD_MAX || Actor->OctreeBox.Min.Z > HALF_WORLD_MAX))
    {
        if (Actor->Ref1a4 && !((*Actor->Ref1a4->Target)->Flags & 2)) {
            Actor->bWasSNFiltered = 0;
            RootNode->MultiNodeFilter(Actor, (FCollisionOctree *)this, &RootNodeBox);
        } else {
            Actor->bWasSNFiltered = 1;
            RootNode->SingleNodeFilter(Actor, (FCollisionOctree *)this, &RootNodeBox);
        }
    }
}

// Callees retail calls with LTCG conventions; bodies are stand-ins so the
// linker sees definitions (they are not part of the match).
class FArray {
public:
    void Remove(INT Index, INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
    void *Data; INT ArrayNum; INT ArrayMax;
};
struct FOctreeNodeActors { char Pad[0x10]; FArray Actors; };
void FCollisionOctreeA::RemoveActor(AActor *Actor)
{
    FArray &Nodes = *(FArray *)&Actor->OctreeNodesData;
    for (INT i = 0; i < Nodes.ArrayNum; i++) {
        FOctreeNodeActors *Node = ((FOctreeNodeActors **)Nodes.Data)[i];
        for (INT j = 0; j < Node->Actors.ArrayNum; j++)
            if (((AActor **)Node->Actors.Data)[j] == Actor)
                Node->Actors.Remove(j--, 1, sizeof(AActor *));
    }
    Nodes.Empty(sizeof(void *), 0);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_119860(void *A, void *B) { Escape(&GMalloc); new(A) FCollisionOctree; new(B) FCollisionOctree; Escape(A); }
void Driver_1198a0(FCollisionOctreeA *O, AActor *A, AActor *B) { Escape((void *)&GMath_Zero); Escape((void *)&GMath_UnitX); O->AddActor(A); O->AddActor(B); O->RemoveActor(A); }
