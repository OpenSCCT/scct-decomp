// campaign_leaf_17c9f0.cpp -- AActor::execDestroy
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::execDestroy
void AActor::execDestroy(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    *(DWORD *)Result = XLevel->DestroyActor(this);
}
