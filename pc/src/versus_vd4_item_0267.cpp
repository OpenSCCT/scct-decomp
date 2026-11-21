// Work item 0267: Versus RVA 0x67740, the glow post-process chain of the
// Direct3D render interface. Compiled with VC7.0 /GL and linked with /LTCG,
// so it and its callees use custom register conventions.
// Class names are neutral: the owner holds the render device at 0x108; the
// device keeps the Direct3D device at 0x46a4, a chain of render-target
// textures at 0x30e68 and three pixel shader handles at 0x30f6c.
typedef unsigned long DWORD;
typedef int INT;
typedef float FLOAT;
typedef unsigned char BYTE;

struct D3DSURFACE_DESC
{
    DWORD Format, Type, Usage, Pool, Size, MultiSampleType, Width, Height;
};

class IDirect3DSurface8
{
public:
    virtual void __stdcall QueryInterface(); virtual void __stdcall AddRef(); virtual void __stdcall Release();
};

class IDirect3DTexture8
{
public:
    virtual void __stdcall QueryInterface(); virtual void __stdcall AddRef(); virtual void __stdcall Release();
    virtual void __stdcall S03(); virtual void __stdcall S04(); virtual void __stdcall S05(); virtual void __stdcall S06(); virtual void __stdcall S07();
    virtual void __stdcall S08(); virtual void __stdcall S09(); virtual void __stdcall S10(); virtual void __stdcall S11(); virtual void __stdcall S12();
    virtual void __stdcall S13();
    virtual long __stdcall GetLevelDesc(DWORD Level, D3DSURFACE_DESC* Desc);              // 0x38
    virtual long __stdcall GetSurfaceLevel(DWORD Level, IDirect3DSurface8** Surface);     // 0x3c
};

class IDirect3DDevice8
{
public:
    virtual void __stdcall S00(); virtual void __stdcall S01(); virtual void __stdcall S02(); virtual void __stdcall S03(); virtual void __stdcall S04();
    virtual void __stdcall S05(); virtual void __stdcall S06(); virtual void __stdcall S07(); virtual void __stdcall S08(); virtual void __stdcall S09();
    virtual void __stdcall S10(); virtual void __stdcall S11(); virtual void __stdcall S12(); virtual void __stdcall S13(); virtual void __stdcall S14();
    virtual void __stdcall S15(); virtual void __stdcall S16(); virtual void __stdcall S17(); virtual void __stdcall S18(); virtual void __stdcall S19();
    virtual void __stdcall S20(); virtual void __stdcall S21(); virtual void __stdcall S22(); virtual void __stdcall S23(); virtual void __stdcall S24();
    virtual void __stdcall S25(); virtual void __stdcall S26(); virtual void __stdcall S27(); virtual void __stdcall S28(); virtual void __stdcall S29();
    virtual void __stdcall S30();
    virtual long __stdcall SetRenderTarget(IDirect3DSurface8* Target, IDirect3DSurface8* Depth);  // 0x7c
    virtual void __stdcall S32(); virtual void __stdcall S33(); virtual void __stdcall S34(); virtual void __stdcall S35(); virtual void __stdcall S36();
    virtual void __stdcall S37(); virtual void __stdcall S38(); virtual void __stdcall S39(); virtual void __stdcall S40(); virtual void __stdcall S41();
    virtual void __stdcall S42(); virtual void __stdcall S43(); virtual void __stdcall S44(); virtual void __stdcall S45(); virtual void __stdcall S46();
    virtual void __stdcall S47(); virtual void __stdcall S48(); virtual void __stdcall S49();
    virtual long __stdcall SetRenderState(DWORD State, DWORD Value);                     // 0xc8
    virtual void __stdcall S51(); virtual void __stdcall S52(); virtual void __stdcall S53(); virtual void __stdcall S54(); virtual void __stdcall S55();
    virtual void __stdcall S56(); virtual void __stdcall S57(); virtual void __stdcall S58(); virtual void __stdcall S59(); virtual void __stdcall S60();
    virtual void __stdcall S61(); virtual void __stdcall S62();
    virtual long __stdcall SetTextureStageState(DWORD Stage, DWORD Type, DWORD Value);   // 0xfc
    virtual void __stdcall S64(); virtual void __stdcall S65(); virtual void __stdcall S66(); virtual void __stdcall S67(); virtual void __stdcall S68();
    virtual void __stdcall S69(); virtual void __stdcall S70(); virtual void __stdcall S71();
    virtual long __stdcall DrawPrimitiveUP(DWORD Type, DWORD Count, const void* Data, DWORD Stride); // 0x120
    virtual void __stdcall S73(); virtual void __stdcall S74(); virtual void __stdcall S75(); virtual void __stdcall S76(); virtual void __stdcall S77();
    virtual void __stdcall S78(); virtual void __stdcall S79(); virtual void __stdcall S80(); virtual void __stdcall S81(); virtual void __stdcall S82();
    virtual void __stdcall S83(); virtual void __stdcall S84(); virtual void __stdcall S85(); virtual void __stdcall S86(); virtual void __stdcall S87();
    virtual void __stdcall S88(); virtual void __stdcall S89(); virtual void __stdcall S90();
    virtual long __stdcall SetPixelShaderConstant(DWORD Register, const void* Data, DWORD Count); // 0x16c
};

