// Work item 0293: Versus RVA 0x101a00, UCanvas::execDrawPortal (UnCanvas.cpp,
// Engine). LTCG unit: the canvas utility constructor (0x111ad0) and
// destructor (0x111c00) take `this` on the stack, DrawTile (0x111f50) takes it
// in EAX, Flush (0x111c60) in ESI, the actor scene node constructor
// (0x1165a0) takes the render target in ECX and the view actor in EBX, and
// the pending-resource flush at 0x146800 takes the viewport in EBX. Those
// callees are defined here, following their retail bodies, so the link gives
// them those conventions; only execDrawPortal is the unit being matched.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned __int64 QWORD;
#define RESULT_DECL void *const Result
#define NULL 0

class UObject;
struct FFrame;
typedef void (UObject::*Native)(FFrame &Stack, RESULT_DECL);
extern Native GNatives[];

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

struct FVector { FLOAT X, Y, Z; };
struct FPlane { FLOAT X, Y, Z, W; FPlane() {} FPlane(FVector V, FLOAT InW) : X(V.X), Y(V.Y), Z(V.Z), W(InW) {} };
struct FRotator { INT Pitch, Yaw, Roll; };
struct FMatrix { FLOAT M[4][4]; };
struct FColor
{
    BYTE R, G, B, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : R(InR), G(InG), B(InB), A(InA) {}
};
extern FMatrix GIdentityMatrix;
extern FVector *GAmbientLight;

class FRenderInterface;
class FVertexStream;
class UMaterial;

class FRenderState
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10();
    virtual void SetLight(FRenderInterface *RI, INT Index, FPlane Color, INT A, INT B, INT C); // +0x14
    virtual void SetTransform(FRenderInterface *RI, INT Type, const FMatrix *Matrix);        // +0x18
    virtual void Slot1c();
    virtual INT SetDynamicStream(FRenderInterface *RI, INT Index, FVertexStream *Stream);     // +0x20
    virtual void SetMaterial(FRenderInterface *RI, UMaterial *Material, INT Flags);          // +0x24
};

class FRenderInterface
{
public:
    virtual void PushState();                                      // +0x00
    virtual void PopState();                                       // +0x04
    virtual void Slot08();
    virtual void SetViewport(INT X, INT Y, INT Width, INT Height); // +0x0c
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18();
    virtual void SetCullMode(INT Mode);                            // +0x1c
    virtual void Slot20();
    virtual void Clear(INT A, INT B, INT C, FColor Color);         // +0x24
    virtual void Slot28(); virtual void Slot2c(); virtual void Slot30(); virtual void Slot34();
    virtual void Slot38(); virtual void Slot3c(); virtual void Slot40(); virtual void Slot44();
    virtual void Slot48(); virtual void Slot4c(); virtual void Slot50(); virtual void Slot54();
    virtual void Slot58();
    virtual void EnableLighting(INT A, INT B);                     // +0x5c
    virtual void Slot60();
    virtual void DrawPrimitive(INT Type, INT FirstIndex, INT NumPrimitives, INT MinIndex, INT MaxIndex); // +0x64
    BYTE Pad04[0x14 - 0x04];
    FRenderState *State;                                           // +0x14
};

class FRenderTarget
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06();
    virtual INT GetHeight();                                       // +0x1c
    virtual INT GetWidth();                                        // +0x20
};

class UObject
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21();
    virtual void GetViewpoint(FVector *Location, FRotator *Rotation); // +0x58
    virtual void Slot23(); virtual void Slot24(); virtual void Slot25();
    virtual INT MaterialUSize();                                   // +0x68
    virtual INT MaterialVSize();                                   // +0x6c
};

class AActor : public UObject
{
public:
    BYTE Pad04[0x1a0 - 0x04];
    void *Region;                                                  // +0x1a0
};
class UMaterial : public UObject {};

class APlayerController
{
public:
    BYTE Pad[0x308];
    FLOAT FovAngle;                                                // +0x308
};

class UCanvas;
class FCanvasUtil;

class FCacheFlusher
{
public:
    virtual void Slot00(); virtual void Slot04(); virtual void Slot08(); virtual void Slot0c();
    virtual void Slot10(); virtual void Slot14(); virtual void Slot18(); virtual void Slot1c();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2c();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3c();
    virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5c();
    virtual void Slot60(); virtual void Slot64(); virtual void Slot68(); virtual void Slot6c();
    virtual void Slot70(); virtual void Slot74(); virtual void Slot78();
    virtual void Flush(QWORD CacheId);                             // +0x7c
};

