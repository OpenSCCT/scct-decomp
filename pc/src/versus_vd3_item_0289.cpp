// Work item 0289: Versus RVA 0x75ce0-0x75f98.
// Three Direct3D render-interface helpers. The owner is the D3D render
// interface (RenderDevice at +0x108, Viewport at +0x10c, current state at
// +0x2af10; see item 0252). 0x75ce0 and 0x75e20 were built with VC7.0 /GL and
// linked /LTCG, so they take the interface and arguments in registers.
// The material-state and stage layouts are neutral guesses: stages are 0x7c
// bytes, start at +0x34 of the state, and the stage count sits at +0x30. The
// texture address modes 1 and 3 are D3DTADDRESS_WRAP and D3DTADDRESS_CLAMP,
// picked from the bitmap material's UClampMode/VClampMode bytes (+0x5d/+0x5e).

typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;
typedef float FLOAT;

struct FMatrix
{
    FLOAT M[4][4];
    FMatrix() {}
    void SetZero()
    {
        M[0][0] = 0; M[0][1] = 0; M[0][2] = 0; M[0][3] = 0;
        M[1][0] = 0; M[1][1] = 0; M[1][2] = 0; M[1][3] = 0;
        M[2][0] = 0; M[2][1] = 0; M[2][2] = 0; M[2][3] = 0;
        M[3][0] = 0; M[3][1] = 0; M[3][2] = 0; M[3][3] = 0;
    }
};

struct FUnnamedStage_75ce0                  // 0x7c bytes, neutral name
{
    void *Texture;                          // +0x00
    INT AddressU;                           // +0x04
    INT AddressV;                           // +0x08
    INT AddressW;                           // +0x0c
    BYTE Pad10[0x30 - 0x10];
    INT Flags;                              // +0x30
    INT Count;                              // +0x34
    INT Enabled;                            // +0x38
    FMatrix Matrix;                         // +0x3c
};

struct FUnnamedMaterialState_75ce0          // neutral name
{
    BYTE Pad0[0x14];
    INT Value14;                            // +0x14
    BYTE Pad18[0x30 - 0x18];
    INT NumStages;                          // +0x30
    FUnnamedStage_75ce0 Stages[8];          // +0x34
};

struct FD3DRenderState
{
    BYTE Pad0[0x534];
    FUnnamedMaterialState_75ce0 *MaterialState; // +0x534
};

struct FD3DTexture
{
    BYTE Pad0[0x30];
    INT Flag30;                             // +0x30
};

class FBaseTexture;

class UBitmapMaterial
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34();
    virtual FBaseTexture *GetRenderInterface();                   // +0x8c
    virtual UBitmapMaterial *Get(INT Time0, INT Time1, void *Viewport); // +0x90
    BYTE Pad4[0x5d - 4];
    BYTE UClampMode;                        // +0x5d
    BYTE VClampMode;                        // +0x5e
};

struct FUnnamedMaterialInfo_75e20           // neutral name
{
    BYTE Pad0[0x50];
    INT TwoStages;                          // +0x50
    INT Value54;                            // +0x54
    BYTE Pad58[0x5c - 0x58];
    UBitmapMaterial *Bitmap;                // +0x5c
};

struct FUnnamedBlock_84                     // 0x84 bytes passed by value, unused here
{
    DWORD Data[0x21];
};

struct UViewport
{
    BYTE Pad0[0x130];
    INT Time0;                              // +0x130
    INT Time1;                              // +0x134
};

class IDirect3DDevice8
{
public:
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34(); virtual void Slot35();
    virtual void Slot36(); virtual void Slot37(); virtual void Slot38(); virtual void Slot39();
    virtual void Slot40(); virtual void Slot41(); virtual void Slot42(); virtual void Slot43();
    virtual void Slot44(); virtual void Slot45(); virtual void Slot46(); virtual void Slot47();
    virtual void Slot48(); virtual void Slot49();
    virtual long __stdcall SetRenderState(DWORD State, DWORD Value);   // +0xc8
};

struct UD3DRenderDevice
{
    BYTE Pad0[0x4658];
    INT DefaultAddressMode;                 // +0x4658
    BYTE Pad465c[0x46a4 - 0x465c];
    IDirect3DDevice8 *Direct3DDevice8;      // +0x46a4
};

