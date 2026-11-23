// campaign_leaf_3f09c0.cpp -- UObject::execRand
#include "unreal_script.h"

INT Unk_10ccac00();

// UObject::execRand
void UObject::execRand(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(A);
    P_FINISH;
    INT Random = Unk_10ccac00();
    *(INT *)Result = A > 0 ? Random % A : 0;
}
