// Work item w3 0032: Versus RVA 0x67e30 (1716 bytes), link-time-optimised (VC7.0 /GL).
// Blends two textures into a third render-target texture with one screen-aligned
// quad: stage 0 selects texture 1, stage 1 blends texture 2 by the texture factor
// (D3DTOP_BLENDFACTORALPHA); vertex alpha comes from Alpha. The owning class
// (render device pointer at +0x108) and the rectangle type are not identified, so
// they keep neutral names. D3D8 declarations copied from item_0265.

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
    char Pad104[0x40cc - 0x104];
    DWORD UseTrilinear;                  // +0x40cc
    DWORD UseMipmapping;                 // +0x40d0
    char Pad40D4[0x46a4 - 0x40d4];
    IDirect3DDevice8 *Direct3DDevice8;   // +0x46a4
    char Pad46A8[0x2fb58 - 0x46a8];
    FD3DDeferredState DeferredState;     // +0x2fb58
};

struct FPlane {
    FLOAT X, Y, Z, W;
    FPlane() {}
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : X(InX), Y(InY), Z(InZ), W(InW) {}
};

struct FBlendVertex {
    FPlane Position;                     // X, Y, Z, RHW
    DWORD Color;
    FLOAT U0, V0;
    FLOAT U1, V1;
};

// Neutral name: integer rectangle (left, top, right, bottom).
struct FRect_67e30 {
    INT X1, Y1, X2, Y2;
    FRect_67e30(INT InX1, INT InY1, INT InX2, INT InY2) : X1(InX1), Y1(InY1), X2(InX2), Y2(InY2) {}
};

class FUnnamedRenderTarget_67e30 {
public:
    virtual void Slot0();
    char Pad04[0x108 - 0x04];
    UD3DRenderDevice *RenDev;            // +0x108

    void BlendTextures(FRect_67e30 *Src1, FRect_67e30 *Src2, IDirect3DTexture8 *Target,
                       IDirect3DTexture8 *Tex1, IDirect3DTexture8 *Tex2,
                       unsigned char Alpha, unsigned char Factor, FRect_67e30 *Dest);
};

#define DEVFIELD(Offset) (*(DWORD *)((char *)RenDev + (Offset)))

