// Core math wrappers. The compiler expands sqrt and atan2 as x87 intrinsics.
typedef double DOUBLE;
extern "C" double exp(double);
extern "C" double log(double);
extern "C" double sin(double);
extern "C" double cos(double);
extern "C" double asin(double);
extern "C" double tan(double);
extern "C" double atan(double);
extern "C" double sqrt(double);
extern "C" double atan2(double, double);
#pragma intrinsic(exp, log, sin, cos, asin, tan, atan, sqrt, atan2)

DOUBLE appExp(DOUBLE Value)
{
    return exp(Value);
}

DOUBLE appLoge(DOUBLE Value)
{
    return log(Value);
}

DOUBLE appSin(DOUBLE Value)
{
    return sin(Value);
}

DOUBLE appCos(DOUBLE Value)
{
    return cos(Value);
}

DOUBLE appAsin(DOUBLE Value)
{
    return asin(Value);
}

DOUBLE appTan(DOUBLE Value)
{
    return tan(Value);
}

DOUBLE appAtan(DOUBLE Value)
{
    return atan(Value);
}

DOUBLE appSqrt(DOUBLE Value)
{
    return sqrt(Value);
}

DOUBLE appAtan2(DOUBLE Y, DOUBLE X)
{
    return atan2(Y, X);
}
