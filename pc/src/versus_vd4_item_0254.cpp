// Work item 0254: UD3DRenderDevice shader helpers (D3D8), RVA 0x5f6b0-0x5f9b2.
// Direct3D 8 and D3DX 8 interfaces are declared with their real slot order;
// only the methods these functions call are named.

typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef float FLOAT;
#include "d3dx_buffer.h"

struct IDirect3DDevice8
{
    virtual long __stdcall QueryInterface(const void *Iid, void **Out);
    virtual DWORD __stdcall AddRef();
    virtual DWORD __stdcall Release();
    virtual long __stdcall Method3(); // not used here
    virtual long __stdcall Method4(); // not used here
    virtual long __stdcall Method5(); // not used here
    virtual long __stdcall Method6(); // not used here
    virtual long __stdcall Method7(); // not used here
    virtual long __stdcall Method8(); // not used here
    virtual long __stdcall Method9(); // not used here
    virtual long __stdcall Method10(); // not used here
    virtual long __stdcall Method11(); // not used here
    virtual long __stdcall Method12(); // not used here
    virtual long __stdcall Method13(); // not used here
    virtual long __stdcall Method14(); // not used here
    virtual long __stdcall Method15(); // not used here
    virtual long __stdcall Method16(); // not used here
    virtual long __stdcall Method17(); // not used here
    virtual long __stdcall Method18(); // not used here
    virtual long __stdcall Method19(); // not used here
    virtual long __stdcall Method20(); // not used here
    virtual long __stdcall Method21(); // not used here
    virtual long __stdcall Method22(); // not used here
    virtual long __stdcall Method23(); // not used here
    virtual long __stdcall Method24(); // not used here
    virtual long __stdcall Method25(); // not used here
    virtual long __stdcall Method26(); // not used here
    virtual long __stdcall Method27(); // not used here
    virtual long __stdcall Method28(); // not used here
    virtual long __stdcall Method29(); // not used here
    virtual long __stdcall Method30(); // not used here
    virtual long __stdcall Method31(); // not used here
    virtual long __stdcall Method32(); // not used here
    virtual long __stdcall Method33(); // not used here
    virtual long __stdcall Method34(); // not used here
    virtual long __stdcall Method35(); // not used here
    virtual long __stdcall Method36(); // not used here
    virtual long __stdcall Method37(); // not used here
    virtual long __stdcall Method38(); // not used here
    virtual long __stdcall Method39(); // not used here
    virtual long __stdcall Method40(); // not used here
    virtual long __stdcall Method41(); // not used here
    virtual long __stdcall Method42(); // not used here
    virtual long __stdcall Method43(); // not used here
    virtual long __stdcall Method44(); // not used here
    virtual long __stdcall Method45(); // not used here
    virtual long __stdcall Method46(); // not used here
    virtual long __stdcall Method47(); // not used here
    virtual long __stdcall Method48(); // not used here
    virtual long __stdcall Method49(); // not used here
    virtual long __stdcall Method50(); // not used here
    virtual long __stdcall Method51(); // not used here
    virtual long __stdcall Method52(); // not used here
    virtual long __stdcall Method53(); // not used here
    virtual long __stdcall Method54(); // not used here
    virtual long __stdcall Method55(); // not used here
    virtual long __stdcall Method56(); // not used here
    virtual long __stdcall Method57(); // not used here
    virtual long __stdcall Method58(); // not used here
    virtual long __stdcall Method59(); // not used here
    virtual long __stdcall Method60(); // not used here
    virtual long __stdcall Method61(); // not used here
    virtual long __stdcall Method62(); // not used here
    virtual long __stdcall Method63(); // not used here
    virtual long __stdcall Method64(); // not used here
    virtual long __stdcall Method65(); // not used here
    virtual long __stdcall Method66(); // not used here
    virtual long __stdcall Method67(); // not used here
    virtual long __stdcall Method68(); // not used here
    virtual long __stdcall Method69(); // not used here
    virtual long __stdcall Method70(); // not used here
    virtual long __stdcall Method71(); // not used here
    virtual long __stdcall Method72(); // not used here
    virtual long __stdcall Method73(); // not used here
    virtual long __stdcall Method74(); // not used here
    virtual long __stdcall CreateVertexShader(const DWORD *Declaration, const DWORD *Function, DWORD *Handle, DWORD Usage);
    virtual long __stdcall Method76(); // not used here
    virtual long __stdcall Method77(); // not used here
    virtual long __stdcall Method78(); // not used here
    virtual long __stdcall SetVertexShaderConstant(DWORD Register, const void *ConstantData, DWORD ConstantCount);
    virtual long __stdcall Method80(); // not used here
    virtual long __stdcall Method81(); // not used here
    virtual long __stdcall Method82(); // not used here
    virtual long __stdcall Method83(); // not used here
    virtual long __stdcall Method84(); // not used here
    virtual long __stdcall Method85(); // not used here
    virtual long __stdcall Method86(); // not used here
    virtual long __stdcall CreatePixelShader(const DWORD *Function, DWORD *Handle);
};


