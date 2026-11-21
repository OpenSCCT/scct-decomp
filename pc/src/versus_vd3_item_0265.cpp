// Work item 0265: Versus RVA 0x62e50 (566 bytes), link-time-optimised (VC7.0 /GL).
// Draws a texture onto its own surface-level-0 render target with a screen-aligned
// quad (D3D8: GetSurfaceLevel, GetLevelDesc, SetRenderTarget, DrawPrimitiveUP).
// The owning class (render device pointer at +0x108) is not yet identified, so it
// keeps a neutral name. Device field offsets come from the retail code.

typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef int INT;
typedef float FLOAT;

extern "C" int memcmp(const void *, const void *, unsigned int);
extern "C" void *memcpy(void *, const void *, unsigned int);
#pragma intrinsic(memcmp, memcpy)

struct IDirect3DSurface8 {
    virtual void __stdcall QueryInterface();
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
};

struct D3DSURFACE_DESC {
    DWORD Format;
    DWORD Type;
    DWORD Usage;
    DWORD Pool;
    UINT Size;
    DWORD MultiSampleType;
    UINT Width;
    UINT Height;
};

struct IDirect3DTexture8 {
    virtual void __stdcall Slot00();
    virtual void __stdcall Slot01();
    virtual void __stdcall Slot02();
    virtual void __stdcall Slot03();
    virtual void __stdcall Slot04();
    virtual void __stdcall Slot05();
    virtual void __stdcall Slot06();
    virtual void __stdcall Slot07();
    virtual void __stdcall Slot08();
    virtual void __stdcall Slot09();
    virtual void __stdcall Slot10();
    virtual void __stdcall Slot11();
    virtual void __stdcall Slot12();
    virtual void __stdcall Slot13();
    virtual INT __stdcall GetLevelDesc(UINT Level, D3DSURFACE_DESC *Desc);
    virtual INT __stdcall GetSurfaceLevel(UINT Level, IDirect3DSurface8 **Surface);
};

struct IDirect3DDevice8 {
    virtual void __stdcall Slot00();
    virtual void __stdcall Slot01();
    virtual void __stdcall Slot02();
    virtual void __stdcall Slot03();
    virtual void __stdcall Slot04();
    virtual void __stdcall Slot05();
    virtual void __stdcall Slot06();
    virtual void __stdcall Slot07();
    virtual void __stdcall Slot08();
    virtual void __stdcall Slot09();
    virtual void __stdcall Slot10();
    virtual void __stdcall Slot11();
    virtual void __stdcall Slot12();
    virtual void __stdcall Slot13();
    virtual void __stdcall Slot14();
    virtual void __stdcall Slot15();
    virtual void __stdcall Slot16();
    virtual void __stdcall Slot17();
    virtual void __stdcall Slot18();
    virtual void __stdcall Slot19();
    virtual void __stdcall Slot20();
    virtual void __stdcall Slot21();
    virtual void __stdcall Slot22();
    virtual void __stdcall Slot23();
    virtual void __stdcall Slot24();
    virtual void __stdcall Slot25();
    virtual void __stdcall Slot26();
    virtual void __stdcall Slot27();
    virtual void __stdcall Slot28();
    virtual void __stdcall Slot29();
    virtual void __stdcall Slot30();
    virtual INT __stdcall SetRenderTarget(IDirect3DSurface8 *RenderTarget, IDirect3DSurface8 *ZStencil);
    virtual void __stdcall Slot32();
    virtual void __stdcall Slot33();
    virtual void __stdcall Slot34();
    virtual void __stdcall Slot35();
    virtual void __stdcall Slot36();
    virtual INT __stdcall SetTransform(DWORD State, const void *Matrix);
    virtual void __stdcall Slot38();
    virtual void __stdcall Slot39();
    virtual void __stdcall Slot40();
    virtual void __stdcall Slot41();
    virtual void __stdcall Slot42();
    virtual void __stdcall Slot43();
    virtual void __stdcall Slot44();
    virtual void __stdcall Slot45();
    virtual void __stdcall Slot46();
    virtual void __stdcall Slot47();
    virtual void __stdcall Slot48();
    virtual void __stdcall Slot49();
    virtual INT __stdcall SetRenderState(DWORD State, DWORD Value);
    virtual void __stdcall Slot51();
    virtual void __stdcall Slot52();
    virtual void __stdcall Slot53();
    virtual void __stdcall Slot54();
    virtual void __stdcall Slot55();
    virtual void __stdcall Slot56();
    virtual void __stdcall Slot57();
    virtual void __stdcall Slot58();
    virtual void __stdcall Slot59();
    virtual void __stdcall Slot60();
    virtual void __stdcall Slot61();
    virtual void __stdcall Slot62();
    virtual INT __stdcall SetTextureStageState(DWORD Stage, DWORD Type, DWORD Value);
    virtual void __stdcall Slot64();
    virtual void __stdcall Slot65();
    virtual void __stdcall Slot66();
    virtual void __stdcall Slot67();
    virtual void __stdcall Slot68();
    virtual void __stdcall Slot69();
    virtual void __stdcall Slot70();
    virtual void __stdcall Slot71();
    virtual INT __stdcall DrawPrimitiveUP(DWORD PrimitiveType, UINT PrimitiveCount, const void *Data, UINT Stride);
};

class UD3DRenderDevice;

// Deferred device state embedded in the render device at +0x2fb58; Commit (RVA
// 0x6c1d0) pushes changed render states to the device.
struct FD3DDeferredState {
    UD3DRenderDevice *RenDev;            // +0x000
    DWORD RenderState[0x4d4 / 4 - 1];    // +0x004
    DWORD Field4D4;                      // +0x4d4
    DWORD Field4D8;                      // +0x4d8
    char Pad4DC[0x8dc - 0x4dc];
    DWORD CachedState[8];                // +0x8dc
    void Commit();
};

