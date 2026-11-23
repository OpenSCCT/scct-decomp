// campaign_leaf_3f43e0.cpp -- UObject::execClassIsChildOf
#include "unreal_script.h"
#include "unreal_class.h"

// UObject::execClassIsChildOf
void UObject::execClassIsChildOf(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UClass, TestClass);
    P_GET_OBJECT(UClass, ParentClass);
    P_FINISH;
    *(DWORD *)Result = (ParentClass && TestClass) ? TestClass->IsChildOf(ParentClass) : 0;
}
