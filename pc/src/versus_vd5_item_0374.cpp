// Work item w3 0374: Versus RVA 0x118630-0x1188b9 (Engine, UnOctree.cpp).
//   0x118630 FOctreeNode::StoreActor (LTCG object; keeps thiscall, ret 0xc)
//   0x1187d0 FirstNode   (neutral name: octant flags of the larger axis)
//   0x118880 NewNode          (neutral name: value paired with the smallest key)
// FOctreeNode is named from the L"FOctreeNode" allocation tag; the body follows
// UE2's FOctreeNode::StoreActor (split at 3 actors, re-filter pending actors).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned int size_t;
typedef float FLOAT;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern const TCHAR FArray_ProtectedCstorTag[]; // 0x10c10944
extern const TCHAR FOctreeNode_Tag[];          // 0x10c47b1c L"FOctreeNode"

inline void *operator new(size_t Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }
inline void *operator new[](size_t Size, const TCHAR *Tag) { return GMalloc->Malloc(Size, Tag); }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstorTag);
    }
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);                // RVA 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
    void Empty()
    {
        ArrayNum = 0;
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    __declspec(noinline) TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T)) // RVA 0x10ff00
    {
        ArrayNum = 0;
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) T(((T *)Other.Data)[i]);
    }
    __declspec(noinline) ~TArray() // RVA 0x17bf30
    {
        FArray::Remove(0, ArrayNum, sizeof(T));
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT AddItem(const T &Item)
    {
        INT Index = FArray::Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
    __declspec(noinline) INT RemoveItem(const T &Item) // RVA 0x10bd60
    {
        INT OriginalNum = ArrayNum;
        for (INT Index = 0; Index < ArrayNum; Index++)
            if ((*this)(Index) == Item)
                Remove(Index--, 1, sizeof(T));
        return OriginalNum - ArrayNum;
    }
};

template <class T> inline void *operator new(size_t Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

struct FPlane { FLOAT X, Y, Z, W; };
class AActor;
class FCollisionOctree {
public:
    void __stdcall RemoveActor(AActor *Actor);
};
class FOctreeNode;

class AActor
{
public:
    char Pad000[0x1e8];
    TArray<FOctreeNode *> OctreeNodes; // 0x1e8
    char Pad1F4[0x2e8 - 0x1f4];
    DWORD BitsLow : 31;                // 0x2e8
    DWORD bWasSNFiltered : 1;
};

#define MAX_ACTORS_PER_NODE 3
#define MIN_NODE_SIZE 100.0f

class FOctreeNode
{
public:
    TArray<AActor *> Actors;
    FOctreeNode *Children;

    FOctreeNode();  // RVA 0x1183b0
    ~FOctreeNode(); // RVA 0x1183c0
    void SingleNodeFilter(AActor *Actor, FCollisionOctree *o, const FPlane *NodeBox); // RVA 0x1184c0
    void MultiNodeFilter(AActor *Actor, FCollisionOctree *o, const FPlane *NodeBox);  // RVA 0x118530
    void StoreActor(AActor *Actor, FCollisionOctree *o, const FPlane *NodeBox);
};

// RVA 0x118630
void FOctreeNode::StoreActor(AActor *Actor, FCollisionOctree *o, const FPlane *NodeBox)
{
    // A full leaf that is still big enough splits and re-filters its actors.
    if (Actors.Num() >= MAX_ACTORS_PER_NODE && Children == 0 && NodeBox->W * 0.5f > MIN_NODE_SIZE)
    {
        Children = new (FOctreeNode_Tag) FOctreeNode[8];
        TArray<AActor *> PendingActors = Actors;
        PendingActors.AddItem(Actor);
        Actors.Empty();
        for (INT i = 0; i < PendingActors.Num(); i++)
        {
            PendingActors(i)->OctreeNodes.RemoveItem(this);
            if (PendingActors(i)->bWasSNFiltered)
                SingleNodeFilter(PendingActors(i), o, NodeBox);
            else
                MultiNodeFilter(PendingActors(i), o, NodeBox);
        }
    }
    else
    {
        Actors.AddItem(Actor);
        Actor->OctreeNodes.AddItem(this);
    }
}

void __stdcall FCollisionOctree::RemoveActor(AActor *Actor)
{
    if (!Actor)
        return;
    for (INT Index = 0; Index < Actor->OctreeNodes.Num(); Index++)
        Actor->OctreeNodes(Index)->Actors.RemoveItem(Actor);
    Actor->OctreeNodes.Empty();
}

// RVA 0x1187d0: first child octant a ray enters (UE2 UnOctree.cpp FirstNode).
INT FirstNode(FLOAT tx0, FLOAT ty0, FLOAT tz0, FLOAT txm, FLOAT tym, FLOAT tzm)
{
    INT Answer = 0;
    if (tx0 > ty0)
    {
        if (tx0 > tz0) // plane YZ
        {
            if (tym < tx0)
                Answer |= 2;
            if (tzm < tx0)
                Answer |= 1;
            return Answer;
        }
        // plane XY
        if (txm < tz0)
            Answer |= 4;
        if (tym < tz0)
            Answer |= 2;
        return Answer;
    }
    else
    {
        if (ty0 > tz0) // plane XZ
        {
            if (txm < ty0)
                Answer |= 4;
            if (tzm < ty0)
                Answer |= 1;
            return Answer;
        }
        // plane XY
        if (txm < tz0)
            Answer |= 4;
        if (tym < tz0)
            Answer |= 2;
        return Answer;
    }
}

// RVA 0x118880: next child octant along a ray (UE2 UnOctree.cpp NewNode).
static __declspec(noinline) INT NewNode(FLOAT txm, INT x, FLOAT tym, INT y, FLOAT tzm, INT z)
{
    if (txm < tym)
    {
        if (txm < tzm)
            return x;
    }
    else
    {
        if (tym < tzm)
            return y;
    }
    return z;
}

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_118630(FOctreeNode *N, AActor *A, FCollisionOctree *o, const FPlane *B)
{
    void (FOctreeNode::*P)(AActor *, FCollisionOctree *, const FPlane *) = &FOctreeNode::StoreActor;
    Escape(&P);
    Escape(&GMalloc);
    N->StoreActor(A, o, B);
}
void Visit(INT Node);
void Driver_118880(INT currNode, FLOAT txm, FLOAT tym, FLOAT tzm, FLOAT tx1, FLOAT ty1, FLOAT tz1)
{
    do
    {
        Visit(currNode);
        switch (currNode)
        {
        case 0: currNode = NewNode(txm, 4, tym, 2, tzm, 1); break;
        case 1: currNode = NewNode(txm, 5, tym, 3, tz1, 8); break;
        case 2: currNode = NewNode(txm, 6, ty1, 8, tzm, 3); break;
        case 3: currNode = NewNode(txm, 7, ty1, 8, tz1, 8); break;
        case 4: currNode = NewNode(tx1, 8, tym, 6, tzm, 5); break;
        case 5: currNode = NewNode(tx1, 8, tym, 7, tz1, 8); break;
        case 6: currNode = NewNode(tx1, 8, ty1, 8, tzm, 7); break;
        case 7: currNode = 8; break;
        }
    } while (currNode < 8);
}
INT Driver_1187d0(FLOAT *T)
{
    return FirstNode(T[0], T[1], T[2], T[3], T[4], T[5]);
}
