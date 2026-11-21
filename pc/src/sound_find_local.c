#include "sound_bank_layout.h"

static tdstBlockResourceMem *find_resource(tdstBlockResMemList *pstBlockResMemList, unsigned long ulEdId)
{
    long i;
    tdstBlockResourceMem *pstBlockResMem = pstBlockResMemList->hFirstElementOpt;
    for (i = 0; i < pstBlockResMemList->lNumberOfElementsOpt; ++i, ++pstBlockResMem)
        if (pstBlockResMem->Id == ulEdId)
            return pstBlockResMem;
    return 0;
}

tdstBlockResourceMem *__stdcall SND_fn_pstGetResFromEdIdSnd_Map(unsigned long ulEdId)
{
    tdstBlockResourceMem *pstBlockResMem;
    if (gs_stCurrentMap.bLoaded) {
        if ((pstBlockResMem = find_resource(&gs_stCurrentMap.stNLoc.stBlockResMemList, ulEdId)) != 0)
            return pstBlockResMem;
        if ((pstBlockResMem = find_resource(&gs_stCurrentMap.stLoc.stBlockResMemList, ulEdId)) != 0)
            return pstBlockResMem;
    }
    if (gs_stMapFix.bLoaded) {
        if ((pstBlockResMem = find_resource(&gs_stMapFix.stNLoc.stBlockResMemList, ulEdId)) != 0)
            return pstBlockResMem;
        if ((pstBlockResMem = find_resource(&gs_stMapFix.stLoc.stBlockResMemList, ulEdId)) != 0)
            return pstBlockResMem;
    }
    return 0;
}
