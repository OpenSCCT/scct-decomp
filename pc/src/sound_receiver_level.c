/* sound_receiver_level.c -- the loudest a sound is heard by any microphone (sndxdmic.c) */
#include "sound_micro.h"
#include "sound_volume.h"

/* SND_fn_rGetNormeSxd */
SndReal __stdcall SND_fn_rGetNormeSxd(const SoundParam *par3D)
{
    SndReal rRetVol_dB = SND_VOLUME_MIN_DB;
    tdstMicroDescription *pstMicro;
    SndVector vect;

    if (par3D->iFlags & 1)
        return 0;
    if (g_iNbMicrosSxd) {
        for (pstMicro = gs_stMicrosSxd.pList.hFirstElementDyn; pstMicro; pstMicro = pstMicro->hNextBrotherDyn) {
            SndReal rVol_dB = SND_VOLUME_MIN_DB;
            if (!pstMicro->bJustCreated) {
                int j;
                for (j = 0; j < par3D->iNbLinks; ++j)
                    if (par3D->astMicro[j].lId == (long)pstMicro)
                        break;
                if (j < par3D->iNbLinks && par3D->astMicro[j].bLinked) {
                    SndReal rDist;
                    vect.x = par3D->Pos.x - pstMicro->pos.x;
                    vect.y = par3D->Pos.y - pstMicro->pos.y;
                    vect.z = par3D->Pos.z - pstMicro->pos.z;
                    rDist = SND_fn_rPseudoNormeVectorSnd(&vect);
                    if (par3D->iFlags & 4)
                        rVol_dB = SND_fn_rDistanceToVolumeEx(rDist, &par3D->xExtra.stRollOff);
                    else
                        rVol_dB = SND_fn_rDistanceToVolume(rDist);
                }
            }
            if (rRetVol_dB < rVol_dB)
                rRetVol_dB = rVol_dB;
        }
    }
    return rRetVol_dB;
}
