// campaign_leaf_17e4b0.cpp -- AActor::execAdd_ColorColor
#include "unreal_script.h"
#include "unreal_actor.h"

// AActor::execAdd_ColorColor
// The alpha of A passes through unchanged.
void AActor::execAdd_ColorColor(FFrame &Stack, RESULT_DECL)
{
    P_GET_STRUCT(FColor, A);
    P_GET_STRUCT(FColor, B);
    P_FINISH;
    A.R += B.R;
    A.G += B.G;
    A.B += B.B;
    *(FColor *)Result = A;
}
