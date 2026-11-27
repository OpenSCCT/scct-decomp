#ifndef D3D8_VIEWPORT_H
#define D3D8_VIEWPORT_H

#include "windows_dispatch_types.h"

struct _D3DVIEWPORT8 {
    DWORD X, Y, Width, Height;
    float MinZ, MaxZ;
};

typedef struct _D3DVIEWPORT8 D3DVIEWPORT8;

#endif
