// campaign_leaf_3f55b0.cpp -- UObject::execIntToString
#include "unreal_script.h"
#include "unreal_containers.h"

// UObject::execIntToString
void UObject::execIntToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(I);
    *(FString *)Result = FString::Printf(L"%i", I);
}
