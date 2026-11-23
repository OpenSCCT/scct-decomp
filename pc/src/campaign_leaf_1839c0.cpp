// campaign_leaf_1839c0.cpp -- AActor::execIsGameOver
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execIsGameOver
void AActor::execIsGameOver(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio)
        *(DWORD *)Result = Audio->IsGameOver();
    else
        *(DWORD *)Result = 0;
}
