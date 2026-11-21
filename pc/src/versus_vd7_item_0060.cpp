// Work item 0060: Versus RVA 0x1357f0-0x135a76 (6 functions).
// Neutral names are used where no retail symbol or string identifies a type.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

enum { INDEX_NONE = -1 };
enum { DEFAULT_ALIGNMENT = 8 };

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0

extern "C" __declspec(dllimport) INT __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
inline INT appStricmp(const TCHAR *String1, const TCHAR *String2)
{
    return _wcsicmp(String1, String2);
}

class FArray
{
public:
    void Remove(INT Index, INT Count, INT ElementSize);          // 0x109119c0
    INT Num() const { return ArrayNum; }
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
    INT FindItemIndex(const T &Item) const;
    void Remove(INT Index, INT Count = 1);
    ~TArray();
};

// RVA 0x1357f0: TArray<INT>::FindItemIndex(const INT &Item) const
template<class T> INT TArray<T>::FindItemIndex(const T &Item) const
{
    for (INT i = 0; i < ArrayNum; i++)
        if ((*this)(i) == Item)
            return i;
    return INDEX_NONE;
}
template INT TArray<INT>::FindItemIndex(const INT &Item) const;

template<class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template<class T> TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

extern const TCHAR GEmptyString[];       // 0x10c10928

class FString : public FArray
{
public:
    ~FString();                          // 0x109048b0
    const TCHAR *operator*() const { return ArrayNum ? (const TCHAR *)Data : GEmptyString; }
};

// ---- RVA 0x135820: TMapBase<FString, 4-byte value>::Remove(const TCHAR *InKey) ----
// Neutral names for the specialization; 20-byte pair element (FUnnamedEntry_14 in
// item 0110, destructor at 0x109a3370).
struct FStringIntPair
{
    INT HashNext;                        // +0x00
    FString Key;                         // +0x04
    INT Value;                           // +0x10
    ~FStringIntPair();                   // 0x109a3370
};

class FStringIntMap
{
public:
    TArray<FStringIntPair> Pairs;        // +0x00
    INT *Hash;                           // +0x0c
    INT HashCount;                       // +0x10

    void Rehash();                       // 0x1091f9c0
    void Relax()
    {
        while (HashCount > Pairs.Num() * 2 + 8)
            HashCount /= 2;
        Rehash();
    }
    INT Remove(const TCHAR *InKey);
};

// RVA 0x135820
INT FStringIntMap::Remove(const TCHAR *InKey)
{
    INT Count = 0;
    for (INT i = Pairs.Num() - 1; i >= 0; i--) {
        if (appStricmp(*Pairs(i).Key, InKey) == 0) {
            Pairs.Remove(i);
            Count++;
        }
    }
    if (Count)
        Relax();
    return Count;
}

// ---- RVA 0x135900, 0x135970, 0x1359c0: TArray<FUnnamedEntry_34> teardown ----
// Neutral names: no evidence identifies this 0x34-byte element type.
struct FUnnamedSubElement_10a7bf30
{
    INT unk_00;
    ~FUnnamedSubElement_10a7bf30();
};

// Array member at +0x04 of FUnnamedEntry_34 (destructor at 0x10a7bf30, this on stack).
struct FUnnamedEntry_34
{
    INT unk_00;                                      // +0x00
    TArray<FUnnamedSubElement_10a7bf30> SubItems;    // +0x04
    BYTE unk_10[8];                                  // +0x10
    FString Name;                                    // +0x18
    BYTE unk_24[0x10];                               // +0x24

    ~FUnnamedEntry_34();
};

// RVA 0x1359c0
FUnnamedEntry_34::~FUnnamedEntry_34()
{
}

// RVA 0x135970: out of line in retail (Index in EDI, this and Count on stack).
template <> __declspec(noinline) void TArray<FUnnamedEntry_34>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~FUnnamedEntry_34();
    FArray::Remove(Index, Count, sizeof(FUnnamedEntry_34));
}

// Explicit instantiation for RVA 0x135900 (~TArray).
template TArray<FUnnamedEntry_34>::~TArray();

// ---- RVA 0x135a10: stack-allocated working buffer constructor ----
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

    BYTE *AllocateNewChunk(INT MinSize); // 0x109577c0 (this in EDI, MinSize in EAX)
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

template<class T> inline T *New(FMemStack &Mem, INT Count = 1, INT Align = DEFAULT_ALIGNMENT)
{
    return (T *)Mem.PushBytes(Count * sizeof(T), Align);
}

extern FMemStack GMemStack_c73cac;       // 0x10c73cac

struct FUnnamedSection_135a10
{
    BYTE unk_00[0x1c];
    INT Count;                           // +0x1c
    BYTE unk_20[0x18];
};

struct FUnnamedOwner_135a10
{
    BYTE unk_00[0xd4];
    TArray<FUnnamedSection_135a10> Sections; // +0xd4
};

struct FUnnamedContext_135a10
{
    FUnnamedOwner_135a10 *Owner;         // +0x00
    INT SectionIndex;                    // +0x04
    INT unk_08;                          // +0x08
    INT unk_0c;                          // +0x0c
    DWORD *Buffer;                       // +0x10

    FUnnamedContext_135a10(FUnnamedOwner_135a10 *InOwner, INT InIndex);
};

// RVA 0x135a10
FUnnamedContext_135a10::FUnnamedContext_135a10(FUnnamedOwner_135a10 *InOwner, INT InIndex)
    : Owner(InOwner)
    , SectionIndex(InIndex)
    , unk_08(0)
    , unk_0c(0)
{
    Buffer = New<DWORD>(GMemStack_c73cac, Owner->Sections(InIndex).Count);
}

// ---- Scaffolding for LTCG link, not part of the unit ----
extern DWORD GCRCTable[256];
extern const TCHAR HashMapHash_Tag[];
extern const TCHAR MemChunk_Tag[];
TCHAR appToUpper(TCHAR c);
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

DWORD appStrihash(const TCHAR *Data)
{
    DWORD Hash = 0;
    while (*Data) {
        TCHAR Ch = appToUpper(*Data++);
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ (Ch & 0xff)) & 0xff];
        Hash = ((Hash >> 8) & 0x00FFFFFF) ^ GCRCTable[(Hash ^ (Ch >> 8)) & 0xff];
    }
    return Hash;
}

void FStringIntMap::Rehash()
{
    INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), HashMapHash_Tag);
    INT i;
    for (i = 0; i < HashCount; i++)
        NewHash[i] = -1;
    for (i = 0; i < Pairs.Num(); i++) {
        FStringIntPair &Pair = Pairs(i);
        INT iHash = appStrihash(*Pair.Key) & (HashCount - 1);
        Pair.HashNext = NewHash[iHash];
        NewHash[iHash] = i;
    }
    if (Hash)
        GMalloc->Free(Hash);
    Hash = NewHash;
}

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
inline void *operator new(unsigned int, void *Mem) { return Mem; }

INT Driver_135820(FStringIntMap *M, const TCHAR *Key)
{
    Escape(&GMalloc);
    return M->Remove(Key);
}

void Driver_135900(TArray<FUnnamedEntry_34> *A, INT Index, INT Count)
{
    Escape(&GMalloc);
    A->Remove(Index, Count);
    A->~TArray<FUnnamedEntry_34>();
}

void Driver_135a10(void *Mem, FUnnamedOwner_135a10 *Owner, INT Index)
{
    Escape(&GMemStack_c73cac);
    Escape(&GMalloc);
    Escape(&FMemStack::UnusedChunks);
    Escape(new(Mem) FUnnamedContext_135a10(Owner, Index));
}
