// campaign_script_natives_4.cpp -- Campaign script natives: animation, physics and console commands
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_output.h"
#include "unreal_actor.h"
#include "unreal_pawn.h"
#include "unreal_interaction.h"
#include "unreal_commandlet.h"
#include "campaign_engine_classes.h"

// AActor::execSetRelativeRotation
void AActor::execSetRelativeRotation(FFrame &Stack, RESULT_DECL)
{
    P_GET_ROTATOR(NewRotation);
    P_FINISH;
    *(DWORD *)Result = SetRelativeRotation(NewRotation);
}

// AActor::execStopAllSoundsActor
void AActor::execStopAllSoundsActor(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Flags);
    P_GET_FLOAT(FadeTime);
    P_GET_BYTE(Slot);
    P_FINISH;
    StopAllSoundsActor(Flags, FadeTime, Slot);
}

// AActor::execInterpolateRotator
void AActor::execInterpolateRotator(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Alpha);
    P_GET_ROTATOR(A);
    P_GET_ROTATOR(B);
    P_FINISH;
    *(FRotator *)Result = InterpolateRotator(Alpha, A, B);
}

// AActor::execSetPhysics
void AActor::execSetPhysics(FFrame &Stack, RESULT_DECL)
{
    P_GET_BYTE(NewPhysics);
    P_GET_UBOOL(bExtra);
    P_FINISH;
    setPhysics(NewPhysics, 0, FVector(0.0f, 0.0f, 1.0f), bExtra);
}

// AActor::execTweenAnim
void AActor::execTweenAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(Sequence);
    P_GET_FLOAT(Time);
    P_GET_INT(Channel);
    P_FINISH;
    PlayAnim(Channel, Sequence, 0.0f, Time, 0, 0, 0, 0);
}

// AActor::execPlayAnim
void AActor::execPlayAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(Sequence);
    P_GET_FLOAT_OPTX(Rate, 1.0f);
    P_GET_FLOAT(TweenTime);
    P_GET_INT(Channel);
    P_GET_INT(Param5);
    P_GET_INT(Param6);
    P_FINISH;
    PlayAnim(Channel, Sequence, Rate, TweenTime, 0, Param5, Param6, 0);
}

// AActor::execLoopAnim
void AActor::execLoopAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(Sequence);
    P_GET_FLOAT_OPTX(Rate, 1.0f);
    P_GET_FLOAT(TweenTime);
    P_GET_INT(Channel);
    P_GET_INT(Param5);
    P_GET_INT(Param6);
    P_FINISH;
    PlayAnim(Channel, Sequence, Rate, TweenTime, 1, Param5, Param6, 0);
}

// APlayerController::execCopyToClipboard
void APlayerController::execCopyToClipboard(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Text);
    P_FINISH;
    appClipboardCopy(*Text);
}

// UInteraction::execConsoleCommand
void UInteraction::execConsoleCommand(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(S);
    P_FINISH;
    *(DWORD *)Result = ConsoleCommand(S);
}

// UCommandlet::execMain
void UCommandlet::execMain(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Parms);
    P_FINISH;
    *(INT *)Result = Main(*Parms);
}

// AActor::execConsoleCommand
void AActor::execConsoleCommand(FFrame &Stack, RESULT_DECL)
{
    P_GET_STR(Command);
    P_FINISH;
    FStringOutputDevice StrOut;
    GetLevel()->Engine->Exec(*Command, StrOut);
    *(FString *)Result = *StrOut;
}
