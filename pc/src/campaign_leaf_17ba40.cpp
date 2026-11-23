// campaign_leaf_17ba40.cpp -- AActor::execSetCollisionSize
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execSetCollisionSize
void AActor::execSetCollisionSize(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(NewRadius);
    P_GET_FLOAT(NewHeight);
    P_FINISH;
    SetCollisionSize(NewRadius, NewHeight, 0);
    *(DWORD *)Result = 1;
}
