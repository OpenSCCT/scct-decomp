/* sound_space.h -- distance roll-off, Doppler and panning (sndspace.c) */
#ifndef SOUND_SPACE_H
#define SOUND_SPACE_H

#include "sound_real.h"
#include "sound_vector.h"

/* In a roll-off set by the caller, a distance of ROLLOFF_DEFAULT asks for the library
   default and ROLLOFF_NONE switches that stage off. Both macro names are invented. */
#define ROLLOFF_NONE    (-1)
#define ROLLOFF_DEFAULT (-2)

typedef struct _RollOffParam {
    SndReal rDistSatur;             /* nearer than this, the sound keeps its full volume */
    SndReal rDistBackGround;        /* farther than this, the attenuation stops growing */
    SndReal rDistTransitLinear;     /* where the linear fade to silence starts */
    SndReal rDistInaudible;         /* where the linear fade reaches silence */
} RollOffParam;

/* File-static in sndspace.c of the sibling builds. */
extern long gs_lSoundSpeed;                         /* metres per second; 0 switches Doppler off */
extern SndReal gs_rDefaultDistSatur;                /* the default roll-off, member by member */
extern SndReal gs_rDefaultDistBackGround;
extern SndReal gs_rDefaultDistTransitLinear;
extern SndReal gs_rDefaultDistInaudible;
extern SndReal LocalisedVolume_table[4][128];       /* decibels per band and position */
extern SndReal g_rCoefA[4];                         /* position = g_rCoefA * ratio + g_rCoefB */
extern SndReal g_rCoefB[4];
extern SndReal g_rLimitTab[4];                      /* the largest distance ratio of each band */
extern SndReal g_rCoefLinA;                         /* past the last band: a straight line */
extern SndReal g_rCoefLinB;
extern SndReal gs_arPanToRVol_dB[129];
extern float g_fDolbyLtCoef[360];
extern float g_fDolbyRtCoef[360];

SndReal __cdecl fn_rDist2Vol(SndReal rDist, SndReal rDistSatur);

void __stdcall SND_fn_vSetDefaultRollOff(const RollOffParam *pstRollOff);
void __stdcall SND_fn_vGetDefaultRollOff(RollOffParam *pstRollOff);
SndReal __stdcall SND_fn_rDistanceToVolume(SndReal _rDist);
SndReal __stdcall SND_fn_rDistanceToVolumeEx(SndReal _rDist, const RollOffParam *_pstRollOff);
SndReal __stdcall SND_fn_rDopplerPitch(const SndVector *Ps, const SndVector *Vs, const SndVector *Pm,
                                       const SndVector *Vm);
void __stdcall SND_fn_vSetDopplerFactor(SndReal rFactor);
SndReal __stdcall SND_fn_rGetDopplerFactor(void);
unsigned char __stdcall SND_fn_ucPositionToPan(const SndVector *src, const SndVector *mic,
                                               const SndVector *mic_nor, const SndVector *mic_tan);
unsigned char __stdcall SND_fn_ucPositionToDolby(const SndVector *src, const SndVector *mic,
                                                 const SndVector *mic_nor);
void __stdcall SND_fn_vVolPanToVolLR(SndReal rVol_dB, unsigned char ucPan, SndReal *prVolL_dB,
                                     SndReal *prVolR_dB);
long __stdcall SND_fn_lSoundAngleToDolbyAngle(long lPrevious, long lCurrent);
float __stdcall SND_fn_fGetDolbyLtCoef(long lAngle);
float __stdcall SND_fn_fGetDolbyRtCoef(long lAngle);

#endif
