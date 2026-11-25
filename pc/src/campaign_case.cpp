// campaign_case.cpp -- evaluate a non-default case expression and discard its result
#include "unreal_script.h"
#include "unreal_containers.h"

// UObject::execCase
void UObject::execCase(FFrame &Stack, RESULT_DECL)
{
    if (Stack.ReadWord() != MAXWORD) {
        BYTE Value[1024];
        appMemzero(Value, sizeof(FString));
        Stack.Step(Stack.Object, Value);
    }
}
