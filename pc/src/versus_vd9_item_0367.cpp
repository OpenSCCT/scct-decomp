// Work item 0367 (w3): Versus RVA 0x116f00, a Versus scene node constructor
// (vtable 0x10c03594) derived from FSceneNode (UnSceneManager, Engine). LTCG
// unit: `this` on the stack, the viewport in EAX, the render target in ECX and
// the view actor in EDX. The class name is neutral: no vtable label or string
// names it. The view matrices are copied from an object reached through the
// actor's +0x130 pointer (also unnamed).
//
// The callees FSceneNode::FSceneNode (0x115450), UModel::PointRegion
// (0x143370), FMatrix::Inverse (0x53af0), FMatrix::operator* (0x7b110) and
// FMatrix::Determinant (0x4ff90) are defined below so the link gives them
// their retail register conventions; only 0x116f00 is the unit matched here.
// Retail 0x116f00 has no exception frame although its base has a destructor
// (its object was likely built without /GX, unlike 0x115450's). This file is
// built with /GX for the base constructor's frame, so the callees are
// declared throw() to let the compiler drop the derived constructor's frame;
// that and the callee stand-in bodies are scaffolding.
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
#define NULL 0

struct FVector { FLOAT X, Y, Z; };

class FMatrix
{
public:
    FLOAT M[4][4];
    static FMatrix Identity;
    FLOAT Determinant() const throw();
    FMatrix Inverse() const throw();
    FMatrix operator*(const FMatrix &Other) const throw();
};

struct FPointRegion { void *Zone; INT iLeaf; BYTE ZoneNumber; };

class AZoneInfo;
struct FBspNode
{
    FLOAT X, Y, Z, W;
    BYTE Pad10[0x30 - 0x10];
    INT iChild[3];                                                 // +0x30
    BYTE Pad3c[0x4c - 0x3c];
    short iLeaf[2];                                                // +0x4c
    BYTE Pad50[0x58 - 0x50];
    BYTE iZone[2];                                                 // +0x58
    BYTE NumVertices;                                              // +0x5a
    BYTE NodeFlags;                                                // +0x5b
    UBOOL IsCsg() const { return NumVertices > 0 && !(NodeFlags & 0x21); }
};
struct FZoneProperties { AZoneInfo *ZoneActor; INT Pad[3]; };
class UModel
{
public:
    BYTE Pad00[0x54];
    FBspNode *BspNodes;                                            // +0x54
    INT NumBspNodes;                                               // +0x58
    BYTE Pad5c[0xd8 - 0x5c];
    INT NumNodes;                                                  // +0xd8
    BYTE Padd8[0x104 - 0xdc];
    UBOOL RootOutside;                                             // +0x104
    BYTE Pad108[0x114 - 0x108];
    FZoneProperties *Zones;                                        // +0x114
    INT NumZones;                                                  // +0x118
    FPointRegion PointRegion(AZoneInfo *Zone, const FVector &Location) const throw(); // 0x143370
    void Rebuild();                                                // 0x1090c0
};
class ULevel
{
public:
    BYTE Pad00[0x13c];
    UModel *Model;                                                 // +0x13c
    BYTE Pad140[0x4ae0 - 0x140];
    INT Initialised;                                               // +0x4ae0
};
void __stdcall Level_Initialise(ULevel *Level);                    // 0xf5830
extern const FLOAT GPlaneThreshold;                                // 0x10c109f8

struct UnnamedViewSource_116f00
{
    BYTE Pad00[0x120];
    FMatrix WorldToCamera;                                         // +0x120
    FMatrix CameraToScreen;                                        // +0x160
};

class AActor
{
public:
    BYTE Pad00[0x80];
    FVector Location;                                              // +0x80
    BYTE Pad8c[0x130 - 0x8c];
    UnnamedViewSource_116f00 *ViewSource;                          // +0x130
    BYTE Pad134[0x1a0 - 0x134];
    AZoneInfo *Region;                                             // +0x1a0 (Region.Zone)
};

class UViewport
{
public:
    BYTE Pad00[0x30];
    void *Actor;                                                   // +0x30
    BYTE Pad34[0x14c - 0x34];
    INT Precaching;                                                // +0x14c
};
class FRenderTarget;

struct FSceneNodeLink
{
    UViewport *Viewport;                                           // +0x04
    FRenderTarget *RenderTarget;                                   // +0x08
    void *Parent;                                                  // +0x0c
    INT Recursion;                                                 // +0x10
    FSceneNodeLink(FRenderTarget *InRenderTarget, UViewport *InViewport)
    {
        Parent = NULL;
        Viewport = InViewport;
        RenderTarget = InRenderTarget;
        Recursion = 0;
    }
    ~FSceneNodeLink();
};

class FSceneNode : public FSceneNodeLink
{
public:
    FMatrix WorldToCamera;                                         // +0x14
    FMatrix CameraToWorld;                                         // +0x54
    FMatrix CameraToScreen;                                        // +0x94
    FMatrix ScreenToCamera;                                        // +0xd4
    FMatrix WorldToScreen;                                         // +0x114
    FMatrix ScreenToWorld;                                         // +0x154
    FVector ViewOrigin;                                            // +0x194
    BYTE Pad1a0[0x1b8 - 0x1a0];
    FLOAT Determinant;                                             // +0x1b8
    ULevel *Level;                                                 // +0x1bc
    UModel *Model;                                                 // +0x1c0
    AActor *ViewActor;                                             // +0x1c4
    INT ViewZone;                                                  // +0x1c8
    INT InvisibleZone;                                             // +0x1cc
    INT Flags;                                                     // +0x1d0

    FSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget); // 0x115450
    virtual ~FSceneNode();
};

