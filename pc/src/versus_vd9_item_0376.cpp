// Work item 0376: collision octree node queries (RVA 0x119170-0x1196e6).
// These are UE2's FOctreeNode::ActorEncroachmentCheck, ActorPointCheck and
// ActorRadiusCheck (Engine/UnOctree.cpp), compiled with /GL and linked with
// /LTCG. Field names follow UE2 where the use matches; SCCT additions are
// neutral (FieldNNN). Node bounds are passed by pointer (FOctreeNodeBounds), as in the
// published FCollisionOctree callers at 0x11a0a0-0x11a370.
#include "versus_octree_bounds.h"

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;
extern const TCHAR MemChunk_Tag[]; // L"MemChunk"
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
    BYTE *AllocateNewChunk(INT MinSize);        // RVA 0x577c0 (size in EAX, this in EDI)
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

// RVA 0x577c0, defined here only so LTCG gives it its retail convention.
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

// RVA 0x9e4d0 (LTCG: Mem in EAX, Align in EBX, Size and Count on the stack).
// Retail keeps an out-of-line copy that ActorEncroachmentCheck and
// ActorPointCheck call, while ActorRadiusCheck has the allocation inlined; the
// out-of-line copy is defined noinline here (like the other stand-ins) and the
// inlined form is the short overload below.
__declspec(noinline) void *operator new(unsigned int Size, FMemStack &Mem, INT Count, INT Align)
{
    return Mem.PushBytes(Size * Count, Align);
}
inline void *operator new(unsigned int Size, FMemStack &Mem)
{
    return Mem.PushBytes(Size, 8);
}

class AActor;
class UPrimitive;

// 0x38 bytes.
struct FCheckResult
{
    FCheckResult *Next;     // 0x00
    AActor *Actor;          // 0x04
    FVector Location;       // 0x08
    FVector Normal;         // 0x14
    UPrimitive *Primitive;  // 0x20
    FLOAT Time;             // 0x24
    INT Item;               // 0x28
    DWORD Field2C;
    DWORD Field30;
    DWORD Field34;

    FCheckResult() { Field2C = 0; Field30 = 0; Field34 = 0; }
    FCheckResult(FLOAT InTime, FCheckResult *InNext = 0);   // RVA 0x927b0
    FCheckResult(const FCheckResult &O);                    // RVA 0x91be0
    FCheckResult *&GetNext() { return Next; }
};

// RVA 0x91be0, defined here only for its LTCG convention (this in EAX, source in ECX).
__declspec(noinline) FCheckResult::FCheckResult(const FCheckResult &O)
    : Next(O.Next), Actor(O.Actor), Location(O.Location), Normal(O.Normal),
      Primitive(O.Primitive), Time(O.Time), Item(O.Item),
      Field2C(O.Field2C), Field30(O.Field30), Field34(O.Field34)
{
}

class UPrimitive
{
public:
    virtual void Vf00(); virtual void Vf01(); virtual void Vf02(); virtual void Vf03();
    virtual void Vf04(); virtual void Vf05(); virtual void Vf06(); virtual void Vf07();
    virtual void Vf08(); virtual void Vf09(); virtual void Vf10(); virtual void Vf11();
    virtual void Vf12(); virtual void Vf13(); virtual void Vf14(); virtual void Vf15();
    virtual void Vf16(); virtual void Vf17(); virtual void Vf18(); virtual void Vf19();
    virtual void Vf20(); virtual void Vf21();
    virtual UBOOL PointCheck(FCheckResult &Result, AActor *Owner, const FVector &Location,
                             const FVector &Extent, DWORD ExtraNodeFlags);  // 0x58
};

class AActor
{
public:
    virtual void Vf00(); virtual void Vf01(); virtual void Vf02(); virtual void Vf03();
    virtual void Vf04(); virtual void Vf05(); virtual void Vf06(); virtual void Vf07();
    virtual void Vf08(); virtual void Vf09(); virtual void Vf10(); virtual void Vf11();
    virtual void Vf12(); virtual void Vf13(); virtual void Vf14(); virtual void Vf15();
    virtual void Vf16(); virtual void Vf17(); virtual void Vf18(); virtual void Vf19();
    virtual void Vf20(); virtual void Vf21(); virtual void Vf22(); virtual void Vf23();
    virtual void Vf24(); virtual void Vf25(); virtual void Vf26(); virtual void Vf27();
    virtual void Vf28(); virtual void Vf29(); virtual void Vf30(); virtual void Vf31();
    virtual void Vf32(); virtual void Vf33(); virtual void Vf34(); virtual void Vf35();
    virtual void Vf36(); virtual void Vf37(); virtual void Vf38(); virtual void Vf39();
    virtual void Vf40(); virtual void Vf41(); virtual void Vf42();
    virtual UBOOL ShouldTrace(AActor *SourceActor, DWORD TraceFlags);   // 0xac
    virtual UPrimitive *GetPrimitive();                                 // 0xb0
    virtual UBOOL IsOverlapping(AActor *Other, FCheckResult *Hit);      // 0xb4

