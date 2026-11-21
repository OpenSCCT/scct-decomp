// w4_item_0093.cpp -- Versus RVA 0x14e3f0-0x14e67a (work item 0093).
// Static mesh batch list accumulation (0x14e3f0), TArray destructor/Remove/Empty
// for a 0x2c-byte element (0x14e510, 0x14e560, 0x14e5d0, 0x14e620), and
// chained FBspDrawList constructor (0x14e660).

typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

enum { INDEX_NONE = -1 };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

extern const TCHAR MemChunk_Tag[]; // L"MemChunk"

template <class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

// FMemStack (UE2 Core/UnMem.h).
class FMemStack
{
public:
    struct FTaggedMemory
    {
        FTaggedMemory *Next;
        INT DataSize;
        BYTE Data[1];
    };

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
        if (Top > End)
        {
            AllocateNewChunk(AllocSize + Align);
            Result = (BYTE *)(((INT)Top + (Align - 1)) & ~(Align - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};

// Scene memory stack at retail 0x10c73cac (GSceneMem).
extern FMemStack GSceneMem;

template <class T> inline T *New(FMemStack &Mem, INT Count = 1)
{
    return (T *)Mem.PushBytes(Count * sizeof(T), 8);
}

// FArray / TArray (UE2 Core/UnTemplate.h).
class FArray
{
public:
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayMax = 0;
        ArrayNum = 0;
    }
    void Empty(INT ElementSize, INT Slack);
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Num() const { return ArrayNum; }

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray
{
public:
    // RVA 0x14e560 (instantiated for FElement2C).
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    void Empty(INT Slack = 0);
    void Remove(INT Index, INT Count = 1);
};

// TArray<T>::Empty (RVA 0x14e620 for FElement2C; kept out of line in retail).
template <class T> __declspec(noinline) void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        ((T *)Data)[i].~T();
    FArray::Empty(sizeof(T), Slack);
}

// TArray<T>::Remove (RVA 0x14e5d0 for FElement2C; kept out of line in retail).
template <class T> __declspec(noinline) void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        ((T *)Data)[i].~T();
    FArray::Remove(Index, Count, sizeof(T));
}

// --- 0x14e3f0: Static mesh batch list accumulation ---

struct FStaticMeshBatchIndex
{
    INT BatchIndex;
    INT ElementIndex;
};

struct FStaticMeshSection
{
    BYTE unk_00[0x20];
};

class UStaticMesh
{
public:
    BYTE unk_00[0x50];
    TArray<FStaticMeshSection> Sections; // 0x50 (Num at 0x54)
};

class AActor
{
public:
    BYTE unk_00[0x100];
    UStaticMesh *StaticMesh;                           // 0x100
    BYTE unk_104[0x138 - 0x104];
    TArray<FStaticMeshBatchIndex> StaticSectionBatches; // 0x138 (Num at 0x13c)
};

struct FDynamicActor
{
    AActor *Actor; // 0x00
};

struct FStaticMeshBatch
{
    BYTE unk_00[0x08];
    FArray Elements;     // 0x08 (Num at 0x0c)
    BYTE unk_14[0x48 - 0x14];
};

class ULevel
{
public:
    BYTE unk_00[0x4a74];
    TArray<FStaticMeshBatch> StaticMeshBatches; // 0x4a74
};

class FLevelSceneNode
{
public:
    BYTE unk_00[0x1bc];
    ULevel *Level; // 0x1bc
};

struct FStaticMeshBatchList
{
    INT unk_00;        // 0x00
    INT *Batches;      // 0x04
    INT **Elements;    // 0x08
    INT *NumElements;  // 0x0c
    INT NumBatches;    // 0x10
};

// AddStaticMeshToBatchList (RVA 0x14e3f0; neutral name).
// Appends each batched static mesh section of DynamicActor->Actor into BatchList.
void AddStaticMeshToBatchList(
    FDynamicActor *DynamicActor,
    FStaticMeshBatchList *BatchList,
    FLevelSceneNode *SceneNode)
{
    AActor *Owner = DynamicActor->Actor;
    UStaticMesh *Mesh = Owner->StaticMesh;
    if (Mesh && Owner->StaticSectionBatches.Num() == Mesh->Sections.Num())
    {
        for (INT SectionIndex = 0; SectionIndex < Mesh->Sections.Num(); SectionIndex++)
        {
            FStaticMeshBatchIndex &Entry = Owner->StaticSectionBatches(SectionIndex);
            if (Entry.ElementIndex != INDEX_NONE)
            {
                if (!BatchList->Elements[Entry.BatchIndex])
                {
                    BatchList->Elements[Entry.BatchIndex] = New<INT>(
                        GSceneMem,
                        SceneNode->Level->StaticMeshBatches(Entry.BatchIndex).Elements.Num());
                    BatchList->NumElements[Entry.BatchIndex] = 0;
                    BatchList->Batches[BatchList->NumBatches++] = Entry.BatchIndex;
                }
                BatchList->Elements[Entry.BatchIndex][BatchList->NumElements[Entry.BatchIndex]++] =
                    Entry.ElementIndex;
            }
        }
    }
}

// --- 0x14e510, 0x14e560, 0x14e5d0, 0x14e620: TArray of 0x2c-byte elements ---

// 12-byte member with out-of-line destructor (retail 0x10a79000; neutral name).
class FMember12
{
public:
    ~FMember12();
    BYTE unk_00[12];
};

// 0x2c-byte array element (neutral name).
struct FElement2C
{
    FMember12 Inner; // 0x00
    BYTE unk_0c[0x2c - 0x0c];
};

// Owner class holding TArray<FElement2C> at offset 4 (neutral name).
class FArrayOwner
{
public:
    INT unk_00;                  // 0x00
    TArray<FElement2C> Entries;  // 0x04
    ~FArrayOwner();
};

// FArrayOwner::~FArrayOwner (RVA 0x14e510; neutral name).
FArrayOwner::~FArrayOwner()
{
    Entries.Empty(0);
}

// --- 0x14e660: Chained FBspDrawList constructor ---

struct FBspSection
{
    BYTE unk_00[0x1c];
    INT NumNodes;      // 0x1c
    BYTE unk_20[0x38 - 0x20];
};

class UModel
{
public:
    BYTE unk_00[0xd4];
    TArray<FBspSection> Sections; // 0xd4
};

struct FBspSectionKey
{
    UModel *Model;    // 0x00
    INT SectionIndex; // 0x04
};

class FBspDrawList
{
public:
    UModel *Model;     // 0x00
    INT SectionIndex;  // 0x04
    INT NumNodes;      // 0x08
    INT NumTriangles;  // 0x0c
    INT *Nodes;        // 0x10

