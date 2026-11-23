// campaign_leaf_3ed990.cpp -- UObject::execEndFunctionParms
#include "unreal_script.h"

// UObject::execEndFunctionParms
// Steps back onto the end-of-parameters token so that the caller's P_FINISH consumes it.
void UObject::execEndFunctionParms(FFrame &Stack, RESULT_DECL)
{
    GPropObject = 0;
    Stack.Code--;
}
