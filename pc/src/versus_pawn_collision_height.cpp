#include "versus_pawn_collision_math.h"
#include "versus_pawn_action_events.h"
#include "versus_level_trace_types.h"

class ULevel {
public:
    UBOOL FarMoveActor(AActor *Actor, const FVector &Destination,
                       UBOOL bTest, UBOOL bNoCheck, UBOOL bAttachedMove);
};

enum { ROLE_SimulatedProxy = 2 };

BYTE ASBasePawn::UnZipSpeed(UBOOL bTest)
{
    if (Role == ROLE_SimulatedProxy)
        return 0;
    initSlowReplication = 1;
    FCheckResult Hit(1.f);
    const AActor *Defaults = static_cast<AActor *>(Class->Defaults.Data);
    FLOAT HeightAdjust = Defaults->CollisionHeight - CollisionHeight;
    if (Role == ROLE_SimulatedProxy)
        HeightAdjust = 0.f;
    SetCollisionSize(Defaults->CollisionRadius, Defaults->CollisionHeight);
    const FVector OldLocation = Location;
    FVector NewLocation(Location.X, Location.Y, Location.Z - HeightAdjust);
    BYTE bBlocked;
    if (GetLevel()->FarMoveActor(this, NewLocation, bTest, 0, 1)) {
        bBlocked = 0;
        if (!bTest) {
            PrePivot = static_cast<AActor *>(Class->Defaults.Data)->PrePivot;
            bIsZipSpeed = 0;
            ZoneConfig = 0;
            ZoneConfigForClient = 0;
        }
    } else {
        bBlocked = 1;
    }
    if (bBlocked || bTest) {
        SetCollisionSize(CollisionRadius, ZipHeight);
        GetLevel()->FarMoveActor(this, OldLocation, bTest, 0, 1);
    }
    return bTest ? !bBlocked : bIsZipSpeed;
}

BYTE ASBasePawn::SetColAfterPipe4(UBOOL bTest)
{
    if (!bIsPipe4Decal)
        return 1;
    if (CollisionHeight != Pipe4Height)
        return 1;
    if (Role == ROLE_SimulatedProxy)
        return 0;
    initSlowReplication = 1;
    FCheckResult Hit(1.f);
    FLOAT OldHeight = CollisionHeight;
    const AActor *Defaults = static_cast<AActor *>(Class->Defaults.Data);
    FLOAT HeightAdjust = CollisionHeight - Defaults->CollisionHeight;
    if (Role == ROLE_SimulatedProxy)
        HeightAdjust = 0.f;
    SetCollisionSize(CollisionRadius, Defaults->CollisionHeight);
    const FVector OldLocation = Location;
    FVector NewLocation(Location);
    NewLocation.Z += HeightAdjust;
    BYTE bBlocked;
    if (GetLevel()->FarMoveActor(this, NewLocation, 1, 0, 1)) {
        bBlocked = 0;
        if (!bTest) {
            PrePivot = static_cast<AActor *>(Class->Defaults.Data)->PrePivot;
            bIsPipe4Decal = 0;
            ZoneConfig = 0;
            ZoneConfigForClient = 0;
        }
    } else {
        bBlocked = 1;
    }
    if (bBlocked || bTest) {
        SetCollisionSize(CollisionRadius, OldHeight);
        GetLevel()->FarMoveActor(this, OldLocation, 1, 0, 1);
    }
    return bTest ? !bBlocked : !bIsPipe4Decal;
}

void ASBasePawn::execCanUnZipSpeed(FFrame &Stack, void *const Result)
{
    ++Stack.Code;
    *static_cast<BYTE *>(Result) = UnZipSpeed(1);
}

void ASBasePawn::execCanSetColAfterPipe4(FFrame &Stack, void *const Result)
{
    ++Stack.Code;
    *static_cast<BYTE *>(Result) = SetColAfterPipe4(1);
}