struct UnnamedDevice_67740
{
    BYTE Pad0[0x46a4];
    IDirect3DDevice8* Direct3DDevice;       // 0x46a4
    BYTE Pad1[0x30e68 - 0x46a8];
    IDirect3DTexture8* Targets[10];         // 0x30e68
    BYTE Pad2[0x30f6c - 0x30e90];
    DWORD GlowShader;                       // 0x30f6c
    DWORD BlendShader;                      // 0x30f70
    DWORD ScaledShader;                     // 0x30f74

    DWORD& State(INT Offset) { return *(DWORD*)((BYTE*)this + Offset); }
};

struct FUVRect { FLOAT U0, V0, U1, V1; };

void DrawQuads(UnnamedDevice_67740* Device, INT* DstRect, INT* SrcRect, INT NumTaps, FLOAT* Offsets);
void CommitState(void* RenderState);    // retail 0x1096c1d0
extern FLOAT GlowWeights[4];             // retail 0x10bff1b8

class UnnamedRender_67740
{
public:
    BYTE Pad0[0x108];
    UnnamedDevice_67740* Device;            // 0x108

    void Filter(IDirect3DTexture8* Dst, IDirect3DTexture8* Src, INT NumTaps, FLOAT* Offsets, INT DivX, INT DivY, INT* DstRect, INT* SrcRect);
    void Pass(DWORD Shader, IDirect3DTexture8* Dst, IDirect3DTexture8* Src, FLOAT Alpha, BYTE Bilinear, INT* DstRect, DWORD* Color, INT* SrcRect);
    void Blur(IDirect3DTexture8* Tmp, IDirect3DTexture8* Src, IDirect3DTexture8* Dst, INT* DstRect, INT* TmpRect, INT* SrcRect);
    void Combine(IDirect3DTexture8* A, IDirect3DTexture8* B, IDirect3DTexture8* C, IDirect3DTexture8* D, IDirect3DTexture8* E,
                 INT* DstRect, INT* R1, INT* R2, INT* R3, INT* R4, BYTE Additive);
    void Glow(INT Mode, IDirect3DTexture8* Src, IDirect3DTexture8** OutTexture, FUVRect* OutUV, FLOAT Alpha, DWORD* Color);
};

