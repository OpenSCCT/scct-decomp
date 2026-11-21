// campaign_engine_helpers_2.cpp -- InterpolateRotatorValue and FVector::Rotation
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"

// FVector::Rotation
FRotator FVector::Rotation()
{
    FRotator R;
    R.Yaw = (INT)(appAtan2(Y, X) * (FLOAT)MAXWORD / (2.f * PI));
    R.Pitch = (INT)(appAtan2(Z, appSqrt(X * X + Y * Y)) * (FLOAT)MAXWORD / (2.f * PI));
    R.Roll = 0;
    return R;
}

// InterpolateRotatorValue
// The script passes the rate first; the native above names its parameters by position.
INT InterpolateRotatorValue(FLOAT Rate, INT Current, INT Desired)
{
    INT Result = 0;
    Current &= 0xFFFF;
    Desired &= 0xFFFF;
    if (Current == Desired)
        Result = Current;
    if (Current > Desired)
    {
        INT Delta = Current - Desired;
        if (Delta < 0x8000)
        {
            if (Delta > Rate)
                Result = (INT)(Current - Rate);
            else
                Result = Desired;
        }
        else
        {
            Delta = 0x10000 - Delta;
            if (Delta > Rate)
                Result = (INT)(Current + Rate);
            else
                Result = Desired;
        }
    }
    else if (Desired > Current)
    {
        INT Delta = Desired - Current;
        if (Delta < 0x8000)
        {
            if (Delta > Rate)
                Result = (INT)(Current + Rate);
            else
                Result = Desired;
        }
        else
        {
            Delta = 0x10000 - Delta;
            if (Delta > Rate)
                Result = (INT)(Current - Rate);
            else
                Result = Desired;
        }
    }
    return Result & 0xFFFF;
}
