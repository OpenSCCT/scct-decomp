// Work item 0384 (RVA 0xa5da0-0xa6044): TLazyArray<T> pieces (UE2 UnTemplate.h)
// for two element types, plus a TArray destructor. This object was built with
// /GL and linked with /LTCG, so several functions take arguments in registers.
//   0xa5da0 TLazyArray<FUnnamedStruct_a5df0>::Load
//   0xa5df0 operator<<(FArchive&, TArray<FUnnamedStruct_a5df0>&)  (Ar in EAX, array in EBX)
//   0xa5ed0 TLazyArray<FUnnamedStruct_a5df0>::~TLazyArray         (this on the stack)
//   0xa5f30 TLazyArray<_WORD>::Load
//   0xa5f80 TLazyArray<_WORD>::~TLazyArray                         (this on the stack)
//   0xa5fe0 TArray<FUnnamedStruct_a60a0>::~TArray                  (this on the stack)
// Layout: FLazyLoader vtable 0x00, SavedAr 0x04, SavedPos 0x08, TArray 0x0c.
// FArchive slots: Serialize +0x04, CountBytes +0x14, Tell +0x28, Seek +0x3c,
// DetachLazyLoader +0x44 (Versus has two extra slots before Seek).
typedef unsigned short TCHAR;
typedef unsigned short _WORD;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0

// Retail keeps this literal in writable data (0x10c748fc).
extern const TCHAR OperatorShlTArray[];  // L"operator<<(TArray)"

inline void *operator new(unsigned int, void *Mem) { return Mem; }

class FLazyLoader;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void Slot08(); virtual void Slot0c(); virtual void Slot10();
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual void Slot18(); virtual void Slot1c(); virtual void Slot20(); virtual void Slot24();
    virtual INT Tell();                                     // +0x28
    virtual void Slot2c(); virtual void Slot30(); virtual void Slot34(); virtual void Slot38();
    virtual void Seek(INT InPos);                           // +0x3c
    virtual void AttachLazyLoader(FLazyLoader *L);          // +0x40
    virtual void DetachLazyLoader(FLazyLoader *L);          // +0x44
    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving, ArIsTrans, ArIsPersistent;
};

FArchive &SerializeIndex(FArchive &Ar, INT &Value);   // RVA 0x1ea40, Ar in ESI, value in EDI

inline FArchive &operator<<(FArchive &Ar, INT &V) { Ar.Serialize(&V, sizeof(V)); return Ar; }
inline FArchive &operator<<(FArchive &Ar, _WORD &V) { Ar.Serialize(&V, sizeof(V)); return Ar; }

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
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
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
    void Realloc(INT ElementSize);                          // RVA 0x4600
    void Remove(INT Index, INT Count, INT ElementSize);     // RVA 0x119c0
};

template<class T> class TArray : public FArray
{
public:
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

template<class T> TArray<T>::~TArray()
{
    Remove(0, ArrayNum);
}

// TArray<_WORD> is used by another object too: its destructor is RVA 0xc4e0,
// compiled there as an ordinary thiscall, so it is only declared here.
template<> class TArray<_WORD> : public FArray
{
public:
    ~TArray();
};

class FLazyLoader
{
public:
    virtual void Load() = 0;
    virtual void Unload() = 0;
    FArchive *SavedAr;
    INT SavedPos;
};

template<class T> class TLazyArray : public TArray<T>, public FLazyLoader
{
public:
    ~TLazyArray()
    {
        if (SavedAr)
            SavedAr->DetachLazyLoader(this);
    }
    void Load()
    {
        if (SavedPos > 0)
        {
            INT PushedPos = SavedAr->Tell();
            SavedAr->Seek(SavedPos);
            *SavedAr << (TArray<T> &)*this;
            SavedPos *= -1;
            SavedAr->Seek(PushedPos);
        }
    }
    void Unload();
};

// 8-byte element; field meanings not recovered.
struct FUnnamedStruct_a5df0
{
    INT A;
    _WORD B, C;
};
inline FArchive &operator<<(FArchive &Ar, FUnnamedStruct_a5df0 &S)
{
    return Ar << S.A << S.B << S.C;
}

// 0x110-byte element whose destructor is RVA 0xa60a0.
struct FUnnamedStruct_a60a0
{
    BYTE Pad[0x110];
    ~FUnnamedStruct_a60a0();
};

FArchive &operator<<(FArchive &Ar, TArray<FUnnamedStruct_a5df0> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FUnnamedStruct_a5df0), A.ArrayMax * sizeof(FUnnamedStruct_a5df0));
    if (Ar.ArIsLoading)
    {
        INT NewNum;
        SerializeIndex(Ar, NewNum);
        A.Empty(sizeof(FUnnamedStruct_a5df0), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&A(A.Add(1, sizeof(FUnnamedStruct_a5df0)))) FUnnamedStruct_a5df0;
    }
    else
    {
        SerializeIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// RVA 0x99710 (item 0350): bulk serializer for word arrays.
FArchive &operator<<(FArchive &Ar, TArray<_WORD> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(_WORD), A.ArrayMax * sizeof(_WORD));
    SerializeIndex(Ar, A.ArrayNum);
    if (Ar.ArIsLoading) {
        A.ArrayMax = A.ArrayNum;
        if (!A.Data) {
            if (!A.ArrayNum)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(_WORD), OperatorShlTArray);
        } else if (A.ArrayNum) {
            A.Realloc(sizeof(_WORD));
        } else {
            A.ArrayNum = 0;
            A.ArrayMax = 0;
            GMalloc->Free(A.Data);
            A.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(_WORD));
    return Ar;
}

template class TLazyArray<FUnnamedStruct_a5df0>;
template class TLazyArray<_WORD>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
// Stand-in for the compact index serializer (RVA 0x1ea40), defined so the
// link gives calls to it retail's convention (Ar in ESI, value in EDI).
__declspec(noinline) FArchive &SerializeIndex(FArchive &Ar, INT &Value)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving) {
        Ar.Serialize(&Value, sizeof(INT));
        return Ar;
    }
    unsigned char B0 = (unsigned char)Value;
    Ar.Serialize(&B0, 1);
    Value = B0;
    return Ar;
}
void Driver_a5da0(TLazyArray<FUnnamedStruct_a5df0> *A, TLazyArray<_WORD> *W, TArray<FUnnamedStruct_a60a0> *B)
{
    Escape(&GMalloc);
    A->Load();
    W->Load();
    A->~TLazyArray();
    W->~TLazyArray();
    B->~TArray();
}
