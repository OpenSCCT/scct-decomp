// campaign_script_short_circuit.cpp -- short-circuit boolean operators
#include "unreal_script.h"

// UObject::execAndAnd_BoolBool
void UObject::execAndAnd_BoolBool(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    _WORD Skip = Stack.ReadSkipCount();
    if (A) {
        P_GET_UBOOL(B);
        *(UBOOL *)Result = A && B;
        Stack.Code++;
    } else {
        *(UBOOL *)Result = 0;
        Stack.Code += Skip;
    }
}

// UObject::execOrOr_BoolBool
void UObject::execOrOr_BoolBool(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(A);
    _WORD Skip = Stack.ReadSkipCount();
    if (!A) {
        P_GET_UBOOL(B);
        *(UBOOL *)Result = A || B;
        Stack.Code++;
    } else {
        *(UBOOL *)Result = 1;
        Stack.Code += Skip;
    }
}
