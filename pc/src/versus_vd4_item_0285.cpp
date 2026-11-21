// Work item 0285: Versus RVA 0x6d6f0, 0x6d930, 0x6d960 (LTCG, register conventions).
// D3D render-interface texture stage setup. The stage-state constants are the
// Direct3D ones (D3DTTFF_COUNT2..4, D3DTTFF_PROJECTED, D3DTSS_TCI_CAMERASPACE*),
// and the modifier fields follow the UE2 FTexModifierInfo. Other class and field
// names are neutral.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

struct FMatrix
{
    FLOAT M[4][4];
    UBOOL operator==(const FMatrix &Other) const;   // retail 0x74860, not in this unit
    static FMatrix Identity;                          // retail 0xcc9560
};

// Retail 0x74860 (another unit). Defined here so the link gives it the same
// register convention (this in ECX, Other in EAX).
__declspec(noinline) UBOOL FMatrix::operator==(const FMatrix &Other) const
{
    for (INT X = 0; X < 4; X++)
        for (INT Y = 0; Y < 4; Y++)
            if (M[X][Y] != Other.M[X][Y])
                return 0;
    return 1;
}

extern "C" FMatrix *__stdcall D3DXMatrixInverse(FMatrix *Out, FLOAT *Determinant, const FMatrix *M);
extern "C" FMatrix *__stdcall D3DXMatrixMultiply(FMatrix *Out, const FMatrix *A, const FMatrix *B);
extern "C" FMatrix *__stdcall D3DXMatrixTranspose(FMatrix *Out, const FMatrix *M);

// UE2 ETexCoordSrc.
enum ETexCoordSrc
{
    TCS_Stream0, TCS_Stream1, TCS_Stream2, TCS_Stream3,
    TCS_Stream4, TCS_Stream5, TCS_Stream6, TCS_Stream7,
    TCS_WorldCoords, TCS_CameraCoords, TCS_WorldEnvMapCoords,
    TCS_CameraEnvMapCoords, TCS_ProjectorCoords, TCS_NoChange
};

struct FTexModifierInfo
{
    UBOOL ModifyTextureTransforms;  // 0x00
    INT Pad04[3];
    FMatrix Matrix;                 // 0x10
    BYTE TexCoordSource;            // 0x50
    BYTE TexCoordCount;             // 0x51
    BYTE Pad52[2];
    UBOOL TexCoordProjected;        // 0x54
};

// Per-stage state block (neutral name).
struct FD3DStageState
{
    void *Texture;          // 0x00
    INT AddressU;           // 0x04
    INT AddressV;           // 0x08
    INT AddressW;           // 0x0c
    INT Pad10;
    INT ColorOp;            // 0x14
    INT ColorArg1;          // 0x18
    INT ColorArg2;          // 0x1c
    INT AlphaArg1;          // 0x20
    INT AlphaArg2;          // 0x24
    INT AlphaOp;            // 0x28
    INT Pad2C;
    INT TexCoordIndex;      // 0x30
    INT TextureTransformFlags; // 0x34
    UBOOL UseMatrix;        // 0x38
    FMatrix Matrix;         // 0x3c
};

struct UnnamedTransforms_2af10
{
    BYTE Pad[0x78];
    FMatrix View;           // 0x78
};

struct UnnamedRenderInterface_6d6f0
{
    BYTE Pad[0x2af10];
    UnnamedTransforms_2af10 *Transforms; // 0x2af10

    void SetTexModifier(FTexModifierInfo *Info, FD3DStageState *Stage);
};

__declspec(noinline) void UnnamedRenderInterface_6d6f0::SetTexModifier(FTexModifierInfo *Info, FD3DStageState *Stage)
{
    if (!Info->ModifyTextureTransforms)
        return;

    switch (Info->TexCoordCount)
    {
    case 0: Stage->TextureTransformFlags = 2; break;
    case 1: Stage->TextureTransformFlags = 3; break;
    case 2: Stage->TextureTransformFlags = 4; break;
    }
    if (Info->TexCoordProjected)
        Stage->TextureTransformFlags |= 0x100;

    switch (Info->TexCoordSource)
    {
    case TCS_NoChange:
        Stage->TexCoordIndex = 0;
        Stage->UseMatrix = 0;
        break;
    case TCS_Stream0: case TCS_Stream1: case TCS_Stream2: case TCS_Stream3:
    case TCS_Stream4: case TCS_Stream5: case TCS_Stream6: case TCS_Stream7:
        Stage->TexCoordIndex = Info->TexCoordSource;
        if (!Info->TexCoordProjected && Info->Matrix == FMatrix::Identity)
            Stage->UseMatrix = 0;
        else
        {
            Stage->Matrix = Info->Matrix;
            Stage->UseMatrix = 1;
        }
        break;
    case TCS_WorldCoords:
    {
        FMatrix Inverse, Combined;
        D3DXMatrixInverse(&Inverse, 0, &Transforms->View);
        if (!(Info->Matrix == FMatrix::Identity))
        {
            D3DXMatrixMultiply(&Combined, &Inverse, &Info->Matrix);
            Stage->Matrix = Combined;
        }
        else
            Stage->Matrix = Inverse;
        Stage->UseMatrix = 1;
        Stage->TexCoordIndex = 0x20000;
        break;
    }
    case TCS_CameraCoords:
        if (!(Info->Matrix == FMatrix::Identity))
        {
            Stage->Matrix = Info->Matrix;
            Stage->UseMatrix = 1;
        }
        else
            Stage->UseMatrix = 0;
        Stage->TexCoordIndex = 0x20000;
        break;
    case TCS_WorldEnvMapCoords:
    {
        FMatrix Temp;
        if (!(Info->Matrix == FMatrix::Identity))
        {
            D3DXMatrixMultiply(&Temp, &Transforms->View, &Info->Matrix);
            D3DXMatrixTranspose(&Temp, &Temp);
        }
        else
            D3DXMatrixTranspose(&Temp, &Transforms->View);
        Stage->Matrix = Temp;
        Stage->UseMatrix = 1;
        Stage->TexCoordIndex = 0x30000;
        break;
    }
    case TCS_CameraEnvMapCoords:
        if (!(Info->Matrix == FMatrix::Identity))
        {
            Stage->Matrix = Info->Matrix;
            Stage->UseMatrix = 1;
        }
        else
            Stage->UseMatrix = 0;
        Stage->TexCoordIndex = 0x30000;
        break;
    }
}

