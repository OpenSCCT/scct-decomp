/* sound_find_event.c -- an event of the loaded maps by editor identifier (sndldmap.c) */
#include "sound_bank_layout.h"

/* fn_pGetEventPointerFromEdId_Map: searches the events of one map, common or localised */
static __forceinline SND_tdstBlockEvent *fn_pGetEventPointerFromEdId_Map(unsigned long ulEdId,
                                                                         int bMapFix,
                                                                         int bLocalised)
{
    tdstMapMem *pstMapMem;
    tdstMapHeader *pstMapHeader;
    tdstBlockEventList *pstBlockEventList;
    SND_tdstBlockEvent *pstBlockEvent;
    long i;
    pstMapMem = bMapFix ? &gs_stMapFix : &gs_stCurrentMap;
    pstMapHeader = bLocalised ? pstMapMem->stLoc.pstMapHeader : pstMapMem->stNLoc.pstMapHeader;
    if (pstMapHeader) {
        pstBlockEventList = &pstMapHeader->stBlockEventList;
        if (pstBlockEventList) {
            pstBlockEvent = pstBlockEventList->hFirstElementOpt;
            for (i = 0; i < pstBlockEventList->lNumberOfElementsOpt; ++i, ++pstBlockEvent)
                if (pstBlockEvent->Id == ulEdId)
                    return pstBlockEvent;
        }
    }
    return 0;
}

/* SND_fn_hGetSoundEventHandleFromEditorId_Map: the fixed map first, then the current one;
   then the same for the current language when the project is localised */
SND_tdstBlockEvent *__cdecl SND_fn_hGetSoundEventHandleFromEditorId_Map(unsigned long ulEdId)
{
    SND_tdstBlockEvent *pstBlockEvent;
    if ((pstBlockEvent = fn_pGetEventPointerFromEdId_Map(ulEdId, 1, 0)) != 0)
        return pstBlockEvent;
    if ((pstBlockEvent = fn_pGetEventPointerFromEdId_Map(ulEdId, 0, 0)) != 0)
        return pstBlockEvent;
    if (g_stProjectDesc.bLocalised) {
        if ((pstBlockEvent = fn_pGetEventPointerFromEdId_Map(ulEdId, 1, 1)) != 0)
            return pstBlockEvent;
        if ((pstBlockEvent = fn_pGetEventPointerFromEdId_Map(ulEdId, 0, 1)) != 0)
            return pstBlockEvent;
    }
    return 0;
}
