// Work item 0028: RVA 0x5f9c0, UD3DRenderDevice shader release (LTCG, this in ESI).
// Device vtable slots 0x138/0x168 are IDirect3DDevice8::DeleteVertexShader (78)
// and DeletePixelShader (90). The function name is a guess; the class is
// inferred from the neighbouring delete_UD3DRenderDevice and the D3D8 calls.
typedef unsigned long DWORD;
typedef long HRESULT;

struct IDirect3DDevice8
{
    virtual HRESULT __stdcall QueryInterface() = 0; // signature not needed here
    virtual HRESULT __stdcall AddRef() = 0; // signature not needed here
    virtual HRESULT __stdcall Release() = 0; // signature not needed here
    virtual HRESULT __stdcall TestCooperativeLevel() = 0; // signature not needed here
    virtual HRESULT __stdcall GetAvailableTextureMem() = 0; // signature not needed here
    virtual HRESULT __stdcall ResourceManagerDiscardBytes() = 0; // signature not needed here
    virtual HRESULT __stdcall GetDirect3D() = 0; // signature not needed here
    virtual HRESULT __stdcall GetDeviceCaps() = 0; // signature not needed here
    virtual HRESULT __stdcall GetDisplayMode() = 0; // signature not needed here
    virtual HRESULT __stdcall GetCreationParameters() = 0; // signature not needed here
    virtual HRESULT __stdcall SetCursorProperties() = 0; // signature not needed here
    virtual HRESULT __stdcall SetCursorPosition() = 0; // signature not needed here
    virtual HRESULT __stdcall ShowCursor() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateAdditionalSwapChain() = 0; // signature not needed here
    virtual HRESULT __stdcall Reset() = 0; // signature not needed here
    virtual HRESULT __stdcall Present() = 0; // signature not needed here
    virtual HRESULT __stdcall GetBackBuffer() = 0; // signature not needed here
    virtual HRESULT __stdcall GetRasterStatus() = 0; // signature not needed here
    virtual HRESULT __stdcall SetGammaRamp() = 0; // signature not needed here
    virtual HRESULT __stdcall GetGammaRamp() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateTexture() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateVolumeTexture() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateCubeTexture() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateVertexBuffer() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateIndexBuffer() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateRenderTarget() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateDepthStencilSurface() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateImageSurface() = 0; // signature not needed here
    virtual HRESULT __stdcall CopyRects() = 0; // signature not needed here
    virtual HRESULT __stdcall UpdateTexture() = 0; // signature not needed here
    virtual HRESULT __stdcall GetFrontBuffer() = 0; // signature not needed here
    virtual HRESULT __stdcall SetRenderTarget() = 0; // signature not needed here
    virtual HRESULT __stdcall GetRenderTarget() = 0; // signature not needed here
    virtual HRESULT __stdcall GetDepthStencilSurface() = 0; // signature not needed here
    virtual HRESULT __stdcall BeginScene() = 0; // signature not needed here
    virtual HRESULT __stdcall EndScene() = 0; // signature not needed here
    virtual HRESULT __stdcall Clear() = 0; // signature not needed here
    virtual HRESULT __stdcall SetTransform() = 0; // signature not needed here
    virtual HRESULT __stdcall GetTransform() = 0; // signature not needed here
    virtual HRESULT __stdcall MultiplyTransform() = 0; // signature not needed here
    virtual HRESULT __stdcall SetViewport() = 0; // signature not needed here
    virtual HRESULT __stdcall GetViewport() = 0; // signature not needed here
    virtual HRESULT __stdcall SetMaterial() = 0; // signature not needed here
    virtual HRESULT __stdcall GetMaterial() = 0; // signature not needed here
    virtual HRESULT __stdcall SetLight() = 0; // signature not needed here
    virtual HRESULT __stdcall GetLight() = 0; // signature not needed here
    virtual HRESULT __stdcall LightEnable() = 0; // signature not needed here
    virtual HRESULT __stdcall GetLightEnable() = 0; // signature not needed here
    virtual HRESULT __stdcall SetClipPlane() = 0; // signature not needed here
    virtual HRESULT __stdcall GetClipPlane() = 0; // signature not needed here
    virtual HRESULT __stdcall SetRenderState() = 0; // signature not needed here
    virtual HRESULT __stdcall GetRenderState() = 0; // signature not needed here
    virtual HRESULT __stdcall BeginStateBlock() = 0; // signature not needed here
    virtual HRESULT __stdcall EndStateBlock() = 0; // signature not needed here
    virtual HRESULT __stdcall ApplyStateBlock() = 0; // signature not needed here
    virtual HRESULT __stdcall CaptureStateBlock() = 0; // signature not needed here
    virtual HRESULT __stdcall DeleteStateBlock() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateStateBlock() = 0; // signature not needed here
    virtual HRESULT __stdcall SetClipStatus() = 0; // signature not needed here
    virtual HRESULT __stdcall GetClipStatus() = 0; // signature not needed here
    virtual HRESULT __stdcall GetTexture() = 0; // signature not needed here
    virtual HRESULT __stdcall SetTexture() = 0; // signature not needed here
    virtual HRESULT __stdcall GetTextureStageState() = 0; // signature not needed here
    virtual HRESULT __stdcall SetTextureStageState() = 0; // signature not needed here
    virtual HRESULT __stdcall ValidateDevice() = 0; // signature not needed here
    virtual HRESULT __stdcall GetInfo() = 0; // signature not needed here
    virtual HRESULT __stdcall SetPaletteEntries() = 0; // signature not needed here
    virtual HRESULT __stdcall GetPaletteEntries() = 0; // signature not needed here
    virtual HRESULT __stdcall SetCurrentTexturePalette() = 0; // signature not needed here
    virtual HRESULT __stdcall GetCurrentTexturePalette() = 0; // signature not needed here
    virtual HRESULT __stdcall DrawPrimitive() = 0; // signature not needed here
    virtual HRESULT __stdcall DrawIndexedPrimitive() = 0; // signature not needed here
    virtual HRESULT __stdcall DrawPrimitiveUP() = 0; // signature not needed here
    virtual HRESULT __stdcall DrawIndexedPrimitiveUP() = 0; // signature not needed here
    virtual HRESULT __stdcall ProcessVertices() = 0; // signature not needed here
    virtual HRESULT __stdcall CreateVertexShader() = 0; // signature not needed here
    virtual HRESULT __stdcall SetVertexShader() = 0; // signature not needed here
    virtual HRESULT __stdcall GetVertexShader() = 0; // signature not needed here
    virtual HRESULT __stdcall DeleteVertexShader(DWORD Handle) = 0;
    virtual HRESULT __stdcall SetVertexShaderConstant() = 0; // signature not needed here
    virtual HRESULT __stdcall GetVertexShaderConstant() = 0; // signature not needed here
    virtual HRESULT __stdcall GetVertexShaderDeclaration() = 0; // signature not needed here
    virtual HRESULT __stdcall GetVertexShaderFunction() = 0; // signature not needed here
    virtual HRESULT __stdcall SetStreamSource() = 0; // signature not needed here
    virtual HRESULT __stdcall GetStreamSource() = 0; // signature not needed here
    virtual HRESULT __stdcall SetIndices() = 0; // signature not needed here
    virtual HRESULT __stdcall GetIndices() = 0; // signature not needed here
    virtual HRESULT __stdcall CreatePixelShader() = 0; // signature not needed here
    virtual HRESULT __stdcall SetPixelShader() = 0; // signature not needed here
    virtual HRESULT __stdcall GetPixelShader() = 0; // signature not needed here
    virtual HRESULT __stdcall DeletePixelShader(DWORD Handle) = 0;
};

