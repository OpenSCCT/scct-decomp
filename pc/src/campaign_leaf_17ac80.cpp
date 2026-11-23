// campaign_leaf_17ac80.cpp -- AActor::execAnimBlendToAlpha
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execAnimBlendToAlpha
void AActor::execAnimBlendToAlpha(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Channel);
    P_GET_FLOAT(DestAlpha);
    P_GET_FLOAT(TweenTime);
    P_FINISH;
    AnimBlendToAlpha(Channel, DestAlpha, TweenTime);
}
