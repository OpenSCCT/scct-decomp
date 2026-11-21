// campaign_script_natives_8.cpp -- Campaign natives: movement, traces, noise and animation queries
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_actor.h"
#include "unreal_pawn.h"
#include "campaign_engine_classes.h"
#include "campaign_mesh_classes.h"

// AActor::execGetAnimParams
void AActor::execGetAnimParams(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Channel);
    P_GET_NAME_REF(OutSeqName);
    P_GET_FLOAT_REF(OutAnimFrame);
    P_GET_FLOAT_REF(OutAnimRate);
    P_GET_FLOAT_REF(OutAnimBlend);
    P_FINISH;
    *OutSeqName = NAME_None;
    *OutAnimFrame = 0.0f;
    *OutAnimRate = 0.0f;
    *OutAnimBlend = 0.0f;
    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        *OutSeqName = MeshInstance->GetActiveAnimSequence(Channel);
        *OutAnimFrame = MeshInstance->GetActiveAnimFrame(Channel);
        *OutAnimRate = MeshInstance->GetActiveAnimRate(Channel);
        *OutAnimBlend = MeshInstance->GetActiveAnimBlend(Channel);
    }
}

// AActor::execAttachToBone
// Parameters after Slot are named by position; the script declaration is not decoded yet.
void AActor::execAttachToBone(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(AActor, Attachment);
    P_GET_NAME(BoneName);
    P_GET_INT_OPTX(Slot, -1);
    P_GET_INT(Option4);
    P_GET_INT(Option5);
    P_GET_INT(Option6);
    P_GET_INT(Option7);
    P_GET_VECTOR_OPTX(RelLocation, GDefaultVector);
    P_GET_ROTATOR_OPTX(RelRotation, FRotator(0, 0, 0));
    P_FINISH;
    *(DWORD *)Result = AttachToBone(Attachment, BoneName, Slot, Option4, Option5, Option6, Option7, RelLocation, RelRotation);
}

// AActor::execDistancePointToLine
void AActor::execDistancePointToLine(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Point);
    P_GET_VECTOR_REF(LineOrigin);
    P_GET_VECTOR_REF(LineDir);
    P_FINISH;
    *(FLOAT *)Result = PointToLineDistance(Point, *LineOrigin, *LineDir);
}

// AController::execEAdjustJump
void AController::execEAdjustJump(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(BaseZ);
    P_GET_FLOAT(XYSpeed);
    P_FINISH;
    if (Pawn)
        *(FVector *)Result = Pawn->SuggestJumpVelocity(Destination, XYSpeed, BaseZ);
    else
        *(FVector *)Result = GDefaultVector;
}

// AActor::execMove
void AActor::execMove(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(Delta);
    P_FINISH;
    FCheckResult Hit(1.0f);
    *(DWORD *)Result = XLevel->MoveActor(this, Delta, Rotation, Hit);
}

// AActor::execFastTrace
void AActor::execFastTrace(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR(TraceEnd);
    P_GET_VECTOR(TraceStart);
    P_GET_BYTE(TraceFlags);
    P_GET_UBOOL(bOption);
    P_FINISH;
    *(DWORD *)Result = FastTraceCheck(TraceEnd, TraceStart, FVector(0, 0, 0), TraceFlags, bOption);
}

// AActor::execAddSoundRequest
// Parameters after the sound are named by position; the script declaration is not decoded yet.
void AActor::execAddSoundRequest(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_GET_BYTE(Slot);
    P_GET_FLOAT(Value1);
    P_GET_FLOAT(Value2);
    P_GET_INT(Flags);
    P_FINISH;
    if (Sound)
    {
        UAudioSubsystem *Audio = XLevel->Engine->Audio;
        if (Audio)
            Audio->AddSoundRequest(this, Sound, Slot, Value1, Value2, Flags);
    }
}

// AActor::execMakeNoise
void AActor::execMakeNoise(FFrame &Stack, RESULT_DECL)
{
    P_GET_FLOAT(Loudness);
    P_GET_BYTE(NoiseType);
    P_GET_VECTOR(NoiseLocation);
    P_GET_INT(Option4);
    P_GET_VECTOR_OPTX(Option5, GDefaultVector);
    P_GET_INT(Option6);
    P_FINISH;
    MakeNoise(Loudness, NoiseType, NoiseLocation, Option4, Option5, Option6, 1);
}