void UnnamedRender_67740::Glow(INT Mode, IDirect3DTexture8* Src, IDirect3DTexture8** OutTexture, FUVRect* OutUV, FLOAT Alpha, DWORD* Color)
{
    if (Mode == 1)
        Pass(Device->GlowShader, Device->Targets[0], Src, Alpha, 1, 0, 0, 0);
    else if (Mode == 2)
        Pass(Device->ScaledShader, Device->Targets[0], Src, Alpha, 1, 0, Color, 0);
    else
        Pass(Device->BlendShader, Device->Targets[0], Src, Alpha, 1, 0, 0, 0);
    Blur(Device->Targets[1], Device->Targets[0], Device->Targets[2], 0, 0, 0);
    Blur(Device->Targets[3], Device->Targets[2], Device->Targets[4], 0, 0, 0);
    Blur(Device->Targets[5], Device->Targets[4], Device->Targets[6], 0, 0, 0);
    Blur(Device->Targets[7], Device->Targets[6], Device->Targets[8], 0, 0, 0);
    Combine(Device->Targets[0], Device->Targets[2], Device->Targets[4], Device->Targets[6], Device->Targets[8], 0, 0, 0, 0, 0, 0);
    *OutTexture = Device->Targets[0];
    if (OutUV)
    {
        OutUV->U0 = 0.f;
        OutUV->V0 = 0.f;
        OutUV->U1 = 1.f;
        OutUV->V1 = 1.f;
    }
}

// ---------------------------------------------------------------------------
// Out-of-line callees (retail 0x66bb0, 0x67200, 0x67d70, 0x684f0), written
// after the retail code closely enough that the link gives them LTCG
// conventions like the retail ones. Scaffolding, not part of the unit.
__declspec(noinline) void UnnamedRender_67740::Filter(IDirect3DTexture8* Dst, IDirect3DTexture8* Src, INT NumTaps, FLOAT* Offsets, INT DivX, INT DivY, INT* DstRect, INT* SrcRect)
{
    IDirect3DSurface8* Surface = 0;
    Dst->GetSurfaceLevel(0, &Surface);
    Device->Direct3DDevice->SetRenderTarget(Surface, 0);
    Surface->Release();
    D3DSURFACE_DESC SrcDesc, DstDesc;
    Src->GetLevelDesc(0, &SrcDesc);
    Dst->GetLevelDesc(0, &DstDesc);
    INT DefSrc[4] = { 0, 0, (INT)SrcDesc.Width, (INT)SrcDesc.Height };
    if (!SrcRect)
        SrcRect = DefSrc;
    INT DefDst[4] = { 0, 0, (INT)DstDesc.Width, (INT)DstDesc.Height };
    if (!DstRect)
    {
        DefDst[2] = (DWORD)(SrcRect[2] - SrcRect[0]) / DivX;
        DefDst[3] = (DWORD)(SrcRect[3] - SrcRect[1]) / DivY;
        DstRect = DefDst;
    }
    Device->State(0x2fbb4) = 0;
    Device->State(0x2fb5c) = 3;
    Device->State(0x2fb64) = 0;
    Device->Direct3DDevice->SetRenderState(7, 0);
    Device->Direct3DDevice->SetRenderState(0x34, 0);
    Device->State(0x2fb80) = 0;
    Device->State(0x2fb7c) = 0;
    Device->State(0x2fb68) = 2;
    Device->State(0x2fb6c) = 2;
    for (INT i = 0; i < NumTaps; i++)
    {
        Device->State(0x300b4 + i * 4) = (DWORD)Src;
        Device->State(0x2fbc0 + i * 0x34) = 2;
        Device->State(0x2fbcc + i * 0x34) = 1;
        Device->State(0x2fbe4 + i * 0x34) = 0;
        Device->State(0x2fbd8 + i * 0x34) = i;
        Device->State(0x2fbdc + i * 0x34) = 3;
        Device->State(0x2fbe0 + i * 0x34) = 3;
        Device->Direct3DDevice->SetTextureStageState(i, 0x12, 0);
        Device->Direct3DDevice->SetTextureStageState(i, 0x11, 2);
        Device->Direct3DDevice->SetTextureStageState(i, 0x10, 2);
    }
    DrawQuads(Device, DstRect, SrcRect, NumTaps, Offsets);
}

