// Work item 0321: Versus RVA 0x10af70 and 0x10b050 (LTCG unit, Engine viewport
// code). Both functions are UViewport members (Actor at +0x30, RenderTarget at
// +0xe4, RI at +0x140, Precaching at +0x14c, as recovered in item 0293). The
// render interface here carries Versus-specific screen-effect state and
// virtuals, so those keep neutral names.
//
// 0x10b050 constructs a camera scene node whose base constructor (0x1164b0)
// takes the render target in ECX, the camera actor in EBX and the location in
// EDI, and empties a TArray at +0x80 with a helper (0x68dc0) taking the array
// in ESI. Those callees are defined below, following their retail bodies, so
// the link gives them the same conventions; only the two viewport functions
// are the units being matched.
typedef unsigned char BYTE;
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
#define NULL 0

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

struct FVector
{
    FLOAT X, Y, Z;
    FVector() {}
    FVector(FLOAT InX, FLOAT InY, FLOAT InZ) : X(InX), Y(InY), Z(InZ) {}
    FVector(const FVector &V) : X(V.X), Y(V.Y), Z(V.Z) {}
};
struct FRotator { INT Pitch, Yaw, Roll; };
struct FColor
{
    BYTE R, G, B, A;
    FColor() {}
    FColor(BYTE InR, BYTE InG, BYTE InB, BYTE InA = 255) : R(InR), G(InG), B(InB), A(InA) {}
};

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

// A TArray of 16-byte elements; Empty4 (0x68dc0) empties it to a slack of four.
template <class T> class TArray : public FArray
{
public:
    void Empty4();
};
struct FViewportEntry { DWORD A, B, C, D; };   // 16-byte element, unidentified

// Viewport render interface with Versus screen-effect state (neutral names).
// noinline: retail calls this helper (0x68dc0) rather than inlining it.
template <class T> __declspec(noinline) void TArray<T>::Empty4()
{
    ArrayNum = 0;
    if (ArrayMax != 4) {
        ArrayMax = 4;
        if (Data == NULL)
            Data = GMalloc->Malloc(4 * sizeof(T), L"FArray::Empty");
        else
            Data = GMalloc->Realloc(Data, 4 * sizeof(T), L"FArray");
    }
}

class FRenderInterface
{
public:
    virtual void PushState();                                      // +0x00
    virtual void PopState();                                       // +0x04
    virtual void Slot08();
    virtual void SetViewport(INT X, INT Y, INT Width, INT Height); // +0x0c
    virtual void Clear(UBOOL UseColor, FColor Color, UBOOL UseDepth, FLOAT Depth,
                       UBOOL UseStencil, DWORD Stencil);           // +0x10
    virtual void Slot14(); virtual void Slot18(); virtual void Slot1c();
    virtual void Slot20(); virtual void Slot24(); virtual void Slot28(); virtual void Slot2c();
    virtual void Slot30(); virtual void Slot34(); virtual void Slot38(); virtual void Slot3c();
    virtual void Slot40(); virtual void Slot44(); virtual void Slot48(); virtual void Slot4c();
    virtual void Slot50(); virtual void Slot54(); virtual void Slot58(); virtual void Slot5c();
    virtual void Slot60(); virtual void Slot64(); virtual void Slot68(); virtual void Slot6c();
    virtual void Slot70(); virtual void Slot74();
    virtual void UpdateEffects();                                  // +0x78
    virtual void Slot7c();
    virtual void Effect80(INT SizeX, INT SizeY);                   // +0x80
    virtual void Effect84(INT SizeX, INT SizeY, FLOAT Amount);     // +0x84
    virtual void BeginFade(INT SizeX, INT SizeY);                  // +0x88
    virtual void BeginFlash(INT SizeX, INT SizeY);                 // +0x8c
    virtual void Effect90(INT SizeX, INT SizeY, FLOAT Amount);     // +0x90
    virtual void Effect94(INT SizeX, INT SizeY, FLOAT Amount);     // +0x94
    virtual void Effect98();                                       // +0x98
    INT  Fading;                                                   // +0x04
    INT  Flashing;                                                 // +0x08
    BYTE EffectAlpha;                                              // +0x0c
};

