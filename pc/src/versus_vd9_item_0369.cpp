// Work item w3 0369: Versus RVA 0x1178e0-0x117c54 (VC7.0 /GL, linked /LTCG).
// Engine scene manager (UE2 UnSceneManager): two FLevelSceneNode subclasses
// and the mirror matrix one of them is built from.
//  0x1178e0  FSkySceneNode::FSkySceneNode (vtable 0x10c03688; the matrix moves
//            the view into the frame of the zone's zone actor)
//  0x117a00  FMirrorMatrix::FMirrorMatrix: the unit coordinate system mirrored
//            by a plane, as a matrix (UE2 FCoords::MirrorByPlane + Matrix())
//  0x117c00  FMirrorSceneNode::FMirrorSceneNode (vtable 0x10c03654, ParentSurf
//            at 0x1d8)
// The class names follow UE2; retail's vtables are not labelled.
typedef int INT;
typedef unsigned long DWORD;
typedef float FLOAT;
typedef unsigned char BYTE;

inline void* operator new(unsigned int, void* Mem) { return Mem; }

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator-() const { return FVector(-X, -Y, -Z); }
    FVector operator-(const FVector& V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FVector operator*(FLOAT Scale) const { return FVector(X * Scale, Y * Scale, Z * Scale); }
    FLOAT operator|(const FVector& V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FVector MirrorByVector(const FVector& MirrorNormal) const
    {
        return *this - MirrorNormal * (2.f * (*this | MirrorNormal));
    }
};
struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
    FPlane(const FVector& V, FLOAT InW) { X = V.X; Y = V.Y; Z = V.Z; W = InW; }
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
    FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW);   // 0x4fbc0
    FPlane TransformFPlane(const FPlane& P) const;   // 0x4fe60
    FMatrix operator*(const FMatrix& Other) const;   // 0x7b110
    void operator*=(const FMatrix& Other);           // 0x4fc30
    FMatrix Inverse() const;                         // 0x53af0
    FLOAT Determinant() const;                       // 0x4ff90
    FVector TransformFVector(const FVector& V) const { return TransformFPlane(FPlane(V.X, V.Y, V.Z, 1.f)); }
    FPlane TransformNormal(const FVector& V) const { return TransformFPlane(FPlane(V.X, V.Y, V.Z, 0.f)); }
};
extern FMatrix GIdentityMatrix;

struct FTranslationMatrix : public FMatrix { FTranslationMatrix(const FVector& Delta); };            // 0x819b0
struct FInverseRotationMatrix : public FMatrix { FInverseRotationMatrix(const FRotator& Rot); };      // 0x50ed0
struct FMirrorMatrix : public FMatrix { FMirrorMatrix(const FPlane& Plane); };                       // 0x117a00

// FGlobalMath at 0x10ccac00; its sine/cosine helper is RVA 0x40950.
struct FGlobalMath
{
    void SinCos(INT Angle, FLOAT* OutSin, FLOAT* OutCos);
};
extern FGlobalMath GMath;
// Constant vectors reached through references (0x10ccacb8..0x10ccacc4).
extern const FVector& GMath_UnitY;  // 0x10ccacb8
extern const FVector& GMath_UnitZ;  // 0x10ccacbc
extern const FVector& GMath_Zero;   // 0x10ccacc0
extern const FVector& GMath_UnitX;  // 0x10ccacc4

template<class T> class TArray
{
public:
    T* Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Num() const { return ArrayNum; }
    T& operator()(INT i) { return Data[i]; }
};

class AActor
{
public:
    BYTE Pad00[0x80];
    FVector Location;           // 0x080
    BYTE Pad8C[0xe0 - 0x8c];
    FRotator Rotation;          // 0x0e0
};
class AZoneInfo : public AActor {};
class ALevelInfo : public AZoneInfo {};

struct FZoneProperties
{
    AZoneInfo* ZoneActor;       // 0x00
    INT Unknown04, Unknown08, Unknown0C;
};
class UModel
{
public:
    BYTE Pad[0x114];
    TArray<FZoneProperties> Zones;  // 0x114
};
class ULevel
{
public:
    BYTE Pad[0x2c];
    TArray<AActor*> Actors;         // 0x2c
    BYTE Pad38[0x13c - 0x38];
    UModel* Model;                  // 0x13c
    ALevelInfo* GetLevelInfo() { return (ALevelInfo*)Actors(0); }
    AZoneInfo* GetZoneActor(INT iZone)
    {
        return (iZone < Model->Zones.Num() && Model->Zones(iZone).ZoneActor) ? Model->Zones(iZone).ZoneActor : GetLevelInfo();
    }
};

