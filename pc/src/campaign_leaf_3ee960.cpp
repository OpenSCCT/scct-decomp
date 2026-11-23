// campaign_leaf_3ee960.cpp -- UObject::execLocalVariable
#include "unreal_script.h"
#include "unreal_property.h"

// UObject::execLocalVariable
// Addresses a local variable of the executing function and copies its value to Result.
void UObject::execLocalVariable(FFrame &Stack, RESULT_DECL)
{
    GProperty = (UProperty *)Stack.ReadObject();
    GPropAddr = Stack.Locals + GProperty->Offset;
    GPropObject = 0;
    if (Result)
        GProperty->CopyCompleteValue(Result, GPropAddr);
}
