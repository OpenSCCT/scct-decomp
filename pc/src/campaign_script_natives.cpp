// campaign_script_natives.cpp -- Campaign natives: bytecode primitives, vectors, actor movement
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_field.h"
#include "unreal_class.h"
#include "unreal_property.h"
#include "unreal_actor.h"

// UObject::execJumpIfNot
void UObject::execJumpIfNot(FFrame &Stack, RESULT_DECL)
{
    INT wOffset = Stack.ReadWord();
    UBOOL Value = 0;
    Stack.Step(Stack.Object, &Value);
    if (!Value)
        Stack.Code = &Stack.Node->Script(wOffset);
}

// UObject::execVirtualFunction
void UObject::execVirtualFunction(FFrame &Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, FindFunctionChecked(Stack.ReadName(), 0));
}

// UObject::execGlobalFunction
void UObject::execGlobalFunction(FFrame &Stack, RESULT_DECL)
{
    CallFunction(Stack, Result, FindFunctionChecked(Stack.ReadName(), 1));
}

// UObject::execStringConst
void UObject::execStringConst(FFrame &Stack, RESULT_DECL)
{
    *(FString *)Result = appFromAnsi((ANSICHAR *)Stack.Code);
    while (*Stack.Code)
        Stack.Code++;
    Stack.Code++;
}

// UObject::execUnicodeStringConst
void UObject::execUnicodeStringConst(FFrame &Stack, RESULT_DECL)
{
    *(FString *)Result = appFromUnicode((TCHAR *)Stack.Code);
    while (*(_WORD *)Stack.Code)
        Stack.Code += sizeof(_WORD);
    Stack.Code += sizeof(_WORD);
}

// UObject::execBoolToString
void UObject::execBoolToString(FFrame &Stack, RESULT_DECL)
{
    P_GET_UBOOL(B);
    *(FString *)Result = B ? GTrue : GFalse;
}

// UObject::execInstanceVariable
void UObject::execInstanceVariable(FFrame &Stack, RESULT_DECL)
{
    GProperty = (UProperty *)Stack.ReadObject();
    GPropAddr = (BYTE *)this + GProperty->Offset;
    GPropObject = this;
    if (Result)
        GProperty->CopyCompleteValue(Result, GPropAddr);
}

// UObject::execDefaultVariable
void UObject::execDefaultVariable(FFrame &Stack, RESULT_DECL)
{
    GProperty = (UProperty *)Stack.ReadObject();
    GPropAddr = &GetClass()->Defaults(GProperty->Offset);
    GPropObject = 0;
    if (Result)
        GProperty->CopyCompleteValue(Result, GPropAddr);
}

// UObject::execLetBool
void UObject::execLetBool(FFrame &Stack, RESULT_DECL)
{
    GPropAddr = 0;
    GProperty = 0;
    GPropObject = 0;
    Stack.Step(Stack.Object, 0);
    BITFIELD *BoolAddr = (BITFIELD *)GPropAddr;
    UBoolProperty *BoolProperty = (UBoolProperty *)GProperty;
    INT NewValue = 0;
    Stack.Step(Stack.Object, &NewValue);
    if (BoolAddr) {
        if (NewValue)
            *BoolAddr |= BoolProperty->BitMask;
        else
            *BoolAddr &= ~BoolProperty->BitMask;
    }
}

// UObject::execCross_VectorVector
void UObject::execCross_VectorVector(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_GET_VECTOR(B);
    P_FINISH;
    *(FVector *)Result = A ^ B;
}

// UObject::execNormal
void UObject::execNormal(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(A);
    P_FINISH;
    *(FVector *)Result = A.SafeNormal();
}

// AActor::execPollFinishAnim
void AActor::execPollFinishAnim(FFrame &Stack, RESULT_DECL)
{
    if (AnimationFinished((INT)LatentFloat))
        StateFrame->LatentAction = 0;
}

// AActor::execSetRotation
void AActor::execSetRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(NewRotation);
    P_FINISH;
    *(DWORD *)Result = SetRotation(NewRotation);
}

// AActor::execSetRelativeLocation
void AActor::execSetRelativeLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewLocation);
    P_FINISH;
    *(DWORD *)Result = SetRelativeLocation(NewLocation);
}

// AActor::execSetLocation
void AActor::execSetLocation(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewLocation);
    P_GET_UBOOL(bNoCheck);
    P_FINISH;
    *(DWORD *)Result = SetLocation(NewLocation, bNoCheck);
}

// AActor::execSetDrawScale3D
void AActor::execSetDrawScale3D(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(NewScale3D);
    P_FINISH;
    SetDrawScale3D(NewScale3D);
}

// AActor::execMoveSmooth
void AActor::execMoveSmooth(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Delta);
    P_FINISH;
    bJustTeleported = 0;
    *(DWORD *)Result = MoveSmooth(Delta);
}

// UObject::execVectorToRotator
void UObject::execVectorToRotator(FFrame &Stack, RESULT_DECL)
{
    FVector V(0.0f, 0.0f, 0.0f);
    Stack.Step(Stack.Object, &V);
    *(FRotator *)Result = V.Rotation();
}

// UObject::execRotatorToVector
void UObject::execRotatorToVector(FFrame &Stack, RESULT_DECL)
{
    FRotator R(0, 0, 0);
    Stack.Step(Stack.Object, &R);
    *(FVector *)Result = R.Vector();
}