class UViewport
{
public:
    BYTE Pad[0xa0];
    INT SizeX;              // 0xa0
    INT SizeY;              // 0xa4
    BYTE Pad2[0x148 - 0xa8];
    BYTE NextStencilBit;    // 0x148 (neutral name)
};
class FRenderTarget;

class FSceneNode
{
public:
    UViewport* Viewport;          // 0x04
    FRenderTarget* RenderTarget;  // 0x08
    FSceneNode* Parent;           // 0x0c
    INT Recursion;                // 0x10
    FMatrix WorldToCamera;        // 0x14
    FMatrix CameraToWorld;        // 0x54
    FMatrix CameraToScreen;       // 0x94
    FMatrix ScreenToCamera;       // 0xd4
    FMatrix WorldToScreen;        // 0x114
    FMatrix ScreenToWorld;        // 0x154
    FVector ViewOrigin;           // 0x194
    FVector CameraX;              // 0x1a0
    FVector CameraY;              // 0x1ac
    FLOAT Determinant;            // 0x1b8

    FSceneNode(FSceneNode* InParent);   // 0x112c70
    virtual ~FSceneNode() {}
};

extern const FLOAT GSceneNodeScreenScale;   // 0x10c10acc (2.0, shared float constant)

class FLevelSceneNode : public FSceneNode
{
public:
    ULevel* Level;              // 0x1bc
    UModel* Model;              // 0x1c0
    DWORD StencilMask;          // 0x1c4
    INT ViewZone;               // 0x1c8
    INT InvisibleZone;          // 0x1cc
    DWORD StencilBit;           // 0x1d0

    FLevelSceneNode(FLevelSceneNode* InParent, INT InViewZone, FMatrix LocalToParent);
    virtual ~FLevelSceneNode() {}
};

class FSkySceneNode : public FLevelSceneNode
{
public:
    FSkySceneNode(FLevelSceneNode* InParent, INT InZone);
};

class FMirrorSceneNode : public FLevelSceneNode
{
public:
    INT Unknown1D4;             // 0x1d4
    INT ParentSurf;             // 0x1d8
    FMirrorSceneNode(FLevelSceneNode* InParent, const FPlane& MirrorPlane, INT InViewZone, INT InParentSurf);
};

// RVA 0x1178e0 (LTCG: this, InParent and InZone on the stack, ret 0xc).
__declspec(noinline) FSkySceneNode::FSkySceneNode(FLevelSceneNode* InParent, INT InZone)
    : FLevelSceneNode(InParent, InZone,
        FTranslationMatrix(-InParent->Level->GetZoneActor(InZone)->Location) *
        FInverseRotationMatrix(InParent->Level->GetZoneActor(InZone)->Rotation) *
        FTranslationMatrix(InParent->ViewOrigin))
{
}

// RVA 0x117a00 (LTCG: Plane in EAX, this in EBX).
__declspec(noinline) FMirrorMatrix::FMirrorMatrix(const FPlane& Plane)
{
    FVector Origin = Plane * (2.f * Plane.W);
    FVector XAxis = GMath_UnitX.MirrorByVector(Plane);
    FVector YAxis = GMath_UnitY.MirrorByVector(Plane);
    FVector ZAxis = GMath_UnitZ.MirrorByVector(Plane);
    FVector NegOrigin = -Origin;
    *(FMatrix*)this = FMatrix(
        FPlane(XAxis.X, YAxis.X, ZAxis.X, 0.f),
        FPlane(XAxis.Y, YAxis.Y, ZAxis.Y, 0.f),
        FPlane(XAxis.Z, YAxis.Z, ZAxis.Z, 0.f),
        FPlane(NegOrigin | XAxis, NegOrigin | YAxis, NegOrigin | ZAxis, 1.f));
}

// RVA 0x117c00 (LTCG: MirrorPlane in EAX; this, InParent, InViewZone and
// InParentSurf on the stack, ret 0x10).
__declspec(noinline) FMirrorSceneNode::FMirrorSceneNode(FLevelSceneNode* InParent, const FPlane& MirrorPlane, INT InViewZone, INT InParentSurf)
    : FLevelSceneNode(InParent, InViewZone, FMirrorMatrix(MirrorPlane))
{
    ParentSurf = InParentSurf;
}

