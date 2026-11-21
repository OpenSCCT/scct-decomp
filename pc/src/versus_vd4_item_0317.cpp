// Work item 0317: Versus RVA 0x86750-0x86b3d.
// A 12-byte-element TArray destructor, a six-float box (min three, max three)
// with += and +, and the Unreal Engine 2 TArray serializers for a 0x5c-byte
// record and a 4-byte element. Except 0x86750 (plain thiscall), these come from
// a VC7.0 /GL object linked with /LTCG (custom register conventions).
// The LTCG functions match with /O2 /Ob1 /Gy /GX (only explicitly inline
// functions inlined; exception handling on, as the record destructor shows).
// 0x86aa0 is a near miss: 6 bytes differ (eax/ecx/edx naming in the saving loop).
// Neutral names where no string or vtable identifies the type.
// Unreal Engine 2 builds with 4-byte structure packing.
#pragma pack(push, 4)
typedef unsigned short TCHAR;
typedef unsigned short _WORD;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned int size_t;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArchive {
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);                  // slot 1
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void CountBytes(size_t InNum, size_t InMax);          // slot 5
    UBOOL IsLoading() { return ArIsLoading; }
    FArchive &ByteOrderSerialize(void *V, INT Length) { Serialize(V, Length); return *this; }
    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;          // +0x10
    UBOOL ArIsSaving;           // +0x14
    UBOOL ArIsTrans;            // +0x18
    UBOOL ArFlag1c;             // +0x1c (tested by the 0x5c record serializer)
};
inline FArchive &operator<<(FArchive &Ar, _WORD &W) { return Ar.ByteOrderSerialize(&W, sizeof(W)); }
inline FArchive &operator<<(FArchive &Ar, DWORD &D) { return Ar.ByteOrderSerialize(&D, sizeof(D)); }
inline FArchive &operator<<(FArchive &Ar, INT &I) { return Ar.ByteOrderSerialize(&I, sizeof(I)); }

class FCompactIndex { public: INT Value; };
FArchive &operator<<(FArchive &Ar, FCompactIndex &I);             // RVA 0x1ea40
#define AR_INDEX(intref) (*(FCompactIndex *)&(intref))

