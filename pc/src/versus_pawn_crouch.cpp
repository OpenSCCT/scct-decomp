#include "versus_pawn_action_events.h"
#include "versus_level_trace_types.h"

class ULevel {
public:
    UBOOL MoveActor(AActor *Actor, const FVector &Delta, const FRotator &NewRotation,
                    FCheckResult &Hit, UBOOL Test = 0, UBOOL IgnorePawns = 0,
                    UBOOL IgnoreBases = 0, UBOOL NoFail = 0, UBOOL Unused = 0);
};

enum { ROLE_SimulatedProxy = 2 };

inline void ASBasePawn::eventStartCrouch(FLOAT HeightAdjust)
{
    struct { FLOAT HeightAdjust; } Parms;
    Parms.HeightAdjust = HeightAdjust;
    ProcessEvent(FindFunctionChecked(NAME_StartCrouch, 0), &Parms, 0);
}

void ASBasePawn::Crouch(UBOOL bClientSimulation)
{
    initSlowReplication = 1;
    if (Role == ROLE_SimulatedProxy) {
        bIsCrouched = 1;
        return;
    }
    if (CollisionHeight == CrouchHeight && CollisionRadius == CrouchRadius)
        return;

    const FVector &DefaultPivot = static_cast<AActor *>(Class->Defaults.Data)->PrePivot;
    FVector BasePivot;
    BasePivot.X = DefaultPivot.X;
    BasePivot.Y = DefaultPivot.Y;
    BasePivot.Z = DefaultPivot.Z;
    FLOAT OldHeight = CollisionHeight;
    SetCollisionSize(CrouchRadius, CrouchHeight);

    FLOAT HeightAdjust = OldHeight - CrouchHeight;
    FCheckResult Hit(1.f);
    GetLevel()->MoveActor(this, FVector(0.f, 0.f, -HeightAdjust), Rotation, Hit);
    if (!bClientSimulation) {
        PrePivot = BasePivot;
        PrePivot.Z += HeightAdjust;
        bIsCrouched = 1;
        ZoneConfig = 1;
        ZoneConfigForClient = 1;
        eventStartCrouch(HeightAdjust);
    }
}