// Scaffolding for the link, not part of the unit: bodies of the callees
// (items 0202, 0207, 0299, 0307, 0356, 0363) so LTCG gives them their retail
// register conventions, and drivers.
void Escape(void*);
__declspec(noinline) FMatrix::FMatrix(const FPlane& InX, const FPlane& InY, const FPlane& InZ, const FPlane& InW)
{
    XPlane = InX;
    YPlane = InY;
    ZPlane = InZ;
    WPlane = InW;
}
__declspec(noinline) FTranslationMatrix::FTranslationMatrix(const FVector& Delta)
    : FMatrix(
        FPlane(1.f, 0.f, 0.f, 0.f),
        FPlane(0.f, 1.f, 0.f, 0.f),
        FPlane(0.f, 0.f, 1.f, 0.f),
        FPlane(Delta.X, Delta.Y, Delta.Z, 1.f))
{
}
__declspec(noinline) void FMatrix::operator*=(const FMatrix& Other)
{
    *this = *this * Other;
}
__declspec(noinline) FInverseRotationMatrix::FInverseRotationMatrix(const FRotator& Rot)
{
    FLOAT S, C;
    GMath.SinCos(-Rot.Yaw, &S, &C);
    FPlane W(GMath_Zero, 1.f);
    *(FMatrix*)this = FMatrix(FPlane(+C, +S, 0.f, 0.f), FPlane(-S, +C, 0.f, 0.f), FPlane(GMath_UnitZ, 0.f), W);
    GMath.SinCos(-Rot.Pitch, &S, &C);
    *this *= FMatrix(FPlane(+C, 0.f, +S, 0.f), FPlane(GMath_UnitY, 0.f), FPlane(-S, 0.f, +C, 0.f), W);
    GMath.SinCos(-Rot.Roll, &S, &C);
    *this *= FMatrix(FPlane(GMath_UnitX, 0.f), FPlane(0.f, +C, -S, 0.f), FPlane(0.f, +S, +C, 0.f), W);
}
// RVA 0x115530 (item 0363): InParent in EAX, this on the stack.
FLevelSceneNode::FLevelSceneNode(FLevelSceneNode* InParent, INT InViewZone, FMatrix LocalToParent)
    : FSceneNode(InParent)
{
    Level = InParent->Level;
    Model = InParent->Model;
    ViewZone = InViewZone;
    InvisibleZone = -1;
    StencilMask = 0;
    StencilBit = Viewport->NextStencilBit;
    Viewport->NextStencilBit <<= 1;

    FMatrix ParentToLocal = LocalToParent.Inverse();
    { FMatrix T = Parent->WorldToCamera * LocalToParent; WorldToCamera = T; }
    { FMatrix T = ParentToLocal * Parent->CameraToWorld; CameraToWorld = T; }
    { FMatrix T = CameraToScreen * WorldToCamera; WorldToScreen = T; }
    { FMatrix T = CameraToWorld * ScreenToCamera; ScreenToWorld = T; }
    Determinant = WorldToScreen.Determinant();

    ViewOrigin = ParentToLocal.TransformFVector(Parent->ViewOrigin);
    CameraX = ScreenToWorld.TransformNormal(FVector(GSceneNodeScreenScale / Viewport->SizeX, 0.f, 0.f));
    CameraY = ScreenToWorld.TransformNormal(FVector(0.f, GSceneNodeScreenScale / Viewport->SizeY, 0.f));
}

