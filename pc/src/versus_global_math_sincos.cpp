#include "versus_build.h"
#include "unreal_math.h"

extern "C" double __cdecl sqrt(double);
extern "C" double __cdecl cos(double);
extern "C" double __cdecl fabs(double);
#pragma intrinsic(sqrt, cos, fabs)

static inline FLOAT Sign(FLOAT A)
{
    return A < 0.f ? -1.f : A > 0.f ? 1.f : 0.f;
}

void FGlobalMath::SinCos(INT Angle, FLOAT* OutSin, FLOAT* OutCos)
{
    const FLOAT Radians = Angle * (FLOAT)(2.0 * PI / 65536.0);
    const FLOAT Wrapped = Radians - (INT)(Radians * (FLOAT)(1.0 / (2.0 * PI))) * (FLOAT)(2.0 * PI);
    const FLOAT C = (FLOAT)cos(Radians);
    *OutCos = C;
    const FLOAT SineSign = (FLOAT)fabs(Wrapped) < (FLOAT)PI ? Sign(Wrapped) : -Sign(Wrapped);
    *OutSin = (FLOAT)sqrt(1.f - C * C) * SineSign;
}
