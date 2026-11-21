// Versus work item 0064: RVA 0x137060-0x137460 (6 functions).
// Unreal Engine 2 dynamic lighting / actor render helpers.
// Core/Engine base types (FMemStack, FMemCache, UObject, AActor, UViewport,
// FRenderInterface, FLevelSceneNode, FDynamicActor, FDynamicLight) follow UE2
// conventions; function names and Chaos Theory-specific fields/structs here are
// neutral/inferred where retail carries no symbol.

typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef double DOUBLE;
typedef unsigned __int64 QWORD;

enum { DEFAULT_ALIGNMENT = 8 };
enum { COST_INFINITE = 0x1000000, HASH_COUNT = 16384 };

template <class T> inline T Align(const T Ptr, INT Alignment)
{
    return (T)(((DWORD)Ptr + Alignment - 1) & ~(Alignment - 1));
}

template <class T> inline T Min(const T A, const T B)
{
    return (A <= B) ? A : B;
}

template <class T> inline T Max(const T A, const T B)
{
    return (A >= B) ? A : B;
}

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
inline void appFree(void *Ptr) { GMalloc->Free(Ptr); }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
};

// ---------------------------------------------------------------------------
// FMemStack (Core/UnMem.cpp)
// ---------------------------------------------------------------------------
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

    __declspec(noinline) BYTE *AllocateNewChunk(INT MinSize);

    BYTE *PushBytes(INT AllocSize, INT Alignment)
    {
        BYTE *Result = (BYTE *)(((INT)Top + (Alignment - 1)) & ~(Alignment - 1));
        Top = Result + AllocSize;
        if (Top > End)
        {
            AllocateNewChunk(AllocSize + Alignment);
            Result = (BYTE *)(((INT)Top + (Alignment - 1)) & ~(Alignment - 1));
            Top = Result + AllocSize;
        }
        return Result;
    }
};

extern FMemStack GSceneMem; // 0x10c73cac

inline void *operator new(unsigned int Size, FMemStack &Mem)
{
    return Mem.PushBytes(Size, DEFAULT_ALIGNMENT);
}

// ---------------------------------------------------------------------------
// FMemCache (Core/UnCache.cpp)
// ---------------------------------------------------------------------------
class FMemCache
{
public:
    class FCacheItem
    {
    public:
        QWORD Id;
        BYTE *Data;
        _WORD Time;
        BYTE Segment;
        BYTE Extra;
        INT Cost;
        FCacheItem *LinearNext;
        FCacheItem *LinearPrev;
        FCacheItem *HashNext;

        void Unlock()
        {
            Cost -= COST_INFINITE;
        }
    };

    INT Initialized;
    _WORD Time;
    QWORD MruId;
    FCacheItem *MruItem;
    DWORD Unknown14[4];
    FCacheItem *HashItems[HASH_COUNT];

    static DWORD GHash(DWORD Val) { return (Val ^ (Val >> 12) ^ (Val >> 24)) & (HASH_COUNT - 1); }
    __declspec(noinline) BYTE *Get(QWORD Id, FCacheItem *&Item, INT Alignment = DEFAULT_ALIGNMENT);
};

extern FMemCache GCache; // 0x10ca77f0

// ---------------------------------------------------------------------------
// Engine / Rendering structures
// ---------------------------------------------------------------------------
class FDynamicActor;
class FDynamicLight;
class AActor;

class UObject
{
public:
    virtual ~UObject();
    DWORD Index;
    DWORD GetIndex() const { return Index; }
};

inline QWORD MakeCacheID(BYTE Base, UObject *Obj)
{
    return (Obj ? (QWORD)Obj->GetIndex() : (QWORD)0) * (QWORD)0x100 + Base;
}

class AActor : public UObject
{
public:
    BYTE Pad08[0x12c - 0x08];
    FDynamicActor *ActorRenderData;         // +0x12c
    FDynamicLight *LightRenderData;         // +0x130
    INT Revision;                           // +0x134
    BYTE Pad138[0x25c - 0x138];
    TArray<AActor *> ExcludedLights;        // +0x25c
    BYTE Pad268[0x2d2 - 0x268];
    BYTE LightType;                         // +0x2d2
    BYTE Pad2d3[0x2e1 - 0x2d3];
    BYTE MaxLights;                         // +0x2e1
    BYTE Pad2e2[0x2e7 - 0x2e2];
    BYTE bUnlit2e7;                         // +0x2e7
    // +0x2e8 bitfield
    DWORD Bits2e8_0_4 : 5;
    DWORD bLightFade : 1;                   // bit 5 (0x20)
    DWORD Bits2e8_6_16 : 11;
    DWORD bDynamicLight : 1;                // bit 17 (0x20000)
    DWORD Bits2e8_18_31 : 14;
    // +0x2ec bitfield
    DWORD Bits2ec_0_28 : 29;
    DWORD bSkipStaticLights : 1;            // bit 29 (0x20000000)
    DWORD bSkipDynamicLights : 1;           // bit 30 (0x40000000)
    DWORD Bits2ec_31 : 1;

