#ifndef VERSUS_D3D_VERTEX_STREAM_H
#define VERSUS_D3D_VERTEX_STREAM_H

#include "versus_d3d_render_device.h"
#include "versus_d3d8_interfaces.h"

typedef unsigned __int64 QWORD;
class FVertexStream;
class FD3DVertexStream;
class FD3DTexture;
class FD3DIndexBuffer;

#pragma pack(push, 4)
class FD3DResource {
public:
    UD3DRenderDevice *RenDev;   // +0x04
    QWORD CacheId;              // +0x08
    INT CachedRevision;         // +0x10
    INT HashIndex;              // +0x14
    FD3DResource *NextResource; // +0x18
    FD3DResource *HashNext;     // +0x1c
    INT LastFrameUsed;          // +0x20

    FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId);
    virtual ~FD3DResource() throw();
    virtual FD3DTexture *GetTexture() { return 0; }
    virtual FD3DVertexStream *GetVertexStream() { return 0; }
    virtual FD3DIndexBuffer *GetIndexBuffer() { return 0; }
    virtual INT CalculateFootprint() { return 0; }
};

class FD3DVertexStream : public FD3DResource {
public:
    IDirect3DVertexBuffer8 *Direct3DVertexBuffer8; // +0x24
    INT CachedSize;                                // +0x28

    FD3DVertexStream(UD3DRenderDevice *InRenDev, QWORD InCacheId);
    virtual ~FD3DVertexStream();
    virtual FD3DVertexStream *GetVertexStream() { return this; }
    virtual INT CalculateFootprint();
    void Cache(FVertexStream *SourceStream);
};

class FD3DDynamicVertexStream : public FD3DVertexStream {
public:
    INT Tail;

    FD3DDynamicVertexStream(UD3DRenderDevice *InRenDev);
    void Reallocate(INT NewBufferSize);
    INT AddVertices(FVertexStream *Stream);
};
#pragma pack(pop)

#endif
