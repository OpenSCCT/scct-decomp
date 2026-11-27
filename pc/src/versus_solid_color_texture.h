#ifndef VERSUS_SOLID_COLOR_TEXTURE_H
#define VERSUS_SOLID_COLOR_TEXTURE_H

#include "versus_render_resource.h"
#include "unreal_math.h"

extern unsigned __int64 GCacheCounter;

// The first two resource methods have independent retail bodies. Later slots
// of the texture interface are not used by the material getter.
#pragma pack(push, 4)
class FSolidColorTexture : public FRenderResource {
public:
    FColor Color;
    INT Revision;
    unsigned __int64 CacheId;

    FSolidColorTexture(FColor InColor);
    virtual unsigned __int64 GetCacheId() { return CacheId; }
    virtual INT GetRevision() { return Revision; }
};
#pragma pack(pop)

#endif
