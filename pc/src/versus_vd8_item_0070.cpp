// Work item 0070: Versus RVA 0x13c200 and 0x13c2c0 (VC7.0 /GL, linked /LTCG).
// Projection/camera Z-bias helper functions taking FSceneNode*.

typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl fabs(double);
extern "C" double __cdecl tan(double);
extern "C" double __cdecl atan(double);
#pragma intrinsic(sqrt, fabs, tan, atan)

inline FLOAT appSqrt(FLOAT V) { return (FLOAT)sqrt(V); }
inline FLOAT appTan(FLOAT V) { return (FLOAT)tan(V); }
inline FLOAT appAtan(FLOAT V) { return (FLOAT)atan(V); }

extern FLOAT GNearClippingPlane; // 0x10c73b08 (2.0f)
extern FLOAT GFarClippingPlane;  // 0x10c73b0c (32765.0f)

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector operator+(const FVector &V) const { return FVector(X + V.X, Y + V.Y, Z + V.Z); }
    FVector operator-(const FVector &V) const { return FVector(X - V.X, Y - V.Y, Z - V.Z); }
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
    FLOAT Size() const { return appSqrt(X * X + Y * Y + Z * Z); }
};

struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FPlane(const FVector &V, FLOAT InW) : FVector(V), W(InW) {}
};

struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);
    FMatrix operator*(const FMatrix &Other) const;
    FVector GetOrigin() const { return FVector(M[3][0], M[3][1], M[3][2]); }
};

// Defined here (from published versus_vd4_item_0299.cpp, RVA 0x7b110) so LTCG
// assigns the same register convention (result=EAX, this=EDX, Other=ECX).
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

struct FPerspectiveMatrix : public FMatrix
{
    FPerspectiveMatrix(FLOAT FOV, FLOAT Width, FLOAT Height, FLOAT MinZ, FLOAT MaxZ);
};

// Defined here (retail RVA 0x140d40) so LTCG gives it the same calling convention (this=ESI).
__declspec(noinline) FPerspectiveMatrix::FPerspectiveMatrix(FLOAT FOV, FLOAT Width, FLOAT Height, FLOAT MinZ, FLOAT MaxZ)
    : FMatrix(
        FPlane(1.0f / appTan(FOV), 0.0f, 0.0f, 0.0f),
        FPlane(0.0f, Width / appTan(FOV) / Height, 0.0f, 0.0f),
        FPlane(0.0f, 0.0f, MaxZ / (MaxZ - MinZ), 1.0f),
        FPlane(0.0f, 0.0f, -MinZ * (MaxZ / (MaxZ - MinZ)), 0.0f))
{
}

class UViewport
{
public:
    BYTE Pad00[0xa0];
    INT SizeX; // +0xa0
    INT SizeY; // +0xa4
};

class FRenderTarget;

class FSceneNode
{
public:
    virtual ~FSceneNode() {}
    UViewport *Viewport;          // +0x04
    FRenderTarget *RenderTarget;  // +0x08
    FSceneNode *Parent;           // +0x0c
    INT Recursion;                // +0x10
    FMatrix WorldToCamera;        // +0x14
    FMatrix CameraToWorld;        // +0x54
};

// RVA 0x13c200 (neutral name: tests if Point is in front of camera)
__declspec(noinline) bool IsPointInFrontOfCamera_13c200(FSceneNode *SceneNode, FPlane Point, FMatrix WorldToCamera)
{
    FPlane CamOrigin(SceneNode->CameraToWorld.M[3][0], SceneNode->CameraToWorld.M[3][1], SceneNode->CameraToWorld.M[3][2], 0.0f);
    FPlane ForwardPoint(
        CamOrigin.X + WorldToCamera.M[0][2],
        CamOrigin.Y + WorldToCamera.M[1][2],
        CamOrigin.Z + WorldToCamera.M[2][2],
        0.0f);
    FVector DiffCam = CamOrigin - Point;
    FVector DiffFwd = ForwardPoint - Point;
    return DiffFwd.Size() < DiffCam.Size();
}

// RVA 0x13c2c0 (neutral name: builds depth-biased WorldToScreen matrix)
__declspec(noinline) FLOAT BuildBiasedProjection_13c2c0(
    FSceneNode *SceneNode,
    const FVector &Dir,
    const FPlane &Point,
    FMatrix &OutMatrix,
    INT DepthBias,
    INT UnusedFlag)
{
    FMatrix LocalWorldToCamera = SceneNode->WorldToCamera;
    FLOAT Dot = LocalWorldToCamera.M[0][2] * Dir.X + LocalWorldToCamera.M[1][2] * Dir.Y + LocalWorldToCamera.M[2][2] * Dir.Z;

    FLOAT SlopeBias = (FLOAT)fabs(Dot) * 50.0f + DepthBias;
    FLOAT NearClip = GNearClippingPlane;
    FLOAT FarClip = GFarClippingPlane;
    FLOAT AngleFactor = 1.0f / ((Dot + 1.0f) * 1.7f) - 1.0f;
    AngleFactor = !(1.0f < AngleFactor) ? ((AngleFactor > 0.0f) ? AngleFactor : 0.0f) : 1.0f;
    FLOAT DistBias = AngleFactor * 1000.0f + 500.0f;

    FLOAT Shift;
    if (IsPointInFrontOfCamera_13c200(SceneNode, Point, SceneNode->WorldToCamera)) {
        Shift = DistBias + SlopeBias;
        NearClip += Shift;
    } else {
        FLOAT BaseShift = DistBias + SlopeBias;
        NearClip += BaseShift;
        Shift = BaseShift * 2.0f - DistBias;
    }

    LocalWorldToCamera.M[3][2] += Shift;
    FMatrix Proj = FPerspectiveMatrix(
        appAtan((FarClip * 0.66577375f) / (FarClip + Shift)),
        (FLOAT)SceneNode->Viewport->SizeX,
        (FLOAT)SceneNode->Viewport->SizeY,
        NearClip,
        FarClip + Shift);
    OutMatrix = LocalWorldToCamera * Proj;
    return Dot;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
FLOAT Driver_13c2c0(FSceneNode *SceneNode, const FVector *Dir, const FPlane *Point, FMatrix *OutMatrix, INT DepthBias)
{
    Escape(&GNearClippingPlane);
    Escape(&GFarClippingPlane);
    return BuildBiasedProjection_13c2c0(SceneNode, *Dir, *Point, *OutMatrix, DepthBias, 0);
}