    FDynamicLight *GetLightRenderData(); // 0x10990cf0 (external thiscall)
};

#pragma pack(push, 4)
struct FActorLightFadeEntry
{
    AActor *LightActor;     // +0x00
    INT Field04;            // +0x04
    INT Field08;            // +0x08
    DOUBLE FadeStartTime;   // +0x0c
    DWORD Bit0 : 1;         // +0x14
    DWORD bEndOn : 1;       // bit 1 (0x2)
    DWORD bStartOn : 1;     // bit 2 (0x4)
    DWORD Bits3_31 : 29;
};

struct FActorLightFadeCache
{
    FActorLightFadeEntry Entries[12]; // +0x00 .. +0x11f
    INT NumEntries;                   // +0x120
};
#pragma pack(pop)

struct FRenderInterface
{
    virtual void PushState();               // +0x00
    virtual void PopState();                // +0x04
    virtual void Slot08();                  // +0x08
    virtual void Slot0c();                  // +0x0c
    virtual void Slot10();                  // +0x10
    virtual void Slot14();                  // +0x14
    virtual void Slot18();                  // +0x18
    virtual void SetCullMode(UBOOL bInvert);// +0x1c
};

struct UViewport
{
    BYTE Pad00[0x130];
    DOUBLE CurrentTime;     // +0x130
    BYTE Pad138[0x14c - 0x138];
    INT bField14c;          // +0x14c
};

struct FLevelSceneNode
{
    BYTE Pad00[0x04];
    UViewport *Viewport;    // +0x04
    BYTE Pad08[0x1b8 - 0x08];
    FLOAT Determinant;      // +0x1b8
    BYTE Pad1bc[0x1c8 - 0x1bc];
    INT bField1c8;          // +0x1c8
};

struct FZonePortalNode
{
    void *Volume;           // +0x00
    FZonePortalNode *Next;  // +0x04
};

struct FZoneRenderInfo
{
    FZonePortalNode *Portals; // +0x00
    INT Pad04;                // +0x04
};

struct FVisibleZoneNode
{
    INT ZoneIndex;          // +0x00
    FVisibleZoneNode *Next; // +0x04
};

struct FDynamicLightList;

struct FLevelRenderContext
{
    FLevelSceneNode *SceneNode;     // +0x00
    FRenderInterface *RI;           // +0x04
    BYTE Pad08[0x20 - 0x08];
    FDynamicLightList *LightList;   // +0x20
    FZoneRenderInfo Zones[64];      // +0x24 .. +0x223
    FVisibleZoneNode *VisibleZones; // +0x224
    BYTE Pad228[0x258 - 0x228];
    BYTE Field258[4];               // +0x258
};

class FDynamicLight
{
public:
    AActor *Actor;          // +0x00
    INT Revision;           // +0x04
    BYTE Pad08[0x34 - 0x08];
    // +0x34 bitfield
    DWORD Bits0_5 : 6;
    DWORD bBit6 : 1;        // 0x40
    DWORD bBit7 : 1;        // 0x80
    DWORD bBit8 : 1;        // 0x100
    DWORD Bits9_31 : 23;
    INT Pad38;              // +0x38
    FLOAT Alpha;            // +0x3c
    INT ShadowSlot;         // +0x40
    BYTE Pad44[0x50 - 0x44];
    BYTE Bounds50[0x298 - 0x50]; // +0x50
    TArray<INT> Zones;      // +0x298
};

struct FDynamicLightList
{
    FDynamicLight *Light;   // +0x00
    FDynamicLightList *Next;// +0x04

    FDynamicLightList(FDynamicLight *InLight, FDynamicLightList *InNext)
        : Light(InLight), Next(InNext) {}
};

