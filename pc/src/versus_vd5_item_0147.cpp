// Work item 0147 (wave 3): Versus RVA 0xc3e00-0xc4007, UE2 dynamic arrays
// (UnTemplate.h) from an object compiled /GL and linked /LTCG.
//   0xc3e00 TArray<TCHAR>::TArray(const TArray&)   (Other in EDI, this on stack)
//   0xc3e70 UnnamedOwner_c3e70::EmptyAll()          (this in EDI)
//   0xc3f50 TArray<UnnamedItem_c3f50>::~TArray      (this on stack)
//   0xc3fc0 TArray<UnnamedItem_c3f50>::Remove       (Index in EBX)
// Class names for 0xc3e70/0xc3f50 are neutral: no vtable label or string names them.
typedef unsigned short TCHAR;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

void *__cdecl appMemcpy(void *Dest, const void *Src, INT Count); // RVA 0x40a0

// Retail 0x10c10944.
extern const TCHAR FArray_ProtectedCstorTag[]; // L"Farray::protectedcstor"

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
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T))
    {
        appMemcpy(Data, Other.Data, ArrayNum * sizeof(T));
    }
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    void Remove(INT Index, INT Count = 1);
    void Empty()
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty();
    }
};

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

// 0x28-byte record holding three plain arrays.
struct UnnamedEntry_c3e70
{
    INT Unknown0;
    TArray<BYTE> A;
    TArray<BYTE> B;
    TArray<BYTE> C;
    ~UnnamedEntry_c3e70(); // RVA 0xc39d0
};

// Defined here so the link gives it retail's stack-argument convention; it is
// not part of this item (the compiler-generated member destructors).
__declspec(noinline) UnnamedEntry_c3e70::~UnnamedEntry_c3e70() {}

class UnnamedOwner_c3e70
{
public:
    BYTE Unknown0[0x1c];
    TArray<BYTE> Plain;
    TArray<UnnamedEntry_c3e70> Entries;
    void EmptyAll();
};

void UnnamedOwner_c3e70::EmptyAll()
{
    Plain.Empty();
    for (INT i = 0; i < Entries.Num(); i++)
    {
        UnnamedEntry_c3e70 &Entry = Entries(i);
        Entry.A.Empty();
        Entry.B.Empty();
        Entry.C.Empty();
    }
    Entries.Empty();
}

// 0x68-byte object with a virtual destructor.
class UnnamedItem_c3f50
{
public:
    virtual ~UnnamedItem_c3f50();
    BYTE Unknown4[0x64];
};

template class TArray<TCHAR>;
template class TArray<UnnamedItem_c3f50>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void MayThrow(void *);
TArray<TCHAR> Driver_c3e00(TArray<TCHAR> &Local)
{
    Escape(&GMalloc);
    return Local;
}
void Driver_c3e70(UnnamedOwner_c3e70 *A, UnnamedOwner_c3e70 *B)
{
    Escape(&GMalloc);
    A->EmptyAll();
    B->EmptyAll();
}
void Driver_c3f50()
{
    TArray<UnnamedItem_c3f50> L;
    MayThrow(&L);
}
void Driver_c3fc0(TArray<UnnamedItem_c3f50> &L, INT i, INT n)
{
    L.Remove(i, n);
    L.Remove(n, i);
    L.Remove(i);
}
