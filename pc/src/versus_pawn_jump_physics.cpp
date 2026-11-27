#include "versus_pawn_collision_math.h"
#include "versus_pawn_action_events.h"
#include "versus_global_math.h"

FVector operator*(FLOAT Scale, const FVector &V);

enum { ROLE_AutonomousProxy = 3 };
enum {
    PHYS_Walking = 1, PHYS_Falling = 2, PHYS_OnPipe = 6, PHYS_Linear = 7,
    PHYS_OnVerticalPlane = 8, PHYS_Vandamme = 10, PHYS_OnLadder = 13
};
enum { SA_LEDGEFALL = 119 };

void ASBasePawn::MyDoJump()
{
    if (!Controller || Controller->RemoteRole == ROLE_AutonomousProxy)
        return;
    if (Physics == PHYS_OnVerticalPlane || sAction == SA_LEDGEFALL ||
        Physics == PHYS_OnPipe || Physics == PHYS_OnLadder) {
        const FCoords Coords = GMath.UnitCoords / Rotation;
        Velocity = Coords.XAxis * -200.f;
        Velocity.Z += 50.f;
        setPhysics(PHYS_Falling, 0, GMath_UnitZ);
    } else if (Physics == PHYS_Linear) {
        setPhysics(PHYS_Falling, 0, GMath_UnitZ);
    } else if (Physics == PHYS_Falling) {
        if (nJumpNumber == 1) {
            Velocity = 250.f * vWallJumpDir;
            Velocity.Z = 700.f;
            nJumpNumber = 2;
        }
    } else if (Physics == PHYS_Vandamme) {
        Velocity.Z = 0.f;
        nJumpNumber = 0;
        setPhysics(PHYS_Falling, 0, GMath_UnitZ);
    } else if (Physics == PHYS_Walking) {
        nJumpNumber = 1;
        Velocity.Z = JumpZ;
        if (Base && !Base->bWorldGeometry)
            Velocity.Z += Base->Velocity.Z;
        setPhysics(PHYS_Falling, 0, GMath_UnitZ);
    }
}

void ASBasePawn::execMyDoJump(FFrame &Stack, void *const Result)
{
    Stack.Code++;
    MyDoJump();
}
