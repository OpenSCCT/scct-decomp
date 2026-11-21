// Work item w3 0167: Versus RVA 0xcc910-0xcce3c (LTCG object, VC7.0 /GL).
// Archive serializers for arrays of render records:
// 0xcc910 operator<<(FArchive&, TArray<FUnnamedElem_ccf80>&)   (Ar in EAX, array on stack)
// 0xcc9d0 operator<<(FArchive&, TSArray<FUnnamedElem_cc9d0>&)  (Ar in EBX, array on stack)
// 0xcca40 operator<<(FArchive&, TSArray<FUnnamedElem_cca40>&)  (Ar in EBX, array on stack)
// 0xccab0 operator<<(FArchive&, TArray<FUnnamedElem_ccea0>&)   (Ar in EAX, array in EBX)
// 0xccb60 operator<<(FArchive&, TLazyArray<FUnnamedElem_cd440>&) (Ar in ECX, array in EAX)
// 0xccd50 operator<<(FArchive&, TArray<FUnnamedElem_a128d0>&)  (Ar in EBX, array on stack)
// The lazy-array shape is UE2's TLazyArray serializer with SCCT's version
// 0xaf format (same as 0xc1950). Element type names are neutral: their
// meanings are not recovered.
typedef unsigned short TCHAR;
typedef unsigned short _WORD;
typedef short SWORD;
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
    friend FArchive &operator<<(FArchive &Ar, DWORD &I) { Ar.Serialize(&I, 4); return Ar; }
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

inline void *operator new(unsigned int, void *Mem) { return Mem; }

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

// Element types (neutral names).
struct FColor
{
    BYTE B, G, R, A;
    friend FArchive &operator<<(FArchive &Ar, FColor &Color)
    {
        return Ar << Color.R << Color.G << Color.B << Color.A;
    }
};

struct FUnnamedElem_ccf80 { FLOAT V[4]; SWORD S[4]; };          // 0x18 bytes
struct FUnnamedElem_cc9d0 { DWORD Fields[4]; };                  // 0x10 bytes
struct FUnnamedElem_cca40 { DWORD Fields[2]; };                  // 0x08 bytes
struct FUnnamedElem_ccea0 { SWORD S[4]; INT Value; };            // 0x0c bytes
struct FUnnamedElem_cd440 { DWORD Value; };

// 0x1c-byte record with a vtable (0x10c037ac), an out-of-line constructor
// (RVA 0x1128d0, see w3_item_0353) and destructor (RVA 0xa4780).
typedef unsigned __int64 QWORD;
extern QWORD UnnamedClass_1128d0_Serial; // global at 0x10c96930
FArchive &operator<<(FArchive &Ar, TArray<FColor> &A);
#pragma pack(push, 4)
struct FUnnamedElem_a128d0
{
    TArray<FColor> Colors;      // +0x04
    QWORD Id;                   // +0x10
    INT Value;                  // +0x18
    __declspec(noinline) FUnnamedElem_a128d0();
    virtual ~FUnnamedElem_a128d0();
    friend FArchive &operator<<(FArchive &Ar, FUnnamedElem_a128d0 &E)
    {
        return Ar << E.Colors << E.Value;
    }
};
#pragma pack(pop)

class FUnnamedArray_cce40 : public TArray<FUnnamedElem_a128d0>
{
public:
    __declspec(noinline) void Empty(INT Slack);             // RVA 0xcce40
};

// ---- Retail callees outside this item, defined so the LTCG link gives them
// their retail register conventions (scaffolding, not part of the unit). ----
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

FUnnamedElem_a128d0::FUnnamedElem_a128d0()                                  // RVA 0x1128d0
{
    Colors.Data = 0;
    Colors.ArrayNum = 0;
    Colors.ArrayMax = 0;
    QWORD Serial = UnnamedClass_1128d0_Serial;
    QWORD NewId = Serial * 0x100 + 0xe1;
    UnnamedClass_1128d0_Serial = Serial + 1;
    Value = 0;
    Id = NewId;
}
void FUnnamedArray_cce40::Empty(INT Slack)                                  // RVA 0xcce40
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->FUnnamedElem_a128d0::~FUnnamedElem_a128d0();
    FArray::Empty(sizeof(FUnnamedElem_a128d0), Slack);
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FColor> &A)  // RVA 0xf48e0
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((FColor *)A.Data)[A.Add(1, sizeof(FColor))]) FColor;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

