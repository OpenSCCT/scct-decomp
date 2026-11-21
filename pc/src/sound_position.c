#include "sound_space.h"

static __forceinline unsigned char position_pan(const SndVector *src, const SndVector *mic,
                                                const SndVector *axis, int reverse)
{
    SndVector diro;
    SndReal n, s;
    int divisor, pp;

    diro.x = src->x - mic->x;
    diro.y = src->y - mic->y;
    diro.z = src->z - mic->z;
    n = SND_fn_rPseudoNormeVectorSnd(&diro);
    s = SND_fn_rPseudoScalaireNormeVectorSnd(&diro, axis);
    divisor = (2 * n) / 256;

    if (!divisor) {
        pp = 64;
    } else if (s <= -n) {
        pp = reverse ? 128 : 0;
    } else if (s >= n) {
        pp = reverse ? 0 : 128;
    } else {
        int displacement = ((s / 256) * 128) / divisor;
        pp = reverse ? 64 - displacement : 64 + displacement;
        if (pp < 0)
            pp = 0;
        if (pp > 128)
            pp = 128;
    }
    return (unsigned char)pp;
}

unsigned char __stdcall SND_fn_ucPositionToPan(const SndVector *src, const SndVector *mic,
                                               const SndVector *mic_nor, const SndVector *mic_tan)
{
    return position_pan(src, mic, mic_tan, 0);
}

unsigned char __stdcall SND_fn_ucPositionToDolby(const SndVector *src, const SndVector *mic,
                                                 const SndVector *mic_nor)
{
    return position_pan(src, mic, mic_nor, 1);
}

static __inline SndReal calcul_pseudo_d(SndReal a, SndReal b)
{
    a = SND_fn_rAbsRealSnd(a);
    b = SND_fn_rAbsRealSnd(b);
    if (a < b)
        return b + (a >> 1);
    return a + (b >> 1);
}

__declspec(noinline) SndReal __stdcall SND_fn_rPseudoNormeVectorSnd(const SndVector *v)
{
    SndReal x = SND_fn_rAbsRealSnd(v->x);
    SndReal y = SND_fn_rAbsRealSnd(v->y);
    SndReal z = SND_fn_rAbsRealSnd(v->z);
    return calcul_pseudo_d(calcul_pseudo_d(x, y), z);
}
