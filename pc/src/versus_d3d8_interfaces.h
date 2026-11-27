// Direct3D 8 COM declarations through the stream-binding methods used by D3DDrv.
// Slot order and signatures follow the Microsoft DirectX 8.0 SDK (D3D_SDK_VERSION 120).
#ifndef VERSUS_D3D8_INTERFACES_H
#define VERSUS_D3D8_INTERFACES_H

#include "windows_dispatch_types.h"
#include "windows_iunknown.h"

typedef DWORD D3DCOLOR;
typedef struct tagRECT RECT;
typedef struct tagPOINT POINT;
typedef struct tagPALETTEENTRY PALETTEENTRY;
typedef struct _RGNDATA RGNDATA;

typedef enum _D3DBACKBUFFER_TYPE D3DBACKBUFFER_TYPE;
typedef struct _D3DCAPS8 D3DCAPS8;
typedef struct _D3DCLIPSTATUS8 D3DCLIPSTATUS8;
typedef struct _D3DDEVICE_CREATION_PARAMETERS D3DDEVICE_CREATION_PARAMETERS;
typedef struct _D3DDISPLAYMODE D3DDISPLAYMODE;
typedef enum _D3DFORMAT D3DFORMAT;
typedef struct _D3DGAMMARAMP D3DGAMMARAMP;
typedef struct _D3DLIGHT8 D3DLIGHT8;
typedef struct _D3DMATERIAL8 D3DMATERIAL8;
typedef struct _D3DMATRIX D3DMATRIX;
typedef enum _D3DMULTISAMPLE_TYPE D3DMULTISAMPLE_TYPE;
typedef enum _D3DPOOL { D3DPOOL_DEFAULT, D3DPOOL_MANAGED, D3DPOOL_SYSTEMMEM } D3DPOOL;
typedef struct _D3DPRESENT_PARAMETERS_ D3DPRESENT_PARAMETERS;
typedef enum _D3DPRIMITIVETYPE D3DPRIMITIVETYPE;
typedef struct _D3DRASTER_STATUS D3DRASTER_STATUS;
typedef struct _D3DRECT D3DRECT;
typedef enum _D3DRENDERSTATETYPE D3DRENDERSTATETYPE;
typedef enum _D3DRESOURCETYPE D3DRESOURCETYPE;
typedef enum _D3DSTATEBLOCKTYPE D3DSTATEBLOCKTYPE;
typedef enum _D3DTEXTURESTAGESTATETYPE D3DTEXTURESTAGESTATETYPE;
typedef enum _D3DTRANSFORMSTATETYPE D3DTRANSFORMSTATETYPE;
typedef struct _D3DVERTEXBUFFER_DESC D3DVERTEXBUFFER_DESC;
typedef struct _D3DVIEWPORT8 D3DVIEWPORT8;

struct IDirect3D8;
struct IDirect3DBaseTexture8;
struct IDirect3DCubeTexture8;
struct IDirect3DDevice8;
struct IDirect3DIndexBuffer8;
struct IDirect3DSurface8;
struct IDirect3DSwapChain8;
struct IDirect3DTexture8;
struct IDirect3DVertexBuffer8;
struct IDirect3DVolumeTexture8;

struct IDirect3DResource8 : public IUnknown {
    virtual HRESULT __stdcall GetDevice(IDirect3DDevice8 **ppDevice) = 0;
    virtual HRESULT __stdcall SetPrivateData(REFGUID refguid, const void *pData, DWORD SizeOfData, DWORD Flags) = 0;
    virtual HRESULT __stdcall GetPrivateData(REFGUID refguid, void *pData, DWORD *pSizeOfData) = 0;
    virtual HRESULT __stdcall FreePrivateData(REFGUID refguid) = 0;
    virtual DWORD __stdcall SetPriority(DWORD PriorityNew) = 0;
    virtual DWORD __stdcall GetPriority() = 0;
    virtual void __stdcall PreLoad() = 0;
    virtual D3DRESOURCETYPE __stdcall GetType() = 0;
};

struct IDirect3DVertexBuffer8 : public IDirect3DResource8 {
    virtual HRESULT __stdcall Lock(UINT OffsetToLock, UINT SizeToLock, BYTE **ppbData, DWORD Flags) = 0;
    virtual HRESULT __stdcall Unlock() = 0;
    virtual HRESULT __stdcall GetDesc(D3DVERTEXBUFFER_DESC *pDesc) = 0;
};