__declspec(noinline) void UnnamedRender_67740::Pass(DWORD Shader, IDirect3DTexture8* Dst, IDirect3DTexture8* Src, FLOAT Alpha, BYTE Bilinear, INT* DstRect, DWORD* Color, INT* SrcRect)
{
    IDirect3DSurface8* Surface = 0;
    Dst->GetSurfaceLevel(0, &Surface);
    Device->Direct3DDevice->SetRenderTarget(Surface, 0);
    Surface->Release();
    D3DSURFACE_DESC SrcDesc, DstDesc;
    Src->GetLevelDesc(0, &SrcDesc);
    Dst->GetLevelDesc(0, &DstDesc);
    INT DefSrc[4] = { 0, 0, (INT)SrcDesc.Width, (INT)SrcDesc.Height };
    if (!SrcRect)
        SrcRect = DefSrc;
    INT DefDst[4] = { 0, 0, (INT)DstDesc.Width, (INT)DstDesc.Height };
    if (!DstRect)
        DstRect = DefDst;
    Device->State(0x2fbb4) = 0;
    Device->State(0x2fb5c) = 3;
    Device->State(0x2fb64) = 0;
    Device->Direct3DDevice->SetRenderState(7, 0);
    Device->Direct3DDevice->SetRenderState(0x34, 0);
    Device->State(0x2fb80) = 0;
    Device->State(0x2fb7c) = 0;
    Device->State(0x2fb68) = 2;
    Device->State(0x2fb6c) = 2;
    Device->State(0x300b4) = (DWORD)Src;
    Device->State(0x2fbc0) = 2;
    Device->State(0x2fbc4) = 2;
    Device->State(0x2fbcc) = 1;
    Device->State(0x2fbe4) = 0;
    Device->State(0x2fbd8) = 0;
    Device->State(0x2fbdc) = 3;
    Device->State(0x2fbe0) = 3;
    Device->Direct3DDevice->SetTextureStageState(0, 0x12, 0);
    if (Bilinear)
    {
        Device->Direct3DDevice->SetTextureStageState(0, 0x11, 5);
        Device->Direct3DDevice->SetTextureStageState(0, 0x10, 5);
    }
    else
    {
        Device->Direct3DDevice->SetTextureStageState(0, 0x11, 1);
        Device->Direct3DDevice->SetTextureStageState(0, 0x10, 1);
    }
    Device->State(0x2fbf4) = 1;
    Device->State(0x30028) = Shader;
    if (Color)
    {
        Device->State(0x30d10) = Color[0];
        Device->State(0x30d14) = Color[1];
        Device->State(0x30d18) = Color[2];
        Device->State(0x30d1c) = Color[3];
        Device->State(0x30d0c) = 1;
    }
    Device->State(0x30024) = 0x104;
    FLOAT X0 = (FLOAT)DstRect[0] - 0.5f;
    FLOAT Y0 = (FLOAT)DstRect[1] - 0.5f;
    FLOAT X1 = (FLOAT)DstRect[2] - 0.5f;
    FLOAT Y1 = (FLOAT)DstRect[3] - 0.5f;
    FLOAT InvW = 1.f / (FLOAT)SrcDesc.Width;
    FLOAT InvH = 1.f / (FLOAT)SrcDesc.Height;
    FLOAT U0 = SrcRect[0] * InvW, V0 = SrcRect[1] * InvH;
    FLOAT U1 = SrcRect[2] * InvW, V1 = SrcRect[3] * InvH;
    FLOAT Verts[4][6];
    Verts[0][0] = X0; Verts[0][1] = Y0; Verts[0][2] = 0.f; Verts[0][3] = 0.9f; Verts[0][4] = U0; Verts[0][5] = V0;
    Verts[1][0] = X1; Verts[1][1] = Y0; Verts[1][2] = 0.f; Verts[1][3] = 0.9f; Verts[1][4] = U1; Verts[1][5] = V0;
    Verts[2][0] = X1; Verts[2][1] = Y1; Verts[2][2] = 0.f; Verts[2][3] = 0.9f; Verts[2][4] = U1; Verts[2][5] = V1;
    Verts[3][0] = X0; Verts[3][1] = Y1; Verts[3][2] = 0.f; Verts[3][3] = 0.9f; Verts[3][4] = U0; Verts[3][5] = V1;
    Device->State(0x2fb58 + 0x4d4) = 0;
    Device->State(0x2fb58 + 0x4d8) = 0;
    CommitState(&Device->State(0x2fb58));
    FLOAT Constant[4] = { 0.f, 0.f, 0.f, Alpha };
    Device->Direct3DDevice->SetPixelShaderConstant(5, Constant, 1);
    Device->Direct3DDevice->DrawPrimitiveUP(5, 2, Verts, 0x18);
    Device->State(0x300b4) = 0;
    Device->Direct3DDevice->SetRenderState(7, 1);
    Device->Direct3DDevice->SetRenderState(0x34, Device->State(0x5c) != 0);
    UnnamedDevice_67740* D = Device;
    D->Direct3DDevice->SetTextureStageState(0, 0x12, D->State(0x40d0) ? (D->State(0x40cc) != 0) + 1 : 0);
}

