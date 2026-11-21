// Core math wrappers. The compiler expands sqrt and atan2 as x87 intrinsics.
typedef double DOUBLE;
extern "C" double sqrt(double);
extern "C" double atan2(double, double);
#pragma intrinsic(sqrt, atan2)

DOUBLE appSqrt(DOUBLE Value)
{
    return sqrt(Value);
}

DOUBLE appAtan2(DOUBLE Y, DOUBLE X)
{
    return atan2(Y, X);
}
