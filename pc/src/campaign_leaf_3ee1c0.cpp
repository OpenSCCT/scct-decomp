// campaign_leaf_3ee1c0.cpp -- UObject::execIsA
#include "unreal_script.h"
#include "unreal_class.h"

// UObject::execIsA
void UObject::execIsA(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(ClassName);
    P_FINISH;
    UClass *TempClass;
    for (TempClass = GetClass(); TempClass; TempClass = TempClass->GetSuperClass())
        if (TempClass->GetFName() == ClassName)
            break;
    *(DWORD *)Result = TempClass != 0;
}
