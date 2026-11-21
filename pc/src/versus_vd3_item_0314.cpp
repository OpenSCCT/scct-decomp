// Work item 0314 (RVA 0x85f30-0x86194): archive serializers and a TArray
// element type from an LTCG object (custom register conventions).
//  0x85f30 operator<<(FArchive&, TArray<FElement16>&): bulk serializer, array
//          in EBX, archive in EAX (tag string "operator<<(TArray)").
//  0x85fd0 TArray<FUnnamedEntry_86010>::Empty(Slack), array in ESI.
//  0x86010 FUnnamedEntry_86010::~FUnnamedEntry_86010, this on the stack.
//  0x86060 operator<<(FArchive&, FUnnamedVec4_86060&), archive ESI, value EAX.
//  0x860d0 operator<<(FArchive&, FUnnamedPair_860d0&), archive ESI, value EDI.
//  0x86170 FUnnamedEntry_86010 constructor, this in EAX.
// Type names are neutral: nothing in the binary names these structs.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef unsigned char BYTE;
typedef float FLOAT;

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

    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }

    friend FArchive &operator<<(FArchive &Ar, BYTE &B)
    {
        Ar.Serialize(&B, 1);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FLOAT &F)
    {
        Ar.Serialize(&F, 4);
        return Ar;
    }
    friend FArchive &operator<<(FArchive &Ar, FCompactIndex &I);

    INT ArVer;
    INT ArNetVer;
    INT ArLicenseeVer;
    UBOOL ArIsLoading;
    UBOOL ArIsSaving;
    UBOOL ArIsTrans;
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray();                                  // 0x1ef20
    void Realloc(INT ElementSize);              // 0x4600
    void Empty(INT ElementSize, INT Slack);     // 0x4550
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray();
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void CountBytes(FArchive &Ar) { Ar.CountBytes(ArrayNum * sizeof(T), ArrayMax * sizeof(T)); }
    void Empty(INT Slack);
};

class FString : public TArray<TCHAR>
{
public:
    ~FString();
};

// 16-byte element serialized in bulk.
struct FElement16
{
    FLOAT X, Y, Z, W;
};

extern const TCHAR OperatorShlTArray_Tag[];   // L"operator<<(TArray)"

// RVA 0x85f30.
FArchive &operator<<(FArchive &Ar, TArray<FElement16> &A)
{
    A.CountBytes(Ar);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading()) {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) {
            if (A.ArrayNum)
                A.Data = GMalloc->Malloc(A.ArrayNum * sizeof(FElement16), OperatorShlTArray_Tag);
            else
                return Ar;
        } else {
            if (A.ArrayNum) {
                A.Realloc(sizeof(FElement16));
            } else {
                A.ArrayNum = 0;
                A.ArrayMax = 0;
                GMalloc->Free(A.Data);
                A.Data = 0;
                return Ar;
            }
        }
    }
    Ar.Serialize(A.Data, A.ArrayNum * sizeof(FElement16));
    return Ar;
}

struct FUnnamedEntry_86010
{
    INT A;
    TArray<INT> B;
    INT C;
    INT D;
    FLOAT E;
    TArray<FString> F;
    INT G;
    FUnnamedEntry_86010();
};

// RVA 0x86170.
__declspec(noinline) FUnnamedEntry_86010::FUnnamedEntry_86010() : A(0), C(0), D(0), E(30.f) {}

// RVA 0x86010: implicit destructor (F, then B).
// RVA 0x85fd0.
template <> __declspec(noinline) void TArray<FUnnamedEntry_86010>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~FUnnamedEntry_86010();
    FArray::Empty(sizeof(FUnnamedEntry_86010), Slack);
}

struct FUnnamedVec4_86060
{
    FLOAT X, Y, Z, W;
};

// RVA 0x86060.
FArchive &operator<<(FArchive &Ar, FUnnamedVec4_86060 &V)
{
    if (Ar.Ver() <= 61)
        return Ar << V.X << V.Y << V.Z;
    else
        return Ar << V.X << V.Y << V.Z << V.W;
}

class FVector
{
public:
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V)
    {
        return Ar << V.X << V.Y << V.Z;
    }
};

struct FUnnamedPair_860d0
{
    FVector A;
    FVector B;
};

// RVA 0x860d0.
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

// Stand-in for the compact index serializer (RVA 0x1ea40, published in
// item 0116), defined so the LTCG link gives it its retail ESI/EDI form.
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

// Stand-in for TArray<FString>::~TArray (0x1eecc0, retail calls it with this
// on the stack and an exception frame), so the LTCG link gives it that form.
void External_Scaffold(void *);
struct FScaffoldPart { FScaffoldPart(); ~FScaffoldPart(); };
template <> __declspec(noinline) TArray<FString>::~TArray() { FScaffoldPart P; External_Scaffold(this); }
template <> TArray<INT>::~TArray() {}

#pragma pack(pop)

// Scaffolding for the link, not part of the unit.
void Escape(void *);
FArchive &Driver_85f30(FArchive &Ar, char *Owner)
{
    Escape(&GMalloc);
    return Ar << *(TArray<FElement16> *)(Owner + 0x130);
}
void Driver_85fd0(TArray<FUnnamedEntry_86010> *A, INT N)
{
    A->Empty(N);
}
void Driver_86010(TArray<FUnnamedEntry_86010> *A, INT i, INT j)
{
    (&(*A)(i))->~FUnnamedEntry_86010();
    (&(*A)(j))->~FUnnamedEntry_86010();
}
FArchive &Driver_86060(FArchive &Ar, char *Owner)
{
    FArchive &R = Ar << *(FUnnamedPair_860d0 *)(Owner + 0x28);
    return R << *(FUnnamedVec4_86060 *)(Owner + 0x40);
}
void Driver_86170(FUnnamedEntry_86010 *E, FUnnamedEntry_86010 *F)
{
    if (E) new(E) FUnnamedEntry_86010;
    if (F) new(F) FUnnamedEntry_86010;
}
