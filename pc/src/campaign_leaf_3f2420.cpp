// campaign_leaf_3f2420.cpp -- UObject::execRotatorToBool
#include "unreal_script.h"
#include "unreal_math.h"

// UObject::execRotatorToBool
void UObject::execRotatorToBool(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR_OPTX(A, FRotator(0, 0, 0));
    *(DWORD *)Result = !A.IsZero();
}
