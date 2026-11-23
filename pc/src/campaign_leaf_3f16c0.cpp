// campaign_leaf_3f16c0.cpp -- UObject::execAbs
#include "unreal_script.h"

// UObject::execAbs
void UObject::execAbs(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT *)Result = A >= 0.0f ? A : -A;
}
