#include "sound_bank_layout.h"
#include "sound_error.h"


tdstBlockResourceMem *__stdcall SND_fn_pGetBinRes_Map(unsigned long _ulBinId)
{
    tdstMapMem *pstMapMem;
    tdstBlockResMemList *pstBlockResMemList;
    unsigned long ulBinId = _ulBinId;
    unsigned long bLocalised;
    tdstBlockResourceMem *pstBlockResMem;
    if (ulBinId == (unsigned long)-2)
        return 0;
    pstMapMem = (ulBinId >> 31) ? &gs_stCurrentMap : &gs_stMapFix;
    bLocalised = (ulBinId >> 30) & 1;
    ulBinId &= 0xffff;
    pstBlockResMemList = bLocalised ? &pstMapMem->stLoc.stBlockResMemList : &pstMapMem->stNLoc.stBlockResMemList;
    pstBlockResMem = pstBlockResMemList->hFirstElementOpt + ulBinId;
    if (!pstBlockResMem)
        SND_fn_vDisplayError(E_uwSndGenericWarning, "ERROR: Cannot find block resource memory");
    return pstBlockResMem;
}

SND_tdstBlockEvent *__cdecl SND_fn_pGetBinEvent_Map(unsigned long _ulBinId)
{
    tdstMapMem *pstMapMem;
    tdstBlockEventList *pstBlockEventList;
    unsigned long ulBinId = _ulBinId;
    unsigned long bLocalised;
    SND_tdstBlockEvent *pstBlockEvent;
    pstMapMem = (ulBinId >> 31) ? &gs_stCurrentMap : &gs_stMapFix;
    bLocalised = (ulBinId >> 30) & 1;
    ulBinId &= 0xffff;
    pstBlockEventList = bLocalised ? &pstMapMem->stLoc.pstMapHeader->stBlockEventList
                                   : &pstMapMem->stNLoc.pstMapHeader->stBlockEventList;
    pstBlockEvent = pstBlockEventList->hFirstElementOpt + ulBinId;
    if (!pstBlockEvent)
        SND_fn_vDisplayError(E_uwSndGenericWarning, "ERROR: Cannot find block event.");
    return pstBlockEvent;
}
