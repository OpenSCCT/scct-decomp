// campaign_script_natives_3.cpp -- Campaign script natives: math, sound, controller and logging
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_actor.h"
#include "unreal_pawn.h"
#include "campaign_engine_classes.h"

// UObject::execLog
// The release build compiles out the log output; the native still reads its parameters.
void UObject::execLog(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_GET_NAME_OPTX(N, NAME_ScriptLog);
    P_GET_UBOOL_OPTX(bExtra, 0);
    P_FINISH;
}

// UObject::execWarn
void UObject::execWarn(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    Stack.Logf((const TCHAR *)L"%s", *S);
}

// AActor::execSetBase
void AActor::execSetBase(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, NewBase);
    P_GET_VECTOR_OPTX(NewFloor, FVector(0.0f, 0.0f, 1.0f));
    P_FINISH;
    SetBase(NewBase, NewFloor, 1);
}

// AActor::execScreenLog
// The release build compiles out the on-screen log; the native still reads its parameter.
void AActor::execScreenLog(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
}

// AActor::execError
void AActor::execError(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    Stack.Log(*S);
    GetLevel()->DestroyActor(this);
}

// AActor::execStopSound
void AActor::execStopSound(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_GET_FLOAT(FadeTime);
    P_GET_BYTE(Slot);
    P_FINISH;
    if (Sound && GetLevel()->Engine->Audio)
        *(DWORD *)Result = GetLevel()->Engine->Audio->StopSound(this, Sound, FadeTime, Slot);
    else
        *(DWORD *)Result = 0;
}

// AActor::execChangeSoundVolume
void AActor::execChangeSoundVolume(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_GET_FLOAT(Volume);
    P_GET_BYTE(Slot);
    P_FINISH;
    if (GetLevel()->Engine->Audio)
        GetLevel()->Engine->Audio->ChangeSoundVolume(this, Sound, Volume, Slot);
}

// AActor::execInterpolateRotatorValue
void AActor::execInterpolateRotatorValue(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Current);
    P_GET_INT(Desired);
    P_GET_FLOAT(Rate);
    P_FINISH;
    *(INT *)Result = InterpolateRotatorValue(Current, Desired, Rate);
}

// AController::execPickWallAdjust
void AController::execPickWallAdjust(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(HitNormal);
    P_FINISH;
    if (Pawn)
        *(DWORD *)Result = Pawn->PickWallAdjust(HitNormal);
}

// AController::execpointReachable
void AController::execpointReachable(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(aPoint);
    P_FINISH;
    if (!Pawn) {
        *(DWORD *)Result = 0;
        return;
    }
    *(DWORD *)Result = Pawn->pointReachable(aPoint, 0, 0);
}

// AController::execFindPathTo
void AController::execFindPathTo(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Point);
    P_GET_UBOOL_OPTX(bClearPaths, 1);
    P_FINISH;
    if (Pawn)
        Pawn->findPathToward(0, Point, 0, bClearPaths, 0);
    *(AActor **)Result = 0;
}

// UObject::execMultiply_RotatorFloat
void UObject::execMultiply_RotatorFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FRotator *)Result = A * B;
}

// UObject::execMultiply_FloatRotator
void UObject::execMultiply_FloatRotator(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator *)Result = A * B;
}

// UObject::execFClamp
void UObject::execFClamp(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(V);
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT *)Result = Clamp(V, A, B);
}

// UObject::execSmerp
void UObject::execSmerp(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Alpha);
    P_GET_FLOAT(A);
    P_GET_FLOAT(B);
    P_FINISH;
    *(FLOAT *)Result = A + (3.0f * Alpha * Alpha - 2.0f * Alpha * Alpha * Alpha) * (B - A);
}

// UObject::execDampFloat
void UObject::execDampFloat(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Current);
    P_GET_FLOAT(Target);
    P_GET_FLOAT(Rate);
    P_GET_FLOAT(DeltaTime);
    P_FINISH;
    *(FLOAT *)Result = DampFloat(Current, Target, Rate, DeltaTime);
}

// UObject::execDampInt
void UObject::execDampInt(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Current);
    P_GET_INT(Target);
    P_GET_FLOAT(Rate);
    P_GET_FLOAT(DeltaTime);
    P_FINISH;
    *(INT *)Result = DampInt(Current, Target, Rate, DeltaTime);
}

// UObject::execDampVec
void UObject::execDampVec(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Current);
    P_GET_VECTOR(Target);
    P_GET_FLOAT(Rate);
    P_GET_FLOAT(DeltaTime);
    P_FINISH;
    *(FVector *)Result = DampVec(Current, Target, Rate, DeltaTime);
}

// AActor::execMultiply_ColorFloat
void AActor::execMultiply_ColorFloat(FFrame &Stack, RESULT_DECL)
{
    FColor A;
    Stack.Step(Stack.Object, &A);
    P_GET_FLOAT(B);
    P_FINISH;
    A.R = (BYTE)(A.R * B);
    A.G = (BYTE)(A.G * B);
    A.B = (BYTE)(A.B * B);
    *(FColor *)Result = A;
}

// AActor::execMultiply_FloatColor
void AActor::execMultiply_FloatColor(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(A);
    FColor B;
    Stack.Step(Stack.Object, &B);
    P_FINISH;
    B.R = (BYTE)(B.R * A);
    B.G = (BYTE)(B.G * A);
    B.B = (BYTE)(B.B * A);
    *(FColor *)Result = B;
}
