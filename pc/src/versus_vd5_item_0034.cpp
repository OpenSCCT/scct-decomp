// FD3DDeferredState::Commit (RVA 0x6c1d0), D3DDrv render-state cache.
// The device vtable offsets match IDirect3DDevice8 (SetRenderState 0xc8,
// SetTransform 0x94, SetTexture 0xf4, SetTextureStageState 0xfc ...), so the
// names below follow the Direct3D 8 API and UE2's D3DDrv FD3DDeferredState.

typedef unsigned long DWORD;
typedef int INT;
typedef long HRESULT;
typedef unsigned int UINT;

extern "C" int __cdecl memcmp(const void *, const void *, unsigned int);
#pragma intrinsic(memcmp)

struct D3DMATRIX { float m[4][4]; };
struct D3DLIGHT8 { DWORD Data[26]; };

struct IDirect3DDevice8
{
    virtual HRESULT __stdcall Slot00() = 0; virtual HRESULT __stdcall Slot01() = 0;
    virtual HRESULT __stdcall Slot02() = 0; virtual HRESULT __stdcall Slot03() = 0;
    virtual HRESULT __stdcall Slot04() = 0; virtual HRESULT __stdcall Slot05() = 0;
    virtual HRESULT __stdcall Slot06() = 0; virtual HRESULT __stdcall Slot07() = 0;
    virtual HRESULT __stdcall Slot08() = 0; virtual HRESULT __stdcall Slot09() = 0;
    virtual HRESULT __stdcall Slot10() = 0; virtual HRESULT __stdcall Slot11() = 0;
    virtual HRESULT __stdcall Slot12() = 0; virtual HRESULT __stdcall Slot13() = 0;
    virtual HRESULT __stdcall Slot14() = 0; virtual HRESULT __stdcall Slot15() = 0;
    virtual HRESULT __stdcall Slot16() = 0; virtual HRESULT __stdcall Slot17() = 0;
    virtual HRESULT __stdcall Slot18() = 0; virtual HRESULT __stdcall Slot19() = 0;
    virtual HRESULT __stdcall Slot20() = 0; virtual HRESULT __stdcall Slot21() = 0;
    virtual HRESULT __stdcall Slot22() = 0; virtual HRESULT __stdcall Slot23() = 0;
    virtual HRESULT __stdcall Slot24() = 0; virtual HRESULT __stdcall Slot25() = 0;
    virtual HRESULT __stdcall Slot26() = 0; virtual HRESULT __stdcall Slot27() = 0;
    virtual HRESULT __stdcall Slot28() = 0; virtual HRESULT __stdcall Slot29() = 0;
    virtual HRESULT __stdcall Slot30() = 0; virtual HRESULT __stdcall Slot31() = 0;
    virtual HRESULT __stdcall Slot32() = 0; virtual HRESULT __stdcall Slot33() = 0;
    virtual HRESULT __stdcall Slot34() = 0; virtual HRESULT __stdcall Slot35() = 0;
    virtual HRESULT __stdcall Slot36() = 0;
    virtual HRESULT __stdcall SetTransform(DWORD State, const D3DMATRIX *Matrix) = 0;  // 0x94
    virtual HRESULT __stdcall Slot38() = 0; virtual HRESULT __stdcall Slot39() = 0;
    virtual HRESULT __stdcall Slot40() = 0; virtual HRESULT __stdcall Slot41() = 0;
    virtual HRESULT __stdcall Slot42() = 0; virtual HRESULT __stdcall Slot43() = 0;
    virtual HRESULT __stdcall SetLight(DWORD Index, const D3DLIGHT8 *Light) = 0;      // 0xb0
    virtual HRESULT __stdcall Slot45() = 0;
    virtual HRESULT __stdcall LightEnable(DWORD Index, INT Enable) = 0;               // 0xb8
    virtual HRESULT __stdcall Slot47() = 0; virtual HRESULT __stdcall Slot48() = 0;
    virtual HRESULT __stdcall Slot49() = 0;
    virtual HRESULT __stdcall SetRenderState(DWORD State, DWORD Value) = 0;           // 0xc8
    virtual HRESULT __stdcall Slot51() = 0; virtual HRESULT __stdcall Slot52() = 0;
    virtual HRESULT __stdcall Slot53() = 0; virtual HRESULT __stdcall Slot54() = 0;
    virtual HRESULT __stdcall Slot55() = 0; virtual HRESULT __stdcall Slot56() = 0;
    virtual HRESULT __stdcall Slot57() = 0; virtual HRESULT __stdcall Slot58() = 0;
    virtual HRESULT __stdcall Slot59() = 0; virtual HRESULT __stdcall Slot60() = 0;
    virtual HRESULT __stdcall SetTexture(DWORD Stage, void *Texture) = 0;             // 0xf4
    virtual HRESULT __stdcall Slot62() = 0;
    virtual HRESULT __stdcall SetTextureStageState(DWORD Stage, DWORD Type, DWORD Value) = 0; // 0xfc
    virtual HRESULT __stdcall Slot64() = 0; virtual HRESULT __stdcall Slot65() = 0;
    virtual HRESULT __stdcall Slot66() = 0; virtual HRESULT __stdcall Slot67() = 0;
    virtual HRESULT __stdcall Slot68() = 0; virtual HRESULT __stdcall Slot69() = 0;
    virtual HRESULT __stdcall Slot70() = 0; virtual HRESULT __stdcall Slot71() = 0;
    virtual HRESULT __stdcall Slot72() = 0; virtual HRESULT __stdcall Slot73() = 0;
    virtual HRESULT __stdcall Slot74() = 0; virtual HRESULT __stdcall Slot75() = 0;
    virtual HRESULT __stdcall SetVertexShader(DWORD Handle) = 0;                      // 0x130
    virtual HRESULT __stdcall Slot77() = 0; virtual HRESULT __stdcall Slot78() = 0;
    virtual HRESULT __stdcall Slot79() = 0; virtual HRESULT __stdcall Slot80() = 0;
    virtual HRESULT __stdcall Slot81() = 0; virtual HRESULT __stdcall Slot82() = 0;
    virtual HRESULT __stdcall SetStreamSource(UINT Stream, void *Data, UINT Stride) = 0; // 0x14c
    virtual HRESULT __stdcall Slot84() = 0;
    virtual HRESULT __stdcall SetIndices(void *Indices, UINT BaseVertexIndex) = 0;    // 0x154
    virtual HRESULT __stdcall Slot86() = 0; virtual HRESULT __stdcall Slot87() = 0;
    virtual HRESULT __stdcall SetPixelShader(DWORD Handle) = 0;                       // 0x160
    virtual HRESULT __stdcall Slot89() = 0; virtual HRESULT __stdcall Slot90() = 0;
    virtual HRESULT __stdcall SetPixelShaderConstant(DWORD Register, const void *Data, DWORD Count) = 0; // 0x16c
};

