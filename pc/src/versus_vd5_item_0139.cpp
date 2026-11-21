// Work item w3 0139: Versus RVA 0xc1950-0xc1e54 (LTCG object).
// 0xc1950 operator<<(FArchive&, TLazyArray<FUnnamedElem_a5c30>&)  (Ar in ECX, array in EAX)
// 0xc1b40 operator<<(FArchive&, TLazyArray<_WORD>&)               (Ar in ECX, array in EAX)
// 0xc1d30 operator<<(FArchive&, TArray<FUnnamedStruct_c26a0>&)    (Ar in EAX, array in EBX)
// 0xc1de0 operator<<(FArchive&, TSArray<FUnnamedStruct_c1de0>&)   (Ar in EBX, array on stack)
// TLazyArray serializer: a function template so the link keeps it out of line.
// The lazy-array shape is UE2's TLazyArray serializer with SCCT's version
// 0xaf format and the GUglyHackFlags bit that loads at once (see 0xe5b80).
// Element type names are neutral: their meanings are not recovered.
typedef unsigned short TCHAR;
typedef unsigned short _WORD;
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FCompactIndex { INT Value; };
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FLazyLoader;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(void *Object);                     // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual void Slot18();                                  // +0x18
    virtual void Slot1c();                                  // +0x1c
    virtual void Slot20();                                  // +0x20
    virtual void Slot24();                                  // +0x24
    virtual INT Tell();                                     // +0x28
    virtual INT TotalSize();                                // +0x2c
    virtual UBOOL AtEnd();                                  // +0x30
    virtual void Slot34();                                  // +0x34
    virtual void Slot38();                                  // +0x38
    virtual void Seek(INT InPos);                           // +0x3c
    virtual void AttachLazyLoader(FLazyLoader *LazyLoader); // +0x40

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;          // +0x04
    INT ArNetVer;       // +0x08
    INT ArLicenseeVer;  // +0x0c
    UBOOL ArIsLoading;  // +0x10
    UBOOL ArIsSaving;   // +0x14
};

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;                 // 0x10c73bf0
// Retail keeps these literals in writable data.
extern const TCHAR OperatorShlTArray[];  // L"operator<<(TArray)", 0x10c748fc
extern const TCHAR FSArray_Tag[];        // L"FSArray"

extern UBOOL GLazyLoad;          // 0xc96924
extern DWORD GUglyHackFlags;     // 0xc968ec

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
    void Realloc(INT ElementSize);                          // RVA 0x4600
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }
};

// A simple array with only Data and Num (neutral name, as in 0x11a70).
class FSArray
{
public:
    void *Data;
    INT ArrayNum;
    void Realloc(INT ElementSize);                          // RVA 0x11a70
};
template <class T> class TSArray : public FSArray {};

class FLazyLoader
{
public:
    virtual void Load();
    FArchive *SavedAr;
    INT SavedPos;
};

template <class T> class TLazyArray : public FLazyLoader, public TArray<T> {};

template <class T> __declspec(noinline) FArchive &operator<<(FArchive &Ar, TLazyArray<T> &This)
{
    if (Ar.IsLoading()) {
        INT SeekPos = 0;
        if (Ar.Ver() <= 61) {
            Ar.AttachLazyLoader(&This);
            INT SkipCount;
            Ar << AR_INDEX(SkipCount);
            // SCCT drops the old-format skip: the position is read and discarded.
            Ar.Tell();
            return Ar;
        }
        if (Ar.Ver() >= 0xaf) {
            INT Skip;
            Ar << Skip << (TArray<T> &)This;
            return Ar;
        }
        Ar << SeekPos;
        if (GUglyHackFlags & 8)
            Ar << (TArray<T> &)This;
        else
            Ar.AttachLazyLoader(&This);
        if (!GLazyLoad)
            This.Load();
        Ar.Seek(SeekPos);
    } else if (Ar.IsSaving() && Ar.Ver() > 61) {
        if (Ar.Ver() >= 0xaf) {
            INT Skip = 0;
            Ar << Skip << (TArray<T> &)This;
        } else {
            // Save out count for skipping over this data.
            INT CountPos = Ar.Tell();
            Ar << CountPos << (TArray<T> &)This;
            INT EndPos = Ar.Tell();
            Ar.Seek(CountPos);
            Ar << EndPos;
            Ar.Seek(EndPos);
        }
    } else {
        Ar << (TArray<T> &)This;
    }
    return Ar;
}

// Element types (neutral names).
struct FUnnamedElem_a5c30 { DWORD Value; };
struct FUnnamedStruct_c26a0 { FLOAT A, B, C, D; };
struct FUnnamedStruct_c1de0 { BYTE Bytes[0x30]; };

// Retail callees that LTCG gives register conventions; defined here so the
// linker can choose them (scaffolding, matched elsewhere or not part of this item).
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCompactIndex &I)   // RVA 0x1ea40
{
    if (!Ar.IsLoading() && !Ar.IsSaving()) {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    BYTE B0 = (BYTE)I.Value;
    Ar << B0;
    I.Value = B0;
    return Ar;
}

__declspec(noinline) void FSArray::Realloc(INT ElementSize)                  // RVA 0x11a70
{
    Data = GMalloc->Realloc(Data, ArrayNum * ElementSize, FSArray_Tag);
}

template <class T> __forceinline FArchive &BulkSerialize(FArchive &Ar, TArray<T> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(T), A.ArrayMax * sizeof(T));
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (!A.Data) {
            if (!A.ArrayNum)
                return Ar;
            A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(T), OperatorShlTArray);
        } else if (A.ArrayNum) {
            A.Realloc(sizeof(T));
        } else {
            A.ArrayNum = 0;
            A.ArrayMax = 0;
            GMalloc->Free(A.Data);
            A.Data = 0;
            return Ar;
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(T));
    return Ar;
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FUnnamedElem_a5c30> &A)  // RVA 0xa5c30
{
    return BulkSerialize(Ar, A);
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<_WORD> &A)   // RVA 0x99710
{
    return BulkSerialize(Ar, A);
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedStruct_c26a0 &S)  // RVA 0xc26a0
{
    return Ar << S.A << S.B << S.C << S.D;
}

// RVA 0xc1d30
FArchive &operator<<(FArchive &Ar, TArray<FUnnamedStruct_c26a0> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.Add(1, sizeof(FUnnamedStruct_c26a0)));
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// RVA 0xc1de0: bulk serializer for a Data/Num array of 0x30-byte records.
FArchive &operator<<(FArchive &Ar, TSArray<FUnnamedStruct_c1de0> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(FUnnamedStruct_c1de0), A.ArrayNum * sizeof(FUnnamedStruct_c1de0));
    Ar << AR_INDEX(A.ArrayNum);
    if (A.ArrayNum > 0) {
        if (Ar.IsLoading()) {
            if (!A.Data)
                A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(FUnnamedStruct_c1de0), OperatorShlTArray);
            else
                A.Realloc(sizeof(FUnnamedStruct_c1de0));
        }
        Ar.Serialize(A.Data, A.ArrayNum * sizeof(FUnnamedStruct_c1de0));
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_c1950(FArchive *Ar, TLazyArray<FUnnamedElem_a5c30> *L, TLazyArray<_WORD> *W,
                  TArray<FUnnamedStruct_c26a0> *A, TSArray<FUnnamedStruct_c1de0> *S)
{
    Escape(&GLazyLoad); Escape(&GUglyHackFlags); Escape(&GMalloc);
    *Ar << *L;
    *Ar << *W;
    *Ar << *A;
    *Ar << *S;
}
