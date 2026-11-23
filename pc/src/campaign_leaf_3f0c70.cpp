// campaign_leaf_3f0c70.cpp -- UObject::execMultiplyMultiply_FloatFloat
#include "unreal_script.h"

DOUBLE Unk_10ccabd0(DOUBLE X, DOUBLE Y);

// UObject::execMultiplyMultiply_FloatFloat
void UObject::execMultiplyMultiply_FloatFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT *)Result = (FLOAT)Unk_10ccabd0(A, B);
}
