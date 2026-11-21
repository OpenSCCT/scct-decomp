// Work item 0049 (vwork4): Versus RVA 0x12f660-0x12f98b, 6 functions.
// Four AActor probe-event wrappers (0x12f660, 0x12f6a0, 0x12f6f0, 0x12f760)
// and CheckOwnerUpdated on AActor (0x12f7c0, vtable slot 52) and
// ASPawnAttaque (0x12f870, vtable slot 52), compiled with VC7.0 /GL /LTCG.

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
    NAME_None     = 0,
    NAME_PROBEMIN = 0x12c,
    NAME_PROBEMAX = 0x16c,
    NAME_Probe135 = 0x135, // neutral name (probe bit 9)
    NAME_Probe145 = 0x145, // neutral name (probe bit 25)
    NAME_Probe14b = 0x14b, // neutral name (probe bit 31)
    NAME_Probe161 = 0x161, // neutral name (probe bit 53)
};

struct FName
{
    INT Index;
    FName() {}
    FName(EName N) : Index(N) {}
    FName(const FName &Other) : Index(Other.Index) {}
    INT GetIndex() const { return Index; }
};

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
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

    __declspec(noinline) BYTE *AllocateNewChunk(INT MinSize);
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
extern FMemStack GMem; // retail 0x10c8bbe0

inline void *operator new(unsigned int Size, FMemStack &Mem, INT Count = 1, INT Align = 8)
{
    return Mem.PushBytes(Size * Count, Align);
}

#pragma pack(push, 4)
struct FStateFrame
{
    BYTE Pad00[0x1c];
    QWORD ProbeMask;            // +0x1c
};
#pragma pack(pop)

class UFunction;
class AActor;

struct FActorLink
{
    AActor *Actor;
    FActorLink *Next;
    FActorLink(AActor *InActor, FActorLink *InNext)
        : Actor(InActor), Next(InNext) {}
};

class ULevel
{
public:
    BYTE Pad00[0x3a50];
    FActorLink *NewlySpawned;   // +0x3a50
    UBOOL InTick;               // +0x3a54
    UBOOL Ticked;               // +0x3a58
};

class UObject
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0C();
    virtual void ProcessEvent(UFunction *Function, void *Parms, void *Result = 0); // +0x10

    INT Index;                  // +0x04
    UObject *HashNext;          // +0x08
    FStateFrame *StateFrame;    // +0x0c

    UFunction *FindFunctionChecked(FName InName, UBOOL Global = 0); // RVA 0x16830

    UBOOL IsProbing(FName ProbeName)
    {
        return ProbeName.GetIndex() < NAME_PROBEMIN
            || ProbeName.GetIndex() >= NAME_PROBEMAX
            || !StateFrame
            || (StateFrame->ProbeMask & ((QWORD)1 << (ProbeName.GetIndex() - NAME_PROBEMIN)));
    }
};

class AActor : public UObject
{
public:
    BYTE Pad10[0x104 - 0x10];
    AActor *Owner;              // +0x104
    BYTE Pad108[0x1a4 - 0x108];
    ULevel *XLevel;             // +0x1a4
    BYTE Pad1A8[0x2e8 - 0x1a8];
    DWORD Bits2E8_0 : 16;       // +0x2e8
    DWORD bTicked : 1;          // 0x00010000 (+0x2ea bit 0)
    DWORD Bits2E8_17 : 15;

    virtual UBOOL CheckOwnerUpdated(); // vtable slot 52

    __declspec(noinline) void eventProbe145();
    __declspec(noinline) void eventProbe14b(INT A);
    __declspec(noinline) UBOOL eventProbe161(FVector V, INT A);
    __declspec(noinline) void eventProbe135(FVector V, INT A);
};

class ASPawnAttaque : public AActor
{
public:
    BYTE Pad2EC[0x38c - 0x2ec];
    AActor *Controller;         // +0x38c

    virtual UBOOL CheckOwnerUpdated(); // vtable slot 52
};

// RVA 0x12f660 (LTCG: this in ESI).
void AActor::eventProbe145()
{
    if (IsProbing(NAME_Probe145))
        ProcessEvent(FindFunctionChecked(NAME_Probe145), 0);
}

