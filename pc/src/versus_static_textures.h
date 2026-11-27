#ifndef VERSUS_STATIC_TEXTURES_H
#define VERSUS_STATIC_TEXTURES_H

#include "versus_base_texture.h"

class UCubemap;

#pragma pack(push, 4)
class FStaticTexture : public FTexture {
public:
    unsigned __int64 CacheId;
    UTexture *Owner;
    INT Revision;

    FStaticTexture(UTexture *InOwner);
    virtual unsigned __int64 GetCacheId();
    virtual INT GetRevision();
    virtual FTexture *GetTextureInterface() { return this; }
    virtual INT GetWidth();
    virtual INT GetHeight();
    virtual INT GetFirstMip();
    virtual INT GetNumMips();
    virtual ETextureFormat GetFormat();
    virtual ETexClampMode GetUClamp();
    virtual ETexClampMode GetVClamp();
    virtual void *GetRawTextureData(INT MipIndex);
    virtual void GetTextureData(INT, void *, INT, ETextureFormat, UBOOL);
    virtual void UnloadRawTextureData(INT);
    virtual UTexture *GetUTexture() { return Owner; }
};

class FStaticCubemap : public FCubemap {
public:
    UCubemap *Owner;
    unsigned __int64 CacheId;
    INT Revision;

    FStaticCubemap(UCubemap *InOwner);
    virtual unsigned __int64 GetCacheId() { return CacheId; }
    virtual INT GetRevision();
    virtual FCubemap *GetCubemapInterface() { return this; }
    virtual INT GetWidth();
    virtual INT GetHeight();
    virtual INT GetFirstMip();
    virtual INT GetNumMips();
    virtual ETextureFormat GetFormat();
    virtual ETexClampMode GetUClamp();
    virtual ETexClampMode GetVClamp();
    virtual FTexture *GetFace(INT Face);
};
#pragma pack(pop)

#endif