FSceneNode::FSceneNode(FSceneNode* InParent)
{
    Parent = InParent;
    Viewport = InParent->Viewport;
    RenderTarget = InParent->RenderTarget;
    Recursion = InParent->Recursion + 1;
    WorldToCamera = InParent->WorldToCamera;
    CameraToScreen = InParent->CameraToScreen;
    ScreenToCamera = InParent->ScreenToCamera;
    CameraToWorld = InParent->CameraToWorld;
    WorldToScreen = InParent->WorldToScreen;
    ScreenToWorld = InParent->ScreenToWorld;
    ViewOrigin = InParent->ViewOrigin;
    CameraX = InParent->CameraX;
    CameraY = InParent->CameraY;
    Determinant = WorldToScreen.Determinant();
}
FMatrix FMatrix::Inverse() const
{
    FMatrix Result;
    FLOAT Det = Determinant();

    if (Det == 0.0f)
        return GIdentityMatrix;

    FLOAT RDet = 1.0f / Det;

    Result.M[0][0] = RDet * (
            M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
            M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
            M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
            );
    Result.M[0][1] = -RDet * (
            M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
            M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
            M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
            );
    Result.M[0][2] = RDet * (
            M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
            M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
            M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
            );
    Result.M[0][3] = -RDet * (
            M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
            M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
            M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
            );

    Result.M[1][0] = -RDet * (
            M[1][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
            M[2][0] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
            M[3][0] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
            );
    Result.M[1][1] = RDet * (
            M[0][0] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
            M[2][0] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
            M[3][0] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
            );
    Result.M[1][2] = -RDet * (
            M[0][0] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
            M[1][0] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
            M[3][0] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
            );
    Result.M[1][3] = RDet * (
            M[0][0] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
            M[1][0] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
            M[2][0] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
            );

    Result.M[2][0] = RDet * (
            M[1][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
            M[2][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) +
            M[3][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1])
            );
    Result.M[2][1] = -RDet * (
            M[0][0] * (M[2][1] * M[3][3] - M[2][3] * M[3][1]) -
            M[2][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
            M[3][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1])
            );
    Result.M[2][2] = RDet * (
            M[0][0] * (M[1][1] * M[3][3] - M[1][3] * M[3][1]) -
            M[1][0] * (M[0][1] * M[3][3] - M[0][3] * M[3][1]) +
            M[3][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
            );
    Result.M[2][3] = -RDet * (
            M[0][0] * (M[1][1] * M[2][3] - M[1][3] * M[2][1]) -
            M[1][0] * (M[0][1] * M[2][3] - M[0][3] * M[2][1]) +
            M[2][0] * (M[0][1] * M[1][3] - M[0][3] * M[1][1])
            );

    Result.M[3][0] = -RDet * (
            M[1][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
            M[2][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) +
            M[3][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1])
            );
    Result.M[3][1] = RDet * (
            M[0][0] * (M[2][1] * M[3][2] - M[2][2] * M[3][1]) -
            M[2][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
            M[3][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1])
            );
    Result.M[3][2] = -RDet * (
            M[0][0] * (M[1][1] * M[3][2] - M[1][2] * M[3][1]) -
            M[1][0] * (M[0][1] * M[3][2] - M[0][2] * M[3][1]) +
            M[3][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
            );
    Result.M[3][3] = RDet * (
            M[0][0] * (M[1][1] * M[2][2] - M[1][2] * M[2][1]) -
            M[1][0] * (M[0][1] * M[2][2] - M[0][2] * M[2][1]) +
            M[2][0] * (M[0][1] * M[1][2] - M[0][2] * M[1][1])
            );

    return Result;
}

FLOAT FMatrix::Determinant() const
{
    return  M[0][0] * (
                M[1][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                M[2][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) +
                M[3][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2])
                ) -
            M[1][0] * (
                M[0][1] * (M[2][2] * M[3][3] - M[2][3] * M[3][2]) -
                M[2][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
                M[3][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2])
                ) +
            M[2][0] * (
                M[0][1] * (M[1][2] * M[3][3] - M[1][3] * M[3][2]) -
                M[1][1] * (M[0][2] * M[3][3] - M[0][3] * M[3][2]) +
                M[3][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
                ) -
            M[3][0] * (
                M[0][1] * (M[1][2] * M[2][3] - M[1][3] * M[2][2]) -
                M[1][1] * (M[0][2] * M[2][3] - M[0][3] * M[2][2]) +
                M[2][1] * (M[0][2] * M[1][3] - M[0][3] * M[1][2])
                );
}

__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix& Other) const
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
void Driver_115530(void* Mem, FLevelSceneNode* P, INT Zone, FMatrix* M)
{
    Escape(&GIdentityMatrix);
    Escape(new(Mem) FLevelSceneNode(P, Zone, *M));
}
void Driver_1178e0(void* Mem, FLevelSceneNode* P, INT Zone)
{
    Escape(&GMath);
    Escape(new(Mem) FSkySceneNode(P, Zone));
}
void Driver_117c00(void* Mem, FLevelSceneNode* P, const FPlane* Plane, INT Zone, INT Surf)
{
    Escape(new(Mem) FMirrorSceneNode(P, *Plane, Zone, Surf));
}
void Driver_117a00(FMatrix* Out, const FPlane* P)
{
    new (Out) FMirrorMatrix(*P);
}
// Many direct FMatrix constructions, as in retail, fix 0x4fbc0's register convention.
void Driver_4fbc0(FMatrix* Out, const FPlane* P)
{
    for (INT i = 0; i < 8; i++)
    {
        new (&Out[i * 4 + 0]) FMatrix(P[0], P[1], P[2], P[3]);
        new (&Out[i * 4 + 1]) FMatrix(P[4], P[5], P[6], P[7]);
        new (&Out[i * 4 + 2]) FMatrix(P[8], P[9], P[10], P[11]);
        new (&Out[i * 4 + 3]) FMatrix(P[12], P[13], P[14], P[15]);
    }
}
