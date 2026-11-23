// campaign_leaf_3f1ef0.cpp -- UObject::execFRand
#include "unreal_script.h"

FLOAT Unk_10ccac40();

// UObject::execFRand
void UObject::execFRand(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(FLOAT *)Result = Unk_10ccac40();
}
