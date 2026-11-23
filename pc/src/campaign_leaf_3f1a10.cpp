// campaign_leaf_3f1a10.cpp -- UObject::execPow
#include "unreal_script.h"

DOUBLE Unk_10ccabd0(DOUBLE X, DOUBLE Y);

// UObject::execPow
void UObject::execPow(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT *)Result = (FLOAT)Unk_10ccabd0(A, B);
}
