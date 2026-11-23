// campaign_leaf_3ef020.cpp -- UObject::execDynamicCast
#include "unreal_script.h"
#include "unreal_class.h"

// UObject::execDynamicCast
void UObject::execDynamicCast(FFrame &Stack, RESULT_DECL)
{
    UClass *Class = (UClass *)Stack.ReadObject();
    P_GET_OBJECT(UObject, Castee);
    *(UObject **)Result = (Castee && Castee->IsA(Class)) ? Castee : 0;
}
