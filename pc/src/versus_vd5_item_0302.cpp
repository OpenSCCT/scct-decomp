// Work item 0302: Versus RVA 0x1049f0-0x104cce: AERainVolume and
// UERainPrimitive (class names from the reflected vtables). This object was
// built with VC7.0 /GL and linked with /LTCG, so several functions take
// their arguments in registers.
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef unsigned __int64 QWORD;

#pragma pack(push, 4)
inline void* operator new(unsigned int, void* Mem) { return Mem; }

extern "C" __declspec(dllimport) int __cdecl rand();
inline FLOAT appFrand() { return rand() * (1.f / 32767.f); }

class UObject;
class FName;

class FArchive
{
public:
    virtual ~FArchive();
    virtual void Serialize(void* V, INT Length);
    virtual void SerializeBits(void* V, INT LengthBits);
    virtual void SerializeInt(DWORD& Value, DWORD Max);
    virtual void Preload(UObject* Object);
    virtual void CountBytes(DWORD InNum, DWORD InMax);
    virtual FArchive& operator<<(FName& N);
    virtual FArchive& operator<<(UObject*& Res);
    INT Ver() { return ArVer; }
    UBOOL IsLoading() { return ArIsLoading; }
    UBOOL IsSaving()  { return ArIsSaving; }
    friend FArchive& operator<<(FArchive& Ar, FLOAT& F) { Ar.Serialize(&F, 4); return Ar; }
    friend FArchive& operator<<(FArchive& Ar, INT& I)   { Ar.Serialize(&I, 4); return Ar; }
    friend FArchive& operator<<(FArchive& Ar, BYTE& B)  { Ar.Serialize(&B, 1); return Ar; }
    INT ArVer, ArNetVer, ArLicenseeVer;
    UBOOL ArIsLoading, ArIsSaving;
};

class FCompactIndex
{
public:
    INT Value;
    friend FArchive& operator<<(FArchive& Ar, FCompactIndex& I);   // 0x1ea40
};
#define AR_INDEX(intref) (*(FCompactIndex*)&(intref))

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag);
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag);
};
extern FMalloc* GMalloc;

class FArray
{
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    INT Add(INT Count, INT ElementSize);          // 0x44e0
    void Empty(INT ElementSize, INT Slack);       // 0x4550
    void* Data; INT ArrayNum; INT ArrayMax;
};

inline FLOAT FMin(FLOAT A, FLOAT B) { return (A <= B) ? A : B; }
inline FLOAT FMax(FLOAT A, FLOAT B) { return (A >= B) ? A : B; }

class FVector
{
public:
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};
class FPlane : public FVector
{
public:
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
};
class FMatrix
{
public:
    FPlane XPlane, YPlane, ZPlane, WPlane;
    FPlane TransformFPlane(const FPlane& P) const;   // 0x4fe60
    FMatrix operator*(const FMatrix& Other) const;   // 0x7b110
    FVector TransformFVector(const FVector& V) const { return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.f)); }
};
class FSphere : public FPlane
{
public:
    friend FArchive& operator<<(FArchive& Ar, FSphere& S);   // 0x86060
};

// Two corner vectors; empty is Min.X - Max.X == 1 (serializer at 0x860d0).
// Neutral name: SCCT's box without a stored IsValid byte.
struct FRainBounds
{
    FVector Min, Max;
    FRainBounds() { Min.X = 1.f; Max.X = 0.f; }
    FRainBounds(const FRainBounds& Other)
    {
        Min.X = Other.Min.X; Min.Y = Other.Min.Y; Min.Z = Other.Min.Z;
        Max.X = Other.Max.X; Max.Y = Other.Max.Y; Max.Z = Other.Max.Z;
    }
    FRainBounds& operator+=(const FVector& P);                 // 0x4f820
    FRainBounds(const FVector& InMin, const FVector& InMax);   // 0x81ad0
    UBOOL IsEmpty() { return Min.X - Max.X == 1.f; }
    friend FArchive& operator<<(FArchive& Ar, FRainBounds& B); // 0x860d0
};

