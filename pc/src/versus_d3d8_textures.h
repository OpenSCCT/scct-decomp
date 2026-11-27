#ifndef VERSUS_D3D8_TEXTURES_H
#define VERSUS_D3D8_TEXTURES_H

#include "versus_d3d8_interfaces.h"

enum _D3DFORMAT {
    D3DFMT_UNKNOWN = 0,
    D3DFMT_R8G8B8 = 20,
    D3DFMT_A8R8G8B8 = 21,
    D3DFMT_X8R8G8B8 = 22,
    D3DFMT_R5G6B5 = 23,
    D3DFMT_X1R5G5B5 = 24,
    D3DFMT_A1R5G5B5 = 25,
    D3DFMT_A4R4G4B4 = 26,
    D3DFMT_R3G3B2 = 27,
    D3DFMT_A8 = 28,
    D3DFMT_A8R3G3B2 = 29,
    D3DFMT_X4R4G4B4 = 30,
    D3DFMT_A8P8 = 40,
    D3DFMT_P8 = 41,
    D3DFMT_L8 = 50,
    D3DFMT_A8L8 = 51,
    D3DFMT_A4L4 = 52,
    D3DFMT_V8U8 = 60,
    D3DFMT_L6V5U5 = 61,
    D3DFMT_X8L8V8U8 = 62,
    D3DFMT_Q8W8V8U8 = 63,
    D3DFMT_V16U16 = 64,
    D3DFMT_W11V11U10 = 65,
    D3DFMT_D16_LOCKABLE = 70,
    D3DFMT_D32 = 71,
    D3DFMT_D15S1 = 73,
    D3DFMT_D24S8 = 75,
    D3DFMT_D24X8 = 77,
    D3DFMT_D24X4S4 = 79,
    D3DFMT_D16 = 80,
    D3DFMT_DXT1 = 0x31545844,
    D3DFMT_DXT2 = 0x32545844,
    D3DFMT_DXT3 = 0x33545844,
    D3DFMT_DXT4 = 0x34545844,
    D3DFMT_DXT5 = 0x35545844,
};
enum _D3DMULTISAMPLE_TYPE { D3DMULTISAMPLE_NONE = 0 };
enum { D3DUSAGE_RENDERTARGET = 1 };
struct D3DLOCKED_RECT { INT Pitch; void *pBits; };
struct D3DSURFACE_DESC;
enum D3DCUBEMAP_FACES {
    D3DCUBEMAP_FACE_POSITIVE_X, D3DCUBEMAP_FACE_NEGATIVE_X,
    D3DCUBEMAP_FACE_POSITIVE_Y, D3DCUBEMAP_FACE_NEGATIVE_Y,
    D3DCUBEMAP_FACE_POSITIVE_Z, D3DCUBEMAP_FACE_NEGATIVE_Z
};
struct IDirect3DBaseTexture8 : public IDirect3DResource8 {
    virtual DWORD __stdcall SetLOD(DWORD) = 0;
    virtual DWORD __stdcall GetLOD() = 0;
    virtual DWORD __stdcall GetLevelCount() = 0;
};
struct IDirect3DTexture8 : public IDirect3DBaseTexture8 {
    virtual HRESULT __stdcall GetLevelDesc(UINT, D3DSURFACE_DESC *) = 0;
    virtual HRESULT __stdcall GetSurfaceLevel(UINT, IDirect3DSurface8 **) = 0;
    virtual HRESULT __stdcall LockRect(UINT, D3DLOCKED_RECT *, const RECT *, DWORD) = 0;
    virtual HRESULT __stdcall UnlockRect(UINT) = 0;
};
struct IDirect3DCubeTexture8 : public IDirect3DBaseTexture8 {
    virtual HRESULT __stdcall GetLevelDesc(UINT, D3DSURFACE_DESC *) = 0;
    virtual HRESULT __stdcall GetCubeMapSurface(D3DCUBEMAP_FACES, UINT, IDirect3DSurface8 **) = 0;
    virtual HRESULT __stdcall LockRect(D3DCUBEMAP_FACES, UINT, D3DLOCKED_RECT *, const RECT *, DWORD) = 0;
    virtual HRESULT __stdcall UnlockRect(D3DCUBEMAP_FACES, UINT) = 0;
};
struct IDirect3DSurface8 : public IUnknown {
    // Cache uses the IUnknown portion of a surface.
};

#endif
