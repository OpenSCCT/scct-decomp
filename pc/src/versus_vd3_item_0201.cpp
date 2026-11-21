// Work item 0201: Versus RVA 0x4f670-0x4f937.
// FVector / box helpers (Unreal Engine 2 UnMath.h style).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

inline FLOAT appSqrt(FLOAT F) { return (FLOAT)sqrt(F); }

typedef unsigned short TCHAR;
#define INDEX_NONE -1

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();
    INT Num() const { return ArrayNum; }
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    TArray() : FArray() {}
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class UObject
{
public:
    virtual ~UObject();
    INT Index;
    INT GetIndex() const { return Index; }
};
inline DWORD GetTypeHash(const UObject *A) { return A ? A->GetIndex() : 0; }

extern const TCHAR HashMapHash_Tag[]; // L"HashMapHash"

// TMap keyed by an object pointer with a 4-byte value (UnTemplate.h TMapBase).
template<class TK, class TI> class TMapBase
{
protected:
    class TPair
    {
    public:
        INT HashNext;
        TK Key;
        TI Value;
    };
    TArray<TPair> Pairs;
    INT *Hash;
    INT HashCount;
    void Rehash()
    {
        INT *NewHash = (INT *)GMalloc->Malloc(HashCount * sizeof(INT), HashMapHash_Tag);
        {for (INT i = 0; i < HashCount; i++)
            NewHash[i] = INDEX_NONE;}
        {for (INT i = 0; i < Pairs.Num(); i++)
        {
            TPair &Pair = Pairs(i);
            INT iHash = (GetTypeHash(Pair.Key) & (HashCount - 1));
            Pair.HashNext = NewHash[iHash];
            NewHash[iHash] = i;
        }}
        if (Hash)
            GMalloc->Free(Hash);
        Hash = NewHash;
    }
public:
    TMapBase() : Hash(0), HashCount(8) { Rehash(); }
};

template<class TK, class TI> class TMap : public TMapBase<TK, TI>
{
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

#define SMALL_NUMBER (1.e-8f)

template<class T> inline T Square(const T A) { return A*A; }
template<class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template<class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT SizeSquared() const { return X * X + Y * Y + Z * Z; }
    UBOOL Normalize();
};

// 0x4f7a0
UBOOL FVector::Normalize()
{
    FLOAT SquareSum = X * X + Y * Y + Z * Z;
    if (SquareSum >= SMALL_NUMBER)
    {
        FLOAT Scale = 1.f / appSqrt(SquareSum);
        X *= Scale; Y *= Scale; Z *= Scale;
        return 1;
    }
    return 0;
}

// Box with Min/Max corners and no IsValid flag: SCCT marks an empty box by
// Min.X - Max.X == 1 (neutral name; the class name is not recovered).
class UnnamedBox_4f800
{
public:
    FVector Min;
    FVector Max;
    UBOOL IsValid() const { return Min.X - Max.X != 1.f; }
    UBOOL CheckValid() const;
    UnnamedBox_4f800 &operator+=(const FVector &Other);
};

#pragma auto_inline(off)
// 0x4f800 (LTCG: this in EAX)
UBOOL UnnamedBox_4f800::CheckValid() const
{
    return IsValid();
}

// 0x4f820 (LTCG: this in ECX, Other in EDX)
UnnamedBox_4f800 &UnnamedBox_4f800::operator+=(const FVector &Other)
{
    if (IsValid())
    {
        Min.X = ::Min(Min.X, Other.X);
        Min.Y = ::Min(Min.Y, Other.Y);
        Min.Z = ::Min(Min.Z, Other.Z);
        Max.X = ::Max(Max.X, Other.X);
        Max.Y = ::Max(Max.Y, Other.Y);
        Max.Z = ::Max(Max.Z, Other.Z);
    }
    else
    {
        Max = Other;
        Min = Max;
    }
    return *this;
}

// 0x4f910 (LTCG: V2 in EAX, V1 in ECX)
FLOAT FDistSquared(const FVector &V1, const FVector &V2)
{
    return Square(V2.X-V1.X) + Square(V2.Y-V1.Y) + Square(V2.Z-V1.Z);
}
#pragma auto_inline(on)

