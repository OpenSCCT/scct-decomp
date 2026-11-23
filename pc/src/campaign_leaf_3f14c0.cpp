// campaign_leaf_3f14c0.cpp -- UObject::execDivideEqual_FloatFloat
#include "unreal_script.h"

// UObject::execDivideEqual_FloatFloat: A /= B, leaving A alone when B is zero
void UObject::execDivideEqual_FloatFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT_REF(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f)
        *(FLOAT *)Result = 0.0f;
    else
        *(FLOAT *)Result = (*A /= B);
}
