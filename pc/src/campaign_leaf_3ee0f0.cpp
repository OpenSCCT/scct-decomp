// campaign_leaf_3ee0f0.cpp -- UObject::execIsInState
#include "unreal_script.h"
#include "unreal_field.h"

// UObject::execIsInState
void UObject::execIsInState(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(StateName);
    P_FINISH;
    if (StateFrame)
        for (UState *Test = StateFrame->StateNode; Test; Test = Test->GetSuperState())
            if (Test->GetFName() == StateName)
            {
                *(DWORD *)Result = 1;
                return;
            }
    *(DWORD *)Result = 0;
}
