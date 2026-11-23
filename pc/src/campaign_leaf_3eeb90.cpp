// campaign_leaf_3eeb90.cpp -- UObject::execNativeParm
#include "unreal_script.h"
#include "unreal_property.h"

// UObject::execNativeParm
// Copies a parameter of the executing function to Result.
void UObject::execNativeParm(FFrame &Stack, RESULT_DECL)
{
    UProperty *Property = (UProperty *)Stack.ReadObject();
    if (Result)
    {
        GPropAddr = Stack.Locals + Property->Offset;
        GPropObject = 0;
        Property->CopyCompleteValue(Result, Stack.Locals + Property->Offset);
    }
}
