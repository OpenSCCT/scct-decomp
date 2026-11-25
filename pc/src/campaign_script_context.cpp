// campaign_script_context.cpp -- object and class contexts for script evaluation
#include "unreal_script.h"
#include "unreal_class.h"

// UObject::execContext
void UObject::execContext(FFrame &Stack, RESULT_DECL)
{
    UObject *Context = 0;
    Stack.Step(this, &Context);
    if (Context) {
        Stack.Code += sizeof(_WORD) + sizeof(BYTE);
        Stack.Step(Context, Result);
    } else {
        Stack.Logf(L"Accessed None");
        INT Skip = Stack.ReadWord();
        BYTE Size = *Stack.Code++;
        Stack.Code += Skip;
        GPropAddr = 0;
        GProperty = 0;
        GPropObject = 0;
        if (Result)
            appMemzero(Result, Size);
    }
}

// UObject::execStaticSaveConfig
void UObject::execStaticSaveConfig(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    GetClass()->GetDefaultObject()->SaveConfig();
}

// UObject::execClassContext
void UObject::execClassContext(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UClass, Context);
    if (Context) {
        Stack.Code += sizeof(_WORD) + sizeof(BYTE);
        Stack.Step(Context->GetDefaultObject(), Result);
    } else {
        Stack.Logf(L"Accessed null class context");
        INT Skip = Stack.ReadWord();
        BYTE Size = *Stack.Code++;
        Stack.Code += Skip;
        GPropAddr = 0;
        GPropObject = 0;
        GProperty = 0;
        if (Result)
            appMemzero(Result, Size);
    }
}
