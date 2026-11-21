// campaign_script_natives_9.cpp -- Campaign natives: spawning, sound and traces
#include "unreal_script.h"
#include "unreal_math.h"
#include "unreal_containers.h"
#include "unreal_class.h"
#include "unreal_actor.h"
#include "unreal_pawn.h"
#include "campaign_engine_classes.h"

// AActor::execTrace
// The PC build reads these console rendering natives' parameters and ignores them.
// Parameters after Slot are named by position; the script declaration is not decoded yet.
// Parameters after the sound are named by position; the script declaration is not decoded yet.
// Parameters after Material are named by position; the script declaration is not decoded yet.
void AActor::execTrace(FFrame &Stack, RESULT_DECL)
{
    P_GET_VECTOR_REF(HitLocation);
    P_GET_VECTOR_REF(HitNormal);
    P_GET_VECTOR(TraceEnd);
    P_GET_VECTOR_OPTX(TraceStart, Location);
    P_GET_VECTOR_OPTX(Extent, GDefaultVector);
    P_GET_OBJECT_REF(UMaterial, Material);
    P_GET_BYTE(TraceFlags);
    P_GET_INT(Option8);
    P_GET_INT(Option10);
    P_FINISH;
    *(AActor **)Result = TraceCheck(*HitLocation, *HitNormal, TraceEnd, TraceStart, Extent, Material,
                                    TraceFlags, Option8, 0, Option10);
}

// AActor::execTraceBone
void AActor::execTraceBone(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME_REF(HitBone);
    P_GET_VECTOR_REF(HitLocation);
    P_GET_VECTOR_REF(HitNormal);
    P_GET_VECTOR(TraceEnd);
    P_GET_VECTOR_OPTX(TraceStart, Location);
    P_GET_OBJECT_REF(UMaterial, Material);
    P_GET_INT(TraceFlags);
    P_FINISH;
    *(AActor **)Result = TraceBoneCheck(*HitBone, *HitLocation, *HitNormal, TraceEnd, TraceStart, Material,
                                        TraceFlags, 0);
}

// AActor::execPlaySound
// Parameters after Volume are named by position; the script declaration is not decoded yet.
void AActor::execPlaySound(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(USound, Sound);
    P_GET_BYTE(Slot);
    P_GET_FLOAT(Volume);
    P_GET_BYTE(Option4);
    P_GET_FLOAT(Option5);
    P_GET_FLOAT(Option6);
    P_GET_UBOOL(bOwned);
    P_FINISH;
    if (!Sound || (XLevel->GetLevelInfo()->unk_4a4 & 0x20))
        return;
    UAudioSubsystem *Audio = XLevel->Engine->Audio;
    if (!Audio || !Audio->GetViewport()->Actor)
        return;
    if (bOwned && (unk_2c & 0x10))
    {
        PlayOwnedSound(Sound, Slot);
        return;
    }
    *(DWORD *)Result = PlayActorSound(Sound, Slot, Volume, Option4, Option5, Option6);
}

// AActor::execSpawn
void AActor::execSpawn(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UClass, SpawnClass);
    P_GET_OBJECT(AActor, SpawnOwner);
    P_GET_NAME(SpawnName);
    P_GET_VECTOR_OPTX(SpawnLocation, Location);
    P_GET_ROTATOR_OPTX(SpawnRotation, Rotation);
    P_FINISH;
    AActor *Spawned = SpawnClass ? GetLevel()->SpawnActor(SpawnClass, NAME_None, SpawnLocation, SpawnRotation, 0, 0, 0, SpawnOwner, Instigator) : 0;
    if (Spawned)
        Spawned->Tag = SpawnName;
    *(AActor **)Result = Spawned;
}
