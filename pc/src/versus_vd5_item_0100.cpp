// Work item w3 0100 (RVA 0xaf020-0xaf4d5), Engine, built /GL and linked /LTCG.
//  0xaf020 FRange::GetRand, this in ESI.
//  0xaf050 FRangeVector::GetRand, this in ESI, result FVector in EDI.
//  0xaf0d0 Serialize of a UPrimitive subclass (neutral name UnnamedPrimitive_af0d0),
//          UPrimitive::Serialize inlined; `this` in ECX, ret 4.
//  0xaf360 UPrimitive::Serialize: UObject::Serialize, BoundingBox, BoundingSphere
//          (reflected vtable slot 10 of UPrimitive / UProjectorPrimitive).
//  0xaf390 operator<<(FArchive&, TArray<FUnnamedRecord_af440>&), archive in EAX,
//          array in EBX (the standard TArray serializer template).
//  0xaf440 operator<<(FArchive&, FUnnamedRecord_af440&), archive in ESI, value EAX.
// The bounding box/sphere serializers (0x860d0, 0x86060) and the compact index
// serializer (0x1ea40) are published elsewhere; they are restated here so the
// LTCG link gives them their retail register forms.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef unsigned short _WORD;
typedef float FLOAT;

#pragma pack(push, 4)

extern "C" __declspec(dllimport) int __cdecl rand(void);
#define RAND_MAX 0x7fff
inline FLOAT appFrand() { return rand() / (FLOAT)RAND_MAX; }

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

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    UBOOL IsPersistent() { return ArIsPersistent; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, _WORD &W) { Ar.Serialize(&W, 2); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, INT &I) { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, DWORD &D) { Ar.Serialize(&D, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
    UBOOL ArIsPersistent;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);        // 0x44e0
    void Empty(INT ElementSize, INT Slack);     // 0x4550
    void Realloc(INT ElementSize);              // 0x4600
    void Remove(INT Index, INT Count, INT ElementSize);   // 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    ~TArray();
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }
    void Remove(INT Index, INT Count = 1) { FArray::Remove(Index, Count, sizeof(T)); }
};


template <class T> FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    A.CountBytes(Ar);
    if (Ar.IsLoading()) {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << *new(&((T *)A.Data)[A.Add(1, sizeof(T))]) T;
    } else {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    friend FArchive &operator<<(FArchive &Ar, FVector &V) { return Ar << V.X << V.Y << V.Z; }
};

struct FRange
{
    FLOAT Min, Max;
    FLOAT GetRand();
};

// The FRange::GetRand body; retail inlines it into FRangeVector::GetRand while
// keeping an out-of-line FRange::GetRand.
inline FLOAT RangeRand(const FRange &R) { return R.Max + (R.Min - R.Max) * appFrand(); }

struct FRangeVector
{
    FRange X, Y, Z;
    FVector GetRand();
};

// RVA 0xaf020.
__declspec(noinline) FLOAT FRange::GetRand()
{
    return RangeRand(*this);
}

// RVA 0xaf050.
FVector FRangeVector::GetRand()
{
    return FVector(RangeRand(X), RangeRand(Y), RangeRand(Z));
}

// 0x18-byte bounding box as the retail serializer treats it (see 0x860d0).
struct FUnnamedPair_860d0
{
    FVector A;
    FVector B;
};

// Restated from published RVA 0x860d0.
FArchive &operator<<(FArchive &Ar, FUnnamedPair_860d0 &P)
{
    BYTE Flag = (P.A.X - P.B.X != 1.f);
    Ar << P.A << P.B << Flag;
    if (Ar.IsLoading() && !Flag) {
        P.B.X = 0.f;
        P.A.X = 1.f;
    }
    return Ar;
}

struct FUnnamedVec4_86060
{
    FLOAT X, Y, Z, W;
};

// Restated from published RVA 0x86060.
FArchive &operator<<(FArchive &Ar, FUnnamedVec4_86060 &V)
{
    if (Ar.Ver() <= 61)
        return Ar << V.X << V.Y << V.Z;
    else
        return Ar << V.X << V.Y << V.Z << V.W;
}

// Restated from published RVA 0x1ea40.
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

class UObject
{
public:
    void *VfTable;
    BYTE ObjectPad[0x28 - 4];
    void Serialize(FArchive &Ar);   // 0x15f50
};

class UPrimitive : public UObject
{
public:
    FUnnamedPair_860d0 BoundingBox;     // 0x28
    FUnnamedVec4_86060 BoundingSphere;  // 0x40
    void Serialize(FArchive &Ar);
};

// RVA 0xaf360.
void UPrimitive::Serialize(FArchive &Ar)
{
    UObject::Serialize(Ar);
    Ar << BoundingBox << BoundingSphere;
}

// 0x28-byte record: three words then eight dwords. Neutral name.
inline FArchive &operator<<(FArchive &Ar, FRange &R) { return Ar << R.Min << R.Max; }

struct FUnnamedRecord_af440
{
    _WORD A, B, C;
    FRange D, E, F;
    INT G, H;
};

// RVA 0xaf440.
FArchive &operator<<(FArchive &Ar, FUnnamedRecord_af440 &R)
{
    return Ar << R.A << R.B << R.C << R.D << R.E << R.F << R.G << R.H;
}

// RVA 0xaf390: the TArray<FUnnamedRecord_af440> instance of the serializer above.


extern const TCHAR OperatorShlTArray_Word_Tag[];   // tag at 0x10c748fc