// Only the members this function reads; offsets from the retail code.
class UD3DRenderDevice
{
public:
    char Pad0[0x5c];
    INT UseStencil;                     // 0x5c
    char Pad1[0x41d0 - 0x60];
    INT NumTextureStages;               // 0x41d0
    INT NumTextures;                    // 0x41d4
    INT Pad2;
    INT MaxLights;                      // 0x41dc
    char Pad3[0x41f8 - 0x41e0];
    INT MaxStreams;                     // 0x41f8
    char Pad4[0x46a4 - 0x41fc];
    IDirect3DDevice8 *Direct3DDevice8;  // 0x46a4
};

struct FD3DStageState
{
    DWORD ColorOp, ColorArg1, ColorArg2, AlphaOp, AlphaArg1, AlphaArg2;
    DWORD TexCoordIndex, AddressU, AddressV, TextureTransformFlags;
    DWORD AddressW, ColorArg0, MipMapLODBias;
};

struct FD3DStreamState
{
    void *StreamData;
    UINT StreamStride;
};

struct FD3DInternalState
{
    DWORD FillMode, ZWriteEnable, AlphaTestEnable, SrcBlend, DestBlend;
    DWORD CullMode, ZFunc, AlphaRef, AlphaBlendEnable, FogEnable;
    DWORD FogColor, FogStart, FogEnd, ZBias;
    DWORD StencilFail, StencilZFail, StencilPass, StencilFunc, StencilRef;
    DWORD StencilMask, StencilWriteMask, TextureFactor, Lighting, Ambient, ColorVertex;
    FD3DStageState Stages[8];
    D3DMATRIX Matrices[11];
    DWORD MatricesChanged;
    DWORD VertexShader;
    DWORD PixelShader;
    FD3DStreamState Streams[16];
    void *IndexBuffer;
    UINT IndexBufferBase;
    void *Textures[8];
    D3DLIGHT8 Lights[8];
    INT LightsEnabled[8];
};