// Global cache-id counter (0x10c96930).
extern QWORD GCacheIdCounter;
inline QWORD MakeCacheID(INT Base) { return GCacheIdCounter++ * 256 + Base; }

struct FRainVertex { BYTE Raw[0x18]; friend FArchive& operator<<(FArchive& Ar, FRainVertex& V); };
struct FRainVertexArray : public FArray { friend FArchive& operator<<(FArchive& Ar, FRainVertexArray& A); };
struct FWordArray : public FArray { friend FArchive& operator<<(FArchive& Ar, FWordArray& A); };

// Neutral names: the primitive's vertex stream (vtable 0x10c03d78) and index
// buffer, laid out like UE2 render resources (array, cache id, revision).
class FRainVertexStream
{
public:
    FRainVertexStream() { CacheId = MakeCacheID(0xE1); }
    virtual void Dummy();
    FRainVertexArray Vertices;
    QWORD CacheId;
    INT Revision;
    friend FArchive& operator<<(FArchive& Ar, FRainVertexStream& S) { return Ar << S.Vertices << S.Revision; }
};
class FRainIndexBuffer
{
public:
    FRainIndexBuffer();
    virtual void Dummy();
    FWordArray Indices;
    QWORD CacheId;
    INT Revision;
    friend FArchive& operator<<(FArchive& Ar, FRainIndexBuffer& I) { return Ar << I.Indices << I.Revision; }
};

UBOOL FPointBoxIntersection(const FVector& Point, const FRainBounds& Box);   // 0x92920

class AActor
{
public:
    AActor();
    virtual void Dummy();
    virtual void Serialize(FArchive& Ar);      // 0x990b00
    FMatrix WorldToLocal();                    // 0x9e3b0
    BYTE ActorFields[0x2f8 - 4];
    FVector RainExtent;                        // 0x2f8, neutral name
    BYTE MoreActorFields[0x324 - 0x304];
};

// Was a function-local static of the AERainVolume constructor (0x10c480a8).
extern FLOAT AERainVolume_RandomTable[16];

class AERainVolume : public AActor
{
public:
    AERainVolume();
    virtual void Dummy();
    void Serialize(FArchive& Ar);
    UObject*    Primitive;  // 0x324
    FRainBounds Bounds;     // 0x328
};

AERainVolume::AERainVolume()
:   Primitive(0)
{
    if (AERainVolume_RandomTable[0] < 0.f)
        for (INT i = 0; i < 16; i++)
            AERainVolume_RandomTable[i] = appFrand();
}

void AERainVolume::Serialize(FArchive& Ar)
{
    AActor::Serialize(Ar);
    if (!Ar.IsSaving() && !Ar.IsLoading())
        Ar << Primitive << Bounds;
}

class UPrimitive
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09();
    virtual void Serialize(FArchive& Ar);      // slot 10, 0x915f50
    virtual void V11(); virtual void V12(); virtual void V13(); virtual void V14();
    virtual void V15(); virtual void V16(); virtual void V17(); virtual void V18();
    virtual void V19(); virtual void V20(); virtual void V21(); virtual void V22();
    virtual void V23();
    virtual FRainBounds GetRainBounds(AActor* Owner);   // slot 24, neutral name
    BYTE PrimitiveFields[0x28 - 4];
};

class UERainPrimitive : public UPrimitive
{
public:
    void Serialize(FArchive& Ar);
    FRainBounds GetRainBounds(AActor* Owner);
    bool PointInside(const FVector& Point);
    FRainBounds       Bounds;       // 0x28
    FSphere           Sphere;       // 0x40
    AERainVolume*     Volume;       // 0x50
    FRainVertexStream Stream;       // 0x54
    FRainIndexBuffer  IndexBuffer;  // 0x70
};

