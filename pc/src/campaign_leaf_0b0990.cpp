// campaign_leaf_0b0990.cpp -- AActor::execPlayerCanSeeMe
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execPlayerCanSeeMe: whether the time at 0x50 is less than a second behind the level's
void AActor::execPlayerCanSeeMe(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(DWORD *)Result = XLevel->TimeSeconds - unk_50 < 1.0;
}
