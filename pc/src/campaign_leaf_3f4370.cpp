// campaign_leaf_3f4370.cpp -- UObject::execChr
#include "unreal_script.h"
#include "unreal_containers.h"

// UObject::execChr
void UObject::execChr(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(i);
    P_FINISH;
    TCHAR Temp[2];
    Temp[0] = i;
    Temp[1] = 0;
    *(FString *)Result = Temp;
}
