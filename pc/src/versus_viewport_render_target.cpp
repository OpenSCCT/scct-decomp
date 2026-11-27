#include "versus_native_class_types.h"
#include "versus_output_device.h"
#include "versus_viewport_types.h"

unsigned __int64 FViewportRenderTarget::GetCacheId()
{
    return CacheId;
}

INT FViewportRenderTarget::GetWidth()
{
    return Viewport->SizeX;
}

INT FViewportRenderTarget::GetHeight()
{
    return Viewport->SizeY;
}

ETextureFormat FViewportRenderTarget::GetFormat()
{
    return Viewport->ColorBytes == 2 ? TEXF_RGB16 : TEXF_RGBA8;
}
