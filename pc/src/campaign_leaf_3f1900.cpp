// campaign_leaf_3f1900.cpp -- UObject::execAcos
#include "unreal_script.h"
#include "unreal_math.h"

DOUBLE Unk_10ccab70(DOUBLE Value);

// UObject::execAcos
void UObject::execAcos(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_FINISH;
    A = Clamp(A, -1.0f, 1.0f);
    *(FLOAT *)Result = (FLOAT)Unk_10ccab70(A);
}
