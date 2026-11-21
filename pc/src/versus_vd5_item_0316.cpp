// Work item w3 0316: Versus RVA 0x109e80-0x10a0e4.
// Serializers of an unnamed record (name not recovered; neutral name
// FUnnamedRecord_109e80) holding seven compact indices, a matrix, three
// vectors, an array of 0x34-byte entries and a late-version object reference.
// The object was link-time optimised (/GL + /LTCG), so the helpers have
// custom register conventions.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class UObject;
class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(UObject* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive& operator<<(UObject*& Res);
    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading, ArIsSaving;
    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving() { return ArIsSaving; }
    void ByteOrderSerialize(void* V, INT Length) { Serialize(V, Length); }
    friend FArchive& operator<<(FArchive& Ar, unsigned char& B) { Ar.Serialize(&B, 1); return Ar; }
    friend FArchive& operator<<(FArchive& Ar, INT& I) { Ar.ByteOrderSerialize(&I, sizeof(I)); return Ar; }
    friend FArchive& operator<<(FArchive& Ar, FLOAT& F) { Ar.ByteOrderSerialize(&F, sizeof(F)); return Ar; }
};

// UE2 FCompactIndex (UnArc.h); operator<< is RVA 0x1ea40 (Ar in ESI, index in EDI).
class FCompactIndex
{
public:
    INT Value;
    friend FArchive& operator<<(FArchive& Ar, FCompactIndex& I);
};
#define AR_INDEX(intref) (*(FCompactIndex*)&(intref))

class FVector
{
public:
    FLOAT X, Y, Z;
    friend FArchive& operator<<(FArchive& Ar, FVector& V) { return Ar << V.X << V.Y << V.Z; }
};

class FPlane : public FVector
{
public:
    FLOAT W;
    friend FArchive& operator<<(FArchive& Ar, FPlane& P) { return Ar << P.X << P.Y << P.Z << P.W; }
};

class FMatrix
{
public:
    union
    {
        FLOAT M[4][4];
        struct { FLOAT XPlane[4], YPlane[4], ZPlane[4], WPlane[4]; };
    };
    friend FArchive& operator<<(FArchive& Ar, FMatrix& M);
};

class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    INT Add(INT Count, INT ElementSize);                 // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);              // RVA 0x4550
    void CountBytes(FArchive& Ar, INT ElementSize) { Ar.CountBytes(ArrayNum * ElementSize, ArrayMax * ElementSize); }
};

template<class T> class TArray : public FArray
{
public:
    T& operator()(INT i) { return ((T*)Data)[i]; }
    INT Add(INT n = 1) { return FArray::Add(n, sizeof(T)); }
    // Out of line in retail (RVA 0x109630 for the 0x34-byte entries).
    __declspec(noinline) void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
    friend FArchive& operator<<(FArchive& Ar, TArray& A)
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
};

template<class T> inline void* operator new(unsigned int Size, TArray<T>& Array)
{
    return &Array(Array.Add());
}

// Array storage owned by the entry; FArray::~FArray is RVA 0xf250.
class FUnnamedEntryArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    FUnnamedEntryArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FUnnamedEntryArray();
};

// 0x34-byte entry (name not recovered): constructor RVA 0xcd0e0,
// destructor RVA 0xa4770, serializer RVA 0x107440.
class FUnnamedEntry_34
{
public:
    UObject* Object;                    // +00
    FUnnamedEntryArray Array;           // +04
    INT Pad[9];                         // +10
    __declspec(noinline) FUnnamedEntry_34() {}
    __declspec(noinline) ~FUnnamedEntry_34() {}
    friend FArchive& operator<<(FArchive& Ar, FUnnamedEntry_34& E);
};

class FUnnamedRecord_109e80
{
public:
    INT Unknown0;                       // +00
    UObject* Object;                    // +04
    INT Indices[7];                     // +08..+20
    INT Value24;                        // +24
    FMatrix Matrix;                     // +28
    FVector Vector68;                   // +68
    FVector Vector74;                   // +74
    FVector Vector80;                   // +80
    TArray<FUnnamedEntry_34> Entries;   // +8c
    friend FArchive& operator<<(FArchive& Ar, FUnnamedRecord_109e80& R);
};

// RVA 0x10a010 (Ar in ESI, matrix in EAX)
FArchive& operator<<(FArchive& Ar, FMatrix& M)
{
    return Ar << M.M[0][0] << M.M[0][1] << M.M[0][2] << M.M[0][3]
              << M.M[1][0] << M.M[1][1] << M.M[1][2] << M.M[1][3]
              << M.M[2][0] << M.M[2][1] << M.M[2][2] << M.M[2][3]
              << M.M[3][0] << M.M[3][1] << M.M[3][2] << M.M[3][3];
}

// RVA 0x109e80
FArchive& operator<<(FArchive& Ar, FUnnamedRecord_109e80& R)
{
    Ar << AR_INDEX(R.Indices[0]) << AR_INDEX(R.Indices[1]) << AR_INDEX(R.Indices[2])
       << AR_INDEX(R.Indices[3]) << AR_INDEX(R.Indices[4]) << AR_INDEX(R.Indices[5])
       << AR_INDEX(R.Indices[6])
       << R.Matrix << R.Vector68 << R.Vector74 << R.Vector80;
    if (Ar.Ver() >= 107)
    {
        Ar << R.Entries;
        if (Ar.Ver() < 108)
        {
            INT Obsolete = 0;
            Ar << Obsolete;
        }
    }
    if (Ar.Ver() >= 110)
        Ar << R.Object << R.Value24;
    else if (Ar.IsLoading())
    {
        R.Object = 0;
        R.Value24 = 0;
    }
    return Ar;
}

// Scaffolding for the link, not part of the unit. The FCompactIndex
// serializer lives in Core; it is written out here only so the linker gives
// it retail's register convention.
FArchive& operator<<(FArchive& Ar, FCompactIndex& I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving())
    {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    DWORD V = I.Value >= 0 ? I.Value : -I.Value;
    unsigned char B0 = ((I.Value >= 0) ? 0 : 0x80) + ((V < 0x40) ? V : ((V & 0x3f) + 0x40));
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40)
    {
        V >>= 6;
        unsigned char B1 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
        Ar << B1;
        if (B1 & 0x80)
        {
            V >>= 7;
            unsigned char B2 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
            Ar << B2;
            if (B2 & 0x80)
            {
                V >>= 7;
                unsigned char B3 = (V < 0x80) ? V : ((V & 0x7f) + 0x80);
                Ar << B3;
                if (B3 & 0x80)
                {
                    V >>= 7;
                    unsigned char B4 = V;
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
    return Ar;
}
// Body not recovered here; defined only so the linker gives RVA 0x107440
// retail's register convention (Ar in ESI, entry in EAX).
FArchive& operator<<(FArchive& Ar, FUnnamedEntry_34& E)
{
    Ar << E.Object << E.Pad[0] << E.Pad[1];
    if (Ar.Ver() >= 91)
        Ar << E.Pad[8];
    if (Ar.Ver() >= 107)
        Ar << E.Pad[2] << E.Pad[3] << E.Pad[4] << E.Pad[5];
    return Ar;
}
// Scaffolding driver: retail callers pass Ar and the record on the stack.
void Driver_109e80(FArchive* Ar, FUnnamedRecord_109e80* R) { *Ar << *R; }
