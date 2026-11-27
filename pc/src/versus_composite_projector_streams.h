#ifndef VERSUS_COMPOSITE_PROJECTOR_STREAMS_H
#define VERSUS_COMPOSITE_PROJECTOR_STREAMS_H

#include "versus_render_streams.h"
#include "versus_projector_batch.h"

class FCompositeVertexStream : public FVertexStream
{
public:
    FProjectorRenderBatch *Info;        // +0x04
    INT Size;                          // +0x08
    INT Stride;                        // +0x0c

    FCompositeVertexStream(FProjectorRenderBatch *InInfo);
    virtual unsigned __int64 GetCacheId();
    virtual INT GetRevision();
    virtual INT GetStride();
    virtual INT GetSize();
    virtual INT HintDynamic();
    virtual INT UseNPatches();
    virtual INT GetComponents(FVertexComponent *Components);
    virtual void GetStreamData(void *Dest);
    virtual void GetRawStreamData(void **Dest, INT FirstVertex);
};

class FCompositeIndexBuffer : public FIndexBuffer
{
public:
    FProjectorRenderBatch *Info;        // +0x04
    INT Size;                          // +0x08

    FCompositeIndexBuffer(FProjectorRenderBatch *InInfo);
    virtual unsigned __int64 GetCacheId();
    virtual INT GetRevision();
    virtual INT GetSize();
    virtual void GetContents(void *Data);
};

#endif