// RVA 0x99710 (not part of this item): bulk serializer for word arrays,
// restated so the LTCG link gives it its EAX/EBX form.
template <> FArchive &operator<<(FArchive &Ar, TArray<_WORD> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayNum)
                A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(_WORD), OperatorShlTArray_Word_Tag);
            else
                return Ar;
        } else {
            if (A.ArrayNum) {
                A.Realloc(sizeof(_WORD));
            } else {
                A.ArrayNum = 0;
                A.ArrayMax = 0;
                GMalloc->Free(A.Data);
                A.Data = 0;
                return Ar;
            }
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(_WORD));
    return Ar;
}

// Element types of the arrays below; neutral names.
struct FUnnamedQuad_a6230 { _WORD A, B, C, D; };
inline FArchive &operator<<(FArchive &Ar, FUnnamedQuad_a6230 &Q) { return Ar << Q.A << Q.B << Q.C << Q.D; }
struct FUnnamedTriple_a5a80 { _WORD A; INT B, C; };
inline FArchive &operator<<(FArchive &Ar, FUnnamedTriple_a5a80 &T) { return Ar << T.A << T.B << T.C; }
struct FUnnamedPair_a7400 { INT A, B; };
inline FArchive &operator<<(FArchive &Ar, FUnnamedPair_a7400 &P) { return Ar << P.A << P.B; }

class FColor
{
public:
    BYTE B, G, R, A;
    friend FArchive &operator<<(FArchive &Ar, FColor &C) { return Ar << C.R << C.G << C.B << C.A; }
};

// 0x38-byte entry serialized by 0xaf4e0 (not part of this item).
struct FUnnamedEntry_af4e0
{
    UObject *Object;
    FVector A, B, C;
    FColor Color;
    INT D, E, F;
    FUnnamedEntry_af4e0() : Object(0) {}
    friend FArchive &operator<<(FArchive &Ar, FUnnamedEntry_af4e0 &E)
    {
        Ar << E.Object << E.C << E.B << E.A << E.Color << E.D << E.E << E.F;
        return Ar;
    }
};

// TArray<FUnnamedRecord_af440>::~TArray, RVA 0xc0e20 (not part of this item;
// retail takes `this` on the stack). TArray<_WORD>::~TArray (0xc4e0) stays
// external.
template <> TArray<FUnnamedRecord_af440>::~TArray()
{
    Remove(0, ArrayNum);
}

// A UPrimitive subclass; neutral name, layout from the serializer.
class UnnamedPrimitive_af0d0 : public UPrimitive
{
public:
    UObject *Object50;                          // 0x50
    INT Version;                                // 0x54
    INT Field58;                                // 0x58
    TArray<INT> Ints5c;                         // 0x5c
    TArray<UObject *> Objects68;                // 0x68
    FVector Vector74, Vector80, Vector8c;       // 0x74
    TArray<_WORD> Words98;                      // 0x98
    TArray<FUnnamedQuad_a6230> Quadsa4;         // 0xa4
    TArray<_WORD> Wordsb0;                      // 0xb0
    TArray<FUnnamedTriple_a5a80> Triplesbc;     // 0xbc
    TArray<FUnnamedPair_a7400> Pairsc8;         // 0xc8
    FLOAT Fd4, Fd8, Fdc, Fe0, Fe4, Fe8;         // 0xd4
    INT Fieldec;                                // 0xec
    void Serialize(FArchive &Ar);
};

// RVA 0xaf0d0.
void UnnamedPrimitive_af0d0::Serialize(FArchive &Ar)
{
    UPrimitive::Serialize(Ar);
    if (!Ar.IsPersistent())
        Ar << Object50;
    if (Ar.IsSaving())
        Version = 4;
    Ar << Version;
    Ar << Field58;
    Ar << Ints5c;
    if (Version < 2) {
        TArray<FUnnamedRecord_af440> Dummy;
        Ar << Dummy;
    }
    Ar << Objects68;
    Ar << Vector74 << Vector80 << Vector8c;
    if (Version < 2) {
        TArray<_WORD> Dummy;
        Ar << Dummy;
    }
    Ar << Words98;
    Ar << Quadsa4;
    Ar << Wordsb0;
    Ar << Triplesbc;
    Ar << Pairsc8;
    Ar << Fd4 << Fe8 << Fd8 << Fdc << Fe0 << Fe4;
    if (Version >= 3) {
        INT DummyInt;
        FUnnamedEntry_af4e0 DummyEntry;
        Ar << DummyInt << DummyEntry;
    }
    if (Version >= 4)
        Ar << Fieldec;
}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit. Link roots: all Driver_* below.
// Build: try_ltcg.py --flags "/O2 /Gy /GX".
void Escape(void *);
typedef void (UPrimitive::*SerializeFn)(FArchive &);
typedef void (UnnamedPrimitive_af0d0::*SerializeFn2)(FArchive &);
FLOAT Driver_af020(FRange *R) { return R->GetRand(); }
void Driver_af050(FRangeVector *R, FVector *Out) { *Out = R->GetRand(); }
void Driver_af360(UPrimitive *P, FArchive *Ar) { SerializeFn F = &UPrimitive::Serialize; Escape(&F); (P->*F)(*Ar); }
FArchive &Driver_af390(FArchive &Ar, char *Owner) { return Ar << *(TArray<FUnnamedRecord_af440> *)(Owner + 8); }
void Driver_af0d0(UnnamedPrimitive_af0d0 *P, FArchive *Ar) { Escape(&GMalloc); SerializeFn2 F = &UnnamedPrimitive_af0d0::Serialize; Escape(&F); (P->*F)(*Ar); }
