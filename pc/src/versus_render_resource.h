#ifndef VERSUS_RENDER_RESOURCE_H
#define VERSUS_RENDER_RESOURCE_H

#include "versus_build.h"
#include "unreal_types.h"

class FRenderResource {
public:
    virtual unsigned __int64 GetCacheId() = 0;
    virtual INT GetRevision() = 0;
};

#endif