void FUnnamedRenderTarget_67e30::BlendTextures(FRect_67e30 *Src1, FRect_67e30 *Src2, IDirect3DTexture8 *Target,
                                               IDirect3DTexture8 *Tex1, IDirect3DTexture8 *Tex2,
                                               unsigned char Alpha, unsigned char Factor, FRect_67e30 *Dest)
{
    IDirect3DSurface8 *Surface = 0;
    Target->GetSurfaceLevel(0, &Surface);
    RenDev->Direct3DDevice8->SetRenderTarget(Surface, 0);
    Surface->Release();

    D3DSURFACE_DESC Desc1, Desc2, TargetDesc;
    Tex1->GetLevelDesc(0, &Desc1);
    Tex2->GetLevelDesc(0, &Desc2);
    Target->GetLevelDesc(0, &TargetDesc);

    FRect_67e30 Full1(0, 0, Desc1.Width, Desc1.Height);
    if (!Src1)
        Src1 = &Full1;
    FRect_67e30 Full2(0, 0, Desc2.Width, Desc2.Height);
    if (!Src2)
        Src2 = &Full2;
    FRect_67e30 FullTarget(0, 0, TargetDesc.Width, TargetDesc.Height);
    if (!Dest)
        Dest = &FullTarget;

    FBlendVertex Verts[4];
    Verts[0].Position = FPlane(Dest->X1 - 0.5f, Dest->Y1 - 0.5f, 0.0f, 0.9f);
    Verts[1].Position = FPlane(Dest->X2 - 0.5f, Dest->Y1 - 0.5f, 0.0f, 0.9f);
    Verts[2].Position = FPlane(Dest->X1 - 0.5f, Dest->Y2 - 0.5f, 0.0f, 0.9f);
    Verts[3].Position = FPlane(Dest->X2 - 0.5f, Dest->Y2 - 0.5f, 0.0f, 0.9f);
    Verts[0].Color = Verts[1].Color = Verts[2].Color = Verts[3].Color = (Alpha << 24) | 0xffffff;

    FLOAT SU = 1.0f / Desc1.Width, SV = 1.0f / Desc1.Height;
    FLOAT U1 = Src1->X1 * SU, V1 = Src1->Y1 * SV, U2 = Src1->X2 * SU, V2 = Src1->Y2 * SV;
    Verts[0].U0 = U1; Verts[0].V0 = V1;
    Verts[1].U0 = U2; Verts[1].V0 = V1;
    Verts[2].U0 = U1; Verts[2].V0 = V2;
    Verts[3].U0 = U2; Verts[3].V0 = V2;

    SU = 1.0f / Desc2.Width;
    SV = 1.0f / Desc2.Height;
    U1 = Src2->X1 * SU; V1 = Src2->Y1 * SV; U2 = Src2->X2 * SU; V2 = Src2->Y2 * SV;
    Verts[0].U1 = U1; Verts[0].V1 = V1;
    Verts[1].U1 = U2; Verts[1].V1 = V1;
    Verts[2].U1 = U1; Verts[2].V1 = V2;
    Verts[3].U1 = U2; Verts[3].V1 = V2;

    // Stage 0: select texture 1.
    DEVFIELD(0x30028) = 0;
    DEVFIELD(0x300b4) = (DWORD)Tex1;
    DEVFIELD(0x2fbc0) = 2;
    DEVFIELD(0x2fbc4) = 2;
    DEVFIELD(0x2fbc8) = 0;
    DEVFIELD(0x2fbcc) = 2;
    DEVFIELD(0x2fbd0) = 2;
    DEVFIELD(0x2fbd4) = 0;
    DEVFIELD(0x2fbdc) = 3;
    DEVFIELD(0x2fbe0) = 3;
    RenDev->Direct3DDevice8->SetTextureStageState(0, 17, 2);
    RenDev->Direct3DDevice8->SetTextureStageState(0, 16, 2);
    RenDev->Direct3DDevice8->SetTextureStageState(0, 18, 0);

    // Stage 1: blend texture 2 by the texture factor.
    DEVFIELD(0x300b8) = (DWORD)Tex2;
    DEVFIELD(0x2fbf4) = 14;
    DEVFIELD(0x2fbf8) = 1;
    DEVFIELD(0x2fbfc) = 2;
    DEVFIELD(0x2fc00) = 3;
    DEVFIELD(0x2fc04) = 2;
    DEVFIELD(0x2fc08) = 0;
    DEVFIELD(0x2fc10) = 3;
    DEVFIELD(0x2fc14) = 3;
    RenDev->Direct3DDevice8->SetTextureStageState(1, 17, 2);
    RenDev->Direct3DDevice8->SetTextureStageState(1, 16, 2);
    RenDev->Direct3DDevice8->SetTextureStageState(1, 18, 0);

    DEVFIELD(0x2fc28) = 1;
    DEVFIELD(0x2fbb0) = (Factor << 24) | (Factor << 16) | (Factor << 8) | Factor;
    RenDev->Direct3DDevice8->SetRenderState(7, 0);

    DEVFIELD(0x2fb64) = 0;
    DEVFIELD(0x2fb7c) = 1;
    DEVFIELD(0x2fb68) = 5;
    DEVFIELD(0x2fb6c) = 6;
    DEVFIELD(0x30024) = 0x244;
    FD3DDeferredState *State = &RenDev->DeferredState;
    State->Field4D4 = 0;
    State->Field4D8 = 0;
    RenDev->DeferredState.Commit();

    RenDev->Direct3DDevice8->DrawPrimitiveUP(5, 2, Verts, sizeof(FBlendVertex));
    RenDev->Direct3DDevice8->SetRenderState(7, 1);

    RenDev->Direct3DDevice8->SetTextureStageState(0, 18, RenDev->UseMipmapping ? (RenDev->UseTrilinear ? 2 : 1) : 0);
    RenDev->Direct3DDevice8->SetTextureStageState(1, 18, RenDev->UseMipmapping ? (RenDev->UseTrilinear ? 2 : 1) : 0);
}

// Scaffolding for the link, not part of the unit. Commit (RVA 0x6c1d0) is a long
// run of compare-and-set render states; the first few are reproduced here only so
// link-time code generation gives it the register convention retail uses (this
// in EBX). Copied from item_0265.
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
void Driver_67e30(FUnnamedRenderTarget_67e30 *Owner, FRect_67e30 *Src1, FRect_67e30 *Src2, IDirect3DTexture8 *Target,
                  IDirect3DTexture8 *Tex1, IDirect3DTexture8 *Tex2, unsigned char Alpha, unsigned char Factor,
                  FRect_67e30 *Dest)
{
    Owner->BlendTextures(Src1, Src2, Target, Tex1, Tex2, Alpha, Factor, Dest);
}
