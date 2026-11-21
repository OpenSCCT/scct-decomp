// Work item w3 0140: Versus RVA 0xc1f20 and 0xc2040 (LTCG object).
// Both are operator<<(FArchive&, TArray<T>&) instantiations. Element types
// are not recovered, so they carry neutral names:
//   FElement_c1f20 (0x3c bytes): INT, object reference, INT, then a 0x30-byte
//     sub-record serialized by 0xc2d50.
//   FElement_c2040 (0x44 bytes): serialized as a whole by 0xc23e0.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class UObject;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                    // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);                 // RVA 0x4550
};
template<class T> class TArray : public FArray
{
public:
    INT Num() const { return ArrayNum; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void *V, INT Length);            // +0x04
    virtual void SerializeBits(void *V, INT LengthBits);    // +0x08
    virtual void SerializeInt(DWORD &Value, DWORD Max);     // +0x0c
    virtual void Preload(UObject *Object);                  // +0x10
    virtual void CountBytes(DWORD InNum, DWORD InMax);      // +0x14
    virtual FArchive &SerializeName(INT &N);                // +0x18 (FName)
    virtual FArchive &operator<<(UObject *&Res);            // +0x1c
    FArchive &operator<<(INT &V) { Serialize(&V, sizeof(V)); return *this; }
    FArchive &operator<<(FLOAT &V) { Serialize(&V, sizeof(V)); return *this; }
    INT ArVer, ArNetVer, ArLicenseeVer, ArIsLoading, ArIsSaving;
};

FArchive &SerializeIndex(FArchive &Ar, INT &Value);   // RVA 0x1ea40

struct FVector
{
    FLOAT X, Y, Z;
    friend FArchive &operator<<(FArchive &Ar, FVector &V)
    {
        return Ar << V.X << V.Y << V.Z;
    }
};

// RVA 0xc2d50 serializes four consecutive vectors: the FCoords layout.
struct FCoords
{
    FVector Origin, XAxis, YAxis, ZAxis;
};
FArchive &operator<<(FArchive &Ar, FCoords &F);   // RVA 0xc2d50

struct FElement_c1f20
{
    INT A;
    UObject *Object;
    INT B;
    FCoords Coords;
    friend FArchive &operator<<(FArchive &Ar, FElement_c1f20 &E)
    {
        return Ar << E.A << E.Object << E.B << E.Coords;
    }
};

// Neutral name: 0x44-byte element serialized by RVA 0xc23e0 (an INT, an
// object reference, two vectors and nine floats, by that function's reads).
struct FElement_c2040
{
    INT A;
    UObject *Object;
    FVector V1, V2;
    FLOAT F[9];
};
FArchive &operator<<(FArchive &Ar, FElement_c2040 &E);    // RVA 0xc23e0

// RVA 0xc1f20 (T = FElement_c1f20) and RVA 0xc2040 (T = FElement_c2040).
template<class T> __declspec(noinline) FArchive &operator<<(FArchive &Ar, TArray<T> &A)
{
    Ar.CountBytes(A.ArrayNum * sizeof(T), A.ArrayMax * sizeof(T));
    if (Ar.ArIsLoading) {
        INT NewNum;
        SerializeIndex(Ar, NewNum);
        A.Empty(sizeof(T), NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << A(A.FArray::Add(1, sizeof(T)));
    } else {
        SerializeIndex(Ar, A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << A(i);
    }
    return Ar;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit.
void Escape(void *);
// Stand-ins for the callees, defined so the linker gives them register conventions.
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
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FCoords &F)
{
    return Ar << F.Origin << F.XAxis << F.YAxis << F.ZAxis;
}
__declspec(noinline) FArchive &operator<<(FArchive &Ar, FElement_c2040 &E)
{
    return Ar << E.A << E.Object << E.V1 << E.V2 << E.F[0] << E.F[1] << E.F[2]
              << E.F[3] << E.F[4] << E.F[5] << E.F[6] << E.F[7] << E.F[8];
}
struct FDriverOwner
{
    TArray<FElement_c1f20> A;
    TArray<FElement_c2040> B;
    INT X, Y;
};
// Mirrors the retail caller (USkeletalMeshInstance::Serialize at 0xb5660).
void Driver_c1f20(FArchive &Ar, FDriverOwner *O)
{
    Ar << O->A;
    Ar << O->B;
    Ar << O->X;
    Ar << O->Y;
}
