#ifndef D3DX_BOX_FILTER_H
#define D3DX_BOX_FILTER_H

#include "windows_dispatch_types.h"

typedef LONG BoxFilter2D(UINT *dst, UINT *src, UINT width, UINT height, UINT srcPitch, UINT dstPitch);

BoxFilter2D c_BoxFilter2D_A8R8G8B8;
BoxFilter2D c_BoxFilter2D_X8R8G8B8;
BoxFilter2D mmx_BoxFilter2D_A8R8G8B8;
BoxFilter2D init_BoxFilter2D_A8R8G8B8;
BoxFilter2D init_BoxFilter2D_X8R8G8B8;

extern BoxFilter2D *g_pBoxFilter2D_A8R8G8B8;
extern BoxFilter2D *g_pBoxFilter2D_X8R8G8B8;

#endif
