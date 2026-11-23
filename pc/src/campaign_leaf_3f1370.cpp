// campaign_leaf_3f1370.cpp -- UObject::execComplementEqual_FloatFloat
#include "unreal_script.h"

// UObject::execComplementEqual_FloatFloat: whether A and B differ by less than 0.0001
void UObject::execComplementEqual_FloatFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    FLOAT Difference = A - B;
    *(DWORD *)Result = (Difference >= 0.0f ? Difference : -Difference) < 0.0001;
}