void UERainPrimitive::Serialize(FArchive& Ar)
{
    UPrimitive::Serialize(Ar);
    Ar << Bounds << Sphere;
    Ar << *(UObject**)&Volume << IndexBuffer << Stream;
}

FRainBounds UERainPrimitive::GetRainBounds(AActor* Owner)
{
    if (Volume->Bounds.IsEmpty())
        Volume->Bounds = FRainBounds(FVector(-Volume->RainExtent.X, -Volume->RainExtent.Y, 0.f), Volume->RainExtent);
    return Volume->Bounds;
}

bool UERainPrimitive::PointInside(const FVector& Point)
{
    FVector Local = Volume->WorldToLocal().TransformFVector(Point);
    return FPointBoxIntersection(Local, GetRainBounds(0)) ? true : false;
}

// ---------------------------------------------------------------------------
// Scaffolding for the link, not part of the unit. Stand-ins for retail
// functions that live in other objects; their shape follows retail so the
// linker gives them retail's register conventions. Drivers call the unit's
// functions the way retail does.
// ---------------------------------------------------------------------------
extern void* AActor_VTable;
struct FActorPair { DWORD A, B; };
__declspec(noinline) AActor::AActor()          // 0x992100, this in EAX
{
    *(void**)this = AActor_VTable;
    *(FLOAT*)(ActorFields + 0xc8 - 4) = 1.f;
    *(DWORD*)(ActorFields + 0xd4 - 4) = 0;
    FActorPair* P = (FActorPair*)(ActorFields + 0x10c - 4);
    for (INT i = 0; i < 4; i++) { P[i].A = 0; P[i].B = 0; }
    *(DWORD*)(ActorFields + 0x2e8 - 4) &= ~1u;
}

__declspec(noinline) FArchive& operator<<(FArchive& Ar, FRainBounds& B)   // 0x860d0, Ar ESI, B EDI
{
    BYTE IsValid = 1;
    if (B.Min.X - B.Max.X == 1.f)
        IsValid = 0;
    Ar << B.Min.X << B.Min.Y << B.Min.Z << B.Max.X << B.Max.Y << B.Max.Z << IsValid;
    if (Ar.IsLoading() && !IsValid) { B.Max.X = 0.f; B.Min.X = 1.f; }
    return Ar;
}

__declspec(noinline) FArchive& operator<<(FArchive& Ar, FSphere& S)       // 0x86060, Ar ESI, S EAX
{
    Ar << S.X << S.Y << S.Z;
    if (Ar.Ver() > 61)
        Ar << S.W;
    return Ar;
}

// 0x81ad0, this ESI, InMin EDX, InMax EDI.
extern FVector* GRainBoundsMin;
extern FVector* GRainBoundsMax;
// 0x4f820, this ECX, P EDX.
__declspec(noinline) FRainBounds& FRainBounds::operator+=(const FVector& P)
{
    if (!IsEmpty())
    {
        Min.X = FMin(Min.X, P.X); Min.Y = FMin(Min.Y, P.Y); Min.Z = FMin(Min.Z, P.Z);
        Max.X = FMax(Max.X, P.X); Max.Y = FMax(Max.Y, P.Y); Max.Z = FMax(Max.Z, P.Z);
    }
    else
    {
        Min = P;
        Max = P;
    }
    return *this;
}
__declspec(noinline) FRainBounds::FRainBounds(const FVector& InMin, const FVector& InMax)
{
    Min = InMin;
    Max = InMax;
    Min = *GRainBoundsMin;
    Max = *GRainBoundsMax;
    *this += InMin;
    *this += InMax;
    // Not in retail: a global store so the optimiser cannot assume this call
    // leaves UERainPrimitive::Volume alone (retail reloads it after the call).
    GRainBoundsMin = GRainBoundsMax;
}

