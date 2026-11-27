#ifndef VERSUS_SOLID_COLOR_TEXTURE_H
#define VERSUS_SOLID_COLOR_TEXTURE_H

#include "versus_base_texture.h"
#include "unreal_math.h"

extern unsigned __int64 GCacheCounter;

// A one-texel RGBA texture. The retail vtable supplies all eighteen resource methods.
#pragma pack(push, 4)
class FSolidColorTexture : public FTexture {
public:
    FColor Color;
    INT Revision;
    unsigned __int64 CacheId;

    FSolidColorTexture(FColor InColor);
    virtual FTexture *GetTextureInterface() { return this; }
    virtual INT GetWidth() { return 1; }
    virtual INT GetHeight() { return 1; }
    virtual INT GetFirstMip() { return 0; }
    virtual INT GetNumMips() { return 1; }
    virtual ETextureFormat GetFormat() { return TEXF_RGBA8; }
    virtual ETexClampMode GetUClamp() { return TC_Wrap; }
    virtual ETexClampMode GetVClamp() { return TC_Wrap; }
    virtual void *GetRawTextureData(INT MipIndex) { return &Color; }
    virtual void GetTextureData(INT MipIndex, void *Dest, INT Pitch, ETextureFormat Format, UBOOL ColoredMips)
    {
        *static_cast<FColor *>(Dest) = Color;
    }
    virtual void UnloadRawTextureData(INT MipIndex) {}
    virtual UTexture *GetUTexture() { return 0; }
    virtual unsigned __int64 GetCacheId() { return CacheId; }
    virtual INT GetRevision() { return Revision; }
};
#pragma pack(pop)

#endif
