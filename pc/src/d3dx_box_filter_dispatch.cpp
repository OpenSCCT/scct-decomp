#include "d3dx_box_filter.h"
#include "d3dx_settings.h"

LONG init_BoxFilter2D_A8R8G8B8(UINT *dst, UINT *src, UINT width, UINT height, UINT srcPitch, UINT dstPitch)
{
    if (isMMXprocessor()) {
        g_pBoxFilter2D_A8R8G8B8 = mmx_BoxFilter2D_A8R8G8B8;
        g_pBoxFilter2D_X8R8G8B8 = mmx_BoxFilter2D_A8R8G8B8;
    } else {
        g_pBoxFilter2D_A8R8G8B8 = c_BoxFilter2D_A8R8G8B8;
        g_pBoxFilter2D_X8R8G8B8 = c_BoxFilter2D_X8R8G8B8;
    }
    return g_pBoxFilter2D_A8R8G8B8(dst, src, width, height, srcPitch, dstPitch);
}

LONG init_BoxFilter2D_X8R8G8B8(UINT *dst, UINT *src, UINT width, UINT height, UINT srcPitch, UINT dstPitch)
{
    if (isMMXprocessor()) {
        g_pBoxFilter2D_A8R8G8B8 = mmx_BoxFilter2D_A8R8G8B8;
        g_pBoxFilter2D_X8R8G8B8 = mmx_BoxFilter2D_A8R8G8B8;
    } else {
        g_pBoxFilter2D_A8R8G8B8 = c_BoxFilter2D_A8R8G8B8;
        g_pBoxFilter2D_X8R8G8B8 = c_BoxFilter2D_X8R8G8B8;
    }
    return g_pBoxFilter2D_X8R8G8B8(dst, src, width, height, srcPitch, dstPitch);
}