// ---- 0x6d360 (item 0284) and the two stage presets that call it ----

struct UnnamedBaseTexture
{
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32(); virtual void Slot33(); virtual void Slot34();
    virtual void *GetRenderInterface();                         // 0x8c
    virtual UnnamedBaseTexture *Get(INT A, INT B, void *Owner); // 0x90
    BYTE Pad04[0x59];
    BYTE UClampMode;   // 0x5d
    BYTE VClampMode;   // 0x5e
};

struct UnnamedCachedTexture
{
    BYTE Pad[0x30];
    INT IsRenderTarget;     // 0x30
};

struct UnnamedClient_108 { BYTE Pad[0x4658]; INT DefaultAddress; };
struct UnnamedViewport_10c { BYTE Pad[0x130]; INT X; INT Y; };

struct UnnamedD3DDevice
{
    BYTE Pad[0x108];
    UnnamedClient_108 *Client;      // 0x108
    UnnamedViewport_10c *Viewport;  // 0x10c
};

UnnamedCachedTexture *__stdcall CacheTexture_620f0(UnnamedD3DDevice *Device, void *Interface);

__declspec(noinline) void SetStageTexture_6d360(UnnamedD3DDevice *Device, UnnamedBaseTexture *Texture, FD3DStageState *Stage)
{
    if (!Texture)
    {
        Stage->Texture = 0;
        return;
    }
    UnnamedViewport_10c *Viewport = Device->Viewport;
    UnnamedCachedTexture *Cached = CacheTexture_620f0(Device,
        Texture->Get(Viewport->X, Viewport->Y, Viewport)->GetRenderInterface());
    Stage->Texture = Cached;
    if (Cached->IsRenderTarget)
    {
        Stage->AddressU = Device->Client->DefaultAddress;
        Stage->AddressV = Device->Client->DefaultAddress;
        Stage->AddressW = Device->Client->DefaultAddress;
        return;
    }
    switch (Texture->UClampMode)
    {
    case 0: Stage->AddressU = 1; break;
    case 1: Stage->AddressU = 3; break;
    }
    switch (Texture->VClampMode)
    {
    case 0: Stage->AddressV = 1; break;
    case 1: Stage->AddressV = 3; break;
    }
    Stage->AddressW = Device->Client->DefaultAddress;
}

__declspec(noinline) void SetStageModulate_6d930(UnnamedD3DDevice *Device, UnnamedBaseTexture *Texture, FD3DStageState *Stage)
{
    SetStageTexture_6d360(Device, Texture, Stage);
    Stage->AlphaOp = 1;
    Stage->ColorArg1 = 2;
    Stage->AlphaArg1 = 2;
    Stage->AlphaArg2 = 1;
    Stage->ColorOp = 0x10;
}

__declspec(noinline) void __stdcall SetStageBlend_6d960(UnnamedD3DDevice *Device, UnnamedBaseTexture *Texture, FD3DStageState *Stage, UBOOL A, UBOOL B)
{
    SetStageTexture_6d360(Device, Texture, Stage);
    Stage->AlphaOp = 1;
    Stage->ColorArg1 = 2;
    if (!A)
    {
        Stage->ColorOp = 7;
        Stage->AlphaArg1 = 1;
        Stage->AlphaArg2 = 2;
        return;
    }
    if (B)
    {
        Stage->AlphaArg1 = 3;
        Stage->ColorArg2 = 1;
        Stage->ColorOp = 0x19;
        Stage->AlphaArg2 = 2;
        return;
    }
    Stage->ColorOp = 0x12;
    Stage->AlphaArg1 = 1;
    Stage->AlphaArg2 = 2;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_6d6f0(UnnamedRenderInterface_6d6f0 *RI, FTexModifierInfo *Info, FD3DStageState *Stage)
{
    Escape(&FMatrix::Identity);
    RI->SetTexModifier(Info, Stage);
}
void Driver_6d930(UnnamedD3DDevice *Device, UnnamedBaseTexture *Texture, FD3DStageState *Stage, UBOOL A, UBOOL B)
{
    SetStageModulate_6d930(Device, Texture, Stage);
    SetStageBlend_6d960(Device, Texture, Stage + 1, A, B);
}
