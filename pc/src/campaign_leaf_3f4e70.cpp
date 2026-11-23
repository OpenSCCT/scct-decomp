// campaign_leaf_3f4e70.cpp -- UObject::execGotoLabel
#include "unreal_script.h"

// UObject::execGotoLabel
void UObject::execGotoLabel(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(Label);
    if (!GotoLabel(Label, 0, 0))
        Stack.Logf(L"GotoLabel (%s): Label not found", *Label);
}
