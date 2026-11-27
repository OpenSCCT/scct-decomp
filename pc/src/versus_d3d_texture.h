#ifndef VERSUS_D3D_TEXTURE_H
#define VERSUS_D3D_TEXTURE_H

#include "versus_d3d_vertex_stream.h"
#include "versus_d3d8_textures.h"
#include "versus_base_texture.h"

class FCompositeTexture : public FBaseTexture {
public:
    virtual INT GetNumChildren() = 0;
    virtual FTexture *GetChild(INT index, INT *x, INT *y) = 0;
};
class FD3DTexture : public FD3DResource {
public:
    IDirect3DSurface8 *RenderTargetSurface, *DepthStencilSurface;
    IDirect3DTexture8 *Texture;
    IDirect3DCubeTexture8 *CubeTexture;
    INT CachedWidth, CachedHeight, CachedFirstMip, CachedMipCount;
    D3DFORMAT CachedFormat;
    TArray<INT> ChildRevisions;
    FD3DTexture(UD3DRenderDevice *Device, QWORD Id);
    virtual ~FD3DTexture();
    virtual FD3DTexture *GetTexture() { return this; }
    virtual INT CalculateFootprint();
    UBOOL Cache(FBaseTexture *source);
};

#endif
