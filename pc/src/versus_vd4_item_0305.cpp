// Work item 0305: Versus RVA 0x7ebc0-0x7eeae.
// Type and member names are neutral: the evidence does not name these classes.

struct UnnamedSettings_7ebc0 {
    char Pad0[0x30e48];
    int ValueA;     // 0x30e48
    int Pad1;
    int ValueB;     // 0x30e50
};
struct UnnamedFlags_7ebc0 {
    char Pad0[0x34];
    unsigned char Flags;    // 0x34
};
struct UnnamedPage_7ebc0 {
    char Pad0[0x414];
    int Value;      // 0x414
};
struct UnnamedMenu_7ebc0 {
    char Pad0[0x534];
    UnnamedPage_7ebc0 *Pages[1]; // 0x534
};
struct UnnamedOwner_7ebc0 {
    char Pad0[0x18];
    UnnamedFlags_7ebc0 *Flags;      // 0x18
    char Pad1[0x108 - 0x1c];
    UnnamedSettings_7ebc0 *Settings; // 0x108
    char Pad2[0x2af10 - 0x10c];
    UnnamedMenu_7ebc0 *Menu;        // 0x2af10
};

extern int GVersusGameMode;     // 0x10c78b74
void __stdcall Unnamed_7dbd0(UnnamedOwner_7ebc0 *Owner);

void __stdcall Unnamed_7ebc0(UnnamedOwner_7ebc0 *Owner)
{
    Unnamed_7dbd0(Owner);
    if (GVersusGameMode == 0x15) {
        if ((Owner->Flags->Flags & 0xc) == 0)
            Owner->Menu->Pages[0]->Value = Owner->Settings->ValueA;
        else
            Owner->Menu->Pages[0]->Value = Owner->Settings->ValueB;
    }
}

// ---------------------------------------------------------------------------
// 0x7ec30 and 0x7ed70: D3D render-interface material stages (LTCG, register
// conventions). The stage-state block follows item 0285; FD3DModifierInfo is
// the 0x84-byte modifier block passed by value (FTexModifierInfo plus extras).
// Other class and field names are neutral.

typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;
typedef unsigned char BYTE;

struct FMatrix
{
    FLOAT M[4][4];
    UBOOL operator==(const FMatrix &Other) const;   // retail 0x74860
    static FMatrix Identity;                          // retail 0xcc9560
};

// Retail 0x74860 (another unit), defined so the link gives it its convention.
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

enum ETexCoordSrc
{
    TCS_Stream0, TCS_Stream1, TCS_Stream2, TCS_Stream3,
    TCS_Stream4, TCS_Stream5, TCS_Stream6, TCS_Stream7,
    TCS_WorldCoords, TCS_CameraCoords, TCS_WorldEnvMapCoords,
    TCS_CameraEnvMapCoords, TCS_ProjectorCoords, TCS_NoChange
};

struct UMaterial;

struct FD3DModifierInfo
{
    UBOOL ModifyTextureTransforms;  // 0x00
    INT Pad04[3];
    FMatrix Matrix;                 // 0x10
    BYTE TexCoordSource;            // 0x50
    BYTE TexCoordCount;             // 0x51
    BYTE Pad52[2];
    UBOOL TexCoordProjected;        // 0x54
    INT Pad58[8];
    UMaterial *Modifier;            // 0x78
    INT Pad7C[2];
};

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
    INT Unknown2C;          // 0x2c
    INT TexCoordIndex;      // 0x30
    INT TextureTransformFlags; // 0x34
    UBOOL UseMatrix;        // 0x38
    FMatrix Matrix;         // 0x3c
};

struct FD3DPass
{
    BYTE Pad[0x30];
    INT StagesUsed;                 // 0x30
    FD3DStageState Stages[8];       // 0x34, 0x7c each
};

struct FD3DDeviceState
{
    BYTE Pad[0x78];
    FMatrix View;                   // 0x78
    BYTE PadB8[0x198 - 0xb8];
    INT UseTFactor;                 // 0x198
    BYTE Pad19C[0x534 - 0x19c];
    FD3DPass *Passes[8];            // 0x534
};

struct UClass;
struct UMaterial
{
    virtual void Slot00(); virtual void Slot01(); virtual void Slot02(); virtual void Slot03();
    virtual void Slot04(); virtual void Slot05(); virtual void Slot06(); virtual void Slot07();
    virtual void Slot08(); virtual void Slot09(); virtual void Slot10(); virtual void Slot11();
    virtual void Slot12(); virtual void Slot13(); virtual void Slot14(); virtual void Slot15();
    virtual void Slot16(); virtual void Slot17(); virtual void Slot18(); virtual void Slot19();
    virtual void Slot20(); virtual void Slot21(); virtual void Slot22(); virtual void Slot23();
    virtual void Slot24(); virtual void Slot25(); virtual void Slot26(); virtual void Slot27();
    virtual void Slot28(); virtual void Slot29(); virtual void Slot30(); virtual void Slot31();
    virtual void Slot32();
    virtual UMaterial *CheckFallback();                         // 0x84
    virtual UBOOL Slot34();                                     // 0x88
    virtual void *GetRenderInterface();                         // 0x8c
    virtual UMaterial *Get(INT A, INT B, void *Owner);          // 0x90
    BYTE Pad04[0x20];
    UClass *Class;          // 0x24
    BYTE Pad28[0x35];
    BYTE UClampMode;        // 0x5d
    BYTE VClampMode;        // 0x5e
};
struct UClass
{
    BYTE Pad[0x28];
    UClass *SuperClass;     // 0x28
};

