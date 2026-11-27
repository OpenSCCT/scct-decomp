// Work item 0299: Versus RVA 0x7b110 and 0x7b350 (VC7.0 /GL, linked /LTCG).
// 0x7b110 is the UE2 FMatrix product returning by value (result pointer in
// EAX, this in EDX, Other in ECX). 0x7b350 is a D3D render-interface helper
// that unbinds every texture stage (IDirect3DDevice8 slot 0xf4 = SetTexture)
// and clears the deferred state's cached textures; names other than the UE2
// ones (FMatrix, UD3DRenderDevice, FD3DDeferredState) are neutral.

typedef unsigned long DWORD;
typedef int INT;
typedef float FLOAT;

struct FMatrix
{
    FLOAT M[4][4];

    FMatrix() {}
    FMatrix operator*(const FMatrix &Other) const;
};

// RVA 0x7b110
#include "versus_matrix_product.inl"

struct IDirect3DBaseTexture8;
struct IDirect3DDevice8
{
    virtual void __stdcall S00(); virtual void __stdcall S01(); virtual void __stdcall S02(); virtual void __stdcall S03();
    virtual void __stdcall S04(); virtual void __stdcall S05(); virtual void __stdcall S06(); virtual void __stdcall S07();
    virtual void __stdcall S08(); virtual void __stdcall S09(); virtual void __stdcall S10(); virtual void __stdcall S11();
    virtual void __stdcall S12(); virtual void __stdcall S13(); virtual void __stdcall S14(); virtual void __stdcall S15();
    virtual void __stdcall S16(); virtual void __stdcall S17(); virtual void __stdcall S18(); virtual void __stdcall S19();
    virtual void __stdcall S20(); virtual void __stdcall S21(); virtual void __stdcall S22(); virtual void __stdcall S23();
    virtual void __stdcall S24(); virtual void __stdcall S25(); virtual void __stdcall S26(); virtual void __stdcall S27();
    virtual void __stdcall S28(); virtual void __stdcall S29(); virtual void __stdcall S30(); virtual void __stdcall S31();
    virtual void __stdcall S32(); virtual void __stdcall S33(); virtual void __stdcall S34(); virtual void __stdcall S35();
    virtual void __stdcall S36(); virtual void __stdcall S37(); virtual void __stdcall S38(); virtual void __stdcall S39();
    virtual void __stdcall S40(); virtual void __stdcall S41(); virtual void __stdcall S42(); virtual void __stdcall S43();
    virtual void __stdcall S44(); virtual void __stdcall S45(); virtual void __stdcall S46(); virtual void __stdcall S47();
    virtual void __stdcall S48(); virtual void __stdcall S49(); virtual void __stdcall S50(); virtual void __stdcall S51();
    virtual void __stdcall S52(); virtual void __stdcall S53(); virtual void __stdcall S54(); virtual void __stdcall S55();
    virtual void __stdcall S56(); virtual void __stdcall S57(); virtual void __stdcall S58(); virtual void __stdcall S59();
    virtual void __stdcall S60();
    virtual long __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture8 *Texture);  // 0xf4
};

class UD3DRenderDevice;

struct FD3DDeferredState
{
    UD3DRenderDevice *RenDev;                   // +0x000
    char Pad004[0x4c8 - 0x4];
    DWORD DirtyFlags;                           // +0x4c8 (neutral)
    char Pad4cc[0xe34 - 0x4cc];
    IDirect3DBaseTexture8 *Textures[8];         // +0xe34 (neutral)

    inline void SetTexture(DWORD Stage, IDirect3DBaseTexture8 *Texture);
    inline void SetDirty(DWORD Flag) { DirtyFlags |= Flag; }
};

class UD3DRenderDevice
{
public:
    char Pad0[0x41d4];
    DWORD NumTextureStages;                     // +0x41d4 (neutral)
    char Pad41d8[0x46a4 - 0x41d8];
    IDirect3DDevice8 *Direct3DDevice8;          // +0x46a4
    char Pad46a8[0x2fb58 - 0x46a8];
    FD3DDeferredState DeferredState;            // +0x2fb58
};

class UnnamedRenderInterface_7b350
{
public:
    char Pad0[0x108];
    UD3DRenderDevice *RenDev;                   // +0x108

    void UnbindTextures();
};

// RVA 0x7b350
void UnnamedRenderInterface_7b350::UnbindTextures()
{
    for (DWORD i = 0; i < RenDev->NumTextureStages; i++)
        RenDev->DeferredState.SetTexture(i, 0);
    RenDev->DeferredState.SetDirty(0x400);
}

inline void FD3DDeferredState::SetTexture(DWORD Stage, IDirect3DBaseTexture8 *Texture)
{
    RenDev->Direct3DDevice8->SetTexture(Stage, Texture);
    Textures[Stage] = Texture;
}

// Scaffolding for the link, not part of the unit.
void Driver_7b110(FMatrix *Out, const FMatrix *A, const FMatrix *B) { *Out = *A * *B; }
void Driver_7b350(UnnamedRenderInterface_7b350 *RI) { RI->UnbindTextures(); }
