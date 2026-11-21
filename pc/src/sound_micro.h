/* sound_micro.h -- microphones and the conversion of sound parameters for them (sndxdmic.c) */
#ifndef SOUND_MICRO_H
#define SOUND_MICRO_H

#include "sound_param.h"
#include "sound_resource.h"

typedef struct _tdstMicroDescription tdstMicroDescription;

typedef struct SNDLST2_tdstAnchorToLP_MICRO_DESCRIPTIONDyn {
    tdstMicroDescription *hFirstElementDyn;
    tdstMicroDescription *hLastElementDyn;
    long lNumberOfElementsDyn;
} SNDLST2_tdstAnchorToLP_MICRO_DESCRIPTIONDyn;

typedef struct _tdstMicroList {
    SNDLST2_tdstAnchorToLP_MICRO_DESCRIPTIONDyn pList;
} tdstMicroList;

struct _tdstMicroDescription {
    SndVector pos;
    SndVector vit;
    SndVector dir_nor;
    SndVector dir_tan;
    int bJustCreated;               /* created without parameters: not heard until they are set.
                                       A whole int here; a one-bit field in the sibling build. */
    int unk_34;
    tdstMicroDescription *hNextBrotherDyn;
    tdstMicroDescription *hPrevBrotherDyn;
    SNDLST2_tdstAnchorToLP_MICRO_DESCRIPTIONDyn *hFatherDyn;
};

/* File-static in sndxdmic.c of the sibling builds. */
extern long g_iNbMicrosSxd;
extern tdstMicroList gs_stMicrosSxd;
/* Function-static of Snd_ParConv_ConvertWithNoMicro in the sibling build. It is declared here
   because the verifier's link model resolves no private data. */
extern int bDisplayed;

float __fastcall fn_fGetObjectAngleWithMicroNor(const SndVector *pos);
void __cdecl Snd_ParConv_ConvertWithNoMicro(const SoundParam *par3D, PrivateSoundParam *par);
void __cdecl Snd_ParConv_ConvertWithOneMicro(const SoundParam *par3D, PrivateSoundParam *par);

SndReal __stdcall SND_fn_rGetNormeSxd(const SoundParam *par3D);
void __stdcall SND_fn_vSndParToPrivSndPar(const SoundParam *par3D, PrivateSoundParam *par,
                                          tdePositionFormat format);
void __stdcall SND_fn_vBestConvertionForSndParToPrivSndPar(const SoundParam *par3D,
                                                           PrivateSoundParam *par,
                                                           tdePositionFormat format,
                                                           const tdstBlockResourceMem *res);

#endif
