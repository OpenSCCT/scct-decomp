// campaign_core_math.cpp -- appSqrt and appAtan2
//
// The compiler expands sqrt and atan2 as x87 intrinsics.
#include "unreal_math.h"

extern "C" double sqrt(double);
extern "C" double atan2(double, double);
#pragma intrinsic(sqrt, atan2)

// appSqrt
DOUBLE appSqrt(DOUBLE Value)
{
    return sqrt(Value);
}

// appAtan2
DOUBLE appAtan2(DOUBLE Y, DOUBLE X)
{
    return atan2(Y, X);
}
