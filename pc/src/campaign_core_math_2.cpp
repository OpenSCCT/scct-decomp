// campaign_core_math_2.cpp -- the other one-argument math wrappers of the core
//
// The compiler expands each C function as an x87 intrinsic.
#include "unreal_math.h"

extern "C" double exp(double);
extern "C" double log(double);
extern "C" double sin(double);
extern "C" double cos(double);
extern "C" double asin(double);
extern "C" double tan(double);
extern "C" double atan(double);
#pragma intrinsic(exp, log, sin, cos, asin, tan, atan)

// appExp
DOUBLE appExp(DOUBLE Value)
{
    return exp(Value);
}

// appLoge
DOUBLE appLoge(DOUBLE Value)
{
    return log(Value);
}

// appSin
DOUBLE appSin(DOUBLE Value)
{
    return sin(Value);
}

// appCos
DOUBLE appCos(DOUBLE Value)
{
    return cos(Value);
}

// appAsin
DOUBLE appAsin(DOUBLE Value)
{
    return asin(Value);
}

// appTan
DOUBLE appTan(DOUBLE Value)
{
    return tan(Value);
}

// appAtan
DOUBLE appAtan(DOUBLE Value)
{
    return atan(Value);
}
