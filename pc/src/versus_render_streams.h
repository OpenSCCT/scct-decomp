#ifndef VERSUS_RENDER_STREAMS_H
#define VERSUS_RENDER_STREAMS_H

#include "versus_render_resource.h"
#include "versus_shader_declaration.h"

class FVertexStream : public FRenderResource {
public:
    virtual INT GetStride() = 0;
    virtual INT GetSize() = 0;
    virtual INT HintDynamic() = 0;
    virtual INT UseNPatches() = 0;
    virtual INT GetComponents(FVertexComponent *Components) = 0;
    virtual void GetStreamData(void *Dest) = 0;
    virtual void GetRawStreamData(void **Dest, INT FirstVertex) = 0;
};

class FIndexBuffer : public FRenderResource {
public:
    virtual INT GetSize() = 0;
    virtual void GetContents(void *Dest) = 0;
};

#endif