class FRenderTarget { public: virtual void Slot00(); };

class AActor
{
public:
    virtual void Slot00();
    BYTE Pad04[0x1a0 - 0x04];
    void *Region;                                                  // +0x1a0
};

class ALevelInfo
{
public:
    BYTE Pad[0x344];
    FLOAT Effect344;                                               // +0x344
};

class ULevel
{
public:
    BYTE Pad00[0x2c];
    ALevelInfo **Actors;                                           // +0x2c (Actors.Data)
    BYTE Pad30[0x13c - 0x30];
    void *Model;                                                   // +0x13c
};

class APlayerController
{
public:
    virtual void V000();     virtual void V004();     virtual void V008();     virtual void V00c();     virtual void V010();     virtual void V014();
    virtual void V018();     virtual void V01c();     virtual void V020();     virtual void V024();     virtual void V028();     virtual void V02c();
    virtual void V030();     virtual void V034();     virtual void V038();     virtual void V03c();     virtual void V040();     virtual void V044();
    virtual void V048();     virtual void V04c();     virtual void V050();     virtual void V054();     virtual void V058();     virtual void V05c();
    virtual void V060();     virtual void V064();     virtual void V068();     virtual void V06c();     virtual void V070();     virtual void V074();
    virtual void V078();     virtual void V07c();     virtual void V080();     virtual void V084();     virtual void V088();     virtual void V08c();
    virtual void V090();     virtual void V094();     virtual void V098();     virtual void V09c();     virtual void V0a0();     virtual void V0a4();
    virtual void V0a8();     virtual void V0ac();     virtual void V0b0();     virtual void V0b4();     virtual void V0b8();     virtual void V0bc();
    virtual void V0c0();     virtual void V0c4();     virtual void V0c8();     virtual void V0cc();     virtual void V0d0();     virtual void V0d4();
    virtual void V0d8();     virtual void V0dc();     virtual void V0e0();     virtual void V0e4();     virtual void V0e8();     virtual void V0ec();
    virtual void V0f0();     virtual void V0f4();     virtual void V0f8();     virtual void V0fc();     virtual void V100();     virtual void V104();
    virtual void V108();     virtual void V10c();     virtual void V110();     virtual void V114();     virtual void V118();     virtual void V11c();
    virtual void V120();     virtual void V124();     virtual void V128();     virtual void V12c();     virtual void V130();     virtual void V134();
    virtual void V138();     virtual void V13c();     virtual void V140();     virtual void V144();     virtual void V148();
    virtual void PlayerCalcView(AActor *&ViewActor, FVector &CameraLocation, FRotator &CameraRotation, UBOOL Flag); // +0x14c
    BYTE Pad04[0x80 - 0x04];
    FVector Location;                                              // +0x80
    BYTE Pad8c[0xe0 - 0x8c];
    FRotator Rotation;                                             // +0xe0
    BYTE Padec[0x1a4 - 0xec];
    ULevel *XLevel;                                                // +0x1a4
    BYTE Pad1a8[0x308 - 0x1a8];
    FLOAT FovAngle;                                                // +0x308
    BYTE Pad30c[0x4fc - 0x30c];
    INT ViewState;                                                 // +0x4fc
    BYTE Pad500[0x518 - 0x500];
    FLOAT EffectFade;                                              // +0x518
    BYTE Pad51c[0x524 - 0x51c];
    FLOAT EffectAmount;                                            // +0x524
    BYTE Pad528[0x5f0 - 0x528];
    DWORD ViewFlags;                                               // +0x5f0
};

