// Work item 0358 (RVA 0x9da50-0x9ddf2): an LTCG object. Five template
// instances: TArray<T>::AddItem for a 28-byte element, a chunked pointer list
// allocated on a memory stack, and three TArray<T> serializers
// (operator<<(FArchive&, TArray<T>&)) for 0x48-, 12- and 16-byte elements.
// Element and container names are neutral (no symbols or strings name them);
// FArchive, FArray, TArray, FMemStack and AR_INDEX follow UE2.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

#pragma pack(push, 4)

class UObject;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

inline void *operator new(unsigned int, void *Mem) { return Mem; }

struct FCompactIndex
{
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    // MSVC lays overloaded virtuals out in reverse order.
    virtual FArchive &operator<<(class FName &N);           // +0x1c
    virtual FArchive &operator<<(UObject *&Res);            // +0x18

    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    void ByteOrderSerialize(void *V, INT Length) { Serialize(V, Length); }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.ByteOrderSerialize(&F, sizeof(F)); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &D) { Ar.ByteOrderSerialize(&D, sizeof(D)); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);   // RVA 0x1ea40

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);        // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);     // RVA 0x4550
};

template <class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }
    void AddItem(const T &Item);

    friend FArchive &operator<<(FArchive &Ar, TArray &A)
    {
        A.CountBytes(Ar);
        if (Ar.IsLoading()) {
            INT NewNum;
            Ar << AR_INDEX(NewNum);
            A.Empty(NewNum);
            for (INT i = 0; i < NewNum; i++)
                Ar << *new(A) T;
        } else {
            Ar << AR_INDEX(A.ArrayNum);
            for (INT i = 0; i < A.ArrayNum; i++)
                Ar << A(i);
        }
        return Ar;
    }
};

template <class T> void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};

// 28-byte element (neutral name).
struct FElement28_9da50 { DWORD Fields[7]; };

// RVA 0x9da50 (array in EAX, item on the stack). Near miss: retail loads Data
// before the item pointer (10 bytes of scheduling differ). noinline stands in
// for retail callers the scaffold cannot reproduce.
template <class T> __declspec(noinline) void TArray<T>::AddItem(const T &Item)
{
    ((T *)Data)[Add(1, sizeof(T))] = Item;
}
template void TArray<FElement28_9da50>::AddItem(const FElement28_9da50 &);

// FMemStack (UE2).
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
// Memory stack at retail 0x10c73cac (not GMem; neutral name).
extern FMemStack GMemStack_c73cac;
inline void *operator new(unsigned int Size, FMemStack &Mem) { return Mem.PushBytes(Size, 8); }

// A list of pointers kept in 32-entry chunks pushed on a memory stack
// (neutral names).
struct FPointerChunk_9da80
{
    INT Base;                           // 0x00 index of Items[0]
    void *Items[32];                    // 0x04
    FPointerChunk_9da80 *Next;          // 0x84
};
struct FChunkedPointerList_9da80
{
    FPointerChunk_9da80 *First;         // 0x00
    FPointerChunk_9da80 *Last;          // 0x04
    INT Count;                          // 0x08
    void Add(void *Item);
};

// RVA 0x9da80 (this in ESI, item on the stack).
void FChunkedPointerList_9da80::Add(void *Item)
{
    if (!Last || Count - Last->Base == 32) {
        FPointerChunk_9da80 *Chunk = new(GMemStack_c73cac) FPointerChunk_9da80;
        Chunk->Next = 0;
        if (Last) {
            Chunk->Base = Last->Base + 32;
            Last->Next = Chunk;
        } else {
            Chunk->Base = 0;
            First = Chunk;
        }
        Last = Chunk;
    }
    Last->Items[Count - Last->Base] = Item;
    Count++;
}