extern "C" HRESULT __stdcall D3DXAssembleShader(const void *SrcData, unsigned int SrcDataLen, DWORD Flags,
    ID3DXBuffer **Constants, ID3DXBuffer **CompiledShader, ID3DXBuffer **CompilationErrors);
extern "C" __declspec(dllimport) void __stdcall DebugBreak();
extern "C" unsigned int strlen(const char *);
#pragma intrinsic(strlen)

struct FPlane
{
    FLOAT X, Y, Z, W;
    FPlane(FLOAT InX, FLOAT InY, FLOAT InZ, FLOAT InW) : X(InX), Y(InY), Z(InZ), W(InW) {}
};

// Object returned by the lookup at 0x5b7d0 (unnamed).
struct UnnamedResource_5f6b0
{
    char Pad[0x2c];
    INT Field2C;
    INT Field30;
};
struct UnnamedCacheItem_5f6b0
{
    virtual void Slot0();
    virtual UnnamedResource_5f6b0 *GetResource();
};

class UD3DRenderDevice
{
public:
    virtual UBOOL VirtualSlot32_5f6b0(INT A, INT B); // reflected vtable slot 32 (name unknown)
    void SetDefaultShaderConstants();
    void CreateVertexShaderFromAsm(const char *Source, DWORD *Handle, DWORD Usage, const DWORD *Declaration);
    void CreatePixelShaderFromAsm(const char *Source, DWORD *Handle);
    void CreatePixelShaderFromCode(DWORD *Handle, const DWORD *Function);
    char Pad[0x46a0];
    IDirect3DDevice8 *Direct3DDevice8; // 0x46a4
};

UnnamedCacheItem_5f6b0 *__stdcall FindCacheItem_5b7d0(UD3DRenderDevice *Device, INT A, INT B);

// 0x5f6b0
UBOOL UD3DRenderDevice::VirtualSlot32_5f6b0(INT A, INT B)
{
    UnnamedCacheItem_5f6b0 *Item = FindCacheItem_5b7d0(this, A, B);
    if (!Item)
        return 0;
    UnnamedResource_5f6b0 *Res = Item->GetResource();
    if (Res && !Res->Field2C && !Res->Field30)
        return 0;
    return 1;
}

// 0x5f6f0
void UD3DRenderDevice::SetDefaultShaderConstants()
{
    FPlane Half(0.5f, 0.5f, 0.5f, 0.5f);
    Direct3DDevice8->SetVertexShaderConstant(3, &Half, 1);
    FPlane Two(2.0f, 2.0f, 2.0f, 2.0f);
    Direct3DDevice8->SetVertexShaderConstant(2, &Two, 1);
    FPlane Zero(0.0f, 0.0f, 0.0f, 0.0f);
    Direct3DDevice8->SetVertexShaderConstant(0, &Zero, 1);
    FPlane One(1.0f, 1.0f, 1.0f, 1.0f);
    Direct3DDevice8->SetVertexShaderConstant(1, &One, 1);
}