class UViewport
{
public:
    BYTE Pad00[0x30];
    APlayerController *Actor;                                      // +0x30
    BYTE Pad34[0x80 - 0x34];
    TArray<FViewportEntry> Entries;                                // +0x80
    BYTE Pad8c[0xa0 - 0x8c];
    INT SizeX;                                                     // +0xa0
    INT SizeY;                                                     // +0xa4
    BYTE Pada8[0xe4 - 0xa8];
    FRenderTarget RenderTarget;                                    // +0xe4
    BYTE Pade8[0x140 - 0xe8];
    FRenderInterface *RI;                                          // +0x140
    BYTE Pad144[0x14c - 0x144];
    INT Precaching;                                                // +0x14c
    BYTE Pad150[0x154 - 0x150];
    INT Suspended;                                                 // +0x154
    BYTE Pad158[0x18c - 0x158];
    void *PendingView;                                             // +0x18c

    void UpdateScreenEffects();                                    // 0x10af70
    void __stdcall DrawPendingView();                                      // 0x10b050
};

// --- 0x10af70 ---------------------------------------------------------------
void UViewport::UpdateScreenEffects()
{
    if (Suspended || Precaching)
        return;
    APlayerController *A = Actor;
    INT S = A->ViewState;
    if (S == 0x22) {
        A->ViewState = 5;
        RI->Fading = 1;
        RI->EffectAlpha = 30;
        RI->UpdateEffects();
    } else if (S == 0x25) {
        A->ViewState = 5;
        RI->Flashing = 1;
        RI->UpdateEffects();
    } else if (S == 5) {
        if (A->EffectFade != 0.0f)
            RI->EffectAlpha = (BYTE)(INT)(A->EffectFade * 28.0f);
        RI->UpdateEffects();
    } else if (S == 0x24) {
        RI->UpdateEffects();
    } else if (S == 0x26) {
        RI->UpdateEffects();
    }
}

// --- scene nodes (callees of 0x10b050, defined for their link conventions) --
class FRenderBase
{
public:
    virtual ~FRenderBase() {}
};

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
    void *Model;                                                   // +0x1c0
    AActor *ViewActor;                                             // +0x1c4
    INT ViewZone;                                                  // +0x1c8
    INT InvisibleZone;                                             // +0x1cc
    INT Flags;                                                     // +0x1d0
    BYTE Pad1d4[0x1d8 - 0x1d4];
    FRotator ViewRotation;                                         // +0x1d8
    FLOAT FovAngle;                                                // +0x1e4

    FSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget); // 0x115450
    virtual ~FSceneNode() {}
    virtual void Slot04();
    virtual void Render(FRenderInterface *RI, UBOOL Clear);
};

void SceneNode_NoModel();                                          // 0x1090c0
void __stdcall Level_Initialise(ULevel *Level);                    // 0xf5830

FSceneNode::FSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget)
{
    Parent = NULL;
    Viewport = InViewport;
    RenderTarget = InRenderTarget;
    Recursion = 0;
    Level = InViewport->Actor->XLevel;
    Model = Level->Model;
    ViewZone = -1;
    InvisibleZone = -1;
    ViewActor = NULL;
    Flags = 0;
    if (*(INT *)((BYTE *)Model + 0xd8) == 0)
        SceneNode_NoModel();
    if (*(INT *)((BYTE *)Level + 0x4ae0) == 0)
        Level_Initialise(Level);
}

struct FPointRegion { void *Zone; INT iLeaf; BYTE ZoneNumber; };
FPointRegion *PointRegion(const FVector *Location, void *Model, FPointRegion *Result, void *Hint); // 0x143370
void SceneNode_Setup(FSceneNode *Node);                            // 0x116670

class FCameraSceneNode : public FSceneNode
{
public:
    FCameraSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget, AActor *CameraActor,
                     const FVector &CameraLocation, const FRotator &CameraRotation, FLOAT CameraFOV); // 0x1164b0
    virtual void Render(FRenderInterface *RI, UBOOL Clear);
};

