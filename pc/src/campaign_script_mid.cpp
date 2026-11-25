// campaign_script_mid.cpp -- slice a script string by starting index and optional length
#include "unreal_script.h"
#include "unreal_containers.h"

// UObject::execMid
void UObject::execMid(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_GET_INT(Start);
    P_GET_INT_OPTX(Count, MAXWORD);
    P_FINISH;
    *(FString *)Result = S.Mid(Start, Count);
}
