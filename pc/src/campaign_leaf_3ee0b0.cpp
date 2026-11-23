// campaign_leaf_3ee0b0.cpp -- UObject::execResetConfig
#include "unreal_script.h"

// UObject::execResetConfig
void UObject::execResetConfig(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    ResetConfig(GetClass(), L"", 1);
}