class UViewport
{
public:
    BYTE Pad00[0x30];
    APlayerController *Actor;                                      // +0x30
    BYTE Pad34[0x68 - 0x34];
    UCanvas *Canvas;                                               // +0x68
    BYTE Pad6c[0x70 - 0x6c];
    FCacheFlusher *RenDev;                                         // +0x70
    BYTE Pad74[0xe4 - 0x74];
    FRenderTarget RenderTarget;                                    // +0xe4
    BYTE Pade8[0x140 - 0xe8];
    FRenderInterface *RI;                                          // +0x140
    BYTE Pad144[0x14c - 0x144];
    INT Precaching;                                                // +0x14c
};

class UCanvas
{
public:
    BYTE Pad00[0x78];
    UViewport *Viewport;                                           // +0x78
    FCanvasUtil *pCanvasUtil;                                      // +0x7c
    void execDrawPortal(FFrame &Stack, RESULT_DECL);
};

struct FFrame
{
    void *VfTable;
    void *Node;                 // +0x04
    UObject *Object;            // +0x08
    BYTE *Code;                 // +0x0c

    __forceinline void Step(UObject *Context, RESULT_DECL)
    {
        INT B = *Code++;
        (Context->*GNatives[B])(*this, Result);
    }
};

struct FCanvasVertex { FLOAT X, Y, Z; DWORD Color; FLOAT U, V; };

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);                           // 0x44e0
};

template <class T> class TArray : public FArray
{
public:
    TArray() { Data = 0; ArrayNum = 0; ArrayMax = 0; }
    ~TArray();
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FVertexStream
{
public:
    virtual QWORD GetCacheId();
};

extern QWORD GCacheCounter;
extern const TCHAR CanvasUtil_AllocTag[];
extern const TCHAR CanvasUtil_ReallocTag[];
extern const FLOAT GOne;

class FCanvasUtil : public FVertexStream
{
public:
    INT PrimitiveType;                                             // +0x04
    UMaterial *Material;                                           // +0x08
    INT NumPrimitives;                                             // +0x0c
    FRenderInterface *RI;                                          // +0x10
    BYTE Pad14[0x54 - 0x14];
    FMatrix ScreenToClip;                                          // +0x54
    TArray<FCanvasVertex> Vertices;                                // +0x94
    QWORD CacheId;                                                 // +0xa0

    FCanvasUtil(FRenderTarget *RenderTarget, FRenderInterface *InRI);
    ~FCanvasUtil();
    void Flush();
    void DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1, FLOAT U2, FLOAT V2,
                  FLOAT Z, UMaterial *InMaterial, FColor Color);
    void Init(FRenderInterface *InRI, FLOAT Width, FLOAT Height);  // 0x103f00
};

FCanvasUtil::FCanvasUtil(FRenderTarget *RenderTarget, FRenderInterface *InRI)
{
    CacheId = GCacheCounter * 256 + 0xe1;
    GCacheCounter++;
    PrimitiveType = 4;
    Material = NULL;
    NumPrimitives = 0;
    Vertices.ArrayNum = 0;
    if (Vertices.ArrayMax != 1362) {
        Vertices.ArrayMax = 1362;
        if (Vertices.Data)
            Vertices.Data = GMalloc->Realloc(Vertices.Data, 1362 * sizeof(FCanvasVertex), CanvasUtil_ReallocTag);
        else
            Vertices.Data = GMalloc->Malloc(1362 * sizeof(FCanvasVertex), CanvasUtil_AllocTag);
    }
    Init(InRI, (FLOAT)RenderTarget->GetWidth(), (FLOAT)RenderTarget->GetHeight());
}

void FCanvasUtil::Flush()
{
    if (NumPrimitives > 0) {
        RI->PushState();
        RI->Clear(0, 0, 0, FColor(0, 0, 0));
        RI->State->SetTransform(RI, 0, &GIdentityMatrix);
        RI->State->SetTransform(RI, 1, &GIdentityMatrix);
        RI->State->SetTransform(RI, 2, &ScreenToClip);
        INT FirstVertex = RI->State->SetDynamicStream(RI, 0, this);
        RI->State->SetLight(RI, 0, FPlane(*GAmbientLight, 0), 1, 0, 0);
        RI->State->SetMaterial(RI, Material, 0);
        RI->EnableLighting(0, 0);
        RI->SetCullMode(2);
        RI->DrawPrimitive(PrimitiveType, FirstVertex, NumPrimitives, 0, Vertices.ArrayNum - 1);
        RI->PopState();
        Vertices.ArrayNum = 0;
        NumPrimitives = 0;
    }
}