// 0x5f7e0
void UD3DRenderDevice::CreateVertexShaderFromAsm(const char *Source, DWORD *Handle, DWORD Usage, const DWORD *Declaration)
{
    if (Handle && *Handle == 0xFFFFFFFF)
    {
        ID3DXBuffer *Shader = 0;
        ID3DXBuffer *Errors = 0;
        if (D3DXAssembleShader(Source, strlen(Source), 0, 0, &Shader, &Errors) < 0)
        {
            Errors->GetBufferPointer();
            DebugBreak();
        }
        if (Errors) { Errors->Release(); Errors = 0; }
        if (Direct3DDevice8->CreateVertexShader(Declaration, (DWORD *)Shader->GetBufferPointer(), Handle, Usage) < 0)
            DebugBreak();
        if (Shader) { Shader->Release(); Shader = 0; }
        if (Errors) { Errors->Release(); Errors = 0; }
    }
}

// 0x5f8c0
void UD3DRenderDevice::CreatePixelShaderFromAsm(const char *Source, DWORD *Handle)
{
    if (Handle && *Handle == 0xFFFFFFFF)
    {
        ID3DXBuffer *Shader = 0;
        ID3DXBuffer *Errors = 0;
        if (D3DXAssembleShader(Source, strlen(Source), 0, 0, &Shader, &Errors) < 0)
        {
            Errors->GetBufferPointer();
            DebugBreak();
        }
        if (Errors) { Errors->Release(); Errors = 0; }
        if (Direct3DDevice8->CreatePixelShader((DWORD *)Shader->GetBufferPointer(), Handle) < 0)
            DebugBreak();
        if (Shader) { Shader->Release(); Shader = 0; }
        if (Errors) { Errors->Release(); Errors = 0; }
    }
}

// 0x5f990
void UD3DRenderDevice::CreatePixelShaderFromCode(DWORD *Handle, const DWORD *Function)
{
    if (Direct3DDevice8->CreatePixelShader(Function, Handle) < 0)
        DebugBreak();
}

// Scaffolding for the LTCG link, not part of the unit.
extern const char ShaderSourceA[], ShaderSourceB[], ShaderSourceC[];
extern DWORD ShaderHandles[8];
extern const DWORD ShaderDecls[8];
extern const DWORD ShaderCodes[8];
void Driver_5f6f0(UD3DRenderDevice *D) { D->SetDefaultShaderConstants(); }
void Driver_5f7e0(UD3DRenderDevice *D)
{
    D->CreateVertexShaderFromAsm(ShaderSourceA, &ShaderHandles[0], 0, &ShaderDecls[0]);
    D->CreateVertexShaderFromAsm(ShaderSourceB, &ShaderHandles[1], 1, &ShaderDecls[1]);
    D->CreateVertexShaderFromAsm(ShaderSourceC, &ShaderHandles[2], 0, &ShaderDecls[2]);
}
void Driver_5f8c0(UD3DRenderDevice *D)
{
    D->CreatePixelShaderFromAsm(ShaderSourceA, &ShaderHandles[3]);
    D->CreatePixelShaderFromAsm(ShaderSourceB, &ShaderHandles[4]);
    D->CreatePixelShaderFromAsm(ShaderSourceC, &ShaderHandles[5]);
}
struct UnnamedShaderOwner { char Pad[0x30f00]; DWORD Handles[64]; };
// Retail does not inline it into its caller at 0x5d260 (35 calls in a row).
#pragma inline_depth(0)
void Driver_5f990(UD3DRenderDevice *D, UnnamedShaderOwner *O)
{
    D->CreatePixelShaderFromCode(&O->Handles[0], &ShaderCodes[0]);
    D->CreatePixelShaderFromCode(&O->Handles[1], &ShaderCodes[1]);
    D->CreatePixelShaderFromCode(&O->Handles[2], &ShaderCodes[2]);
    D->CreatePixelShaderFromCode(&O->Handles[3], &ShaderCodes[3]);
}
