// Work item 0373: octree node of the collision hash (RVA 0x1183c0-0x11852e).
// Names are neutral (FOctreeNode_1183c0 etc.); no vtable or string names the type.
// The node is 16 bytes: a TArray of actor pointers and a pointer to an array of
// eight children (new[]-allocated, so the count sits at Children[-4]).
typedef int INT;
typedef float FLOAT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

struct FMalloc {
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

inline void operator delete[](void *Ptr) { GMalloc->Free(Ptr); }

struct FVec3 { FLOAT X, Y, Z; };
struct FBoxMinMax { FVec3 Min; FVec3 Max; };
struct FCube { FLOAT X, Y, Z, W; };

extern FLOAT OctreeChildScale_118170; // constant at 0x10c10a10 (0.5)

class AActor {
public:
    char Pad000[0xc8];
    FBoxMinMax Bounds;          // 0xc8
    char Pad0e0[0x1ec - 0xe0];
    INT HashCount;              // 0x1ec
};

class FCollisionHash;
void __stdcall FCollisionHash_RemoveActor(FCollisionHash *Hash, AActor *Actor); // RVA 0x119a20

class FArray {
public:
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// TArray<AActor*>. Its out-of-line destructor (RVA 0x17bf30) was rewritten by
// LTCG to take the array on the stack, so it is declared __stdcall here.
class FActorList;
void __stdcall ActorList_Destroy_17bf30(FActorList *List);
class FActorList : public FArray {
public:
    AActor *&operator()(INT i) { return ((AActor **)Data)[i]; }
    INT Num() { return ArrayNum; }
    void RemoveItem(AActor *Item)
    {
        for (INT i = 0; i < ArrayNum; i++)
            if ((*this)(i) == Item)
                Remove(i--, 1, sizeof(AActor *));
    }
    ~FActorList() { ActorList_Destroy_17bf30(this); }
};

// RVA 0x118170 (item 0372; defined here for its LTCG convention).
__declspec(noinline) void ChildCube_118170(FCube *Out, INT Index, const FCube *In)
{
    Out->W = In->W * OctreeChildScale_118170;
    Out->X = (FLOAT)(((Index >> 1) & 2) - 1) * Out->W + In->X;
    Out->Y = (FLOAT)((Index & 2) - 1) * Out->W + In->Y;
    Out->Z = (FLOAT)((Index & 1) * 2 - 1) * Out->W + In->Z;
}

// RVA 0x118340 (item 0372; defined here for its LTCG convention).
__declspec(noinline) INT ChildIndex_118340(const FCube *P, const FBoxMinMax *B)
{
    INT Index = 0;
    if (B->Min.X > P->X) Index = 4;
    else if (B->Max.X > P->X) return -1;
    if (B->Min.Y > P->Y) Index |= 2;
    else if (B->Max.Y > P->Y) return -1;
    if (B->Min.Z > P->Z) Index |= 1;
    else if (B->Max.Z > P->Z) return -1;
    return Index;
}

class FOctreeNode_1183c0 {
public:
    FActorList Actors;                  // 0x00
    FOctreeNode_1183c0 *Children;       // 0x0c, eight of them
    ~FOctreeNode_1183c0();
    void RemoveAll(FCollisionHash *Hash);
    void AddActor(AActor *Actor, FCollisionHash *Hash, const FCube *Cube);
    void StoreActor(AActor *Actor, FCollisionHash *Hash, const FCube *Cube); // RVA 0x118630
};

// RVA 0x1183c0
FOctreeNode_1183c0::~FOctreeNode_1183c0()
{
    if (Children) {
        delete[] Children;
        Children = 0;
    }
}

// RVA 0x118440
void FOctreeNode_1183c0::RemoveAll(FCollisionHash *Hash)
{
    while (Actors.Num()) {
        AActor *Actor = Actors(0);
        if (Actor->HashCount > 0)
            FCollisionHash_RemoveActor(Hash, Actor);
        else
            Actors.RemoveItem(Actor);
    }
    if (Children) {
        for (INT i = 0; i < 8; i++)
            Children[i].RemoveAll(Hash);
    }
}

// RVA 0x1184c0
void FOctreeNode_1183c0::AddActor(AActor *Actor, FCollisionHash *Hash, const FCube *Cube)
{
    INT Index = ChildIndex_118340(Cube, &Actor->Bounds);
    if (Children && Index != -1) {
        FCube ChildCube;
        ChildCube_118170(&ChildCube, Index, Cube);
        Children[Index].AddActor(Actor, Hash, &ChildCube);
        return;
    }
    StoreActor(Actor, Hash, Cube);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_1183c0(FOctreeNode_1183c0 *N) { Escape(&GMalloc); N->~FOctreeNode_1183c0(); delete[] N; }
void Driver_118440(FOctreeNode_1183c0 *N, FCollisionHash *H) { N->RemoveAll(H); }
void Driver_1184c0(FOctreeNode_1183c0 *N, AActor *A, FCollisionHash *H, const FCube *C) { Escape(&OctreeChildScale_118170); N->AddActor(A, H, C); }
