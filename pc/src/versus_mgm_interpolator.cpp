#include "versus_mgm_interpolator.h"
#include <math.h>

extern "C" void *allocate_engine_buffer(unsigned int Bytes, const TCHAR *Tag);
extern "C" void release_engine_buffer(void *Pointer);

MgmInterpolator::MgmInterpolator()
    : SampleCount(0)
{
    for (INT i = 0; i < MGMINTERP_Count; ++i)
        Tables[i] = 0;
    BuildTables(300);
}

MgmInterpolator::~MgmInterpolator()
{
    if (SampleCount > 0) {
        for (INT Mode = MGMINTERP_Linear; Mode < MGMINTERP_Count; ++Mode)
            release_engine_buffer(Tables[Mode]);
    }
}

FLOAT MgmInterpolator::GetCoefficient(EMgmInterpolationMode Mode, INT Index) const
{
    return Tables[Mode][Index];
}

FLOAT MgmInterpolator::Mix(FLOAT From, FLOAT To, const MgmKeyInterpolation &Blend)
{
    const FLOAT Difference = To - From;
    FLOAT Fraction;
    if (Blend.Mode == MGMINTERP_Linear)
        Fraction = Blend.Elapsed / Blend.Duration;
    else
        Fraction = GetCoefficient(Blend.Mode, (INT)(SampleCount * (Blend.Elapsed / Blend.Duration)));
    return From + Difference * Fraction;
}

void MgmInterpolator::BuildTables(INT Count)
{
    SampleCount = Count;
    for (INT Mode = MGMINTERP_Linear; Mode < MGMINTERP_Count; ++Mode)
        Tables[Mode] = (FLOAT *)allocate_engine_buffer(Count * sizeof(FLOAT), 0);

    {
        const DOUBLE Step = 1.0 / Count;
        for (INT i = 0; i < Count; ++i)
            Tables[MGMINTERP_Linear][i] = i * Step;
    }

    {
        const DOUBLE Step = 1.0 / Count;
        for (INT i = 0; i < Count; ++i) {
            const DOUBLE T = i * Step;
            Tables[MGMINTERP_Square][i] = T * T;
        }
    }

    {
        const DOUBLE Step = 1.0 / Count;
        for (INT i = 0; i < Count; ++i)
            Tables[MGMINTERP_Root][i] = sqrt(i * Step);
    }

    {
        const DOUBLE HalfPi = 3.14159265358979 / 2.0;
        const DOUBLE Step = HalfPi * (1.0 / Count);
        for (INT i = 0; i < Count; ++i)
            Tables[MGMINTERP_Sin][i] = sin(i * Step);
    }

    {
        const DOUBLE Step = 1.0 / Count;
        for (INT i = 0; i < Count; ++i) {
            const DOUBLE T = i * Step - 1.0;
            Tables[MGMINTERP_Circle][i] = sqrt(1.0 - T * T);
        }
    }

    for (INT i = 0; i < Count; ++i)
        Tables[MGMINTERP_CircleDecel][i] = 1.0f - Tables[MGMINTERP_Circle][Count - 1 - i];
}
