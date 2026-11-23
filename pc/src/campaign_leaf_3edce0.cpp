// campaign_leaf_3edce0.cpp -- UObject::execNotEqual_ObjectObject
#include "unreal_script.h"

// UObject::execNotEqual_ObjectObject
void UObject::execNotEqual_ObjectObject(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UObject, A);
    P_GET_OBJECT(UObject, B);
    P_FINISH;
    *(DWORD *)Result = A != B;
}