inline UBOOL IsA(UMaterial *M, UClass *C)
{
    for (UClass *Cls = M->Class; Cls; Cls = Cls->SuperClass)
        if (Cls == C)
            return 1;
    return 0;
}

inline UMaterial *Resolve(UMaterial *M, UBOOL UseFallback)
{
    return (UseFallback && M) ? M->CheckFallback() : M;
}

struct UnnamedCachedTexture
{
    BYTE Pad[0x30];
    INT IsRenderTarget;     // 0x30
};

struct UnnamedClient_108
{
    BYTE Pad[0x41d4];
    INT MaxTextureStages;   // 0x41d4
    BYTE Pad41D8[0x4658 - 0x41d8];
    INT DefaultAddress;     // 0x4658
};
struct UnnamedLevel_1a0 { BYTE Pad[0x348]; UMaterial *DefaultTexture; };
struct UnnamedActor_30 { BYTE Pad[0x1a0]; UnnamedLevel_1a0 *Level; };
struct UnnamedViewport_10c
{
    BYTE Pad[0x30];
    UnnamedActor_30 *Actor; // 0x30
    BYTE Pad34[0x130 - 0x34];
    INT X;                  // 0x130
    INT Y;                  // 0x134
};

struct FD3DRenderInterface
{
    BYTE Pad[0x108];
    UnnamedClient_108 *Client;      // 0x108
    UnnamedViewport_10c *Viewport;  // 0x10c
    BYTE Pad110[0x2af10 - 0x110];
    FD3DDeviceState *State;         // 0x2af10

    void SetTexModifier(FD3DModifierInfo *Info, FD3DStageState *Stage);
    void SetDetailStage(void *Unused, UMaterial *Material, FD3DModifierInfo ModifierInfo);
};

extern UClass *UBitmapMaterial_StaticClass;
extern UClass *UModifier_StaticClass;
extern UClass *UConstantMaterial_StaticClass;

// Retail 0x73830 and 0x74100 (another unit): UE2's CheckMaterial<T>, which
// resolves fallbacks, accepts a T directly, or walks a modifier chain down to a
// T while folding each modifier into ModifierInfo. Body abridged; defined only
// so the link gives these their register convention (Material in EAX,
// ModifierInfo in EDI, RI and UseFallback on the stack; UseFallback is
// declared volatile only to keep it on the stack as retail does).
struct FModifierFields
{
    BYTE Pad[0x4c];
    UMaterial *Material;    // 0x4c
    BYTE TexCoordSource;    // 0x50
    BYTE TexCoordCount;     // 0x51
    BYTE Pad52[2];
    DWORD Flags;            // 0x54
    BYTE Extra;             // 0x58
};
extern UClass *UTexModifier_StaticClass;
struct UnnamedLevel_3b0 { BYTE Pad[0x3b0]; void *TimeSource; };

__declspec(noinline) UMaterial *CheckBitmapMaterial_73830(FD3DRenderInterface *RI, UMaterial *Material, FD3DModifierInfo *ModifierInfo, volatile UBOOL UseFallback)
{
    UMaterial *M = Resolve(Material, UseFallback);
    if (M && IsA(M, UBitmapMaterial_StaticClass))
        return M;
    UMaterial *Result = 0;
    M = Resolve(Material, UseFallback);
    while (M && IsA(M, UModifier_StaticClass))
    {
        FModifierFields *Mod = (FModifierFields *)M;
        UMaterial *Inner = Resolve(Mod->Material, UseFallback);
        if (Inner && IsA(Inner, UBitmapMaterial_StaticClass))
            Result = Inner;
        if (ModifierInfo && IsA(M, UTexModifier_StaticClass))
        {
            if (M->Get(0, 0, ((UnnamedLevel_3b0 *)RI->Viewport->Actor->Level)->TimeSource))
                ModifierInfo->ModifyTextureTransforms = 1;
            ModifierInfo->TexCoordSource = Mod->TexCoordSource;
            ModifierInfo->TexCoordCount = Mod->TexCoordCount;
            ModifierInfo->TexCoordProjected = Mod->Flags & 1;
        }
        M = Resolve(Mod->Material, UseFallback);
    }
    return Result;
}