__declspec(noinline) FCanvasUtil::~FCanvasUtil()
{
    Flush();
}

void FCanvasUtil::DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1, FLOAT U2, FLOAT V2,
                           FLOAT Z, UMaterial *InMaterial, FColor Color)
{
    if (PrimitiveType != 0 || Material != InMaterial || Vertices.ArrayNum + 6 > 1362) {
        Flush();
        PrimitiveType = 0;
        Material = InMaterial;
    }
    INT USize, VSize;
    if (InMaterial) {
        USize = InMaterial->MaterialUSize();
        VSize = InMaterial->MaterialVSize();
    } else {
        USize = 1;
        VSize = 1;
    }
    FLOAT UScale = GOne / USize;
    FLOAT VScale = GOne / VSize;
    DWORD C = *(DWORD *)&Color;
    FCanvasVertex *V;
    V = &Vertices((Vertices.Add(1, sizeof(FCanvasVertex))));
    if (V) { V->X = X1; V->Y = Y1; V->Z = Z; V->Color = C; V->U = U1 * UScale; V->V = V1 * VScale; }
    V = &Vertices((Vertices.Add(1, sizeof(FCanvasVertex))));
    if (V) { V->X = X2; V->Y = Y1; V->Z = Z; V->Color = C; V->U = U2 * UScale; V->V = V1 * VScale; }
    V = &Vertices((Vertices.Add(1, sizeof(FCanvasVertex))));
    if (V) { V->X = X2; V->Y = Y2; V->Z = Z; V->Color = C; V->U = U2 * UScale; V->V = V2 * VScale; }
    V = &Vertices((Vertices.Add(1, sizeof(FCanvasVertex))));
    if (V) { V->X = X1; V->Y = Y1; V->Z = Z; V->Color = C; V->U = U1 * UScale; V->V = V1 * VScale; }
    V = &Vertices((Vertices.Add(1, sizeof(FCanvasVertex))));
    if (V) { V->X = X2; V->Y = Y2; V->Z = Z; V->Color = C; V->U = U2 * UScale; V->V = V2 * VScale; }
    V = &Vertices((Vertices.Add(1, sizeof(FCanvasVertex))));
    if (V) { V->X = X1; V->Y = Y2; V->Z = Z; V->Color = C; V->U = U1 * UScale; V->V = V2 * VScale; }
    NumPrimitives += 2;
}

class FRenderBase
{
public:
    virtual ~FRenderBase() {}
};

class ULevel;
class UModel
{
public:
    BYTE Pad00[0xd8];
    INT NumNodes;                                                  // +0xd8
};
class ULevel
{
public:
    BYTE Pad00[0x13c];
    UModel *Model;                                                 // +0x13c
    BYTE Pad140[0x4ae0 - 0x140];
    INT Initialised;                                               // +0x4ae0
};
void SceneNode_NoModel();                                          // 0x1090c0
void __stdcall Level_Initialise(ULevel *Level);                    // 0xf5830

class FSceneNode : public FRenderBase
{
public:
    UViewport *Viewport;                                           // +0x04
    FRenderTarget *RenderTarget;                                   // +0x08
    FSceneNode *Parent;                                            // +0x0c
    INT Recursion;                                                 // +0x10
    BYTE Pad14[0x194 - 0x14];
    FVector ViewOrigin;                                            // +0x194
    BYTE Pad1a0[0x1bc - 0x1a0];
    ULevel *Level;                                                 // +0x1bc
    UModel *Model;                                                 // +0x1c0
    AActor *ViewActor;                                             // +0x1c4
    INT ViewZone;                                                  // +0x1c8
    INT InvisibleZone;                                             // +0x1cc
    INT Flags;                                                     // +0x1d0
    BYTE Pad1d4[0x1d8 - 0x1d4];
    FRotator ViewRotation;                                         // +0x1d8
    FLOAT FovAngle;                                                // +0x1e4

    FSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget); // 0x115450
    virtual ~FSceneNode() {}
    void Render(FRenderInterface *RI, UBOOL Clear);                // 0x115da0
};

FSceneNode::FSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget)
{
    Parent = NULL;
    Viewport = InViewport;
    RenderTarget = InRenderTarget;
    Recursion = 0;
    Level = *(ULevel **)((BYTE *)Viewport->Actor + 0x1a4);
    Model = Level->Model;
    ViewZone = -1;
    InvisibleZone = -1;
    ViewActor = NULL;
    Flags = 0;
    if (Model->NumNodes == 0)
        SceneNode_NoModel();
    if (Level->Initialised == 0)
        Level_Initialise(Level);
}

