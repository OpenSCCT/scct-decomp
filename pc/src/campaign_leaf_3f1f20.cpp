// campaign_leaf_3f1f20.cpp -- UObject::execLocalFRand
#include "unreal_script.h"

FLOAT Unk_10ccac70();

// UObject::execLocalFRand
void UObject::execLocalFRand(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FLOAT *)Result = Unk_10ccac70();
}
