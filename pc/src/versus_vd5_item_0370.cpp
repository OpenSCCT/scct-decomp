// Work item 0370: Versus RVA 0x117ca0-0x117f77.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;

extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const TCHAR *, const TCHAR *);
inline void *operator new(unsigned int, void *P) { return P; }
extern "C" double __cdecl tan(double);
extern "C" double __cdecl sqrt(double);
#pragma intrinsic(tan, sqrt)

struct FVector { FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FLOAT operator|(const FVector &V) const { return X * V.X + Y * V.Y + Z * V.Z; }
};
struct FPlane : FVector { FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FVector(InX, InY, InZ), W(InW) {}
    FLOAT PlaneDot(const FVector &P) const { return X * P.X + Y * P.Y + Z * P.Z - W; }
};
struct FVector4 : FPlane {
    FVector4() {}
    FVector4(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : FPlane(InX, InY, InZ, InW) {}
};
struct FSphere : FPlane {
    FSphere TransformBy(const struct FMatrix &M) const;
};
struct FMatrix {
    FLOAT M[4][4];
    FMatrix() {}
    FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW);  // 0x14fbc0
    FVector4 TransformFVector4(const FVector4 &P) const;
};
struct FPerspectiveMatrix : FMatrix {
    FPerspectiveMatrix(FLOAT FOVX, FLOAT FOVY, FLOAT MultFOVX, FLOAT MultFOVY, FLOAT MinZ, FLOAT MaxZ);
};

inline FLOAT appTan(FLOAT V) { return (FLOAT)tan(V); }
inline FLOAT appSqrt(FLOAT V) { return (FLOAT)sqrt(V); }
// Max of two non-negative floats compared by their bit patterns.
inline FLOAT FloatMax(FLOAT A, FLOAT B) { return *(DWORD *)&A >= *(DWORD *)&B ? A : B; }

// 0x117ca0: sphere against six frustum planes (class name unknown, planes at +0x60).
class UnnamedFrustum_117ca0 {
public:
    char Pad[0x60];
    FPlane Planes[6];
    UBOOL SphereCheck(const FSphere &S);
};
UBOOL UnnamedFrustum_117ca0::SphereCheck(const FSphere &S)
{
    FLOAT NegRadius = -S.W;
    for (INT i = 0; i < 6; i++)
        if (Planes[i].PlaneDot(S) <= NegRadius)
            return 0;
    return 1;
}

// 0x117cf0
FPerspectiveMatrix::FPerspectiveMatrix(FLOAT FOVX, FLOAT FOVY, FLOAT MultFOVX, FLOAT MultFOVY, FLOAT MinZ, FLOAT MaxZ)
    : FMatrix(
        FPlane(MultFOVX / appTan(FOVX), 0.0f, 0.0f, 0.0f),
        FPlane(0.0f, MultFOVY / appTan(FOVY), 0.0f, 0.0f),
        FPlane(0.0f, 0.0f, MaxZ / (MaxZ - MinZ), 1.0f),
        FPlane(0.0f, 0.0f, -MinZ * (MaxZ / (MaxZ - MinZ)), 0.0f))
{
}

// 0x117db0
FSphere FSphere::TransformBy(const FMatrix &M) const
{
    FSphere Result;
    (FVector &)Result = M.TransformFVector4(FVector4(X, Y, Z, 1.0f));
    FVector XAxis(M.M[0][0], M.M[0][1], M.M[0][2]);
    FVector YAxis(M.M[1][0], M.M[1][1], M.M[1][2]);
    FVector ZAxis(M.M[2][0], M.M[2][1], M.M[2][2]);
    Result.W = appSqrt(FloatMax(XAxis | XAxis, FloatMax(YAxis | YAxis, ZAxis | ZAxis))) * W;
    return Result;
}

// 0x117ef0: hit proxy type checks.
// Retail literals bound as data (shared with longer strings).
extern const TCHAR HHitProxy_Name[];  // L"HHitProxy"
struct HHitProxy {
    virtual UBOOL IsA(const TCHAR *Str) { return !_wcsicmp(HHitProxy_Name, Str); }
};
// Retail shares this literal with a longer string, so it is bound as data.
extern const TCHAR HActor_Name[];  // L"HActor"
struct HActor : HHitProxy {
    virtual UBOOL IsA(const TCHAR *Str);
};
UBOOL HActor::IsA(const TCHAR *Str)
{
    return !_wcsicmp(HActor_Name, Str) || HHitProxy::IsA(Str);
}

// 0x117f30: render resource constructor taking a fresh cache id (class name unknown).
extern QWORD GCacheIDCounter;  // 0x10c96930
inline QWORD MakeCacheID(INT Base) { return GCacheIDCounter++ * 256 + Base; }
#pragma pack(push, 4)
// Render resource base: takes its cache id from the derived constructor.
struct UnnamedResourceBase_117f30 {
    virtual ~UnnamedResourceBase_117f30();
    char Pad[0x60];
    QWORD CacheId;
    UnnamedResourceBase_117f30(QWORD InCacheId) : CacheId(InCacheId) {}
};
#pragma pack(pop)
class UnnamedResource_117f30 : public UnnamedResourceBase_117f30 {
public:
    UnnamedResource_117f30();
    virtual ~UnnamedResource_117f30();
};
__declspec(noinline) UnnamedResource_117f30::UnnamedResource_117f30()
    : UnnamedResourceBase_117f30(MakeCacheID(0xE1))
{
}

// Scaffolding for the link, not part of the unit.
// The FMatrix constructor lives in another unit (0x14fbc0); a body here lets
// the linker give it the register convention retail uses.
__declspec(noinline) FMatrix::FMatrix(const FPlane &InX, const FPlane &InY, const FPlane &InZ, const FPlane &InW)
{
    M[0][0] = InX.X; M[0][1] = InX.Y; M[0][2] = InX.Z; M[0][3] = InX.W;
    M[1][0] = InY.X; M[1][1] = InY.Y; M[1][2] = InY.Z; M[1][3] = InY.W;
    M[2][0] = InZ.X; M[2][1] = InZ.Y; M[2][2] = InZ.Z; M[2][3] = InZ.W;
    M[3][0] = InW.X; M[3][1] = InW.Y; M[3][2] = InW.Z; M[3][3] = InW.W;
}
void Escape(void *);
UBOOL Driver_117ca0(UnnamedFrustum_117ca0 *F, const FSphere *S) { return F->SphereCheck(*S); }
FPerspectiveMatrix Driver_117cf0(FLOAT a, FLOAT b, FLOAT c, FLOAT d, FLOAT e, FLOAT f) { return FPerspectiveMatrix(a, b, c, d, e, f); }
void Driver_117db0(FSphere *Out, const FSphere *S, const FMatrix *M) { *Out = S->TransformBy(*M); }
UBOOL Driver_117ef0(HActor *A, const TCHAR *S) { return A->HActor::IsA(S); }
void *Driver_117f30(void *P) { Escape(&GCacheIDCounter); return new (P) UnnamedResource_117f30; }
