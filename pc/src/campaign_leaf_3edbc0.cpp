// campaign_leaf_3edbc0.cpp -- UObject::execNotEqual_NameName
#include "unreal_script.h"

// UObject::execNotEqual_NameName
void UObject::execNotEqual_NameName(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(A);
    P_GET_NAME(B);
    P_FINISH;
    *(DWORD *)Result = A != B;
}
