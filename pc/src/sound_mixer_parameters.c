/* sound_mixer_parameters.c -- a sound's parameters converted for a renderer (sndxdmic.c) */
#include "sound_micro.h"
#include "sound_manager.h"

/* Snd_ParConv_ConvertWithNoPosition: the volume and pan as the game gave them */
static __forceinline void Snd_ParConv_ConvertWithNoPosition(const SoundParam *par3D,
                                                            PrivateSoundParam *par)
{
    par->volume = par3D->rVol_dB;
    par->pitch = par3D->Freq;
    switch (par->format) {
    case 0:
        par->position.channels.pan = par3D->ucPan;
        break;
    case 1:
        par->position.channels.pan = par3D->ucPan;
        par->position.channels.dolby = 0;
        break;
    case 2:
        par->position.angle = 0;
        break;
    }
}

/* SND_fn_vSndParToPrivSndPar */
__declspec(noinline) void __stdcall SND_fn_vSndParToPrivSndPar(const SoundParam *par3D,
                                                               PrivateSoundParam *par,
                                                               tdePositionFormat format)
{
    par->format = format;
    if (par3D->iFlags & 1)
        Snd_ParConv_ConvertWithNoPosition(par3D, par);
    else if (!g_iNbMicrosSxd)
        Snd_ParConv_ConvertWithNoMicro(par3D, par);
    else
        Snd_ParConv_ConvertWithOneMicro(par3D, par);
}

/* SND_fn_vBestConvertionForSndParToPrivSndPar: a resource with several channels keeps a plain
   pan, centred unless the resource may be panned */
void __stdcall SND_fn_vBestConvertionForSndParToPrivSndPar(const SoundParam *par3D,
                                                           PrivateSoundParam *par,
                                                           tdePositionFormat format,
                                                           const tdstBlockResourceMem *res)
{
    tdePositionFormat chosen = format;
    if (res && res->eType == TYPE_SAMPLE && SND_fn_ulGetResourceNbChannel(res) > 1)
        chosen = 0;
    if (format == 2 && (par3D->iFlags & 1))
        chosen = 0;
    SND_fn_vSndParToPrivSndPar(par3D, par, chosen);
    if (res && SND_fn_ulGetResourceNbChannel(res) > 1 && !res->uRes.stSample.bBalance)
        par->position.channels.pan = 64;
}