FCameraSceneNode::FCameraSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget, AActor *CameraActor,
                                   const FVector &CameraLocation, const FRotator &CameraRotation, FLOAT CameraFOV)
    : FSceneNode(InViewport, InRenderTarget)
{
    FPointRegion Temp;
    PointRegion(&CameraLocation, Model, &Temp, CameraActor->Region);
    ViewOrigin = CameraLocation;
    ViewActor = CameraActor;
    ViewZone = Viewport->Precaching ? 0 : PointRegion(&ViewOrigin, Model, &Temp, CameraActor->Region)->ZoneNumber;
    ViewRotation = CameraRotation;
    FovAngle = CameraFOV;
    SceneNode_Setup(this);
}

// Versus scene node rendering the viewport's pending view (vtable 0x10c036bc).
class FPendingViewSceneNode : public FCameraSceneNode
{
public:
    void *PendingView;                                             // +0x1e8
    FPendingViewSceneNode(UViewport *InViewport, FRenderTarget *InRenderTarget, AActor *CameraActor,
                          const FVector &CameraLocation, const FRotator &CameraRotation, FLOAT CameraFOV,
                          void *InPendingView)
        : FCameraSceneNode(InViewport, InRenderTarget, CameraActor, CameraLocation, CameraRotation, CameraFOV),
          PendingView(InPendingView) {}
    virtual void Render(FRenderInterface *RI, UBOOL Clear);
};

// --- 0x10b050 ---------------------------------------------------------------
void __stdcall UViewport::DrawPendingView()
{
    if (Suspended || Precaching)
        return;

    if (PendingView) {
        APlayerController *A = Actor;
        AActor *ViewActor = (AActor *)A;
        FVector CameraLocation = A->Location;
        FRotator CameraRotation = A->Rotation;
        RI->Clear(0, FColor(0, 0, 0), 1, 1.0f, 0, 0);
        Actor->PlayerCalcView(ViewActor, CameraLocation, CameraRotation, 1);
        {
            FPendingViewSceneNode Node(this, &RenderTarget, ViewActor, CameraLocation, CameraRotation,
                                       Actor->FovAngle, PendingView);
            FSceneNode *N = &Node;
            N->Render(RI, 1);
        }
        PendingView = NULL;
    }

    if (Actor->ViewFlags & 0x800) {
        RI->Effect80(SizeX, SizeY);
        Actor->ViewFlags &= ~0x800;
    }
    INT S = Actor->ViewState;
    if (S != 0x24 && S != 0x26 && !RI->Flashing && Actor->EffectAmount > 0.0039f)
        RI->Effect84(SizeX, SizeY, Actor->EffectAmount);

    if (RI->Fading) {
        RI->BeginFade(SizeX, SizeY);
        RI->EffectAlpha = 0;
        RI->Fading = 0;
        Actor->ViewState = 0x22;
    } else if (RI->Flashing) {
        RI->BeginFlash(SizeX, SizeY);
        RI->Flashing = 0;
        Actor->ViewState = 0x25;
    } else {
        S = Actor->ViewState;
        if (S == 5) {
            RI->EffectAlpha = 0;
            RI->Effect98();
        } else if (S == 0x24) {
            RI->Effect90(SizeX, SizeY, Actor->XLevel->Actors[0]->Effect344);
        } else if (S == 0x26) {
            RI->Effect94(SizeX, SizeY, Actor->XLevel->Actors[0]->Effect344);
        }
    }
    RI->SetViewport(0, 0, SizeX, SizeY);
    Entries.Empty4();

    S = Actor->ViewState;
    if ((S == 0x24 || S == 0x26 || S == 0x25) && Actor->EffectAmount > 0.0039f)
        RI->Effect84(SizeX, SizeY, Actor->EffectAmount);
}

// Scaffolding for the link, not part of the unit. Taking DrawPendingView's
// address keeps its standard __stdcall convention (this on the stack, ret 4),
// as retail has it; with only in-file callers the link moves `this` into ESI.
void Escape(void *);
void Driver_10af70(UViewport *P) { P->UpdateScreenEffects(); }
typedef void (__stdcall UViewport::*ViewportFn)();
extern ViewportFn KeepDrawPendingView;
void Driver_10b050() { KeepDrawPendingView = &UViewport::DrawPendingView; }