// 0x4f670: TMap<UObject*,INT>::TMap() with TMapBase's ctor inlined (LTCG:
// this on the stack, ret 4). Rehash (0x5aca0, this in ESI) is defined so the
// linker gives it the retail calling convention.

// ---- 0x4f6c0: operator<<(FArchive&, TArray<FUnnamedArray_4f6c0>&) ----
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
// register convention).
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

// Element: a 12-byte array type whose constructor (FArray::FArray, 0x4630)
// this unit calls rather than inlines. Neutral name.
class FUnnamedArray_4f6c0 : public FArray
{
public:
    FUnnamedArray_4f6c0();
    ~FUnnamedArray_4f6c0();
};
class FArrayEx : public FArray
{
public:
    INT Add(INT Count, INT ElementSize);
    void Empty(INT ElementSize, INT Slack);
    friend FArchive &operator<<(FArchive &Ar, FUnnamedArray_4f6c0 &A);
};

// 0x11b80 (body assumed: a byte array; defined so the linker picks its
// register convention).
#pragma auto_inline(off)
FArchive &operator<<(FArchive &Ar, FUnnamedArray_4f6c0 &InA)
{
    FArrayEx &A = (FArrayEx &)InA;
    Ar.CountBytes(A.ArrayNum, A.ArrayMax);
    if (Ar.IsLoading())
    {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(1, NewNum);
        A.ArrayNum = NewNum;
        Ar.Serialize(A.Data, NewNum);
    }
    else
    {
        Ar << AR_INDEX(A.ArrayNum);
        Ar.Serialize(A.Data, A.ArrayNum);
    }
    return Ar;
}
#pragma auto_inline(on)

class TArrayUnnamed : public FArray
{
public:
    FUnnamedArray_4f6c0 &operator()(INT i) { return ((FUnnamedArray_4f6c0 *)Data)[i]; }
    INT AddSlots(INT Count) { return ((FArrayEx *)this)->Add(Count, sizeof(FUnnamedArray_4f6c0)); }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(FUnnamedArray_4f6c0), ArrayMax * sizeof(FUnnamedArray_4f6c0)); }
    void Empty(INT Slack);
    // Inline helper; its explicit destructor call makes the compiler emit the
    // scalar deleting destructor here, outside the auto_inline(off) region.
    void Remove(INT Index, INT Count)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~FUnnamedArray_4f6c0();
    }
    friend FArchive &operator<<(FArchive &Ar, TArrayUnnamed &A);
};
#pragma auto_inline(off)
// 0xc660 (defined so the linker picks its register convention).
void TArrayUnnamed::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FUnnamedArray_4f6c0();
    ((FArrayEx *)this)->Empty(sizeof(FUnnamedArray_4f6c0), Slack);
}
#pragma auto_inline(on)
inline void *operator new(unsigned int, TArrayUnnamed &Array)
{
    INT Index = Array.AddSlots(1);
    return &Array(Index);
}

#pragma auto_inline(off)
FArchive &operator<<(FArchive &Ar, TArrayUnnamed &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading())
    {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) FUnnamedArray_4f6c0;
    }
    else
    {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}
#pragma auto_inline(on)

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
TMap<UObject *, INT> *Driver_4f670(void *Mem) { Escape(&GMalloc); return new(Mem) TMap<UObject *, INT>; }
typedef FArchive &(*SerializeArrayFn)(FArchive &, TArrayUnnamed &);
FArchive *Driver_4f6c0(FArchive *Ar, TArrayUnnamed *A) { Escape((void *)(SerializeArrayFn)operator<<); return &(*Ar << *A); }
UBOOL Driver_4f800(const UnnamedBox_4f800 *B) { return B->CheckValid(); }
void Driver_4f820(UnnamedBox_4f800 *B, const FVector *V) { *B += *V; }
FLOAT Driver_4f910(const FVector *A, const FVector *B) { return FDistSquared(*A, *B); }
