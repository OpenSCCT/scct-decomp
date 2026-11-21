// Work item 0356: FSceneNode copy constructor / Project / Deproject (Engine, UnRender),
// and a neighbouring 64-slot table class (neutral name UnnamedTable_112e30).
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

void *operator new(unsigned int Size);
class UViewport;
class FRenderTarget;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
};
struct FPlane : public FVector
{
    FLOAT W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) { X = InX; Y = InY; Z = InZ; W = InW; }
    FPlane(const FVector &V, FLOAT InW) { X = V.X; Y = V.Y; Z = V.Z; W = InW; }
};
struct FMatrix
{
    FLOAT M[4][4];
    FPlane TransformFPlane(const FPlane &P) const;   // 0x4fe60
    FLOAT Determinant() const;                       // 0x4ff90 (defined below so the link sees its convention)
};

// 0x4ff90, from UnMath.h; defined here so LTCG gives it its register convention.
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

class FSceneNode
{
public:
    UViewport *Viewport;          // +0x04
    FRenderTarget *RenderTarget;  // +0x08
    FSceneNode *Parent;           // +0x0c
    INT Recursion;                // +0x10
    FMatrix WorldToCamera;        // +0x14
    FMatrix CameraToWorld;        // +0x54
    FMatrix CameraToScreen;       // +0x94
    FMatrix ScreenToCamera;       // +0xd4
    FMatrix WorldToScreen;        // +0x114
    FMatrix ScreenToWorld;        // +0x154
    FVector ViewOrigin;           // +0x194
    FVector CameraX;              // +0x1a0
    FVector CameraY;              // +0x1ac
    FLOAT Determinant;            // +0x1b8

    FSceneNode(FSceneNode *InParent);
    virtual ~FSceneNode() {}
    FPlane Project(const FVector &Point);
    FVector Deproject(const FPlane &Screen);
};

// 0x112c70 (near: LTCG picks this=edx/parent=eax here, retail this=ebx/parent=edx and returns this)
FSceneNode::FSceneNode(FSceneNode *InParent)
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

// 0x112d60
FPlane FSceneNode::Project(const FVector &Point)
{
    FPlane Result = WorldToScreen.TransformFPlane(FPlane(Point, 1.0f));
    FLOAT RHW = 1.0f / Result.W;
    return FPlane(Result.X * RHW, Result.Y * RHW, Result.Z * RHW, Result.W);
}

// 0x112dd0 (near: the final FVector copy goes through ecx instead of esi)
__declspec(noinline) FVector FSceneNode::Deproject(const FPlane &Screen)
{
    return ScreenToWorld.TransformFPlane(FPlane(Screen.X * Screen.W, Screen.Y * Screen.W, Screen.Z * Screen.W, Screen.W));
}

// Neutral names: vtable 0x10c03724; 64 entries of 24 bytes, then 64 INTs.
struct UnnamedEntry_112e30
{
    INT A, B, C, D, E, F;
    UnnamedEntry_112e30() { A = 0; B = 0; C = 0; D = 0; E = 0; F = 0; }
};

extern "C" void *memset(void *Dest, int C, unsigned int Count);
#pragma intrinsic(memset)
inline void appMemzero(void *Dest, INT Count) { memset(Dest, 0, Count); }

class UnnamedTable_112e30
{
public:
    UnnamedEntry_112e30 Entries[64];  // +0x004
    INT Items[64];                    // +0x604
    INT Value704;                     // +0x704
    INT Value708;                     // +0x708
    INT Value70C;                     // +0x70c
    INT Value710;                     // +0x710
    INT Count;                        // +0x714

    UnnamedTable_112e30();
    virtual ~UnnamedTable_112e30() {}
    void Reset();
    void AddItem(INT Item);
};

// 0x112e30
__declspec(noinline) UnnamedTable_112e30::UnnamedTable_112e30()
{
    Reset();
}

// 0x112e60. Retail inlines UE2's inline-asm appMemzero (UnVcWin32.h); this C memset
// version is a near miss kept within the brief's no-asm rule.
__declspec(noinline) void UnnamedTable_112e30::Reset()
{
    Value70C = 0;
    Value704 = 0;
    Value708 = 0;
    Value710 = 0;
    Count = 0;
    appMemzero(Entries, sizeof(Entries));
    appMemzero(Items, sizeof(Items));
}

// 0x112ef0
void UnnamedTable_112e30::AddItem(INT Item)
{
    INT Num = Count;
    INT i;
    for (i = 0; i < Count; i++)
        if (Items[i] == Item)
            break;
    if (i == Num)
    {
        Items[Num] = Item;
        Count++;
    }
    Count = Count % 64;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
class FDerivedSceneNode_115530 : public FSceneNode
{
public:
    INT Extra1BC, Extra1C0, Extra1C4, Extra1C8;
    FDerivedSceneNode_115530(FSceneNode *InParent, INT InExtra);
};
FDerivedSceneNode_115530::FDerivedSceneNode_115530(FSceneNode *InParent, INT InExtra)
    : FSceneNode(InParent)
{
    Extra1BC = ((FDerivedSceneNode_115530 *)InParent)->Extra1BC;
    Extra1C0 = ((FDerivedSceneNode_115530 *)InParent)->Extra1C0;
    Extra1C8 = InExtra;
    Extra1C4 = 0;
    Escape(this);
}
inline void *operator new(unsigned int Size, void *Mem) { return Mem; }
void Driver_112c70(void *Mem, FSceneNode *Parent) { FSceneNode *N = new(Mem) FSceneNode(Parent); N->Recursion = 5; Escape(N); }
void Driver_112d60(FSceneNode *N, FVector *V, FPlane *Out) { *Out = N->Project(*V); }
void Driver_112dd0(FSceneNode *N, FPlane *P, FVector *Out) { for (INT i = 0; i < 7; i++) { Out[i] = N->Deproject(P[i]); Escape(Out); } Out[9] = N->Deproject(P[9]); Escape(N); Out[8] = N->Deproject(P[8]); Escape(N); Out[10] = N->Deproject(P[10]); Escape(N); Out[11] = N->Deproject(P[11]); }
void Driver_112e30(UnnamedTable_112e30 *T, UnnamedTable_112e30 *U) { new(T) UnnamedTable_112e30; Escape(T); U->Reset(); Escape(U); }
void Driver_112ef0(UnnamedTable_112e30 *T, INT I) { T->AddItem(I); }
