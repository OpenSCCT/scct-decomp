// campaign_leaf_3f12d0.cpp -- UObject::execNotEqual_FloatFloat
#include "unreal_script.h"

// UObject::execNotEqual_FloatFloat
void UObject::execNotEqual_FloatFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(DWORD *)Result = A != B;
}