class FDynamicActor
{
public:
    AActor *Actor;              // +0x00
    INT Revision;               // +0x04
    FLOAT Determinant;          // +0x08
    BYTE Pad0c[0xe8 - 0x0c];
    FDynamicLightList *Lights;  // +0xe8
    INT PadEc[2];
    void *Projectors;           // +0xf4

    void UpdateLightFade(FLevelSceneNode *SceneNode);
    void Render(FLevelSceneNode *SceneNode, FDynamicLightList *InLights, void *InProjectors, FRenderInterface *RI, INT Pass, void *Extra);
};

// External callee of ZoneIntersectsBounds (0x10a11570).
UBOOL VolumeIntersectsBounds(const void *Bounds, void *Volume);
// Out-of-item LTCG callee (0x10a35be0); defined in scaffolding below.
__declspec(noinline) UBOOL ZoneIntersectsBounds(FZoneRenderInfo *Zone, const void *Bounds);

// ===========================================================================
// Function 1: RVA 0x137060 — FDynamicActor::UpdateLightFade
// ===========================================================================
void FDynamicActor::UpdateLightFade(FLevelSceneNode *SceneNode)
{
    if (Actor->bLightFade)
    {
        FMemCache::FCacheItem *Item = 0;
        FActorLightFadeCache *Cache = (FActorLightFadeCache *)GCache.Get(MakeCacheID(0x30, Actor), Item, DEFAULT_ALIGNMENT);
        if (!Cache)
        {
            for (FDynamicLightList *L = Lights; L; L = L->Next)
                L->Light->Alpha = 1.0f;
            return;
        }
        INT MaxLights = Min<INT>(8, Actor->MaxLights);
        INT ActiveCount = 0;
        for (INT i = 0; i < Cache->NumEntries; i++)
        {
            FDynamicLight *Light = Cache->Entries[i].LightActor->GetLightRenderData();
            if (ActiveCount < MaxLights)
            {
                UBOOL bEnd = Cache->Entries[i].bEndOn;
                if (bEnd || Cache->Entries[i].bStartOn)
                {
                    DOUBLE StartAlpha = Cache->Entries[i].bStartOn ? 1.0f : 0.0f;
                    DOUBLE EndAlpha = bEnd ? 1.0f : 0.0f;
                    Light->Alpha = (FLOAT)(StartAlpha + (EndAlpha - StartAlpha) * ((SceneNode->Viewport->CurrentTime - Cache->Entries[i].FadeStartTime) / 0.35f));
                    ActiveCount++;
                }
            }
        }
        Item->Unlock();
    }
    else
    {
        for (FDynamicLightList *L = Lights; L; L = L->Next)
            L->Light->Alpha = 1.0f;
    }
}

// ===========================================================================
// Function 2: RVA 0x1371d0 — RenderDynamicActor
// ===========================================================================
void RenderDynamicActor(FLevelRenderContext *Context, FDynamicActor *DynamicActor, UBOOL bUpdateFade, INT Pass)
{
    Context->RI->PushState();
    Context->RI->SetCullMode(Context->SceneNode->Determinant * DynamicActor->Determinant < 0.0f);
    if (bUpdateFade && DynamicActor->Lights)
        DynamicActor->UpdateLightFade(Context->SceneNode);
    DynamicActor->Render(Context->SceneNode, DynamicActor->Lights, DynamicActor->Projectors, Context->RI, Pass, &Context->Field258);
    Context->RI->PopState();
}

// ===========================================================================
// Function 3: RVA 0x137250 — InsertSortedLight
// ===========================================================================
void InsertSortedLight(FDynamicLightList **List, FDynamicLight *Light)
{
    while (*List && Light->ShadowSlot >= (*List)->Light->ShadowSlot)
        List = &(*List)->Next;
    *List = new(GSceneMem) FDynamicLightList(Light, *List);
}

// ===========================================================================
// Function 4: RVA 0x1372d0 — AssignLightSlots
// ===========================================================================
INT AssignLightSlots(FDynamicLightList *Node)
{
    if (!Node)
        return 0;
    INT Slot = AssignLightSlots(Node->Next);
    if (Node->Light->ShadowSlot == 0)
    {
        Node->Light->ShadowSlot = Slot;
        if (Slot == 3 || Slot == -2)
            return -2;
        return Slot + 1;
    }
    return Slot;
}