class UD3DRenderDevice
{
public:
    unsigned char Pad0[0x46a4];
    IDirect3DDevice8 *Direct3DDevice8;          // 0x46a4
    unsigned char Pad1[0x30e44 - 0x46a8];
    DWORD ExtraPixelShaders[6];                 // 0x30e44
    unsigned char Pad2[0x30f2c - 0x30e5c];
    DWORD VertexShaderHandle;                   // 0x30f2c
    DWORD PixelShaders[(0x30fc0 - 0x30f30) / 4];// 0x30f30..0x30fbc

    void ReleaseShaders();
};

#define PS(off) PixelShaders[((off) - 0x30f30) / 4]
#define FREE_PS(h) if (h != 0 && h != (DWORD)-1) { Direct3DDevice8->DeletePixelShader(h); h = (DWORD)-1; }

void UD3DRenderDevice::ReleaseShaders()
{
    if (VertexShaderHandle != 0 && VertexShaderHandle != (DWORD)-1)
    {
        Direct3DDevice8->DeleteVertexShader(VertexShaderHandle);
        VertexShaderHandle = (DWORD)-1;
    }
    FREE_PS(PS(0x30f68));
    FREE_PS(PS(0x30f30));
    FREE_PS(PS(0x30f34));
    FREE_PS(PS(0x30f38));
    FREE_PS(PS(0x30f3c));
    FREE_PS(PS(0x30f40));
    FREE_PS(PS(0x30f44));
    FREE_PS(PS(0x30f48));
    FREE_PS(PS(0x30f4c));
    FREE_PS(PS(0x30f50));
    FREE_PS(PS(0x30f60));
    FREE_PS(PS(0x30f64));
    FREE_PS(PS(0x30f54));
    FREE_PS(PS(0x30f58));
    FREE_PS(PS(0x30f5c));
    FREE_PS(PS(0x30f6c));
    FREE_PS(PS(0x30f70));
    FREE_PS(PS(0x30f74));
    FREE_PS(PS(0x30f78));
    FREE_PS(PS(0x30f7c));
    FREE_PS(PS(0x30f80));
    FREE_PS(PS(0x30f84));
    FREE_PS(PS(0x30f88));
    FREE_PS(PS(0x30f8c));
    FREE_PS(PS(0x30f90));
    FREE_PS(PS(0x30f94));
    FREE_PS(PS(0x30f98));
    FREE_PS(PS(0x30f9c));
    FREE_PS(PS(0x30fa0));
    FREE_PS(PS(0x30fa4));
    FREE_PS(PS(0x30fa8));
    FREE_PS(PS(0x30fac));
    FREE_PS(PS(0x30fb0));
    FREE_PS(PS(0x30fb4));
    FREE_PS(PS(0x30fb8));
    FREE_PS(PS(0x30fbc));
    FREE_PS(ExtraPixelShaders[0]);
    FREE_PS(ExtraPixelShaders[1]);
    FREE_PS(ExtraPixelShaders[2]);
    FREE_PS(ExtraPixelShaders[3]);
    FREE_PS(ExtraPixelShaders[4]);
    FREE_PS(ExtraPixelShaders[5]);
}

// Scaffolding for the link, not part of the unit.
void Driver_5f9c0(UD3DRenderDevice *D) { D->ReleaseShaders(); }
