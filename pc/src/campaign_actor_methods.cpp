// campaign_actor_methods.cpp -- AActor methods the script natives call
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_actor.h"
#include "campaign_engine_classes.h"

// AActor::SetLocation
UBOOL AActor::SetLocation(const FVector &NewLocation, UBOOL bNoCheck)
{
    return XLevel->FarMoveActor(this, NewLocation, 0, bNoCheck);
}

// AActor::PlayActorSound
// Parameters after Volume are named by position; the script declaration is not decoded yet.
UBOOL AActor::PlayActorSound(USound *Sound, BYTE Slot, FLOAT Volume, INT Option4, FLOAT Option5, FLOAT Option6)
{
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (Audio && !(unk_28 & 4))
        return Audio->PlaySound(this, Sound, Slot, Volume, Option4, Option5, Option6);
    return 0;
}

// AActor::SetRotation
UBOOL AActor::SetRotation(const FRotator &NewRotation)
{
    FCheckResult Hit(1.0f);
    return GetLevel()->MoveActor(this, GDefaultVector, NewRotation, Hit);
}

// AActor::SetDrawScale3D
void AActor::SetDrawScale3D(FVector NewScale3D)
{
    if (bCollideActors && GetLevel()->Hash)
        GetLevel()->Hash->RemoveActor(this);
    DrawScale3D = NewScale3D;
    if (bCollideActors && GetLevel()->Hash)
        GetLevel()->Hash->AddActor(this);
    ClearRenderData();
}

// AActor::FastTraceCheck
UBOOL AActor::FastTraceCheck(const FVector &TraceEnd, const FVector &TraceStart, const FVector &Extent, INT TraceFlags, UBOOL bOption)
{
    FCheckResult Hit(1.0f);
    DWORD TraceType = 0x17;
    if (TraceFlags == 1)
        TraceType = 0x8017;
    else if (TraceFlags == 2)
        TraceType = 0x10017;
    else if (TraceFlags == 3)
        TraceType = 0x20017;
    else if (TraceFlags == 4)
        TraceType = 0x80017;
    else if (TraceFlags == 6)
        TraceType = 0x18017;
    if (bOption)
        TraceType |= 8;
    GetLevel()->SingleLineCheck(Hit, this, TraceEnd, TraceStart, TraceType | 0x20, Extent, 0, 0);
    return Hit.Actor == 0;
}
