#ifndef VERSUS_D3D8_TEXTURES_H
#define VERSUS_D3D8_TEXTURES_H

#include "versus_d3d8_interfaces.h"

enum _D3DFORMAT {
    D3DFMT_UNKNOWN = 0, D3DFMT_A8R8G8B8 = 21, D3DFMT_R5G6B5 = 23, D3DFMT_A4R4G4B4 = 26,
    D3DFMT_DXT1 = 0x31545844, D3DFMT_DXT3 = 0x33545844, D3DFMT_DXT5 = 0x35545844
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
