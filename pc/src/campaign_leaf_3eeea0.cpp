// campaign_leaf_3eeea0.cpp -- UObject::execFinalFunction
#include "unreal_script.h"

// UObject::execFinalFunction
// Calls the function whose object the bytecode names, without a virtual lookup.
void UObject::execFinalFunction(FFrame &Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, (UFunction *)Stack.ReadObject());
}
