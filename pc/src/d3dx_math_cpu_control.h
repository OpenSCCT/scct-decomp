#ifndef D3DX_MATH_CPU_CONTROL_H
#define D3DX_MATH_CPU_CONTROL_H

#include "d3dx_fast_table.h"

extern D3DXFASTTABLE g_D3DXFastTableC;
extern D3DX_CPU_OPTIMIZATION g_CpuOptimization;
void x86_D3DXInitFastTable(D3DXFASTTABLE *table);
void x3d_D3DXInitFastTable(D3DXFASTTABLE *table);
void sse_D3DXInitFastTable(D3DXFASTTABLE *table);
void sse2_D3DXInitFastTable(D3DXFASTTABLE *table);
DWORD IsIntelSSEProcessor();
extern "C" __declspec(dllimport) BOOL __stdcall IsProcessorFeaturePresent(DWORD feature);

#endif