// 0x48-byte element; its serializer is RVA 0x9dee0 (element in EAX, archive
// in ESI), defined below as scaffolding so the link gives it that convention.
struct FElement48_9db20
{
    FLOAT A;
    FVector V0, V1, V2, V3, V4;
    FLOAT B, C;
    friend FArchive &operator<<(FArchive &Ar, FElement48_9db20 &E);
};

// 16-byte element: an object reference and a vector.
struct FElement16_9dcd0
{
    UObject *Object;
    FVector Location;
    friend FArchive &operator<<(FArchive &Ar, FElement16_9dcd0 &E) { return Ar << E.Object << E.Location.X << E.Location.Y << E.Location.Z; }
};

// RVA 0x9db20: operator<<(FArchive&, TArray<FElement48_9db20>&) (archive in EAX, array in EBX).
// RVA 0x9dbd0: operator<<(FArchive&, TArray<FVector>&) (archive in EAX, array on the stack).
// RVA 0x9dcd0: operator<<(FArchive&, TArray<FElement16_9dcd0>&) (archive in EAX, array on the stack).
template class TArray<FElement48_9db20>;
template class TArray<FVector>;
template class TArray<FElement16_9dcd0>;

#pragma pack(pop)

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.

// RVA 0x1ea40, from item 0116.
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
    } else {
        INT Original = I.Value;
        DWORD V = Original >= 0 ? Original : -Original;
        BYTE B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40) {
            V >>= 6;
            BYTE B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B1;
            if (B1 & 0x80) {
                V >>= 7;
                BYTE B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B2;
                if (B2 & 0x80) {
                    V >>= 7;
                    BYTE B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                    Ar << B3;
                    if (B3 & 0x80) {
                        V >>= 7;
                        BYTE B4 = V;
                        Ar << B4;
                        I.Value = B4;
                    }
                    I.Value = (I.Value << 7) + (B3 & 0x7f);
                }
                I.Value = (I.Value << 7) + (B2 & 0x7f);
            }
            I.Value = (I.Value << 7) + (B1 & 0x7f);
        }
        I.Value = (I.Value << 6) + (B0 & 0x3f);
        if (B0 & 0x80)
            I.Value = -I.Value;
    }
    return Ar;
}

// RVA 0x9dee0.
FArchive &operator<<(FArchive &Ar, FElement48_9db20 &E)
{
    return Ar << E.A << E.V0 << E.V1 << E.V2 << E.V3 << E.V4 << E.B << E.C;
}

// RVA 0x577c0 (UE2 FMemStack::AllocateNewChunk), as matched in item 0234.
extern const TCHAR MemChunk_Tag[]; // L"MemChunk"
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }
BYTE *FMemStack::AllocateNewChunk(INT MinSize)
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
        Chunk = (FTaggedMemory *)GMalloc->Malloc(DataSize + sizeof(FTaggedMemory), MemChunk_Tag);
        Chunk->DataSize = DataSize;
    }
    Chunk->Next = TopChunk;
    TopChunk = Chunk;
    Top = Chunk->Data;
    End = Top + Chunk->DataSize;
    return Top;
}

void Escape(void *);
void Driver_9da50(TArray<FElement28_9da50> *A, FElement28_9da50 *Item)
{
    for (INT i = 0; i < 16; i++)
        A[i].AddItem(Item[i]);
}
void Driver_9da50b(TArray<FElement28_9da50> *A, FElement28_9da50 *Item)
{
    A[3].AddItem(Item[5]);
    Escape(A);
    A[1].AddItem(Item[2]);
    Escape(A);
    A[2].AddItem(Item[7]);
}
void Driver_9da80(FChunkedPointerList_9da80 *L, void *Item)
{
    Escape(&GMemStack_c73cac);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    L->Add(Item);
}
void Driver_9db20(FArchive *Ar, TArray<FElement48_9db20> *A, TArray<FVector> *B, TArray<FElement16_9dcd0> *C)
{
    Escape(&(*Ar << *A));
    Escape(&(*Ar << *B));
    Escape(&(*Ar << *C));
}
