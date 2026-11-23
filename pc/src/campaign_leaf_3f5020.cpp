// campaign_leaf_3f5020.cpp -- UObject::execNameToString
#include "unreal_script.h"
#include "unreal_containers.h"

// UObject::execNameToString
void UObject::execNameToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(A);
    *(FString *)Result = *A;
}
