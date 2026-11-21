#include "sound_space.h"

SndReal __stdcall SND_fn_rNormeVectorSnd(const SndVector *v)
{
    SndReal z = v->z >> 8;
    SndReal y = v->y >> 8;
    SndReal x = v->x >> 8;
    return x * x + y * y + z * z;
}

long __stdcall SND_fn_lSoundAngleToDolbyAngle(long lPrevious, long lCurrent)
{
    long reference = lPrevious % 360;
    long distance = lCurrent - reference;
    if (distance < 0)
        distance = -distance;
    if (distance > 180) {
        distance = 360 - distance;
        if (lCurrent > reference)
            distance = -distance;
    } else if (lCurrent < reference) {
        distance = -distance;
    }
    distance += lPrevious;
    if (distance >= 720)
        distance -= 720;
    else if (distance < 0)
        distance += 720;
    return distance;
}
