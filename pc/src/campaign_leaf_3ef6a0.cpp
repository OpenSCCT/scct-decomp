// campaign_leaf_3ef6a0.cpp -- UObject::execXorXor_BoolBool
#include "unreal_script.h"

// UObject::execXorXor_BoolBool
void UObject::execXorXor_BoolBool(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    P_GET_UBOOL(B);
    P_FINISH;
    *(DWORD *)Result = !A ^ !B;
}