struct IDirect3DDevice8 : public IUnknown {
    virtual HRESULT __stdcall TestCooperativeLevel() = 0;
    virtual UINT __stdcall GetAvailableTextureMem() = 0;
    virtual HRESULT __stdcall ResourceManagerDiscardBytes(DWORD Bytes) = 0;
    virtual HRESULT __stdcall GetDirect3D(IDirect3D8 **ppD3D8) = 0;
    virtual HRESULT __stdcall GetDeviceCaps(D3DCAPS8 *pCaps) = 0;
    virtual HRESULT __stdcall GetDisplayMode(D3DDISPLAYMODE *pMode) = 0;
    virtual HRESULT __stdcall GetCreationParameters(D3DDEVICE_CREATION_PARAMETERS *pParameters) = 0;
    virtual HRESULT __stdcall SetCursorProperties(UINT XHotSpot, UINT YHotSpot, IDirect3DSurface8 *pCursorBitmap) = 0;
    virtual void __stdcall SetCursorPosition(UINT XScreenSpace, UINT YScreenSpace, DWORD Flags) = 0;
    virtual BOOL __stdcall ShowCursor(BOOL bShow) = 0;
    virtual HRESULT __stdcall CreateAdditionalSwapChain(D3DPRESENT_PARAMETERS *pPresentationParameters, IDirect3DSwapChain8 **pSwapChain) = 0;
    virtual HRESULT __stdcall Reset(D3DPRESENT_PARAMETERS *pPresentationParameters) = 0;
    virtual HRESULT __stdcall Present(const RECT *pSourceRect, const RECT *pDestRect, HWND hDestWindowOverride, const RGNDATA *pDirtyRegion) = 0;
    virtual HRESULT __stdcall GetBackBuffer(UINT BackBuffer, D3DBACKBUFFER_TYPE Type, IDirect3DSurface8 **ppBackBuffer) = 0;
    virtual HRESULT __stdcall GetRasterStatus(D3DRASTER_STATUS *pRasterStatus) = 0;
    virtual void __stdcall SetGammaRamp(DWORD Flags, const D3DGAMMARAMP *pRamp) = 0;
    virtual void __stdcall GetGammaRamp(D3DGAMMARAMP *pRamp) = 0;
    virtual HRESULT __stdcall CreateTexture(UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture8 **ppTexture) = 0;
    virtual HRESULT __stdcall CreateVolumeTexture(UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture8 **ppVolumeTexture) = 0;
    virtual HRESULT __stdcall CreateCubeTexture(UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture8 **ppCubeTexture) = 0;
    virtual HRESULT __stdcall CreateVertexBuffer(UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer8 **ppVertexBuffer) = 0;
    virtual HRESULT __stdcall CreateIndexBuffer(UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer8 **ppIndexBuffer) = 0;
    virtual HRESULT __stdcall CreateRenderTarget(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, BOOL Lockable, IDirect3DSurface8 **ppSurface) = 0;
    virtual HRESULT __stdcall CreateDepthStencilSurface(UINT Width, UINT Height, D3DFORMAT Format, D3DMULTISAMPLE_TYPE MultiSample, IDirect3DSurface8 **ppSurface) = 0;
    virtual HRESULT __stdcall CreateImageSurface(UINT Width, UINT Height, D3DFORMAT Format, IDirect3DSurface8 **ppSurface) = 0;
    virtual HRESULT __stdcall CopyRects(IDirect3DSurface8 *pSourceSurface, const RECT *pSourceRectsArray, UINT cRects, IDirect3DSurface8 *pDestinationSurface, const POINT *pDestPointsArray) = 0;
    virtual HRESULT __stdcall UpdateTexture(IDirect3DBaseTexture8 *pSourceTexture, IDirect3DBaseTexture8 *pDestinationTexture) = 0;
    virtual HRESULT __stdcall GetFrontBuffer(IDirect3DSurface8 *pDestSurface) = 0;
    virtual HRESULT __stdcall SetRenderTarget(IDirect3DSurface8 *pRenderTarget, IDirect3DSurface8 *pNewZStencil) = 0;
    virtual HRESULT __stdcall GetRenderTarget(IDirect3DSurface8 **ppRenderTarget) = 0;
    virtual HRESULT __stdcall GetDepthStencilSurface(IDirect3DSurface8 **ppZStencilSurface) = 0;
    virtual HRESULT __stdcall BeginScene() = 0;
    virtual HRESULT __stdcall EndScene() = 0;
    virtual HRESULT __stdcall Clear(DWORD Count, const D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z, DWORD Stencil) = 0;
    virtual HRESULT __stdcall SetTransform(D3DTRANSFORMSTATETYPE State, const D3DMATRIX *pMatrix) = 0;
    virtual HRESULT __stdcall GetTransform(D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix) = 0;
    virtual HRESULT __stdcall MultiplyTransform(D3DTRANSFORMSTATETYPE, const D3DMATRIX *) = 0;
    virtual HRESULT __stdcall SetViewport(const D3DVIEWPORT8 *pViewport) = 0;
    virtual HRESULT __stdcall GetViewport(D3DVIEWPORT8 *pViewport) = 0;
    virtual HRESULT __stdcall SetMaterial(const D3DMATERIAL8 *pMaterial) = 0;
    virtual HRESULT __stdcall GetMaterial(D3DMATERIAL8 *pMaterial) = 0;
    virtual HRESULT __stdcall SetLight(DWORD Index, const D3DLIGHT8 *) = 0;
    virtual HRESULT __stdcall GetLight(DWORD Index, D3DLIGHT8 *) = 0;
    virtual HRESULT __stdcall LightEnable(DWORD Index, BOOL Enable) = 0;
    virtual HRESULT __stdcall GetLightEnable(DWORD Index, BOOL *pEnable) = 0;
    virtual HRESULT __stdcall SetClipPlane(DWORD Index, const float *pPlane) = 0;
    virtual HRESULT __stdcall GetClipPlane(DWORD Index, float *pPlane) = 0;
    virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE State, DWORD Value) = 0;
    virtual HRESULT __stdcall GetRenderState(D3DRENDERSTATETYPE State, DWORD *pValue) = 0;
    virtual HRESULT __stdcall BeginStateBlock() = 0;
    virtual HRESULT __stdcall EndStateBlock(DWORD *pToken) = 0;
    virtual HRESULT __stdcall ApplyStateBlock(DWORD Token) = 0;
    virtual HRESULT __stdcall CaptureStateBlock(DWORD Token) = 0;
    virtual HRESULT __stdcall DeleteStateBlock(DWORD Token) = 0;
    virtual HRESULT __stdcall CreateStateBlock(D3DSTATEBLOCKTYPE Type, DWORD *pToken) = 0;
    virtual HRESULT __stdcall SetClipStatus(const D3DCLIPSTATUS8 *pClipStatus) = 0;
    virtual HRESULT __stdcall GetClipStatus(D3DCLIPSTATUS8 *pClipStatus) = 0;
    virtual HRESULT __stdcall GetTexture(DWORD Stage, IDirect3DBaseTexture8 **ppTexture) = 0;
    virtual HRESULT __stdcall SetTexture(DWORD Stage, IDirect3DBaseTexture8 *pTexture) = 0;
    virtual HRESULT __stdcall GetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue) = 0;
    virtual HRESULT __stdcall SetTextureStageState(DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value) = 0;
    virtual HRESULT __stdcall ValidateDevice(DWORD *pNumPasses) = 0;
    virtual HRESULT __stdcall GetInfo(DWORD DevInfoID, void *pDevInfoStruct, DWORD DevInfoStructSize) = 0;
    virtual HRESULT __stdcall SetPaletteEntries(UINT PaletteNumber, const PALETTEENTRY *pEntries) = 0;
    virtual HRESULT __stdcall GetPaletteEntries(UINT PaletteNumber, PALETTEENTRY *pEntries) = 0;
    virtual HRESULT __stdcall SetCurrentTexturePalette(UINT PaletteNumber) = 0;
    virtual HRESULT __stdcall GetCurrentTexturePalette(UINT *PaletteNumber) = 0;
    virtual HRESULT __stdcall DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount) = 0;
    virtual HRESULT __stdcall DrawIndexedPrimitive(D3DPRIMITIVETYPE, UINT minIndex, UINT NumVertices, UINT startIndex, UINT primCount) = 0;
    virtual HRESULT __stdcall DrawPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride) = 0;
    virtual HRESULT __stdcall DrawIndexedPrimitiveUP(D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex, UINT NumVertexIndices, UINT PrimitiveCount, const void *pIndexData, D3DFORMAT IndexDataFormat, const void *pVertexStreamZeroData, UINT VertexStreamZeroStride) = 0;
    virtual HRESULT __stdcall ProcessVertices(UINT SrcStartIndex, UINT DestIndex, UINT VertexCount, IDirect3DVertexBuffer8 *pDestBuffer, DWORD Flags) = 0;
    virtual HRESULT __stdcall CreateVertexShader(const DWORD *pDeclaration, const DWORD *pFunction, DWORD *pHandle, DWORD Usage) = 0;
    virtual HRESULT __stdcall SetVertexShader(DWORD Handle) = 0;
    virtual HRESULT __stdcall GetVertexShader(DWORD *pHandle) = 0;
    virtual HRESULT __stdcall DeleteVertexShader(DWORD Handle) = 0;
    virtual HRESULT __stdcall SetVertexShaderConstant(DWORD Register, const void *pConstantData, DWORD ConstantCount) = 0;
    virtual HRESULT __stdcall GetVertexShaderConstant(DWORD Register, void *pConstantData, DWORD ConstantCount) = 0;
    virtual HRESULT __stdcall GetVertexShaderDeclaration(DWORD Handle, void *pData, DWORD *pSizeOfData) = 0;
    virtual HRESULT __stdcall GetVertexShaderFunction(DWORD Handle, void *pData, DWORD *pSizeOfData) = 0;
    virtual HRESULT __stdcall SetStreamSource(UINT StreamNumber, IDirect3DVertexBuffer8 *pStreamData, UINT Stride) = 0;
};

#endif