inline INT Min(INT A, INT B) { return A < B ? A : B; }

class FD3DDeferredState
{
public:
    UD3DRenderDevice *RenDev;
    FD3DInternalState WantedState;
    FD3DInternalState HardwareState;
    INT PixelShaderConstantsDirty;
    float PixelShaderConstants[4];

    void Commit();
};

#define COMMIT_RENDER_STATE(Member, State) \
    if (WantedState.Member != HardwareState.Member) \
    { \
        RenDev->Direct3DDevice8->SetRenderState(State, WantedState.Member); \
        HardwareState.Member = WantedState.Member; \
    }

#define COMMIT_STAGE_STATE(Member, State) \
    if (WantedState.Stages[StageIndex].Member != HardwareState.Stages[StageIndex].Member) \
    { \
        RenDev->Direct3DDevice8->SetTextureStageState(StageIndex, State, WantedState.Stages[StageIndex].Member); \
        HardwareState.Stages[StageIndex].Member = WantedState.Stages[StageIndex].Member; \
    }

#define COMMIT_TRANSFORM(Bit, Index, State) \
    if ((WantedState.MatricesChanged & Bit) && memcmp(&WantedState.Matrices[Index], &HardwareState.Matrices[Index], sizeof(D3DMATRIX)) != 0) \
    { \
        RenDev->Direct3DDevice8->SetTransform(State, &WantedState.Matrices[Index]); \
        HardwareState.Matrices[Index] = WantedState.Matrices[Index]; \
    }

