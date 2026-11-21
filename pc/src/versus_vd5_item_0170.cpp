// Work item w3 0170: Versus RVA 0xcd780-0xcda45.
// Bulk TArray serializers and TArray destructors (Unreal Engine 2 UnTemplate.h
// style), built with VC7.0 /GL and linked /LTCG.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned short TCHAR;

class UObject;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);
    virtual void SerializeBits(void *V, INT LengthBits);
    virtual void SerializeInt(DWORD &Value, DWORD Max);
    virtual void Preload(UObject *Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    UBOOL IsLoading() const { return ArIsLoading; }
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
};

class FCompactIndex
{
public:
    INT Value;
};
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

// 0x1ea40 (body approximated, not a match; defined so the linker picks its
// register convention: Ar in ESI, the index in EDI).
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.ArIsLoading && !Ar.ArIsSaving)
    {
        Ar.Serialize(&I.Value, sizeof(I.Value));
        return Ar;
    }
    INT Original = I.Value;
    DWORD V = Original < 0 ? -Original : Original;
    unsigned char B0 = (unsigned char)(((Original >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40)));
    I.Value = 0;
    Ar.Serialize(&B0, 1);
    if (B0 & 0x40)
    {
        V >>= 6;
        unsigned char B1 = (unsigned char)((V < 0x80) ? V : ((V & 0x7f) + 0x80));
        Ar.Serialize(&B1, 1);
        I.Value = B1 & 0x7f;
    }
    if (B0 & 0x80)
        I.Value = -I.Value;
    return Ar;
}

extern const TCHAR TArraySerialize_Tag[]; // L"operator<<(TArray)"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Realloc(INT ElementSize); // 0x4600 (realloc branch only)
    void Remove(INT Index, INT Count, INT ElementSize); // 0x119c0
};

// Element types are not recovered: neutral names by size.
struct FUnnamedElement_cd780 { INT A, B; };              // 8 bytes
struct FUnnamedElement_cd820 { INT A, B, C, D, E, F; };  // 24 bytes

template<class T> class TBulkArray : public FArray
{
};

// 0xcd780: operator<<(FArchive&, TArray<8-byte element>&) (Ar in EAX, A in EBX)
// 0xcd820: operator<<(FArchive&, TArray<24-byte element>&)
template<class T> FArchive &operator<<(FArchive &Ar, TBulkArray<T> &A)
{
        Ar.CountBytes(A.ArrayNum * sizeof(T), A.ArrayMax * sizeof(T));
        Ar << AR_INDEX(A.ArrayNum);
        if (Ar.IsLoading())
        {
            A.ArrayMax = A.ArrayNum;
            if (A.Data == 0)
            {
                if (A.ArrayMax == 0)
                    return Ar;
                A.Data = GMalloc->Malloc(A.ArrayMax * sizeof(T), TArraySerialize_Tag);
            }
            else if (A.ArrayMax)
                A.Realloc(sizeof(T));
            else
            {
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

// ---- Destructors ----

// 8-byte array header (Data, ArrayNum) whose Remove (0x11aa0) shrinks to
// the exact count. Neutral name.
class FSimpleArray
{
public:
    void *Data;
    INT ArrayNum;
    void Remove(INT Index, INT Count, INT ElementSize); // 0x11aa0
    ~FSimpleArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = 0;
    }
};

struct FUnnamedElement_cd8c0 { char Bytes[0x274]; };

template<class T> class TSimpleArray : public FSimpleArray
{
public:
    ~TSimpleArray() { Remove(0, ArrayNum, sizeof(T)); }
};

// 0xcd8c0: TSimpleArray<0x274-byte element>::~TSimpleArray (this on the stack)

class FArrayD
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    void Remove(INT Index, INT Count, INT ElementSize); // 0x119c0
    ~FArrayD()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
};

// 32-byte element with an out-of-line destructor (0xcd430, this in EAX).
// Neutral name.
void UnnamedRelease(void *);
struct FUnnamedElement_cd990
{
    void *P;
    INT Pad[7];
    ~FUnnamedElement_cd990();
};
#pragma auto_inline(off)
// 0xcd430 (body not recovered; defined so the linker picks its register
// convention).
FUnnamedElement_cd990::~FUnnamedElement_cd990() { UnnamedRelease(P); }
#pragma auto_inline(on)

template<class T> class TArrayD : public FArrayD
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    // 0xcda00: TArray<T>::Remove (this and Count on the stack, Index in EDI)
    void Remove(INT Index, INT Count = 1);
    ~TArrayD() { Remove(0, ArrayNum); }
};
#pragma auto_inline(off)
template<class T> __declspec(noinline) void TArrayD<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArrayD::Remove(Index, Count, sizeof(T));
}
#pragma auto_inline(on)

// 0xcd990: TArray<32-byte element>::~TArray (this on the stack)

// 0xcd930: destructor of an object that unregisters itself from an owner
// (owner vtable slot 0x44) and then destroys a member at +0xc (0xcd500).
// Class names are not recovered: neutral names.
class FUnnamedOwner_cd930
{
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40();
    virtual void Unregister(class FUnnamedClass_cd930 *Item); // slot 0x44
};

// Member at +0xc: an array whose destructor is 0xcd500 (element type not
// recovered; neutral name).
struct FUnnamedElement_cd500 { INT A, B; };

// Near miss: retail reserves a 4-byte frame slot (push ecx, and push -1
// before reading fs:[0]) that this source does not reproduce.
class FUnnamedClass_cd930
{
public:
    FUnnamedOwner_cd930 *Owner;
    INT Unknown8;
    TSimpleArray<FUnnamedElement_cd500> Member;
    virtual void Tick(); // vtable 0x10c048e0 contents not recovered
    ~FUnnamedClass_cd930()
    {
        if (Owner)
            Owner->Unregister(this);
    }
};

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
FArchive *Driver_cd780(FArchive *Ar, TBulkArray<FUnnamedElement_cd780> *A) { Escape(&GMalloc); return &(*Ar << *A); }
FArchive *Driver_cd820(FArchive *Ar, TBulkArray<FUnnamedElement_cd820> *A) { Escape(&GMalloc); return &(*Ar << *A); }
void Driver_cd8c0(TSimpleArray<FUnnamedElement_cd8c0> *A) { Escape(&GMalloc); A->~TSimpleArray<FUnnamedElement_cd8c0>(); }
void Driver_cd990(TArrayD<FUnnamedElement_cd990> *A) { Escape(&GMalloc); A->~TArrayD<FUnnamedElement_cd990>(); }
void Driver_cd930(FUnnamedClass_cd930 *P) { P->FUnnamedClass_cd930::~FUnnamedClass_cd930(); }
