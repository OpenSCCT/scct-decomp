// campaign_leaf_3edc50.cpp -- UObject::execEqualEqual_ObjectObject
#include "unreal_script.h"

// UObject::execEqualEqual_ObjectObject
void UObject::execEqualEqual_ObjectObject(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UObject, A);
    P_GET_OBJECT(UObject, B);
    P_FINISH;
    *(DWORD *)Result = A == B;
}