// RVA 0x12f6a0 (LTCG: this in ESI, arg on stack, ret 4).
void AActor::eventProbe14b(INT A)
{
    if (IsProbing(NAME_Probe14b))
    {
        struct { INT A; } Parms;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(NAME_Probe14b), &Parms);
    }
}

// RVA 0x12f6f0 (LTCG: this in ESI, args on stack, ret 0x10).
UBOOL AActor::eventProbe161(FVector V, INT A)
{
    struct AActor_eventProbe161_Parms { FVector V; INT A; UBOOL ReturnValue; } Parms;
    Parms.ReturnValue = 0;
    if (IsProbing(NAME_Probe161))
    {
        Parms.V = V;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(NAME_Probe161), &Parms);
    }
    return Parms.ReturnValue;
}

// RVA 0x12f760 (LTCG: this in ESI, args on stack, ret 0x10).
void AActor::eventProbe135(FVector V, INT A)
{
    if (IsProbing(NAME_Probe135))
    {
        struct AActor_eventProbe135_Parms { FVector V; INT A; } Parms;
        Parms.V = V;
        Parms.A = A;
        ProcessEvent(FindFunctionChecked(NAME_Probe135), &Parms);
    }
}

// RVA 0x12f7c0 (AActor vtable slot 52, LTCG).
UBOOL AActor::CheckOwnerUpdated()
{
    if (Owner && (UBOOL)Owner->bTicked != XLevel->Ticked)
    {
        XLevel->NewlySpawned = new (GMem) FActorLink(this, XLevel->NewlySpawned);
        return 0;
    }
    return 1;
}

// RVA 0x12f870 (ASPawnAttaque vtable slot 52, LTCG).
// Near miss: retail inlines the first new(GMem) (Owner branch) and calls
// operator new(8, GMem, 1, 8) (0x9e4d0) out-of-line for the second (Controller
// branch); in a standalone LTCG link VC7.0 inlines both calls.
UBOOL ASPawnAttaque::CheckOwnerUpdated()
{
    if (Owner && (UBOOL)Owner->bTicked != XLevel->Ticked)
    {
        XLevel->NewlySpawned = new (GMem) FActorLink(this, XLevel->NewlySpawned);
        return 0;
    }
    if (Controller && (UBOOL)Controller->bTicked != XLevel->Ticked)
    {
        XLevel->NewlySpawned = new (GMem) FActorLink(this, XLevel->NewlySpawned);
        return 0;
    }
    return 1;
}

// RVA 0x577c0 (FMemStack::AllocateNewChunk), copied from versus_vd3_item_0234.cpp
// so LTCG gives it its retail convention (MinSize in EAX, this in EDI).
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

// Scaffolding for the LTCG link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);

void Driver_12f660(AActor *A, AActor *B, AActor *C)
{
    A->eventProbe145();
    B->eventProbe145();
    C->eventProbe145();
}

void Driver_12f6a0(AActor *A, AActor *B, AActor *C, INT X)
{
    A->eventProbe14b(X);
    B->eventProbe14b(X + 1);
    C->eventProbe14b(0);
}

UBOOL Driver_12f6f0(AActor *A, AActor *B, AActor *C, FVector V, INT X)
{
    return A->eventProbe161(V, X) + B->eventProbe161(V, X + 1) + C->eventProbe161(V, 0);
}

void Driver_12f760(AActor *A, AActor *B, AActor *C, FVector V, INT X)
{
    A->eventProbe135(V, X);
    B->eventProbe135(V, X + 1);
    C->eventProbe135(V, 0);
}

UBOOL Driver_12f7c0(AActor *A, void *Buf)
{
    Escape(&GMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    Escape(new (Buf) AActor());
    return A->CheckOwnerUpdated();
}

UBOOL Driver_12f870(AActor *A, void *Buf1, void *Buf2)
{
    Escape(&GMem);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    Escape(new (Buf1) AActor());
    Escape(new (Buf2) ASPawnAttaque());
    return A->CheckOwnerUpdated();
}
