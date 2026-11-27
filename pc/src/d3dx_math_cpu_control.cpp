#include "d3dx_math_cpu_control.h"
#include "d3dx_settings.h"

enum {
    REG_DWORD = 4,
    PF_XMMI_INSTRUCTIONS_AVAILABLE = 6,
    PF_3DNOW_INSTRUCTIONS_AVAILABLE = 7,
    PF_XMMI64_INSTRUCTIONS_AVAILABLE = 10,
    IntelSse2 = 8
};

static inline BOOL D3DXIsProcessorFeaturePresent(UINT feature)
{
    switch (feature) {
    case PF_XMMI64_INSTRUCTIONS_AVAILABLE:
        return IsIntelSSEProcessor() & IntelSse2;
    default:
        return IsProcessorFeaturePresent(feature);
    }
}

extern "C" D3DX_CPU_OPTIMIZATION __stdcall D3DXCpuOptimizations(BOOL enable)
{
    if (!enable) {
        g_CpuOptimization = D3DX_OPTIMIZATION_UNSELECTED;
        g_D3DXFastTable = g_D3DXFastTableC;
    } else if (g_CpuOptimization == D3DX_OPTIMIZATION_UNSELECTED) {
        g_CpuOptimization = D3DX_NO_OPTIMIZATION;
        g_D3DXFastTable = g_D3DXFastTableC;
        x86_D3DXInitFastTable(&g_D3DXFastTable);
        DWORD disabled;
        if (!GetD3DRegValue(REG_DWORD, "DisablePSGP", &disabled, sizeof(disabled)))
            disabled = 0;
        if (disabled != 1) {
            if (D3DXIsProcessorFeaturePresent(PF_3DNOW_INSTRUCTIONS_AVAILABLE)) {
                x3d_D3DXInitFastTable(&g_D3DXFastTable);
                g_CpuOptimization = D3DX_3DNOW_OPTIMIZATION;
            } else if (D3DXIsProcessorFeaturePresent(PF_XMMI64_INSTRUCTIONS_AVAILABLE)) {
                sse2_D3DXInitFastTable(&g_D3DXFastTable);
                g_CpuOptimization = D3DX_SSE2_OPTIMIZATION;
            } else if (D3DXIsProcessorFeaturePresent(PF_XMMI_INSTRUCTIONS_AVAILABLE)) {
                sse_D3DXInitFastTable(&g_D3DXFastTable);
                g_CpuOptimization = D3DX_SSE_OPTIMIZATION;
            }
        }
    }
    return g_CpuOptimization;
}
