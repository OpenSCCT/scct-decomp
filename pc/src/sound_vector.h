/* sound_vector.h -- fixed-point vectors of the sound library (sndvect.c) */
#ifndef SOUND_VECTOR_H
#define SOUND_VECTOR_H

#include "sound_real.h"

typedef struct _SndVector {
    SndReal x;
    SndReal y;
    SndReal z;
} SndVector;

SndReal __stdcall SND_fn_rNormeVectorSnd(const SndVector *v);
SndReal __stdcall SND_fn_rPseudoNormeVectorSnd(const SndVector *v);
SndReal __stdcall SND_fn_rScalaireVectorSnd(const SndVector *v1, const SndVector *v2);
SndReal __stdcall SND_fn_rPseudoScalaireNormeVectorSnd(const SndVector *v1, const SndVector *v2);
void __stdcall SND_fn_vProduitVectorSnd(const SndVector *v1, const SndVector *v2, SndVector *v);

#endif
