// Work item w3 0132: Versus RVA 0xbecd0, USkeletalMeshInstance::MeshToWorld
// (vtable slot 67). Compiled /GL and linked /LTCG: the matrix helpers it calls
// use LTCG register conventions, so they are copied here (from published items
// 0299 and 0307) for the linker to give them their retail conventions.
// Field names follow UE2 (AActor Location/PrePivot/Rotation/DrawScale/
// DrawScale3D, ULodMesh Scale/Origin/RotOrigin); the two instance flags at
// +0x70/+0x74 are neutral names. Only MeshToWorld is the unit here; the
// helper copies (and the SetPlanes stand-in) exist to fix call conventions.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator*(const FVector &V) const { return FVector(X * V.X, Y * V.Y, Z * V.Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
};

struct FRotator
{
    INT Pitch, Yaw, Roll;
};

struct FMatrix
{
    union
    {
        struct { FPlane XPlane, YPlane, ZPlane, WPlane; };
        FLOAT M[4][4];
    };
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
    FMatrix operator*(const FMatrix &Other) const;
    void SetPlanes(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
};

// RVA 0x4fbc0 (item 0202), copied for its LTCG convention.
__declspec(noinline) FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
    : XPlane(InX), YPlane(InY), ZPlane(InZ), WPlane(InW)
{
}

__declspec(noinline) void FMatrix::SetPlanes(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
{
    XPlane = InX; YPlane = InY; ZPlane = InZ; WPlane = InW;
}

// RVA 0x7b110 (item 0299), copied for its LTCG convention.
__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix &Other) const
{
    FMatrix Result;
    Result.M[0][0] = M[0][0] * Other.M[0][0] + M[0][1] * Other.M[1][0] + M[0][2] * Other.M[2][0] + M[0][3] * Other.M[3][0];
    Result.M[0][1] = M[0][0] * Other.M[0][1] + M[0][1] * Other.M[1][1] + M[0][2] * Other.M[2][1] + M[0][3] * Other.M[3][1];
    Result.M[0][2] = M[0][0] * Other.M[0][2] + M[0][1] * Other.M[1][2] + M[0][2] * Other.M[2][2] + M[0][3] * Other.M[3][2];
    Result.M[0][3] = M[0][0] * Other.M[0][3] + M[0][1] * Other.M[1][3] + M[0][2] * Other.M[2][3] + M[0][3] * Other.M[3][3];
    Result.M[1][0] = M[1][0] * Other.M[0][0] + M[1][1] * Other.M[1][0] + M[1][2] * Other.M[2][0] + M[1][3] * Other.M[3][0];
    Result.M[1][1] = M[1][0] * Other.M[0][1] + M[1][1] * Other.M[1][1] + M[1][2] * Other.M[2][1] + M[1][3] * Other.M[3][1];
    Result.M[1][2] = M[1][0] * Other.M[0][2] + M[1][1] * Other.M[1][2] + M[1][2] * Other.M[2][2] + M[1][3] * Other.M[3][2];
    Result.M[1][3] = M[1][0] * Other.M[0][3] + M[1][1] * Other.M[1][3] + M[1][2] * Other.M[2][3] + M[1][3] * Other.M[3][3];
    Result.M[2][0] = M[2][0] * Other.M[0][0] + M[2][1] * Other.M[1][0] + M[2][2] * Other.M[2][0] + M[2][3] * Other.M[3][0];
    Result.M[2][1] = M[2][0] * Other.M[0][1] + M[2][1] * Other.M[1][1] + M[2][2] * Other.M[2][1] + M[2][3] * Other.M[3][1];
    Result.M[2][2] = M[2][0] * Other.M[0][2] + M[2][1] * Other.M[1][2] + M[2][2] * Other.M[2][2] + M[2][3] * Other.M[3][2];
    Result.M[2][3] = M[2][0] * Other.M[0][3] + M[2][1] * Other.M[1][3] + M[2][2] * Other.M[2][3] + M[2][3] * Other.M[3][3];
    Result.M[3][0] = M[3][0] * Other.M[0][0] + M[3][1] * Other.M[1][0] + M[3][2] * Other.M[2][0] + M[3][3] * Other.M[3][0];
    Result.M[3][1] = M[3][0] * Other.M[0][1] + M[3][1] * Other.M[1][1] + M[3][2] * Other.M[2][1] + M[3][3] * Other.M[3][1];
    Result.M[3][2] = M[3][0] * Other.M[0][2] + M[3][1] * Other.M[1][2] + M[3][2] * Other.M[2][2] + M[3][3] * Other.M[3][2];
    Result.M[3][3] = M[3][0] * Other.M[0][3] + M[3][1] * Other.M[1][3] + M[3][2] * Other.M[2][3] + M[3][3] * Other.M[3][3];
    return Result;
}

struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT *OutSin, FLOAT *OutCos);
};
extern FGlobalMath GMath;

struct FRotationMatrix : public FMatrix { FRotationMatrix(const FRotator &Rot); };
struct FScaleMatrix : public FMatrix { FScaleMatrix(const FVector &Scale); };
struct FTranslationMatrix : public FMatrix { FTranslationMatrix(const FVector &Delta); };

// RVA 0x81810 (item 0307).
__declspec(noinline) FRotationMatrix::FRotationMatrix(const FRotator &Rot)
{
    FLOAT SR, SP, SY, CR, CP, CY;
    GMath.SinCos(Rot.Yaw, &SY, &CY);
    GMath.SinCos(Rot.Pitch, &SP, &CP);
    GMath.SinCos(Rot.Roll, &SR, &CR);
    M[0][0] = CP * CY; M[0][1] = CP * SY; M[0][2] = SP; M[0][3] = 0.f;
    M[1][0] = SR * SP * CY - CR * SY; M[1][1] = SR * SP * SY + CR * CY; M[1][2] = -SR * CP; M[1][3] = 0.f;
    M[2][0] = -(CR * SP * CY + SR * SY); M[2][1] = CY * SR - CR * SP * SY; M[2][2] = CR * CP; M[2][3] = 0.f;
    M[3][0] = 0.f; M[3][1] = 0.f; M[3][2] = 0.f; M[3][3] = 1.f;
}