// 0x92920, Box ECX, Point EDX.
__declspec(noinline) UBOOL FPointBoxIntersection(const FVector& Point, const FRainBounds& Box)
{
    if (Point.X >= Box.Min.X && Point.X <= Box.Max.X
     && Point.Y >= Box.Min.Y && Point.Y <= Box.Max.Y
     && Point.Z >= Box.Min.Z && Point.Z <= Box.Max.Z)
        return 1;
    else
        return 0;
}

// 0x4fbc0: FMatrix from four planes (other object, left declared).
FMatrix MakeMatrix(const FPlane& X, const FPlane& Y, const FPlane& Z, const FPlane& W);

// 0x819b0, result ESI, V EAX.
__declspec(noinline) FMatrix FTranslationMatrix(const FVector& V)
{
    return MakeMatrix(FPlane(1.f, 0.f, 0.f, 0.f), FPlane(0.f, 1.f, 0.f, 0.f), FPlane(0.f, 0.f, 1.f, 0.f), FPlane(V.X, V.Y, V.Z, 1.f));
}
// 0x81910, result ESI, V EAX.
__declspec(noinline) FMatrix FScaleMatrix(const FVector& V)
{
    return MakeMatrix(FPlane(V.X, 0.f, 0.f, 0.f), FPlane(0.f, V.Y, 0.f, 0.f), FPlane(0.f, 0.f, V.Z, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
}
// 0x50ed0, result EBX, rotation on the stack.
struct FRotator { INT Pitch, Yaw, Roll; };
void SinCos(INT Angle, FLOAT* S, FLOAT* C);
__declspec(noinline) FMatrix FInverseRotationMatrix(const FRotator& R)
{
    FLOAT S, C;
    SinCos(-R.Yaw, &S, &C);
    FMatrix M = MakeMatrix(FPlane(C, -S, 0.f, 0.f), FPlane(S, C, 0.f, 0.f), FPlane(0.f, 0.f, 1.f, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
    SinCos(-R.Pitch, &S, &C);
    M = M * MakeMatrix(FPlane(C, 0.f, -S, 0.f), FPlane(0.f, 1.f, 0.f, 0.f), FPlane(S, 0.f, C, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
    SinCos(-R.Roll, &S, &C);
    M = M * MakeMatrix(FPlane(1.f, 0.f, 0.f, 0.f), FPlane(0.f, C, S, 0.f), FPlane(0.f, -S, C, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
    return M;
}
// 0x7b110, result EAX, this ECX, Other EDX.
__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix& Other) const
{
    FMatrix Result;
    const FLOAT* A = &XPlane.X;
    const FLOAT* B = &Other.XPlane.X;
    FLOAT* R = &Result.XPlane.X;
    for (INT i = 0; i < 4; i++)
        for (INT j = 0; j < 4; j++)
            R[i * 4 + j] = A[i * 4 + 0] * B[0 * 4 + j] + A[i * 4 + 1] * B[1 * 4 + j]
                         + A[i * 4 + 2] * B[2 * 4 + j] + A[i * 4 + 3] * B[3 * 4 + j];
    return Result;
}
// 0x9e3b0, this EAX, result pointer on the stack (UE2 AActor::WorldToLocal).
__declspec(noinline) FMatrix AActor::WorldToLocal()
{
    FLOAT* F = (FLOAT*)ActorFields;
    FVector Location(F[0x80 / 4 - 1], F[0x84 / 4 - 1], F[0x88 / 4 - 1]);
    FVector DrawScale3D(F[0xb0 / 4 - 1], F[0xb4 / 4 - 1], F[0xb8 / 4 - 1]);
    FLOAT DrawScale = F[0x23c / 4 - 1];
    return FTranslationMatrix(FVector(-Location.X, -Location.Y, -Location.Z))
        * FInverseRotationMatrix(*(FRotator*)&F[0xe0 / 4 - 1])
        * FScaleMatrix(FVector(1.f / DrawScale3D.X / DrawScale, 1.f / DrawScale3D.Y / DrawScale, 1.f / DrawScale3D.Z / DrawScale))
        * FTranslationMatrix(*(FVector*)&F[0xbc / 4 - 1]);
}

// 0x1ea40, Ar ESI, index EDI (UE2 FCompactIndex serializer, SCCT adds the
// raw path for archives that neither load nor save).
__declspec(noinline) FArchive& operator<<(FArchive& Ar, FCompactIndex& I)
{
    if (!Ar.IsLoading() && !Ar.IsSaving())
    {
        Ar.Serialize(&I.Value, 4);
        return Ar;
    }
    INT Original = I.Value;
    DWORD V = Original >= 0 ? Original : -Original;
    BYTE B0 = (BYTE)(((Original >= 0) ? 0 : 0x80) + (V < 0x40 ? V : ((V & 0x3f) + 0x40)));
    I.Value = 0;
    Ar << B0;
    if (B0 & 0x40)
    {
        V >>= 6;
        BYTE B1 = (BYTE)(V < 0x80 ? V : ((V & 0x7f) + 0x80));
        Ar << B1;
        if (B1 & 0x80)
        {
            V >>= 7;
            BYTE B2 = (BYTE)(V < 0x80 ? V : ((V & 0x7f) + 0x80));
            Ar << B2;
            if (B2 & 0x80)
            {
                V >>= 7;
                BYTE B3 = (BYTE)(V < 0x80 ? V : ((V & 0x7f) + 0x80));
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
    if (Ar.IsSaving() && I.Value != Original)
        I.Value = Original;
    return Ar;
}

extern const TCHAR WordArrayTag[];
__declspec(noinline) FArchive& operator<<(FArchive& Ar, FWordArray& A)    // 0x99710, Ar ESI, A EBX
{
    Ar.CountBytes(A.ArrayNum * 2, A.ArrayMax * 2);
    Ar << AR_INDEX(A.ArrayNum);
    if (Ar.IsLoading())
    {
        A.ArrayMax = A.ArrayNum;
        if (A.Data == 0) { if (A.ArrayMax) A.Data = GMalloc->Malloc(A.ArrayMax * 2, WordArrayTag); }
        else A.Data = GMalloc->Realloc(A.Data, A.ArrayMax * 2, WordArrayTag);
    }
    if (A.ArrayNum)
        Ar.Serialize(A.Data, A.ArrayNum * 2);
    return Ar;
}

__declspec(noinline) FArchive& operator<<(FArchive& Ar, FRainVertexArray& A)   // 0x1061b0, Ar EAX, A EBX
{
    Ar.CountBytes(A.ArrayNum * 0x18, A.ArrayMax * 0x18);
    if (Ar.IsLoading())
    {
        INT NewNum;
        Ar << AR_INDEX(NewNum);
        A.Empty(0x18, NewNum);
        for (INT i = 0; i < NewNum; i++)
            Ar << ((FRainVertex*)A.Data)[A.Add(1, 0x18)];
    }
    else
    {
        Ar << AR_INDEX(A.ArrayNum);
        for (INT i = 0; i < A.ArrayNum; i++)
            Ar << ((FRainVertex*)A.Data)[i];
    }
    return Ar;
}

__declspec(noinline) FArchive& operator<<(FArchive& Ar, FRainVertex& V)   // 0x106260
{
    FLOAT* F = (FLOAT*)V.Raw;
    Ar << F[0] << F[1] << F[2];
    Ar << V.Raw[0xe] << V.Raw[0xd] << V.Raw[0xc] << V.Raw[0xf];
    Ar << F[4] << F[5];
    return Ar;
}

void Driver_49F0(void* P) { new(P) FRainVertexStream; }
void Driver_4C20(void* P) { new(P) AERainVolume; }
void Driver_4A80(void* P) { new(P) UERainPrimitive; }
bool Driver_4BA0(UERainPrimitive* P, FVector* V) { return P->PointInside(*V); }
