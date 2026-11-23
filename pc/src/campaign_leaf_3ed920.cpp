// campaign_leaf_3ed920.cpp -- UObject::execBoolVariable
#include "unreal_script.h"
#include "unreal_property.h"

// UObject::execBoolVariable
// Executes the variable expression that follows, then reads the property's bit.
void UObject::execBoolVariable(FFrame &Stack, RESULT_DECL)
{
    BYTE B = *Stack.Code++;
    UBoolProperty *Property = *(UBoolProperty **)Stack.Code;
    (this->*GNatives[B])(Stack, 0);
    GProperty = Property;
    GPropObject = this;
    if (Result)
        *(DWORD *)Result = (GPropAddr && (*(DWORD *)GPropAddr & Property->BitMask)) ? 1 : 0;
}