// RVA 0x81910 and 0x819b0 (item 0307). Stand-in bodies: retail passes this
// to the FMatrix constructor and returns it from ESI rather than reusing the
// constructor's returned this; building the planes through SetPlanes gives
// these constructors that retail register convention (this in ESI, the
// vector in EAX), which is what MeshToWorld's call sites depend on.
__declspec(noinline) FScaleMatrix::FScaleMatrix(const FVector &Scale)
{
    SetPlanes(FPlane(Scale.X, 0.f, 0.f, 0.f), FPlane(0.f, Scale.Y, 0.f, 0.f),
              FPlane(0.f, 0.f, Scale.Z, 0.f), FPlane(0.f, 0.f, 0.f, 1.f));
}

__declspec(noinline) FTranslationMatrix::FTranslationMatrix(const FVector &Delta)
{
    SetPlanes(FPlane(1.f, 0.f, 0.f, 0.f), FPlane(0.f, 1.f, 0.f, 0.f),
              FPlane(0.f, 0.f, 1.f, 0.f), FPlane(Delta.X, Delta.Y, Delta.Z, 1.f));
}

class AActor
{
public:
    char Pad000[0x80];
    FVector Location;           // +0x80
    char Pad08c[0xb0 - 0x8c];
    FVector DrawScale3D;        // +0xb0
    FVector PrePivot;           // +0xbc
    char Pad0c8[0xe0 - 0xc8];
    FRotator Rotation;          // +0xe0
    char Pad0ec[0x23c - 0xec];
    FLOAT DrawScale;            // +0x23c
};

class USkeletalMesh
{
public:
    char Pad000[0x74];
    FVector Scale;              // +0x74
    FVector Origin;             // +0x80
    FRotator RotOrigin;         // +0x8c
};

class UMesh;

class USkeletalMeshInstance
{
public:
    virtual void V00(); virtual void V01(); virtual void V02(); virtual void V03();
    virtual void V04(); virtual void V05(); virtual void V06(); virtual void V07();
    virtual void V08(); virtual void V09(); virtual void V10(); virtual void V11();
    virtual void V12(); virtual void V13(); virtual void V14(); virtual void V15();
    virtual void V16(); virtual void V17(); virtual void V18(); virtual void V19();
    virtual void V20(); virtual void V21(); virtual void V22(); virtual void V23();
    virtual void V24(); virtual void V25(); virtual void V26(); virtual void V27();
    virtual void V28(); virtual void V29();
    virtual AActor *GetActor();         // +0x78
    virtual void V31();
    virtual UMesh *GetMesh();           // +0x80
    virtual void V33(); virtual void V34(); virtual void V35();
    virtual void V36(); virtual void V37(); virtual void V38(); virtual void V39();
    virtual void V40(); virtual void V41(); virtual void V42(); virtual void V43();
    virtual void V44(); virtual void V45(); virtual void V46(); virtual void V47();
    virtual void V48(); virtual void V49(); virtual void V50(); virtual void V51();
    virtual void V52(); virtual void V53(); virtual void V54(); virtual void V55();
    virtual void V56(); virtual void V57(); virtual void V58(); virtual void V59();
    virtual void V60(); virtual void V61(); virtual void V62(); virtual void V63();
    virtual void V64(); virtual void V65(); virtual void V66();
    virtual FMatrix MeshToWorld();      // +0x10c
    USkeletalMeshInstance() {}

    char Pad004[0x70 - 0x4];
    UBOOL bFlag70;              // +0x70 (neutral)
    UBOOL bFlag74;              // +0x74 (neutral)
};

// RVA 0xbecd0
FMatrix USkeletalMeshInstance::MeshToWorld()
{
    USkeletalMesh *Mesh = (USkeletalMesh *)GetMesh();
    FRotator Rot = GetActor()->Rotation;
    FMatrix Result;
    if (bFlag74)
    {
        FVector Scale = GetActor()->DrawScale3D * GetActor()->DrawScale * Mesh->Scale;
        Result = FScaleMatrix(Scale) * FRotationMatrix(Rot) * FTranslationMatrix(GetActor()->Location);
    }
    else
    {
        AActor *Actor = GetActor();
        FVector Loc = GetActor()->Location + Actor->PrePivot;
        FVector Scale = GetActor()->DrawScale3D * GetActor()->DrawScale * Mesh->Scale;
        Result = FScaleMatrix(Scale) * FRotationMatrix(Mesh->RotOrigin) * FRotationMatrix(Rot) * FTranslationMatrix(Loc);
    }
    FVector XAxis(Result.M[0][0], Result.M[1][0], Result.M[2][0]);
    FVector YAxis(Result.M[0][1], Result.M[1][1], Result.M[2][1]);
    FVector ZAxis(Result.M[0][2], Result.M[1][2], Result.M[2][2]);
    if (!bFlag70 && !bFlag74)
    {
        Result.M[3][0] += -Mesh->Origin | XAxis;
        Result.M[3][1] += -Mesh->Origin | YAxis;
        Result.M[3][2] += -Mesh->Origin | ZAxis;
    }
    return Result;
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_becd0(void *Mem, FMatrix *Out)
{
    Escape(&GMath);
    USkeletalMeshInstance *I = new (Mem) USkeletalMeshInstance;
    *Out = I->MeshToWorld();
}
