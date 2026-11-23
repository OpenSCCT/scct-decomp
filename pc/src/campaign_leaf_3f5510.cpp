// campaign_leaf_3f5510.cpp -- UObject::execByteToString
#include "unreal_script.h"
#include "unreal_containers.h"

// UObject::execByteToString
void UObject::execByteToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(B);
    *(FString *)Result = FString::Printf(L"%i", B);
}
