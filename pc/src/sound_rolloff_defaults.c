/* sound_rolloff_defaults.c -- reads the default roll-off (sndspace.c) */
#include "sound_space.h"

/* SND_fn_vGetDefaultRollOff */
void __stdcall SND_fn_vGetDefaultRollOff(RollOffParam *pstRollOff)
{
    pstRollOff->rDistSatur = gs_rDefaultDistSatur;
    pstRollOff->rDistBackGround = gs_rDefaultDistBackGround;
    pstRollOff->rDistTransitLinear = gs_rDefaultDistTransitLinear;
    pstRollOff->rDistInaudible = gs_rDefaultDistInaudible;
}