    FBspDrawList(UModel *InModel, INT InSectionIndex);
};

// FBspDrawList::FBspDrawList (RVA 0x135a10; defined so LTCG derives its calling convention).
FBspDrawList::FBspDrawList(UModel *InModel, INT InSectionIndex)
{
    Model = InModel;
    SectionIndex = InSectionIndex;
    NumNodes = 0;
    NumTriangles = 0;
    Nodes = New<INT>(GSceneMem, Model->Sections(SectionIndex).NumNodes);
}

// Subclass of FBspDrawList adding a link pointer at +0x14 (neutral name).
class FChainedBspDrawList : public FBspDrawList
{
public:
    FChainedBspDrawList *Next; // 0x14

    FChainedBspDrawList(const FBspSectionKey &Key, FChainedBspDrawList *InNext);
};

// FChainedBspDrawList::FChainedBspDrawList (RVA 0x14e660; neutral name).
FChainedBspDrawList::FChainedBspDrawList(const FBspSectionKey &Key, FChainedBspDrawList *InNext)
    : FBspDrawList(Key.Model, Key.SectionIndex), Next(InNext)
{
}

// FMemStack::AllocateNewChunk (RVA 0x577c0; defined so LTCG derives its calling convention).
BYTE *FMemStack::AllocateNewChunk(INT MinSize)
{
    FTaggedMemory *Chunk = 0;
    for (FTaggedMemory **Link = &UnusedChunks; *Link; Link = &(*Link)->Next)
    {
        if ((*Link)->DataSize >= MinSize)
        {
            Chunk = *Link;
            *Link = (*Link)->Next;
            break;
        }
    }
    if (!Chunk)
    {
        INT DataSize = Max(MinSize, DefaultChunkSize - (INT)sizeof(FTaggedMemory));
        Chunk = (FTaggedMemory *)GMalloc->Malloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);

void Driver_14e3f0(FDynamicActor *DA, FStaticMeshBatchList *List, FLevelSceneNode *Node)
{
    Escape(&GSceneMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    AddStaticMeshToBatchList(DA, List, Node);
    Escape(List);
    AddStaticMeshToBatchList(DA + 1, List + 1, Node);
}

void Driver_14e510(FArrayOwner *Owners, INT Idx, INT Count, INT Slack, INT Mode)
{
    Escape(&GMalloc);
    switch (Mode)
    {
    case 0:
        Owners[0].Entries.Remove(Idx, Count);
        Escape(&Owners[0]);
        break;
    case 1:
        Owners[1].Entries.Remove(Idx + 1, Count + 1);
        Escape(&Owners[1]);
        break;
    case 2:
        Owners[2].Entries.Remove(Idx + 2, Count + 2);
        Escape(&Owners[2]);
        break;
    case 3:
        Owners[3].Entries.Remove(Idx + 3, Count + 3);
        Escape(&Owners[3]);
        break;
    case 4:
        Owners[0].Entries.Empty(Slack);
        Escape(&Owners[0]);
        break;
    case 5:
        Owners[1].Entries.Empty(Slack + 1);
        Escape(&Owners[1]);
        break;
    case 6:
        Owners[2].Entries.Empty(Slack + 2);
        Escape(&Owners[2]);
        break;
    case 7:
        Owners[3].Entries.Empty(Slack + 3);
        Escape(&Owners[3]);
        break;
    case 8:
        Owners[0].~FArrayOwner();
        Escape(&Owners[0]);
        break;
    case 9:
        Owners[1].~FArrayOwner();
        Escape(&Owners[1]);
        break;
    case 10:
        Owners[2].Entries.~TArray();
        Escape(&Owners[2]);
        break;
    case 11:
        Owners[3].Entries.~TArray();
        Escape(&Owners[3]);
        break;
    }
}

inline void *operator new(unsigned int, void *Ptr) { return Ptr; }

void Driver_14e660(
    void *Buf,
    const FBspSectionKey *Key,
    FChainedBspDrawList *Next,
    UModel *Model,
    INT SecIdx,
    INT Mode)
{
    Escape(&GSceneMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    switch (Mode)
    {
    case 0: Escape(new (Buf) FBspDrawList(Model, SecIdx)); break;
    case 1: Escape(new (Buf) FBspDrawList(Model, SecIdx + 1)); break;
    case 2: Escape(new (Buf) FChainedBspDrawList(Key[0], Next)); break;
    case 3: Escape(new (Buf) FChainedBspDrawList(Key[1], Next + 1)); break;
    case 4: Escape(new (Buf) FChainedBspDrawList(Key[2], Next + 2)); break;
    case 5: Escape(new (Buf) FChainedBspDrawList(Key[3], Next + 3)); break;
    case 6: Escape(new (Buf) FChainedBspDrawList(Key[4], Next + 4)); break;
    case 7: Escape(new (Buf) FChainedBspDrawList(Key[5], Next + 5)); break;
    }
}
