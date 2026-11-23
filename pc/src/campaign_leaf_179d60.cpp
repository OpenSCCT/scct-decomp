// campaign_leaf_179d60.cpp -- AActor::execFinishAnim
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execFinishAnim
void AActor::execFinishAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Channel);
    P_FINISH;
    LatentFloat = Channel;
    VirtualSlot71();
}
