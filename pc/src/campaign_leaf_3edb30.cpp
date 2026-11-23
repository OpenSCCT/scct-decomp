// campaign_leaf_3edb30.cpp -- UObject::execEqualEqual_NameName
#include "unreal_script.h"

// UObject::execEqualEqual_NameName
void UObject::execEqualEqual_NameName(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(A);
    P_GET_NAME(B);
    P_FINISH;
    *(DWORD *)Result = A == B;
}