__declspec(noinline) UMaterial *CheckConstantMaterial_74100(FD3DRenderInterface *RI, UMaterial *Material, FD3DModifierInfo *ModifierInfo, volatile UBOOL UseFallback)
{
    UMaterial *M = Resolve(Material, UseFallback);
    if (M && IsA(M, UConstantMaterial_StaticClass))
        return M;
    UMaterial *Result = 0;
    M = Resolve(Material, UseFallback);
    while (M && IsA(M, UModifier_StaticClass))
    {
        FModifierFields *Mod = (FModifierFields *)M;
        UMaterial *Inner = Resolve(Mod->Material, UseFallback);
        if (Inner && IsA(Inner, UConstantMaterial_StaticClass))
            Result = Inner;
        if (ModifierInfo && IsA(M, UTexModifier_StaticClass))
        {
            if (M->Get(0, 0, ((UnnamedLevel_3b0 *)RI->Viewport->Actor->Level)->TimeSource))
                ModifierInfo->ModifyTextureTransforms = 1;
            ModifierInfo->TexCoordSource = Mod->TexCoordSource;
            ModifierInfo->TexCoordCount = Mod->TexCoordCount;
            ModifierInfo->TexCoordProjected = Mod->Flags & 1;
        }
        M = Resolve(Mod->Material, UseFallback);
    }
    return Result;
}

// Retail 0x6d6f0 (item 0285).
__declspec(noinline) void FD3DRenderInterface::SetTexModifier(FD3DModifierInfo *Info, FD3DStageState *Stage)
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
        D3DXMatrixInverse(&Inverse, 0, &State->View);
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
            D3DXMatrixMultiply(&Temp, &State->View, &Info->Matrix);
            D3DXMatrixTranspose(&Temp, &Temp);
        }
        else
            D3DXMatrixTranspose(&Temp, &State->View);
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

UnnamedCachedTexture *__stdcall CacheTexture_620f0(FD3DRenderInterface *RI, void *Interface);

// Retail 0x6d360 (items 0284/0285).
__declspec(noinline) void SetStageTexture_6d360(FD3DRenderInterface *Device, UMaterial *Texture, FD3DStageState *Stage)
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

// RVA 0x7ec30. A static helper in retail: the first argument is unused, the
// render interface comes second, and LTCG passes Material in EAX.
UBOOL __stdcall HandleBitmapStage(void *Unused, FD3DRenderInterface *RI, UMaterial *Material, INT &PassesUsed, INT &StagesUsed, INT &StageBase, FD3DModifierInfo ModifierInfo, UBOOL InvertOutputAlpha)
{
    INT MaxStages = RI->Client->MaxTextureStages;
    if (!Material)
        return 0;

    UMaterial *Bitmap = CheckBitmapMaterial_73830(RI, Material, &ModifierInfo, 0);
    if (Bitmap)
    {
        if (StagesUsed >= StageBase + MaxStages)
            return 0;
        SetStageTexture_6d360(RI, Bitmap, &RI->State->Passes[PassesUsed]->Stages[StagesUsed]);
        RI->State->Passes[PassesUsed]->Stages[StagesUsed].AlphaOp = InvertOutputAlpha ? 0x12 : 2;
        RI->State->Passes[PassesUsed]->Stages[StagesUsed].ColorArg1 = 2;
        RI->State->Passes[PassesUsed]->Stages[StagesUsed].AlphaArg1 = 2;
        RI->State->Passes[PassesUsed]->Stages[StagesUsed].ColorOp = 2;
        RI->SetTexModifier(&ModifierInfo, &RI->State->Passes[PassesUsed]->Stages[StagesUsed]);
        StagesUsed++;
        return 1;
    }
    CheckConstantMaterial_74100(RI, Material, &ModifierInfo, 0);
    return 0;
}

// RVA 0x7ed70
void FD3DRenderInterface::SetDetailStage(void *Unused, UMaterial *Material, FD3DModifierInfo ModifierInfo)
{
    INT Stage = GVersusGameMode == 0x15 ? 5 : 3;
    INT PassesUsed = 0, StagesUsed = Stage, StageBase = 0;
    if (HandleBitmapStage(Unused, this, Material, PassesUsed, StagesUsed, StageBase, ModifierInfo, 0))
    {
        State->Passes[0]->Stages[Stage].AlphaArg2 = 1;
        State->Passes[0]->Stages[Stage].ColorOp = (State->UseTFactor != 0) + 4;
        State->Passes[0]->Stages[Stage].Unknown2C = 1;
        State->Passes[0]->Stages[Stage].ColorArg1 = 3;
    }
    else
    {
        UnnamedViewport_10c *VP = Viewport;
        UnnamedActor_30 *Actor = VP->Actor;
        State->Passes[0]->Stages[Stage].Texture = CacheTexture_620f0(this,
            Actor->Level->DefaultTexture->Get(VP->X, VP->Y, VP)->GetRenderInterface());
    }
    State->Passes[0]->StagesUsed = Stage + 1;
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_7ed70(FD3DRenderInterface *RI, void *Unused, UMaterial *Material, FD3DModifierInfo *Info)
{
    Escape(&GVersusGameMode);
    Escape(&FMatrix::Identity);
    UMaterial *M = CheckConstantMaterial_74100(RI, Material, Info, 0);
    if (M)
        RI->SetDetailStage(Unused, M, *Info);
}
