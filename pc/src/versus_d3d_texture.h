#ifndef VERSUS_D3D_TEXTURE_H
#define VERSUS_D3D_TEXTURE_H

#include "versus_d3d_vertex_stream.h"
#include "versus_d3d8_textures.h"
#include "versus_render_resource.h"

class UTexture;
class FCubemap;
class FTexture;
class FCompositeTexture;
class FRenderTarget;
class FBaseTexture : public FRenderResource {
public:
    virtual FBaseTexture *GetBaseTextureInterface() = 0;
    virtual FCubemap *GetCubemapInterface() = 0;
    virtual FTexture *GetTextureInterface() = 0;
    virtual FCompositeTexture *GetCompositeTextureInterface() = 0;
    virtual FRenderTarget *GetRenderTargetInterface() = 0;
    virtual INT GetWidth() = 0;
    virtual INT GetHeight() = 0;
    virtual INT GetFirstMip() = 0;
    virtual INT GetNumMips() = 0;
    virtual ETextureFormat GetFormat() = 0;
    virtual BYTE GetUClamp() = 0;
    virtual BYTE GetVClamp() = 0;
};
class FTexture : public FBaseTexture {
public:
    virtual void *GetRawTextureData(INT MipIndex) = 0;
    virtual void GetTextureData(INT mip, void *dest, INT pitch, ETextureFormat format, UBOOL coloredMips) = 0;
    virtual void UnloadRawTextureData(INT MipIndex) = 0;
    virtual UTexture *GetUTexture() = 0;
};
class FCubemap : public FBaseTexture { public: virtual FTexture *GetFace(INT face) = 0; };
class FCompositeTexture : public FBaseTexture {
public:
    virtual INT GetNumChildren() = 0;
    virtual FTexture *GetChild(INT index, INT *x, INT *y) = 0;
};
class FRenderTarget : public FBaseTexture {};
class FD3DTexture : public FD3DResource {
public:
    IDirect3DSurface8 *RenderTargetSurface, *DepthStencilSurface;
    IDirect3DTexture8 *Texture;
    IDirect3DCubeTexture8 *CubeTexture;
    INT CachedWidth, CachedHeight, CachedFirstMip, CachedMipCount;
    D3DFORMAT CachedFormat;
    TArray<INT> ChildRevisions;
    UBOOL Cache(FBaseTexture *source);
};

#endif