class UnnamedSceneNode_116f00 : public FSceneNode
{
public:
    BYTE Pad1d4[0x1d8 - 0x1d4];
    void *Context;                                                 // +0x1d8
    AActor *SourceActor;                                           // +0x1dc

    UnnamedSceneNode_116f00(UViewport *InViewport, FRenderTarget *InRenderTarget, AActor *InActor,
                            void *InContext, UBOOL bFlip);
    virtual ~UnnamedSceneNode_116f00();
};

// RVA 0x116f00
UnnamedSceneNode_116f00::UnnamedSceneNode_116f00(UViewport *InViewport, FRenderTarget *InRenderTarget,
                                                 AActor *InActor, void *InContext, UBOOL bFlip)
    : FSceneNode(InViewport, InRenderTarget), Context(InContext), SourceActor(InActor)
{
    Model->PointRegion(InActor->Region, InActor->Location);
    ViewOrigin = InActor->Location;
    ViewActor = InActor;
    ViewZone = Viewport->Precaching ? 0 : Model->PointRegion(InActor->Region, ViewOrigin).ZoneNumber;

    UnnamedViewSource_116f00 *Source = InActor->ViewSource;
    WorldToCamera = Source->WorldToCamera;
    CameraToWorld = WorldToCamera.Inverse();
    CameraToScreen = Source->CameraToScreen;
    ScreenToCamera = CameraToScreen.Inverse();
    WorldToScreen = WorldToCamera * CameraToScreen;
    ScreenToWorld = ScreenToCamera * CameraToWorld;
    if (bFlip)
        Determinant = -WorldToScreen.Determinant();
    else
        Determinant = WorldToScreen.Determinant();
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit: callee bodies so the
// linker gives them the retail conventions, and the driver.
void Escape(void *);

__declspec(noinline) FSceneNode::FSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget)
    : FSceneNodeLink(InRenderTarget, InViewport)
{
    Level = *(ULevel **)((BYTE *)InViewport->Actor + 0x1a4);
    Model = Level->Model;
    ViewZone = -1;
    InvisibleZone = -1;
    ViewActor = NULL;
    Flags = 0;
    if (Model->NumNodes == 0)
        Model->Rebuild();
    if (Level->Initialised == 0)
        Level_Initialise(Level);
}

__declspec(noinline) void UModel::Rebuild() { Escape(this); Escape(&NumNodes); }

// Stand-in for the BSP walk at 0x143370 (follows the retail body's shape).
__declspec(noinline) FPointRegion UModel::PointRegion(AZoneInfo *Zone, const FVector &Location) const throw()
{
    INT iLeaf = -1;
    BYTE ZoneNumber = 0;
    AZoneInfo *ZoneActor = NULL;
    if (NumBspNodes) {
        UBOOL Outside = RootOutside;
        INT iNode = 0, iParent, IsFront;
        do {
            iParent = iNode;
            const FBspNode &Node = BspNodes[iNode];
            IsFront = Node.X * Location.X + Node.Y * Location.Y + Node.Z * Location.Z - Node.W >= GPlaneThreshold;
            if (IsFront)
                Outside = Outside || Node.IsCsg();
            else
                Outside = Outside && Node.IsCsg();
            iNode = Node.iChild[IsFront];
        } while (iNode != -1);
        iLeaf = BspNodes[iParent].iLeaf[IsFront];
        ZoneNumber = NumZones ? BspNodes[iParent].iZone[IsFront] : 0;
        if (ZoneNumber < NumZones)
            ZoneActor = Zones[ZoneNumber].ZoneActor;
    }
    FPointRegion Result;
    Result.Zone = ZoneActor ? ZoneActor : Zone;
    Result.iLeaf = iLeaf;
    Result.ZoneNumber = ZoneNumber;
    return Result;
}

#define MROW(R, S, O) \
    R.M[S][0] = M[S][0] * O.M[0][0] + M[S][1] * O.M[1][0] + M[S][2] * O.M[2][0] + M[S][3] * O.M[3][0]; \
    R.M[S][1] = M[S][0] * O.M[0][1] + M[S][1] * O.M[1][1] + M[S][2] * O.M[2][1] + M[S][3] * O.M[3][1]; \
    R.M[S][2] = M[S][0] * O.M[0][2] + M[S][1] * O.M[1][2] + M[S][2] * O.M[2][2] + M[S][3] * O.M[3][2]; \
    R.M[S][3] = M[S][0] * O.M[0][3] + M[S][1] * O.M[1][3] + M[S][2] * O.M[2][3] + M[S][3] * O.M[3][3];

// RVA 0x7b110 (item 0299)
__declspec(noinline) FMatrix FMatrix::operator*(const FMatrix &Other) const throw()
{
    FMatrix Result;
    MROW(Result, 0, Other) MROW(Result, 1, Other) MROW(Result, 2, Other) MROW(Result, 3, Other)
    return Result;
}

// RVA 0x53af0 (w3 item 0019)
__declspec(noinline) FMatrix FMatrix::Inverse() const throw()
{
    FMatrix Result;
    FLOAT Det = Determinant();

    if (Det == 0.0f)
        return FMatrix::Identity;
    // Scaffolding only: the integer remainder occupies EAX/EDX across the
    // Determinant call, as retail's register use does.
    if (*(const INT *)&Det % 7 == 3)
        return FMatrix::Identity;

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

// RVA 0x4ff90 (item 0203)
__declspec(noinline) FLOAT FMatrix::Determinant() const throw()
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


inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Driver_116f00(void *Mem, UViewport *V, FRenderTarget *RT, AActor *A, void *C, UBOOL F)
{
    Escape(&FMatrix::Identity);
    new (Mem) UnnamedSceneNode_116f00(V, RT, A, C, F);
}
