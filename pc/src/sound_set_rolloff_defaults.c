/* sound_set_rolloff_defaults.c -- sets the default roll-off (sndspace.c) */
#include "sound_space.h"

/* SND_fn_vSetDefaultRollOff */
void __stdcall SND_fn_vSetDefaultRollOff(const RollOffParam *pstRollOff)
{
    if (pstRollOff->rDistSatur != ROLLOFF_DEFAULT)
        gs_rDefaultDistSatur = pstRollOff->rDistSatur;
    else
        gs_rDefaultDistSatur = 32768;
    gs_rDefaultDistBackGround =
        pstRollOff->rDistBackGround == ROLLOFF_DEFAULT ? ROLLOFF_NONE : pstRollOff->rDistBackGround;
    if (gs_rDefaultDistBackGround < gs_rDefaultDistSatur)
        gs_rDefaultDistBackGround = ROLLOFF_NONE;
    gs_rDefaultDistTransitLinear = pstRollOff->rDistTransitLinear;
    if (pstRollOff->rDistTransitLinear == ROLLOFF_DEFAULT)
        gs_rDefaultDistTransitLinear = ROLLOFF_NONE;
    gs_rDefaultDistInaudible = pstRollOff->rDistInaudible;
    if (pstRollOff->rDistInaudible == ROLLOFF_DEFAULT)
        gs_rDefaultDistInaudible = ROLLOFF_NONE;
}