    BYTE Pad004[0xc8 - 4];
    FBox OctreeBox;             // 0xc8
    BYTE Pad0e0[0x100 - 0xe0];
    void *Field100;             // 0x100
    BYTE Pad104[4];
    AActor *Base;               // 0x108
    BYTE Pad10c[0x1fc - 0x10c];
    INT CollisionTag;           // 0x1fc
    INT JoinedTag;              // 0x200
    BYTE Pad204[0x268 - 0x204];
    FLOAT CollisionRadius;      // 0x268
    BYTE Pad26c[0x2eb - 0x26c];
    BYTE Flags2EB;              // 0x2eb
    BYTE Pad2EC[4];
    DWORD Flags2F0;             // 0x2f0
    DWORD Flags2F4;             // 0x2f4

    UBOOL IsJoinedTo(const AActor *Other) const
    {
        for (const AActor *Test = this; Test != 0; Test = Test->Base)
            if (Test == Other || (Test && Other && Test->JoinedTag == Other->JoinedTag && Test->JoinedTag))
                return 1;
        return 0;
    }
};

enum { TRACE_StopAtFirstHit = 0x200 };

// UE2 FCollisionOctree query state.
class FCollisionOctree
{
public:
    void *RootNode;             // 0x00
    INT CollisionTag;           // 0x04
    FCheckResult *ChkResult;    // 0x08
    FMemStack *Mem;             // 0x0c
    BYTE Pad10[0x1c - 0x10];
    FVector ChkStart;           // 0x1c
    BYTE Pad28[0x4c - 0x28];
    FVector ChkExtent;          // 0x4c
    DWORD ChkTraceFlags;        // 0x58
    DWORD Pad5C;
    AActor *ChkActor;           // 0x60
    FLOAT ChkRadiusSqr;         // 0x64
    FBox ChkBox;                // 0x68
};

// RVA 0x118110 (item 0372), defined here only for its LTCG convention.
__declspec(noinline) UBOOL Box1OverlapBox2(const FBox *A, const FBox *B)
{
    if (!(B->Min.X > A->Max.X) && !(A->Min.X > B->Max.X) &&
        !(B->Min.Y > A->Max.Y) && !(A->Min.Y > B->Max.Y) &&
        !(B->Min.Z > A->Max.Z) && !(A->Min.Z > B->Max.Z))
        return 1;
    return 0;
}

template <class T> class TArray
{
public:
    T &operator()(INT i) { return Data[i]; }
    INT Num() const { return ArrayNum; }
    T *Data;
    INT ArrayNum;
    INT ArrayMax;
};

class FOctreeNode
{
public:
    TArray<AActor *> Actors;    // 0x00
    FOctreeNode *Children;      // 0x0c
    void ActorEncroachmentCheck(FCollisionOctree *o, const FOctreeNodeBounds *Bounds);
    void ActorPointCheck(FCollisionOctree *o, const FOctreeNodeBounds *Bounds);
    void ActorRadiusCheck(FCollisionOctree *o, const FOctreeNodeBounds *Bounds);
};

