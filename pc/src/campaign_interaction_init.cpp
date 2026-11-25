// campaign_interaction_init.cpp -- start script execution and dispatch the Initialized event
#include "unreal_script.h"
#include "unreal_interaction.h"

// UInteraction::eventInitialized
void UInteraction::eventInitialized()
{
    ProcessEvent(FindFunctionChecked(name_Initialized, 0), 0);
}

// UInteraction::execInitialize
void UInteraction::execInitialize(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    InitExecution();
    eventInitialized();
}
