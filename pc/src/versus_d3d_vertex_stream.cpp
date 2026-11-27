#include "versus_d3d_vertex_stream.h"

enum { D3DUSAGE_WRITEONLY = 8, D3DUSAGE_SOFTWAREPROCESSING = 0x10, D3DUSAGE_DYNAMIC = 0x200 };

FD3DVertexStream::FD3DVertexStream(UD3DRenderDevice *InRenDev, QWORD InCacheId)
    : FD3DResource(InRenDev, InCacheId), Direct3DVertexBuffer8(0)
{}

FD3DVertexStream::~FD3DVertexStream()
{
    if (Direct3DVertexBuffer8)
        Direct3DVertexBuffer8->Release();
}

INT FD3DVertexStream::CalculateFootprint()
{
    return CachedSize;
}

FD3DDynamicVertexStream::FD3DDynamicVertexStream(UD3DRenderDevice *InRenDev)
    : FD3DVertexStream(InRenDev, 0)
{
    Reallocate(128 * 1024);
}

void FD3DDynamicVertexStream::Reallocate(INT NewCachedSize)
{
    if (Direct3DVertexBuffer8) {
        RenDev->DeferredState.UnSetVertexBuffer(Direct3DVertexBuffer8);
        Direct3DVertexBuffer8->Release();
        Direct3DVertexBuffer8 = 0;
    }
    CachedSize = NewCachedSize;
    Tail = 0;
    DWORD Usage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY;
    if (!RenDev->UseHardwareTL)
        Usage = D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY | D3DUSAGE_SOFTWAREPROCESSING;
    D3DPOOL Pool = D3DPOOL_DEFAULT;
    for (INT Attempt = 0; Attempt < 3; Attempt++) {
        if (Attempt == 2)
            Pool = D3DPOOL_SYSTEMMEM;
        if (RenDev->Direct3DDevice8->CreateVertexBuffer(CachedSize, Usage, 0, Pool, &Direct3DVertexBuffer8) >= 0)
            break;
        RenDev->Direct3DDevice8->ResourceManagerDiscardBytes(0);
    }
}

template<class T> inline T Min(T A, T B) { return A < B ? A : B; }

void FD3DDeferredState::UnSetVertexBuffer(IDirect3DVertexBuffer8 *VertexBuffer)
{
    for (INT i = 0; i < Min(RenDev->MaxStreams, 16); i++) {
        if (HardwareStream[i].StreamData == VertexBuffer) {
            HardwareStream[i].StreamData = 0;
            HardwareStream[i].StreamStride = 0;
            RenDev->Direct3DDevice8->SetStreamSource(i, 0, 0);
        }
        if (StreamState[i].StreamData == VertexBuffer) {
            StreamState[i].StreamData = 0;
            StreamState[i].StreamStride = 0;
        }
    }
}

inline INT GetResourceHashIndex(QWORD CacheId)
{
    DWORD Lo = (DWORD)CacheId;
    return (((Lo >> 4) & 0xff0) + ((Lo >> 16) & 0xf)) ^ (Lo & 0xfff);
}

FD3DResource::FD3DResource(UD3DRenderDevice *InRenDev, QWORD InCacheId)
    : RenDev(InRenDev), CacheId(InCacheId)
{
    CachedRevision = 0;
    NextResource = RenDev->ResourceList;
    RenDev->ResourceList = this;
    HashIndex = GetResourceHashIndex(CacheId);
    HashNext = RenDev->ResourceHash[HashIndex];
    RenDev->ResourceHash[HashIndex] = this;
    LastFrameUsed = 0;
}
