// campaign_leaf_1862a0.cpp -- AActor::execSetIKFade
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execSetIKFade
// Parameters are named by position; the script declaration is not decoded yet. Both are
// floats as far as the bytes tell: with two integers the compiler allocates other registers.
void AActor::execSetIKFade(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Option1);
    P_GET_FLOAT(Option2);
    P_FINISH;
    SetIKFade(Option1, Option2);
}