struct FPointRegion { void *Zone; INT iLeaf; BYTE ZoneNumber; };
FPointRegion *PointRegion(const FVector *Location, void *Model, FPointRegion *Result, void *Hint); // 0x143370
void SceneNode_Setup(FSceneNode *Node);                            // 0x116670

class FActorSceneNode : public FSceneNode
{
public:
    FActorSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget, AActor *InViewActor,
                    AActor *InCameraActor, FLOAT InFOV);
};

FActorSceneNode::FActorSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget, AActor *InViewActor,
                                 AActor *InCameraActor, FLOAT InFOV)
    : FSceneNode(InViewport, InRenderTarget)
{
    FPointRegion Temp;
    InCameraActor->GetViewpoint(&ViewOrigin, &ViewRotation);
    PointRegion(&ViewOrigin, Model, &Temp, InViewActor->Region);
    ViewActor = InViewActor;
    ViewZone = Viewport->Precaching ? 0 : PointRegion(&ViewOrigin, Model, &Temp, InViewActor->Region)->ZoneNumber;
    FovAngle = InFOV;
    SceneNode_Setup(this);
}

void __stdcall Viewport_Precache(UViewport *Viewport);             // 0x10b050

struct FPendingFlush
{
    virtual QWORD GetCacheId();
    BYTE Pad04[0x18 - 0x04];
    INT Flushed;                                                   // +0x18
    FPendingFlush *Next;                                           // +0x1c
    INT FramesLeft;                                                // +0x20
};
extern FPendingFlush *GPendingFlushes;

void FlushPendingResources(UViewport *Viewport)                    // 0x146800
{
    FPendingFlush *Prev = NULL;
    FPendingFlush *E = GPendingFlushes;
    while (E) {
        E->Flushed = 0;
        if (--E->FramesLeft <= 0) {
            if (Prev) Prev->Next = E->Next; else GPendingFlushes = E->Next;
            E->Next = NULL;
            Viewport->RenDev->Flush(E->GetCacheId());
            GMalloc->Free(E);
            E = Prev;
        }
        Prev = E;
        E = E ? E->Next : GPendingFlushes;
    }
}

#define P_GET_INT(var) INT var = 0; Stack.Step(Stack.Object, &var);
#define P_GET_INT_OPTX(var, def) INT var = def; Stack.Step(Stack.Object, &var);
#define P_GET_UBOOL_OPTX(var, def) UBOOL var = def; Stack.Step(Stack.Object, &var);
#define P_GET_OBJECT(cls, var) cls *var = NULL; Stack.Step(Stack.Object, &var);
#define P_GET_VECTOR(var) FVector var; Stack.Step(Stack.Object, &var);
#define P_GET_ROTATOR(var) FRotator var; Stack.Step(Stack.Object, &var);
#define P_FINISH Stack.Code++;

void UCanvas::execDrawPortal(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(X);
    P_GET_INT(Y);
    P_GET_INT(Width);
    P_GET_INT(Height);
    P_GET_OBJECT(AActor, CamActor);
    P_GET_VECTOR(CamLocation);
    P_GET_ROTATOR(CamRotation);
    P_GET_INT_OPTX(FOV, 90);
    P_GET_UBOOL_OPTX(ClearZ, 1);
    P_FINISH;

    Viewport->RI->PushState();
    FLOAT SavedFOV = Viewport->Actor->FovAngle;
    // Clear the portal area with a temporary canvas utility.
    FCanvasUtil(&Viewport->RenderTarget, Viewport->RI)
        .DrawTile(X, Y, X + Width, Y + Height, 0, 0, 0, 0, 1.0f, NULL, FColor(0, 0, 0));
    Viewport->RI->SetViewport(X, Y, Width, Height);

    FActorSceneNode SceneNode(Viewport, &Viewport->RenderTarget, CamActor, CamActor, FOV);
    Viewport->Actor->FovAngle = FOV;

    FRenderInterface *RI = Viewport->RI;
    RI->PushState();
    SceneNode.Render(RI, 1);
    Viewport_Precache(SceneNode.Viewport);
    FlushPendingResources(SceneNode.Viewport);
    SceneNode.Viewport->Canvas->pCanvasUtil->Flush();
    RI->PopState();

    Viewport->Actor->FovAngle = SavedFOV;
    Viewport->RI->PopState();
}

// Scaffolding for the link, not part of the unit: the native table takes the
// function's address.
typedef void (UCanvas::*CanvasNative)(FFrame &Stack, RESULT_DECL);
extern CanvasNative KeepDrawPortal;
void Driver_101a00() { KeepDrawPortal = &UCanvas::execDrawPortal; }
