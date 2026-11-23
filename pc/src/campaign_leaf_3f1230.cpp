// campaign_leaf_3f1230.cpp -- UObject::execEqualEqual_FloatFloat
#include "unreal_script.h"

// UObject::execEqualEqual_FloatFloat
void UObject::execEqualEqual_FloatFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD *)Result = A == B;
}
