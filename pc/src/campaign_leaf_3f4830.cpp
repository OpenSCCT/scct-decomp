// campaign_leaf_3f4830.cpp -- UObject::execGetStateName
#include "unreal_script.h"
#include "unreal_field.h"

// UObject::execGetStateName
void UObject::execGetStateName(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FName *)Result = (StateFrame && StateFrame->StateNode) ? StateFrame->StateNode->GetFName()
                                                              : FName(NAME_None);
}