inline void SerializeShortIndex(FArchive &Ar, SWORD &S)
{
    INT T = S;
    Ar << AR_INDEX(T);
    S = (SWORD)T;
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedElem_ccf80 &E)  // RVA 0xccf80
{
    Ar << E.V[0] << E.V[1] << E.V[2] << E.V[3];
    if (Ar.Ver() < 0x99) {
        FLOAT Old[4];
        for (INT j = 0; j < 3; j++)
            Ar << Old[0] << Old[1] << Old[2] << Old[3];
    }
    SerializeShortIndex(Ar, E.S[0]);
    SerializeShortIndex(Ar, E.S[1]);
    SerializeShortIndex(Ar, E.S[2]);
    SerializeShortIndex(Ar, E.S[3]);
    return Ar;
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, FUnnamedElem_ccea0 &E)  // RVA 0xccea0
{
    SerializeShortIndex(Ar, E.S[0]);
    SerializeShortIndex(Ar, E.S[1]);
    SerializeShortIndex(Ar, E.S[2]);
    SerializeShortIndex(Ar, E.S[3]);
    if (Ar.Ver() >= 0x9d && Ar.Ver() != 0x9e)
        Ar << E.Value;
    return Ar;
}

__declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<FUnnamedElem_cd440> &A)  // RVA 0xcd440
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.Add(1, sizeof(FUnnamedElem_cd440))).Value;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i).Value;
    }
    return Ar;
}

// ---- The unit. ----

// RVA 0xcc910
FArchive &operator<<(FArchive &Ar, TArray<FUnnamedElem_ccf80> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.Add(1, sizeof(FUnnamedElem_ccf80)));
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

template <class T> __forceinline FArchive &SimpleBulkSerialize(FArchive &Ar, TSArray<T> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(T), A.ArrayNum * sizeof(T));
    Ar << AR_INDEX(A.ArrayNum);
    if (A.ArrayNum > 0) {
        if (Ar.IsLoading()) {
            if (!A.Data)
                A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(T), OperatorShlTArray);
            else
                A.Realloc(sizeof(T));
        }
        Ar.Serialize(A.Data, A.ArrayNum * sizeof(T));
    }
    return Ar;
}

// RVA 0xcc9d0
FArchive &operator<<(FArchive &Ar, TSArray<FUnnamedElem_cc9d0> &A)
{
    return SimpleBulkSerialize(Ar, A);
}

// RVA 0xcca40
FArchive &operator<<(FArchive &Ar, TSArray<FUnnamedElem_cca40> &A)
{
    return SimpleBulkSerialize(Ar, A);
}

// RVA 0xccab0
FArchive &operator<<(FArchive &Ar, TArray<FUnnamedElem_ccea0> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.Add(1, sizeof(FUnnamedElem_ccea0)));
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// RVA 0xccb60
FArchive &operator<<(FArchive &Ar, TLazyArray<FUnnamedElem_cd440> &This)
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
            Ar << Skip << (TArray<FUnnamedElem_cd440> &)This;
            return Ar;
        }
        Ar << SeekPos;
        if (GUglyHackFlags & 8)
            Ar << (TArray<FUnnamedElem_cd440> &)This;
        else
            Ar.AttachLazyLoader(&This);
        if (!GLazyLoad)
            This.Load();
        Ar.Seek(SeekPos);
    } else if (Ar.IsSaving() && Ar.Ver() > 61) {
        if (Ar.Ver() >= 0xaf) {
            INT Skip = 0;
            Ar << Skip << (TArray<FUnnamedElem_cd440> &)This;
        } else {
            // Save out count for skipping over this data.
            INT CountPos = Ar.Tell();
            Ar << CountPos << (TArray<FUnnamedElem_cd440> &)This;
            INT EndPos = Ar.Tell();
            Ar.Seek(CountPos);
            Ar << EndPos;
            Ar.Seek(EndPos);
        }
    } else {
        Ar << (TArray<FUnnamedElem_cd440> &)This;
    }
    return Ar;
}

// RVA 0xccd50
FArchive &operator<<(FArchive &Ar, FUnnamedArray_cce40 &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&A(A.Add(1, sizeof(FUnnamedElem_a128d0)))) FUnnamedElem_a128d0;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_cc910(FArchive *Ar, TArray<FUnnamedElem_ccf80> *A, TSArray<FUnnamedElem_cc9d0> *B,
                  TSArray<FUnnamedElem_cca40> *C, TArray<FUnnamedElem_ccea0> *D,
                  TLazyArray<FUnnamedElem_cd440> *L, FUnnamedArray_cce40 *E)
{
    Escape(&GLazyLoad); Escape(&GUglyHackFlags); Escape(&GMalloc);
    *Ar << *A;
    *Ar << *B;
    *Ar << *C;
    *Ar << *D;
    *Ar << *L;
    *Ar << *E;
}
