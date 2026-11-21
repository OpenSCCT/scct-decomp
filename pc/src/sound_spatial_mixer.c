#include "sound_micro.h"
#include "sound_volume.h"

static __forceinline void convert_for_micro(const SoundParam *par3D, PrivateSoundParam *par,
                                            tdstMicroDescription *pstMicro)
{
    int i, angle;
    unsigned char ucPan, ucDolby;
    SndReal rVol_dB, rDoppler;

    ucPan = 64;
    ucDolby = 0;
    rVol_dB = 0;
    rDoppler = 65536;
    angle = 0;

    if (!pstMicro->bJustCreated) {
        for (i = 0; i < par3D->iNbLinks; ++i)
            if (par3D->astMicro[i].lId == (long)pstMicro)
                break;
        if (i < par3D->iNbLinks && par3D->astMicro[i].bLinked) {
            SndVector vect;
            SndReal rDist;
            vect.x = par3D->Pos.x - pstMicro->pos.x;
            vect.y = par3D->Pos.y - pstMicro->pos.y;
            vect.z = par3D->Pos.z - pstMicro->pos.z;
            rDist = SND_fn_rPseudoNormeVectorSnd(&vect);
            if (par3D->iFlags & 4)
                rVol_dB = SND_fn_rDistanceToVolumeEx(rDist, &par3D->xExtra.stRollOff);
            else
                rVol_dB = SND_fn_rDistanceToVolume(rDist);
            switch (par->format) {
            case 0:
                ucPan = SND_fn_ucPositionToPan(&par3D->Pos, &pstMicro->pos, &pstMicro->dir_nor,
                                               &pstMicro->dir_tan);
                break;
            case 1:
                ucPan = SND_fn_ucPositionToPan(&par3D->Pos, &pstMicro->pos, &pstMicro->dir_nor,
                                               &pstMicro->dir_tan);
                ucDolby = SND_fn_ucPositionToDolby(&par3D->Pos, &pstMicro->pos, &pstMicro->dir_nor);
                break;
            case 2:
                angle = (int)(360.0f * fn_fGetObjectAngleWithMicroNor(&par3D->Pos));
                break;
            }
            if (!(par3D->iFlags & 2))
                rDoppler = SND_fn_rDopplerPitch(&par3D->Pos, &par3D->Vit, &pstMicro->pos, &pstMicro->vit);
        }
    }
    par->pitch = SND_fn_rMulRealRealSnd(rDoppler, par3D->Freq);
    par->volume = par3D->rVol_dB + rVol_dB;
    if (par->volume < SND_VOLUME_MIN_DB)
        par->volume = SND_VOLUME_MIN_DB;
    switch (par->format) {
    case 0:
        par->position.channels.pan = ucPan;
        break;
    case 1:
        par->position.channels.pan = ucPan;
        par->position.channels.dolby = ucDolby;
        break;
    case 2:
        par->position.angle = angle;
        break;
    }
}

void __cdecl Snd_ParConv_ConvertWithOneMicro(const SoundParam *par3D, PrivateSoundParam *par)
{
    convert_for_micro(par3D, par, gs_stMicrosSxd.pList.hFirstElementDyn);
}