// ===========================================================================
// Function 5: RVA 0x137310 — CanActorReceiveLight
// ===========================================================================
UBOOL CanActorReceiveLight(AActor *Actor, AActor *LightActor)
{
    if (!LightActor->bDynamicLight && Actor->bSkipStaticLights)
        return 0;
    if (LightActor->bDynamicLight && Actor->bSkipDynamicLights)
        return 0;
    for (INT i = 0; i < Actor->ExcludedLights.Num(); i++)
        if (Actor->ExcludedLights(i) == LightActor)
            return 0;
    return Actor->bUnlit2e7 == 0;
}

// ===========================================================================
// Function 6: RVA 0x137370 — IsLightVisibleInContext
// ===========================================================================
UBOOL IsLightVisibleInContext(FDynamicLight *Light, FLevelRenderContext *Context)
{
    if (Context->SceneNode->Viewport->bField14c)
        return 1;
    if (!Light->bBit7 || !Light->bBit8)
        return 0;
    if (Light->Actor->bDynamicLight)
    {
        for (FVisibleZoneNode *Z = Context->VisibleZones; Z; Z = Z->Next)
            if (ZoneIntersectsBounds(&Context->Zones[Z->ZoneIndex], Light->Bounds50))
                return 1;
        return 0;
    }
    if (Light->bBit6 && Context->SceneNode->bField1c8)
    {
        Light->bBit8 = 0;
        for (FVisibleZoneNode *Z = Context->VisibleZones; Z; Z = Z->Next)
        {
            for (INT i = 0; i < Light->Zones.Num(); i++)
            {
                if (Z->ZoneIndex == Light->Zones(i))
                {
                    if (ZoneIntersectsBounds(&Context->Zones[Z->ZoneIndex], Light->Bounds50))
                    {
                        Light->bBit8 = 1;
                        goto Done;
                    }
                    break;
                }
            }
        }
    }
    else
    {
        Light->bBit8 = 1;
    }
Done:
    return Light->bBit8;
}

// ===========================================================================
// Scaffolding for LTCG links (not part of the matched units).
// ===========================================================================
void Escape(void *);

UBOOL ZoneIntersectsBounds(FZoneRenderInfo *Zone, const void *Bounds)
{
    for (FZonePortalNode *P = Zone->Portals; P; P = P->Next)
        if (VolumeIntersectsBounds(Bounds, P->Volume))
            return 1;
    return 0;
}

BYTE *FMemCache::Get(QWORD Id, FCacheItem *&Item, INT Alignment)
{
    if (Id == MruId)
    {
        Item = MruItem;
        MruItem->Cost += COST_INFINITE;
        return Align(MruItem->Data, Alignment);
    }
    for (FCacheItem *HashItem = HashItems[GHash((DWORD)Id)]; HashItem; HashItem = HashItem->HashNext)
    {
        if (HashItem->Id == Id)
        {
            MruId = Id;
            MruItem = HashItem;
            Item = HashItem;
            HashItem->Time = Time;
            HashItem->Cost += COST_INFINITE;
            return Align(HashItem->Data, Alignment);
        }
    }
    return 0;
}

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
        Chunk = (FTaggedMemory *)appMalloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

void Driver_137060(FDynamicActor *A, FLevelSceneNode *S)
{
    Escape(&GCache);
    Escape(&GMalloc);
    A->UpdateLightFade(S);
    Escape(A);
    A->UpdateLightFade(S);
}

void Driver_1371d0(FLevelRenderContext *C, FDynamicActor *A, UBOOL bUpdateFade, INT Pass)
{
    Escape(&GCache);
    Escape(&GMalloc);
    RenderDynamicActor(C, A, bUpdateFade, Pass);
    Escape(C);
    RenderDynamicActor(C, A, 0, 2);
}

void Driver_137250(FDynamicLightList **List, FDynamicLight *Light)
{
    Escape(&GSceneMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    InsertSortedLight(List, Light);
    Escape(List);
    InsertSortedLight(List, Light);
}

INT Driver_1372d0(FDynamicLightList *Node)
{
    return AssignLightSlots(Node);
}

UBOOL Driver_137310(AActor *A, AActor *L)
{
    UBOOL R = CanActorReceiveLight(A, L);
    Escape(A);
    Escape(L);
    return R + CanActorReceiveLight(A, L);
}

UBOOL Driver_137370(FDynamicLight *L, FLevelRenderContext *C)
{
    UBOOL R = IsLightVisibleInContext(L, C);
    Escape(L);
    Escape(C);
    return R + IsLightVisibleInContext(L, C);
}
