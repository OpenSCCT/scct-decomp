/* sound_find_local.c -- a resource of the loaded maps by editor identifier (sndldmap.c) */
#include "sound_bank_layout.h"

/* Searches one list of resources. */
static tdstBlockResourceMem *find_resource(tdstBlockResMemList *pstBlockResMemList, unsigned long ulEdId)
{
    long i;
    tdstBlockResourceMem *pstBlockResMem = pstBlockResMemList->hFirstElementOpt;
    for (i = 0; i < pstBlockResMemList->lNumberOfElementsOpt; ++i, ++pstBlockResMem)
        if (pstBlockResMem->Id == ulEdId)
            return pstBlockResMem;
    return 0;
}

/* SND_fn_pstGetResFromEdIdSnd_Map: the current map first, then the fixed one; in each, the
   common data before the current language's */
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
