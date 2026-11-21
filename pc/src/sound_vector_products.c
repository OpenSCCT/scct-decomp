/* sound_vector_products.c -- dot and cross products (sndvect.c) */
#include "sound_vector.h"

/* SND_fn_rScalaireVectorSnd: the dot product */
SndReal __stdcall SND_fn_rScalaireVectorSnd(const SndVector *v1, const SndVector *v2)
{
    return SND_fn_rMulRealRealSnd(v1->x, v2->x)
         + SND_fn_rMulRealRealSnd(v1->y, v2->y)
         + SND_fn_rMulRealRealSnd(v1->z, v2->z);
}

/* SND_fn_rPseudoScalaireNormeVectorSnd: the dot product with the quick multiplication */
SndReal __stdcall SND_fn_rPseudoScalaireNormeVectorSnd(const SndVector *v1, const SndVector *v2)
{
    return SND_fn_rMulRealRealQuickSnd(v1->x, v2->x)
         + SND_fn_rMulRealRealQuickSnd(v1->y, v2->y)
         + SND_fn_rMulRealRealQuickSnd(v1->z, v2->z);
}

/* SND_fn_vProduitVectorSnd: the cross product */
void __stdcall SND_fn_vProduitVectorSnd(const SndVector *v1, const SndVector *v2, SndVector *v)
{
    v->x = SND_fn_rMulRealRealSnd(v1->y, v2->z) - SND_fn_rMulRealRealSnd(v1->z, v2->y);
    v->y = SND_fn_rMulRealRealSnd(v1->z, v2->x) - SND_fn_rMulRealRealSnd(v1->x, v2->z);
    v->z = SND_fn_rMulRealRealSnd(v1->x, v2->y) - SND_fn_rMulRealRealSnd(v1->y, v2->x);
}
