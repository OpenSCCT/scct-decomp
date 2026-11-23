// campaign_leaf_3f05e0.cpp -- UObject::execDivideEqual_IntFloat
#include "unreal_script.h"

// UObject::execDivideEqual_IntFloat: A /= B, leaving A alone when B is zero
void UObject::execDivideEqual_IntFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_REF(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f)
        *(INT *)Result = 0;
    else
        *(INT *)Result = (*A = (INT)(*A / B));
}
