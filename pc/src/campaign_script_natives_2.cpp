// campaign_script_natives_2.cpp -- Campaign script natives: string conversions and comparisons
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"

// UObject::execAssert
void UObject::execAssert(FFrame &Stack, RESULT_DECL)
{
    INT wLine = Stack.ReadWord();
    UBOOL Value = 0;
    Stack.Step(Stack.Object, &Value);
    if (!Value)
        Stack.Logf(NAME_Critical, (const TCHAR *)L"Assertion failed, line %i", wLine);
}

// UObject::execObjectToString
void UObject::execObjectToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UObject, A);
    *(FString *)Result = A ? A->GetName() : (const TCHAR *)L"None";
}

// UObject::execVectorToBool
void UObject::execVectorToBool(FFrame &Stack, RESULT_DECL)
{
    FVector V(0.0f, 0.0f, 0.0f);
    Stack.Step(Stack.Object, &V);
    *(DWORD *)Result = V.IsZero() ? 0 : 1;
}

// UObject::execLen
void UObject::execLen(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT *)Result = S.Len();
}

// UObject::execStringToInt
void UObject::execStringToInt(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(INT *)Result = appAtoi(*Str);
}

// UObject::execStringToByte
void UObject::execStringToByte(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(BYTE *)Result = appAtoi(*Str);
}

// UObject::execStringToFloat
void UObject::execStringToFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    *(FLOAT *)Result = appAtof(*Str);
}

// UObject::execAsc
void UObject::execAsc(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(INT *)Result = **S;
}

// UObject::execEatString
void UObject::execEatString(FFrame &Stack, RESULT_DECL)
{
    FString String;
    Stack.Step(this, &String);
}

// UObject::execEqualEqual_StringString
void UObject::execEqualEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) == 0;
}

// UObject::execNotEqual_StringString
void UObject::execNotEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) != 0;
}

// UObject::execLess_StringString
void UObject::execLess_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) < 0;
}

// UObject::execGreater_StringString
void UObject::execGreater_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) > 0;
}

// UObject::execLessEqual_StringString
void UObject::execLessEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) <= 0;
}

// UObject::execGreaterEqual_StringString
void UObject::execGreaterEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStrcmp(*A, *B) >= 0;
}

// UObject::execComplementEqual_StringString
void UObject::execComplementEqual_StringString(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_GET_STR(B);
    P_FINISH;
    *(DWORD *)Result = appStricmp(*A, *B) == 0;
}

// UObject::execStringToBool
void UObject::execStringToBool(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Str);
    if (appStricmp(*Str, (const TCHAR *)L"True") == 0 || appStricmp(*Str, GTrue) == 0)
        *(INT *)Result = 1;
    else if (appStricmp(*Str, (const TCHAR *)L"False") == 0 || appStricmp(*Str, GFalse) == 0)
        *(INT *)Result = 0;
    else
        *(INT *)Result = appAtoi(*Str) ? 1 : 0;
}

// UObject::execCaps
void UObject::execCaps(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(A);
    P_FINISH;
    *(FString *)Result = A.Caps();
}

// UObject::execInStr
void UObject::execInStr(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_GET_STR(T);
    P_FINISH;
    *(INT *)Result = S.InStr(*T);
}
