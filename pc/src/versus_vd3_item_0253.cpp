// UD3DRenderDevice vtable slots 39 and 40 (Direct3D 8 renderer).
// Member names follow UE2 D3DDrv conventions; offsets from retail.
typedef unsigned long DWORD;
typedef int INT;
typedef DWORD UBOOL;
typedef unsigned char BYTE;

struct D3DCAPS8
{
    DWORD Pad0[37];
    DWORD MaxTextureBlendStages;    // 0x94
    DWORD MaxSimultaneousTextures;  // 0x98
    DWORD Pad1[12];
    DWORD PixelShaderVersion;       // 0xcc
    DWORD Pad2;
};

struct IDirect3D8
{
    virtual long __stdcall QueryInterface(void *, void **) = 0;
    virtual unsigned long __stdcall AddRef() = 0;
    virtual unsigned long __stdcall Release() = 0;
    virtual long __stdcall RegisterSoftwareDevice(void *) = 0;
    virtual unsigned int __stdcall GetAdapterCount() = 0;
    virtual long __stdcall GetAdapterIdentifier(unsigned int, DWORD, void *) = 0;
    virtual unsigned int __stdcall GetAdapterModeCount(unsigned int) = 0;
    virtual long __stdcall EnumAdapterModes(unsigned int, unsigned int, void *) = 0;
    virtual long __stdcall GetAdapterDisplayMode(unsigned int, void *) = 0;
    virtual long __stdcall CheckDeviceType(unsigned int, INT, INT, INT, INT) = 0;
    virtual long __stdcall CheckDeviceFormat(unsigned int, INT, INT, DWORD, INT, INT) = 0;
    virtual long __stdcall CheckDeviceMultiSampleType(unsigned int, INT, INT, INT, INT) = 0;
    virtual long __stdcall CheckDepthStencilMatch(unsigned int, INT, INT, INT, INT) = 0;
    virtual long __stdcall GetDeviceCaps(unsigned int Adapter, INT DeviceType, D3DCAPS8 *Caps) = 0;
};

struct FRenderCaps
{
    INT   MaxSimultaneousTextures;  // tier, 1..3
    INT   PixelShaderVersion;
    UBOOL HardwareTL;
};

// Free functions called after the mode change (unnamed in retail).
void FUN_10997520();
void FUN_10960200();

class UD3DRenderDevice
{
public:
    BYTE        Pad0[0x40d8 - 4];   // after the vtable pointer
    UBOOL       UseHardwareTL;          // 0x40d8
    BYTE        Pad1[0x40fc - 0x40dc];
    UBOOL       UseCubemaps;            // 0x40fc (neutral name)
    BYTE        Pad2[0x41d0 - 0x4100];
    DWORD       MaxTextureBlendStages;  // 0x41d0
    DWORD       MaxSimultaneousTextures;// 0x41d4
    BYTE        Pad3[0x4664 - 0x41d8];
    INT         PixelShaderVersion;     // 0x4664
    BYTE        Pad4[0x4678 - 0x4668];
    DWORD       Adapter;                // 0x4678
    BYTE        Pad5[0x46a0 - 0x467c];
    IDirect3D8 *Direct3D8;              // 0x46a0

    virtual void SetDetailLevel(INT Level);
    virtual FRenderCaps *GetRenderCaps();
};

void UD3DRenderDevice::SetDetailLevel(INT Level)
{
    D3DCAPS8 Caps;
    Direct3D8->GetDeviceCaps(Adapter, 1, &Caps);
    if (Caps.MaxTextureBlendStages > 8)
        Caps.MaxTextureBlendStages = 8;
    if (Caps.MaxSimultaneousTextures > 8)
        Caps.MaxSimultaneousTextures = 8;
    MaxSimultaneousTextures = Caps.MaxSimultaneousTextures;
    MaxTextureBlendStages = Caps.MaxTextureBlendStages;
    PixelShaderVersion = ((Caps.PixelShaderVersion >> 8) * 10 + Caps.PixelShaderVersion) & 0xff;
    switch (Level)
    {
    case 1:
        MaxSimultaneousTextures = 2;
        MaxTextureBlendStages = 3;
        PixelShaderVersion = 0;
        break;
    case 2:
        MaxSimultaneousTextures = 4;
        MaxTextureBlendStages = 4;
        break;
    }
    FUN_10997520();
    FUN_10960200();
}

// Was a function-local static FRenderCaps and its compiler guard.
extern FRenderCaps GetRenderCaps_Caps;
extern DWORD GetRenderCaps_Guard;

FRenderCaps *UD3DRenderDevice::GetRenderCaps()
{
    if (!(GetRenderCaps_Guard & 1))
    {
        GetRenderCaps_Guard |= 1;
        GetRenderCaps_Caps.MaxSimultaneousTextures = 1;
        GetRenderCaps_Caps.PixelShaderVersion = 0;
        GetRenderCaps_Caps.HardwareTL = 0;
    }
    if (PixelShaderVersion >= 14)
        GetRenderCaps_Caps.MaxSimultaneousTextures = 3;
    else if (PixelShaderVersion >= 11)
        GetRenderCaps_Caps.MaxSimultaneousTextures = 3;
    else if (MaxSimultaneousTextures >= 7 && UseCubemaps)
        GetRenderCaps_Caps.MaxSimultaneousTextures = 3;
    else if (MaxSimultaneousTextures >= 4 && !UseCubemaps)
        GetRenderCaps_Caps.MaxSimultaneousTextures = 2;
    else if (MaxSimultaneousTextures >= 2)
        GetRenderCaps_Caps.MaxSimultaneousTextures = 1;
    GetRenderCaps_Caps.PixelShaderVersion = PixelShaderVersion;
    GetRenderCaps_Caps.HardwareTL = UseHardwareTL;
    return &GetRenderCaps_Caps;
}