void FD3DDeferredState::Commit()
{
    COMMIT_RENDER_STATE(FillMode, 8);
    COMMIT_RENDER_STATE(ZWriteEnable, 14);
    COMMIT_RENDER_STATE(AlphaTestEnable, 15);
    COMMIT_RENDER_STATE(SrcBlend, 19);
    COMMIT_RENDER_STATE(DestBlend, 20);
    COMMIT_RENDER_STATE(CullMode, 22);
    COMMIT_RENDER_STATE(ZFunc, 23);
    COMMIT_RENDER_STATE(AlphaRef, 24);
    COMMIT_RENDER_STATE(AlphaBlendEnable, 27);
    COMMIT_RENDER_STATE(FogEnable, 28);
    if (WantedState.FogEnable)
    {
        COMMIT_RENDER_STATE(FogColor, 34);
        COMMIT_RENDER_STATE(FogStart, 36);
        COMMIT_RENDER_STATE(FogEnd, 37);
    }
    else
    {
        WantedState.FogColor = HardwareState.FogColor;
        WantedState.FogStart = HardwareState.FogStart;
        WantedState.FogEnd = HardwareState.FogEnd;
    }
    COMMIT_RENDER_STATE(ZBias, 47);
    if (RenDev->UseStencil)
    {
        COMMIT_RENDER_STATE(StencilFail, 53);
        COMMIT_RENDER_STATE(StencilZFail, 54);
        COMMIT_RENDER_STATE(StencilPass, 55);
        COMMIT_RENDER_STATE(StencilFunc, 56);
        COMMIT_RENDER_STATE(StencilRef, 57);
        COMMIT_RENDER_STATE(StencilMask, 58);
        COMMIT_RENDER_STATE(StencilWriteMask, 59);
    }
    COMMIT_RENDER_STATE(TextureFactor, 60);
    COMMIT_RENDER_STATE(Lighting, 137);
    COMMIT_RENDER_STATE(Ambient, 139);
    COMMIT_RENDER_STATE(ColorVertex, 141);

    for (INT StageIndex = 0; StageIndex < RenDev->NumTextureStages; StageIndex++)
    {
        COMMIT_STAGE_STATE(ColorOp, 1);
        if (WantedState.Stages[StageIndex].ColorOp == 1) // D3DTOP_DISABLE
            break;
        COMMIT_STAGE_STATE(ColorArg1, 2);
        COMMIT_STAGE_STATE(ColorArg2, 3);
        COMMIT_STAGE_STATE(AlphaOp, 4);
        COMMIT_STAGE_STATE(AlphaArg1, 5);
        COMMIT_STAGE_STATE(AlphaArg2, 6);
        COMMIT_STAGE_STATE(TexCoordIndex, 11);
        COMMIT_STAGE_STATE(AddressU, 13);
        COMMIT_STAGE_STATE(AddressV, 14);
        COMMIT_STAGE_STATE(TextureTransformFlags, 24);
        COMMIT_STAGE_STATE(AddressW, 25);
        COMMIT_STAGE_STATE(ColorArg0, 26);
        COMMIT_STAGE_STATE(MipMapLODBias, 19);
    }

    COMMIT_TRANSFORM(0x001, 0, 0x10);   // D3DTS_TEXTURE0
    COMMIT_TRANSFORM(0x002, 1, 0x11);
    COMMIT_TRANSFORM(0x004, 2, 0x12);
    COMMIT_TRANSFORM(0x008, 3, 0x13);
    COMMIT_TRANSFORM(0x010, 4, 0x14);
    COMMIT_TRANSFORM(0x100, 8, 2);      // D3DTS_VIEW
    COMMIT_TRANSFORM(0x200, 9, 3);      // D3DTS_PROJECTION
    COMMIT_TRANSFORM(0x400, 10, 0x100); // D3DTS_WORLD

    for (INT TextureIndex = 0; TextureIndex < RenDev->NumTextures; TextureIndex++)
    {
        if (WantedState.Textures[TextureIndex] != HardwareState.Textures[TextureIndex])
        {
            RenDev->Direct3DDevice8->SetTexture(TextureIndex, WantedState.Textures[TextureIndex]);
            HardwareState.Textures[TextureIndex] = WantedState.Textures[TextureIndex];
        }
    }

    for (INT LightIndex = 0; LightIndex < Min(RenDev->MaxLights, 8); LightIndex++)
    {
        if (WantedState.LightsEnabled[LightIndex])
            RenDev->Direct3DDevice8->SetLight(LightIndex, &WantedState.Lights[LightIndex]);
        if (WantedState.LightsEnabled[LightIndex] != HardwareState.LightsEnabled[LightIndex])
        {
            RenDev->Direct3DDevice8->LightEnable(LightIndex, WantedState.LightsEnabled[LightIndex]);
            HardwareState.LightsEnabled[LightIndex] = WantedState.LightsEnabled[LightIndex];
        }
    }

    if (WantedState.VertexShader != HardwareState.VertexShader)
    {
        RenDev->Direct3DDevice8->SetVertexShader(WantedState.VertexShader);
        HardwareState.VertexShader = WantedState.VertexShader;
    }

    for (INT StreamIndex = 0; StreamIndex < Min(RenDev->MaxStreams, 16); StreamIndex++)
    {
        if (WantedState.Streams[StreamIndex].StreamData != HardwareState.Streams[StreamIndex].StreamData
         || WantedState.Streams[StreamIndex].StreamStride != HardwareState.Streams[StreamIndex].StreamStride)
        {
            RenDev->Direct3DDevice8->SetStreamSource(StreamIndex, WantedState.Streams[StreamIndex].StreamData, WantedState.Streams[StreamIndex].StreamStride);
            HardwareState.Streams[StreamIndex].StreamData = WantedState.Streams[StreamIndex].StreamData;
            HardwareState.Streams[StreamIndex].StreamStride = WantedState.Streams[StreamIndex].StreamStride;
        }
    }

    if (WantedState.PixelShader != HardwareState.PixelShader)
    {
        RenDev->Direct3DDevice8->SetPixelShader(WantedState.PixelShader);
        HardwareState.PixelShader = WantedState.PixelShader;
    }

    if (PixelShaderConstantsDirty && WantedState.PixelShader)
    {
        RenDev->Direct3DDevice8->SetPixelShaderConstant(0, PixelShaderConstants, 1);
        PixelShaderConstantsDirty = 0;
    }

    if (WantedState.IndexBuffer != HardwareState.IndexBuffer
     || WantedState.IndexBufferBase != HardwareState.IndexBufferBase)
    {
        RenDev->Direct3DDevice8->SetIndices(WantedState.IndexBuffer, WantedState.IndexBufferBase);
        HardwareState.IndexBuffer = WantedState.IndexBuffer;
        HardwareState.IndexBufferBase = WantedState.IndexBufferBase;
    }

    WantedState.MatricesChanged = 0;
}

// Scaffolding for the link, not part of the unit.
void Driver_6c1d0(FD3DDeferredState *State)
{
    State->Commit();
}
