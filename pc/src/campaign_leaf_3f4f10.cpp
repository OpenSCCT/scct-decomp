// campaign_leaf_3f4f10.cpp -- UObject::execMetaCast
#include "unreal_script.h"
#include "unreal_class.h"

// UObject::execMetaCast: Castee when it is a class derived from MetaClass, otherwise none
void UObject::execMetaCast(FFrame &Stack, RESULT_DECL)
{
    UClass *MetaClass = (UClass *)Stack.ReadObject();
    P_GET_OBJECT(UObject, Castee);
    *(UObject **)Result = (Castee && Castee->IsA(UClass::StaticClass())
                           && ((UClass *)Castee)->IsChildOf(MetaClass)) ? Castee : 0;
}
