// campaign_leaf_3eeb30.cpp -- UObject::execDynArrayLength
#include "unreal_script.h"
#include "unreal_containers.h"
#include "campaign_global_11230574.h"

// UObject::execDynArrayLength
// Reads the length of a dynamic array; without a Result the script is assigning the length,
// which the interpreter records in a flag.
void UObject::execDynArrayLength(FFrame &Stack, RESULT_DECL)
{
    GProperty = 0;
    Stack.Step(this, 0);
    GPropObject = this;
    if (GPropAddr)
    {
        FArray *Array = (FArray *)GPropAddr;
        if (!Result)
            GUnk_11230574 |= 1;
        else
            *(INT *)Result = Array->ArrayNum;
    }
}
