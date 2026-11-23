// campaign_leaf_17bbe0.cpp -- AActor::execSetDrawType
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execSetDrawType
void AActor::execSetDrawType(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(NewDrawType);
    P_FINISH;
    SetDrawType(NewDrawType);
}
