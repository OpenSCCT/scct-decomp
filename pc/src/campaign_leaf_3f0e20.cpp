// campaign_leaf_3f0e20.cpp -- UObject::execPercent_FloatFloat
#include "unreal_script.h"

DOUBLE Unk_10ccab40(DOUBLE X, DOUBLE Y);

// UObject::execPercent_FloatFloat
void UObject::execPercent_FloatFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT *)Result = (FLOAT)Unk_10ccab40(A, B);
}
