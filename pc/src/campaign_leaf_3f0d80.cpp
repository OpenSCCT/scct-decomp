// campaign_leaf_3f0d80.cpp -- UObject::execDivide_FloatFloat
#include "unreal_script.h"

// UObject::execDivide_FloatFloat
void UObject::execDivide_FloatFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    if (B == 0.0f)
        *(FLOAT *)Result = 0.0f;
    else
        *(FLOAT *)Result = A / B;
}
