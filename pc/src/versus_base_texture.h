#ifndef VERSUS_BASE_TEXTURE_H
#define VERSUS_BASE_TEXTURE_H

#include "versus_render_resource.h"
#include "versus_texture_format.h"

class FCubemap;
class FTexture;
class FCompositeTexture;
class FRenderTarget;
class FBaseTexture : public FRenderResource {
public:
    virtual FBaseTexture *GetBaseTextureInterface() { return this; }
    virtual FCubemap *GetCubemapInterface() { return 0; }
    virtual FTexture *GetTextureInterface() { return 0; }
    virtual FCompositeTexture *GetCompositeTextureInterface() { return 0; }
    virtual FRenderTarget *GetRenderTargetInterface() { return 0; }
    virtual INT GetWidth() = 0;
    virtual INT GetHeight() = 0;
    virtual INT GetFirstMip() = 0;
    virtual INT GetNumMips() = 0;
    virtual ETextureFormat GetFormat() = 0;
    virtual ETexClampMode GetUClamp() = 0;
    virtual ETexClampMode GetVClamp() = 0;
};

class UTexture;
class FTexture : public FBaseTexture {
public:
    virtual void *GetRawTextureData(INT MipIndex) = 0;
    virtual void GetTextureData(INT mip, void *dest, INT pitch, ETextureFormat format, UBOOL coloredMips) = 0;
    virtual void UnloadRawTextureData(INT MipIndex) = 0;
    virtual UTexture *GetUTexture() = 0;
};
class FCubemap : public FBaseTexture { public: virtual FTexture *GetFace(INT face) = 0; };

class FRenderTarget : public FBaseTexture {
public:
    virtual FRenderTarget *GetRenderTargetInterface() { return this; }
};

#endif
