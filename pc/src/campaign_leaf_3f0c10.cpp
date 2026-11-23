// campaign_leaf_3f0c10.cpp -- UObject::execSubtract_PreFloat
#include "unreal_script.h"

// UObject::execSubtract_PreFloat
void UObject::execSubtract_PreFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    *(FLOAT *)Result = -A;
}