class FArray {
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);                          // RVA 0x44e0
    void Remove(INT Index, INT Count, INT ElementSize);           // RVA 0x119c0
    void Empty(INT ElementSize, INT Slack);                       // RVA 0x4550
    void CountBytes(FArchive &Ar, INT ElementSize)
    {
        Ar.CountBytes(ArrayNum * ElementSize, ArrayMax * ElementSize);
    }
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    ~TArray() { Remove(0, ArrayNum); }
    void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    void Empty(INT Slack = 0);
    T &operator()(INT i) { return ((T *)Data)[i]; }
};
template <class T> void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}
template <> inline void TArray<INT>::Empty(INT Slack)
{
    FArray::Empty(sizeof(INT), Slack);
}
template <class T> inline void *operator new(size_t Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}
template <class T> FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    A.CountBytes(Ar, sizeof(T));
    if (Ar.IsLoading())
    {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(A) T;
    }
    else
    {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

class FString : public FArray {
public:
    ~FString();                                                   // RVA 0xc4e0
    friend FArchive &operator<<(FArchive &Ar, FString &S);        // RVA 0x99710
};

// 12-byte POD element (FVector-sized).
struct FVector {
    FVector() {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
    FLOAT X, Y, Z;
};

// RVA 0x86750: TArray<FVector>::~TArray (12-byte elements).
template TArray<FVector>::~TArray();

template <class T> inline T Min(const T A, const T B) { return (A <= B) ? A : B; }
template <class T> inline T Max(const T A, const T B) { return (A >= B) ? A : B; }

// Six-float box; neutral name. Min.X - Max.X == 1 marks it as empty.
struct UnnamedBox_86830 {
    FVector Min;
    FVector Max;
    UnnamedBox_86830 &operator+=(const UnnamedBox_86830 &Other);
    UnnamedBox_86830 operator+(const UnnamedBox_86830 &Other) const;
};

// RVA 0x86830: `this` in EDX, Other in EAX.
UnnamedBox_86830 &UnnamedBox_86830::operator+=(const UnnamedBox_86830 &Other)
{
    if (Min.X - Max.X != 1.f)
    {
        Min.X = ::Min(Min.X, Other.Min.X);
        Min.Y = ::Min(Min.Y, Other.Min.Y);
        Min.Z = ::Min(Min.Z, Other.Min.Z);
        Max.X = ::Max(Max.X, Other.Max.X);
        Max.Y = ::Max(Max.Y, Other.Max.Y);
        Max.Z = ::Max(Max.Z, Other.Max.Z);
    }
    else
    {
        *this = Other;
    }
    return *this;
}

// RVA 0x867c0: `this` in EAX, result in ESI, Other on the stack.
UnnamedBox_86830 UnnamedBox_86830::operator+(const UnnamedBox_86830 &Other) const
{
    return UnnamedBox_86830(*this) += Other;
}

// 32-byte element; serializer at RVA 0x86b40. Neutral name.
struct UnnamedElement_86b40 { DWORD V[8]; };
FArchive &operator<<(FArchive &Ar, UnnamedElement_86b40 &E);

// Parts of the 0x5c-byte record; constructors at RVA 0x86620 and 0x1126e0.
// Both carry a 64-bit id drawn from a shared counter (0x10c96930).
extern unsigned __int64 GUnnamedIdCounter;
struct UnnamedPart_86620 {
    UnnamedPart_86620();
    virtual void Slot0();                   // vtable 0x10c0bd48
    INT Field04;
    TArray<UnnamedElement_86b40> Elements;  // +0x08
    unsigned __int64 Id;                    // +0x14
    DWORD Value;                            // +0x1c
    INT Field20;
    INT Field24;
    INT Field28;
};
struct UnnamedPart_1126e0 {
    UnnamedPart_1126e0();
    virtual void Slot0();                   // vtable 0x10c037f4
    FString Name;                           // +0x04
    unsigned __int64 Id;                    // +0x10
    DWORD Value;                            // +0x18
};

// 0x5c-byte record; neutral name. Constructor at RVA 0x86600; its implicit
// destructor is at RVA 0x861a0.
struct UnnamedRecord_869e0 {
    UnnamedRecord_869e0();
    _WORD Words[9];             // +0x00
    _WORD Pad12;
    UnnamedPart_86620 Part1;    // +0x14
    UnnamedPart_1126e0 Part2;   // +0x40
};

// RVA 0x869e0: Ar in ESI, R in EAX.
FArchive &operator<<(FArchive &Ar, UnnamedRecord_869e0 &R)
{
    Ar << R.Words[0];
    Ar << R.Words[1];
    Ar << R.Words[2];
    Ar << R.Words[3];
    Ar << R.Words[4];
    Ar << R.Words[5];
    Ar << R.Words[6];
    Ar << R.Words[7];
    Ar << R.Words[8];
    if (!Ar.ArFlag1c)
        Ar << R.Part1.Elements << R.Part1.Value << R.Part2.Name << R.Part2.Value;
    return Ar;
}

// RVA 0x86910: operator<<(FArchive&, TArray<UnnamedRecord_869e0>&).
// RVA 0x86aa0: operator<<(FArchive&, TArray<INT>&).

// Scaffolding for the link, not part of the unit. The callees below exist in
// retail (addresses given above) inside the same LTCG image; they are defined
// here only so the linker gives them register conventions like retail's.
void Escape(void *);
typedef unsigned char BYTE;
void appErrorf(const TCHAR *Fmt, ...);
extern const TCHAR CompactIndexMismatch[];
inline FArchive &operator<<(FArchive &Ar, BYTE &B) { return Ar.ByteOrderSerialize(&B, 1); }
FArchive &operator<<(FArchive &Ar, FCompactIndex &I)
{
    if (!Ar.IsLoading() && !Ar.ArIsSaving)
    {
        Ar << I.Value;
    }
    else
    {
        DWORD V = I.Value >= 0 ? I.Value : -I.Value;
        BYTE B0 = (BYTE)(((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40)));
        I.Value = 0;
        Ar << B0;
        if (B0 & 0x40)
        {
            V >>= 6;
            BYTE B1 = (BYTE)((V < 0x80) ? V : ((V & 0x7f) + 0x80));
            Ar << B1;
            if (B1 & 0x80)
            {
                V >>= 7;
                BYTE B2 = (BYTE)((V < 0x80) ? V : ((V & 0x7f) + 0x80));
                Ar << B2;
                if (B2 & 0x80)
                {
                    V >>= 7;
                    BYTE B3 = (BYTE)((V < 0x80) ? V : ((V & 0x7f) + 0x80));
                    Ar << B3;
                    if (B3 & 0x80)
                    {
                        V >>= 7;
                        BYTE B4 = (BYTE)V;
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
FArchive &operator<<(FArchive &Ar, FString &S)
{
    S.CountBytes(Ar, sizeof(TCHAR));
    Ar << AR_INDEX(S.ArrayNum);
    if (Ar.IsLoading())
    {
        S.ArrayMax = S.ArrayNum;
        if (S.Data == 0 && S.ArrayNum)
            S.Data = GMalloc->Malloc(S.ArrayNum * sizeof(TCHAR), CompactIndexMismatch);
    }
    Ar.Serialize(S.Data, S.ArrayNum * sizeof(TCHAR));
    return Ar;
}
FArchive &operator<<(FArchive &Ar, UnnamedElement_86b40 &E)
{
    for (INT i = 0; i < 8; i++) Ar << E.V[i];
    return Ar;
}
UnnamedRecord_869e0::UnnamedRecord_869e0() {}
UnnamedPart_86620::UnnamedPart_86620() : Field04(0)
{
    Id = GUnnamedIdCounter++ * 0x100 + 0xe1;
    Value = 0;
    Field20 = 0;
    Field24 = 0;
}
UnnamedPart_1126e0::UnnamedPart_1126e0()
{
    Id = GUnnamedIdCounter++ * 0x100 + 0xe2;
    Value = 0;
}
struct UnnamedGroup_82440 {
    DWORD A;
    INT Pad04;
    FString Name;               // +0x08
    INT Pad14[2];
    DWORD B;                    // +0x1c
    TArray<UnnamedRecord_869e0> Records;  // +0x20
};
void Driver_867c0(UnnamedBox_86830 *R, const UnnamedBox_86830 *A, const UnnamedBox_86830 *B)
{
    R[0] = A[0] + B[0];
    R[1] = A[1] + B[1];
    R[2] = A[2] + B[2];
    R[3] = A[3] + B[3];
}
FArchive &Driver_86910(FArchive &Ar, UnnamedGroup_82440 *G)
{
    for (INT i = 0; i < 4; i++)
        Ar << G[i].A << G[i].Name << G[i].B << G[i].Records;
    return Ar;
}
struct UnnamedHolder_823e4 {
    INT Pad[0x3d];
    TArray<INT> First;          // +0xf4
    TArray<INT> Second;         // +0x100
    DWORD Value;
};
FArchive &Driver_86aa0(FArchive &Ar, UnnamedHolder_823e4 *H)
{
    Ar << H->Value;
    Ar << H->First;
    Ar << H->Value;
    Ar << H->Second;
    Ar << H->Value;
    return Ar;
}
#pragma pack(pop)
