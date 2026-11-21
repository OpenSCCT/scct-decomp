/* sound_distance_to_volume.c -- distance to volume with the default roll-off (sndspace.c) */
#include "sound_space.h"

/* SND_fn_rDistanceToVolume */
SndReal __stdcall SND_fn_rDistanceToVolume(SndReal _rDist)
{
    RollOffParam rolloff;
    rolloff.rDistSatur = gs_rDefaultDistSatur;
    rolloff.rDistBackGround = gs_rDefaultDistBackGround;
    rolloff.rDistTransitLinear = gs_rDefaultDistTransitLinear;
    rolloff.rDistInaudible = gs_rDefaultDistInaudible;
    return SND_fn_rDistanceToVolumeEx(_rDist, &rolloff);
}