struct FD3DRenderInterface
{
    BYTE Pad0[0x108];
    UD3DRenderDevice *RenderDevice;         // +0x108
    UViewport *Viewport;                    // +0x10c
    BYTE Pad110[0x2af10 - 0x110];
    FD3DRenderState *CurrentState;          // +0x2af10
};

// RVA 0x620f0 (declared): looks the texture up in the device cache.
FD3DTexture *__stdcall CacheTexture_620f0(FD3DRenderInterface *RI, FBaseTexture *Texture);

// RVA 0x75ce0: resets stage Index and makes it the last one.
void __fastcall ResetStage_75ce0(INT Index, FD3DRenderInterface *RI, INT Unused)
{
    FUnnamedMaterialState_75ce0 *State = RI->CurrentState->MaterialState;
    FMatrix Zero;
    Zero.SetZero();
    State->Stages[Index].Matrix = Zero;
    State->Stages[Index].Enabled = 1;
    State->Stages[Index].Matrix.M[2][0] = State->Stages[Index].Matrix.M[2][1] =
        State->Stages[Index].Matrix.M[2][2] = 0.0002f;
    State->Stages[Index].Flags = 0x20000;
    State->Stages[Index].Count = 3;
    State->Stages[Index].Texture = 0;
    State->NumStages = Index + 1;
}

// RVA 0x75dd0
struct UnnamedObject_75dd0
{
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(INT A, INT B, INT C, INT D);                   // +0x20
    BYTE Pad4[0x108 - 4];
    UD3DRenderDevice *RenderDevice;         // +0x108
};

void __stdcall SetMaterialSources_75dd0(UnnamedObject_75dd0 *Obj)
{
    Obj->RenderDevice->Direct3DDevice8->SetRenderState(0x94, 1);
    Obj->RenderDevice->Direct3DDevice8->SetRenderState(0x91, 2);
    Obj->Slot08(1, 1, 1, 1);
}

// RVA 0x75e20
static __forceinline void SetAddressModes(FD3DRenderInterface *RI, FUnnamedStage_75ce0 &Stage,
                                   FD3DTexture *Texture, UBitmapMaterial *Bitmap)
{
    if (Texture && Texture->Flag30)
    {
        Stage.AddressU = RI->RenderDevice->DefaultAddressMode;
        Stage.AddressV = RI->RenderDevice->DefaultAddressMode;
    }
    else if (Bitmap)
    {
        switch (Bitmap->UClampMode)
        {
        case 0: Stage.AddressU = 1; break;
        case 1: Stage.AddressU = 3; break;
        }
        switch (Bitmap->VClampMode)
        {
        case 0: Stage.AddressV = 1; break;
        case 1: Stage.AddressV = 3; break;
        }
    }
    Stage.AddressW = RI->RenderDevice->DefaultAddressMode;
}

void __stdcall SetTextureStages_75e20(FD3DRenderInterface *RI, INT Unused, FUnnamedMaterialInfo_75e20 *Info,
                            FUnnamedBlock_84 Block)
{
    FUnnamedMaterialState_75ce0 *State = RI->CurrentState->MaterialState;
    UBitmapMaterial *Bitmap = Info->Bitmap;
    FD3DTexture *Texture = Bitmap
        ? CacheTexture_620f0(RI, Bitmap->Get(RI->Viewport->Time0, RI->Viewport->Time1, RI->Viewport)->GetRenderInterface())
        : 0;
    INT NumStages;
    State->Stages[0].Texture = Texture;
    SetAddressModes(RI, State->Stages[0], Texture, Bitmap);
    if (!Info->TwoStages)
        NumStages = 1;
    else
    {
        State->Stages[1].Texture = Texture;
        State->Stages[1].Flags = 1;
        SetAddressModes(RI, State->Stages[1], Texture, Bitmap);
        NumStages = 2;
    }
    State->Value14 = Info->Value54;
    RI->CurrentState->MaterialState->NumStages = NumStages;
}

// Scaffolding for the link, not part of the unit.
void Driver_75ce0(FD3DRenderInterface *RI, INT X)
{
    ResetStage_75ce0(1, RI, X);
}
void Driver_75e20(FD3DRenderInterface *RI, INT X, FUnnamedMaterialInfo_75e20 *Info, FUnnamedBlock_84 *B)
{
    SetTextureStages_75e20(RI, X, Info, *B);
}