// RVA 0x119170
void FOctreeNode::ActorEncroachmentCheck(FCollisionOctree *o, const FOctreeNodeBounds *Bounds)
{
    for (INT i = 0; i < Actors.Num(); i++) {
        AActor *testActor = Actors(i);
        if (testActor->CollisionTag != o->CollisionTag &&
            !testActor->IsJoinedTo(o->ChkActor) &&
            testActor->ShouldTrace(o->ChkActor, o->ChkTraceFlags)) {
            AActor *ChkActor = o->ChkActor;
            if ((ChkActor->Flags2F0 & 0x1000) && ChkActor->Field100 &&
                (ChkActor->Flags2F4 & 0x4000) && (testActor->Flags2EB & 1))
                continue;
            testActor->CollisionTag = o->CollisionTag;
            if (Box1OverlapBox2(&testActor->OctreeBox, &o->ChkBox)) {
                FCheckResult TestHit(1.f);
                if (o->ChkActor->IsOverlapping(testActor, &TestHit)) {
                    TestHit.Actor = testActor;
                    TestHit.Primitive = 0;
                    FCheckResult *NewResult = new(*o->Mem, 1, 8) FCheckResult(TestHit);
                    NewResult->GetNext() = o->ChkResult;
                    o->ChkResult = NewResult;
                }
            }
        }
    }
    if (Children) {
        INT childIXs[8];
        INT numChildren = GetOverlappingChildren(Bounds, &o->ChkBox, childIXs);
        for (INT i = 0; i < numChildren; i++) {
            FOctreeNodeBounds ChildBounds(*Bounds, childIXs[i]);
            Children[childIXs[i]].ActorEncroachmentCheck(o, &ChildBounds);
        }
    }
}

// RVA 0x119360
void FOctreeNode::ActorPointCheck(FCollisionOctree *o, const FOctreeNodeBounds *Bounds)
{
    for (INT i = 0; i < Actors.Num(); i++) {
        AActor *testActor = Actors(i);
        if ((testActor->Flags2F0 & 0x80000) &&
            testActor->CollisionTag != o->CollisionTag &&
            testActor->ShouldTrace(0, o->ChkTraceFlags)) {
            testActor->CollisionTag = o->CollisionTag;
            if (Box1OverlapBox2(&testActor->OctreeBox, &o->ChkBox)) {
                FCheckResult TestHit(1.f);
                if (testActor->GetPrimitive()->PointCheck(TestHit, testActor, o->ChkStart, o->ChkExtent, 0) == 0) {
                    FCheckResult *NewResult = new(*o->Mem, 1, 8) FCheckResult(TestHit);
                    NewResult->GetNext() = o->ChkResult;
                    o->ChkResult = NewResult;
                    if (o->ChkTraceFlags & TRACE_StopAtFirstHit)
                        return;
                }
            }
        }
    }
    if (Children) {
        INT childIXs[8];
        INT numChildren = GetOverlappingChildren(Bounds, &o->ChkBox, childIXs);
        for (INT i = 0; i < numChildren; i++) {
            FOctreeNodeBounds ChildBounds(*Bounds, childIXs[i]);
            Children[childIXs[i]].ActorPointCheck(o, &ChildBounds);
        }
    }
}

// RVA 0x119510
void FOctreeNode::ActorRadiusCheck(FCollisionOctree *o, const FOctreeNodeBounds *Bounds)
{
    for (INT i = 0; i < Actors.Num(); i++) {
        AActor *testActor = Actors(i);
        if (testActor->CollisionTag != o->CollisionTag) {
            testActor->CollisionTag = o->CollisionTag;
            const FVector Offset = testActor->OctreeBox.GetCenter() - o->ChkStart;
            if ((Offset | Offset)
                - testActor->CollisionRadius * testActor->CollisionRadius < o->ChkRadiusSqr) {
                FCheckResult *NewResult = new(*o->Mem) FCheckResult;
                NewResult->Actor = testActor;
                NewResult->GetNext() = o->ChkResult;
                o->ChkResult = NewResult;
            }
        }
    }
    if (Children) {
        INT childIXs[8];
        INT numChildren = GetOverlappingChildren(Bounds, &o->ChkBox, childIXs);
        for (INT i = 0; i < numChildren; i++) {
            FOctreeNodeBounds ChildBounds(*Bounds, childIXs[i]);
            Children[childIXs[i]].ActorRadiusCheck(o, &ChildBounds);
        }
    }
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_119510(FOctreeNode *N, FCollisionOctree *o, const FOctreeNodeBounds *B)
{
    Escape(&GMalloc); Escape(&FMemStack::UnusedChunks);
    N->ActorRadiusCheck(o, B);
}
void Driver_119170(FOctreeNode *N, FCollisionOctree *o, const FOctreeNodeBounds *B)
{
    Escape(&GMalloc); Escape(&FMemStack::UnusedChunks);
    N->ActorEncroachmentCheck(o, B);
}
void Driver_119360(FOctreeNode *N, FCollisionOctree *o, const FOctreeNodeBounds *B)
{
    Escape(&GMalloc); Escape(&FMemStack::UnusedChunks);
    N->ActorPointCheck(o, B);
}