__declspec(noinline) void UnnamedRender_67740::Blur(IDirect3DTexture8* Tmp, IDirect3DTexture8* Src, IDirect3DTexture8* Dst, INT* DstRect, INT* TmpRect, INT* SrcRect)
{
    FLOAT Vertical[8] = { 0.f, 1.f, 0.f, 3.f, 0.f, -1.f, 0.f, -3.f };
    FLOAT Horizontal[8] = { 1.f, 0.f, 3.f, 0.f, -1.f, 0.f, -3.f, 0.f };
    Filter(Tmp, Src, 4, Vertical, 1, 2, TmpRect, SrcRect);
    Filter(Dst, Tmp, 4, Horizontal, 2, 1, DstRect, TmpRect);
}

__declspec(noinline) void UnnamedRender_67740::Combine(IDirect3DTexture8* Dst, IDirect3DTexture8* B, IDirect3DTexture8* C, IDirect3DTexture8* D, IDirect3DTexture8* E,
                                                       INT* DstRect, INT* R1, INT* R2, INT* R3, INT* R4, BYTE Additive)
{
    IDirect3DSurface8* Surface = 0;
    Dst->GetSurfaceLevel(0, &Surface);
    Device->Direct3DDevice->SetRenderTarget(Surface, 0);
    Surface->Release();
    D3DSURFACE_DESC Desc[4], DstDesc;
    B->GetLevelDesc(0, &Desc[0]);
    C->GetLevelDesc(0, &Desc[1]);
    D->GetLevelDesc(0, &Desc[2]);
    E->GetLevelDesc(0, &Desc[3]);
    Dst->GetLevelDesc(0, &DstDesc);
    INT Rects[4][4];
    INT* Src[4];
    for (INT i = 0; i < 4; i++)
    {
        Rects[i][0] = Rects[i][1] = 0;
        Rects[i][2] = Desc[i].Width;
        Rects[i][3] = Desc[i].Height;
        Src[i] = Rects[i];
    }
    if (!R1) R1 = Src[0];
    if (!R2) R2 = Src[1];
    if (!R3) R3 = Src[2];
    if (R4) Src[3] = R4;
    INT Full[4] = { 0, 0, (INT)DstDesc.Width, (INT)DstDesc.Height };
    if (!DstRect) DstRect = Full;
    FLOAT X0 = (FLOAT)DstRect[0] - 0.5f;
    FLOAT Y0 = (FLOAT)DstRect[1] - 0.5f;
    FLOAT X1 = (FLOAT)DstRect[2] - 0.5f;
    FLOAT Y1 = (FLOAT)DstRect[3] - 0.5f;
    FLOAT Verts[4][12];
    Verts[0][0] = X0; Verts[0][1] = Y0; Verts[1][0] = X1; Verts[1][1] = Y0;
    Verts[2][0] = X1; Verts[2][1] = Y1; Verts[3][0] = X0; Verts[3][1] = Y1;
    INT* Rect[4] = { R1, R2, R3, Src[3] };
    for (INT v = 0; v < 4; v++) { Verts[v][2] = 0.f; Verts[v][3] = 0.9f; }
    for (INT t = 0; t < 4; t++)
    {
        FLOAT InvW = 1.f / (FLOAT)Desc[t].Width;
        FLOAT InvH = 1.f / (FLOAT)Desc[t].Height;
        FLOAT U0 = Rect[t][0] * InvW, V0 = Rect[t][1] * InvH;
        FLOAT U1 = Rect[t][2] * InvW, V1 = Rect[t][3] * InvH;
        Verts[0][4 + t * 2] = U0; Verts[0][5 + t * 2] = V0;
        Verts[1][4 + t * 2] = U1; Verts[1][5 + t * 2] = V0;
        Verts[2][4 + t * 2] = U1; Verts[2][5 + t * 2] = V1;
        Verts[3][4 + t * 2] = U0; Verts[3][5 + t * 2] = V1;
    }
    Device->State(0x30028) = Device->State(0x30f98);
    Device->State(0x300b4) = (DWORD)B;
    Device->State(0x300b8) = (DWORD)C;
    Device->State(0x300bc) = (DWORD)D;
    Device->State(0x300c0) = (DWORD)E;
    for (INT s = 0; s < 4; s++)
    {
        Device->State(0x2fbdc + s * 0x34) = 3;
        Device->State(0x2fbe0 + s * 0x34) = 3;
        Device->Direct3DDevice->SetTextureStageState(s, 0x11, 2);
        Device->Direct3DDevice->SetTextureStageState(s, 0x10, 2);
        Device->Direct3DDevice->SetTextureStageState(s, 0x12, 0);
    }
    Device->Direct3DDevice->SetRenderState(7, 0);
    Device->State(0x2fb64) = 0;
    if (Additive)
    {
        Device->State(0x2fb7c) = 1;
        Device->State(0x2fb68) = 10;
    }
    else
    {
        Device->State(0x2fb7c) = 0;
        Device->State(0x2fb68) = 2;
    }
    Device->State(0x2fb6c) = 1;
    Device->State(0x30024) = 0x404;
    Device->State(0x2fb58 + 0x4d4) = 0;
    Device->State(0x2fb58 + 0x4d8) = 0;
    CommitState(&Device->State(0x2fb58));
    FLOAT Constant[4][4];
    for (INT k = 0; k < 4; k++)
        Constant[k][0] = Constant[k][1] = Constant[k][2] = Constant[k][3] = GlowWeights[k];
    Device->Direct3DDevice->SetPixelShaderConstant(0, Constant, 4);
    Device->Direct3DDevice->DrawPrimitiveUP(5, 2, Verts, 0x30);
    Device->Direct3DDevice->SetRenderState(7, 1);
    for (INT j = 0; j < 4; j++)
    {
        UnnamedDevice_67740* Dev = Device;
        Dev->Direct3DDevice->SetTextureStageState(j, 0x12, Dev->State(0x40d0) ? (Dev->State(0x40cc) != 0) + 1 : 0);
    }
}

// Scaffolding for the link, not part of the unit.
void Driver_67740(UnnamedRender_67740* R, INT Mode, IDirect3DTexture8* Src, IDirect3DTexture8** Out, FUVRect* UV, FLOAT Alpha, DWORD* Color)
{
    R->Glow(Mode, Src, Out, UV, Alpha, Color);
}