class UD3DRenderDevice {
public:
    char Pad00[0x100];
    INT NumStages;                       // +0x100 (scaffolding only)
    char Pad104[0x46a4 - 0x104];
    IDirect3DDevice8 *Direct3DDevice8;   // +0x46a4
    char Pad46A8[0x2fb58 - 0x46a8];
    FD3DDeferredState DeferredState;     // +0x2fb58
};

struct FQuadVertex { FLOAT X, Y, Z, RHW, U, V; };

// Neutral name: owner of a render device pointer at +0x108; vtable slot 3 takes a
// rectangle (X, Y, Width, Height).
class FUnnamedRenderTarget_62e50 {
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void SetViewport(INT X, INT Y, INT Width, INT Height);
    char Pad04[0x108 - 0x04];
    UD3DRenderDevice *RenDev;            // +0x108

    void DrawToTexture(IDirect3DTexture8 *Texture, DWORD Value);
};

#define DEVFIELD(Offset) (*(DWORD *)((char *)RenDev + (Offset)))

void FUnnamedRenderTarget_62e50::DrawToTexture(IDirect3DTexture8 *Texture, DWORD Value)
{
    IDirect3DSurface8 *Surface;
    D3DSURFACE_DESC Desc;
    Texture->GetSurfaceLevel(0, &Surface);
    Texture->GetLevelDesc(0, &Desc);

    FQuadVertex Verts[4];
    Verts[0].Z   = Verts[1].Z   = Verts[2].Z   = Verts[3].Z   = 0.0f;
    Verts[0].RHW = Verts[1].RHW = Verts[2].RHW = Verts[3].RHW = 0.9f;
    Verts[0].X = Verts[2].X = -0.5f;
    Verts[1].X = Verts[3].X = (FLOAT)Desc.Width - 0.5f;
    Verts[0].Y = Verts[1].Y = -0.5f;
    Verts[2].Y = Verts[3].Y = (FLOAT)Desc.Height - 0.5f;
    Verts[0].U = Verts[2].U = 0.0f;
    Verts[1].U = Verts[3].U = 1.0f;
    Verts[0].V = Verts[1].V = 0.0f;
    Verts[2].V = Verts[3].V = 1.0f;

    DEVFIELD(0x30028) = 0;
    DEVFIELD(0x300b4) = Value;
    RenDev->Direct3DDevice8->SetRenderTarget(Surface, 0);
    SetViewport(0, 0, Desc.Width, Desc.Height);
    Surface->Release();

    DEVFIELD(0x2fbc0) = 2;
    DEVFIELD(0x2fbc4) = 2;
    DEVFIELD(0x2fbcc) = 1;
    DEVFIELD(0x2fbf4) = 1;
    DEVFIELD(0x2fc00) = 1;
    DEVFIELD(0x2fb64) = 0;
    DEVFIELD(0x2fb7c) = 0;
    DEVFIELD(0x30024) = 0x104;
    FD3DDeferredState *State = &RenDev->DeferredState;
    State->Field4D4 = 0;
    State->Field4D8 = 0;
    RenDev->DeferredState.Commit();

    RenDev->Direct3DDevice8->DrawPrimitiveUP(5, 2, Verts, sizeof(FQuadVertex));
    RenDev->Direct3DDevice8->SetRenderState(7, 1);
}

// Scaffolding for the link, not part of the unit. Commit (RVA 0x6c1d0) is a long
// run of compare-and-set render states; the first few are reproduced here only so
// link-time code generation gives it the register convention retail uses (this
// in EBX).
__declspec(noinline) void FD3DDeferredState::Commit()
{
    if (RenderState[0] != CachedState[0]) { RenDev->Direct3DDevice8->SetRenderState(8, RenderState[0]); CachedState[0] = RenderState[0]; }
    if (RenderState[1] != CachedState[1]) { RenDev->Direct3DDevice8->SetRenderState(14, RenderState[1]); CachedState[1] = RenderState[1]; }
    if (RenderState[2] != CachedState[2]) { RenDev->Direct3DDevice8->SetRenderState(15, RenderState[2]); CachedState[2] = RenderState[2]; }
    if (RenderState[3] != CachedState[3]) { RenDev->Direct3DDevice8->SetRenderState(19, RenderState[3]); CachedState[3] = RenderState[3]; }
    for (INT Stage = 0; Stage < RenDev->NumStages; Stage++) {
        DWORD *S = &RenderState[0x64 / 4 + Stage * 13];
        if (S[0] != S[0x8d8 / 4]) { RenDev->Direct3DDevice8->SetTextureStageState(Stage, 1, S[0]); S[0x8d8 / 4] = S[0]; }
        if (S[1] != S[0x8dc / 4]) { RenDev->Direct3DDevice8->SetTextureStageState(Stage, 2, S[1]); S[0x8dc / 4] = S[1]; }
    }
    DWORD *Matrix = &RenderState[0x208 / 4 - 1];
    DWORD *Cached = &RenderState[0xae0 / 4 - 1];
    if (memcmp(Matrix, Cached, 64)) {
        RenDev->Direct3DDevice8->SetTransform(0x10, Matrix);
        memcpy(Cached, Matrix, 64);
    }
}
void Driver_62e50(FUnnamedRenderTarget_62e50 *Owner, IDirect3DTexture8 *Texture, DWORD Value)
{
    Owner->DrawToTexture(Texture, Value);
}
