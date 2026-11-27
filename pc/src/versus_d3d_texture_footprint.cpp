#include "versus_d3d_texture.h"

INT GetFormatBPP(D3DFORMAT format)
{
    switch (format) {
    case D3DFMT_R8G8B8:
        return 24;
    case D3DFMT_A8R8G8B8:
    case D3DFMT_X8R8G8B8:
    case D3DFMT_X8L8V8U8:
    case D3DFMT_Q8W8V8U8:
    case D3DFMT_V16U16:
    case D3DFMT_W11V11U10:
    case D3DFMT_D32:
    case D3DFMT_D24S8:
    case D3DFMT_D24X8:
    case D3DFMT_D24X4S4:
        return 32;
    case D3DFMT_R5G6B5:
    case D3DFMT_X1R5G5B5:
    case D3DFMT_A1R5G5B5:
    case D3DFMT_A4R4G4B4:
    case D3DFMT_A8R3G3B2:
    case D3DFMT_X4R4G4B4:
    case D3DFMT_A8P8:
    case D3DFMT_A8L8:
    case D3DFMT_V8U8:
    case D3DFMT_L6V5U5:
    case D3DFMT_D16_LOCKABLE:
    case D3DFMT_D15S1:
    case D3DFMT_D16:
        return 16;
    case D3DFMT_R3G3B2:
    case D3DFMT_A8:
    case D3DFMT_P8:
    case D3DFMT_L8:
    case D3DFMT_A4L4:
        return 8;
    case D3DFMT_DXT1:
        return 4;
    case D3DFMT_DXT2:
    case D3DFMT_DXT3:
    case D3DFMT_DXT4:
    case D3DFMT_DXT5:
        return 8;
    default:
        return 0;
    }
}

INT FD3DTexture::CalculateFootprint()
{
    INT bytes = 0;
    for (INT mip = CachedFirstMip; mip < CachedMipCount; ++mip) {
        const INT rowBytes = (CachedWidth >> mip) * GetFormatBPP(CachedFormat) / 8;
        bytes += rowBytes * (CachedHeight >> mip);
    }
    return bytes;
}
