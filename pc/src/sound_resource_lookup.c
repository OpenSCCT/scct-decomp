#include "sound_bank_layout.h"
#include "sound_error.h"

tdstBlockResourceMem *__stdcall SND_fn_pGetBinRes(unsigned long ulBinId)
{
    if (!gs_bInitProjectDone) {
        SND_fn_vDisplayError(E_uwSndFatalErr,
                             "ERROR: Cannot get binary resource, project has not been initialized yet.");
        return 0;
    }
    switch (gs_eLoadProjectType) {
    case SND_E_DATALOADMODE_BANK:
        return SND_fn_pGetBinRes_Bank(ulBinId);
    case SND_E_DATALOADMODE_MAP:
        return SND_fn_pGetBinRes_Map(ulBinId);
    default:
        SND_fn_vDisplayError(E_uwSndFatalErr, "ERROR: Cannot get binary resource, load mode is not valid.");
        return 0;
    }
}

SND_tdstBlockEvent *__stdcall SND_fn_pGetBinEvent(unsigned long ulBinId)
{
    if (!gs_bInitProjectDone) {
        SND_fn_vDisplayError(E_uwSndFatalErr,
                             "ERROR: Cannot get binary event, project has not been initialized yet.");
        return 0;
    }
    switch (gs_eLoadProjectType) {
    case SND_E_DATALOADMODE_BANK:
        return SND_fn_pGetBinEvent_Bank(ulBinId);
    case SND_E_DATALOADMODE_MAP:
        return SND_fn_pGetBinEvent_Map(ulBinId);
    default:
        SND_fn_vDisplayError(E_uwSndFatalErr, "ERROR: Cannot get binary event, load mode is not valid.");
        return 0;
    }
}

SND_tdstBlockEvent *__stdcall SND_fn_hGetSoundEventHandleFromEditorId(unsigned long ulEdId)
{
    if (!gs_bInitProjectDone) {
        SND_fn_vDisplayError(E_uwSndFatalErr,
                             "ERROR: Cannot resolve event pointer with editor Id, project has not been initialized yet.");
        return 0;
    }
    switch (gs_eLoadProjectType) {
    case SND_E_DATALOADMODE_BANK:
        return SND_fn_hGetSoundEventHandleFromEditorId_Bank(ulEdId);
    case SND_E_DATALOADMODE_MAP:
        return SND_fn_hGetSoundEventHandleFromEditorId_Map(ulEdId);
    default:
        SND_fn_vDisplayError(E_uwSndFatalErr,
                             "ERROR: Cannot resolve event pointer with editor Id, load mode is not valid.");
        return 0;
    }
}

tdstBlockResourceMem *__stdcall SND_fn_pstGetResFromEdIdSnd(unsigned long ulEdId)
{
    switch (gs_eLoadProjectType) {
    case SND_E_DATALOADMODE_BANK:
        return SND_fn_pstGetResFromEdIdSnd_Bank(ulEdId);
    case SND_E_DATALOADMODE_MAP:
        return SND_fn_pstGetResFromEdIdSnd_Map(ulEdId);
    default:
        SND_fn_vDisplayError(E_uwSndFatalErr,
                             "ERROR: Cannot resolve event pointer with editor Id, load mode is not valid.");
        return 0;
    }
}
