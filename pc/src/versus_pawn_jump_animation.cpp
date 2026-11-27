#include "versus_pawn_action_events.h"
#include "versus_mesh_instance_types.h"

extern "C" double __cdecl sqrt(double);

// The method name describes the shared response to the two SBase standing jump actions.
void ASBasePawn::PlayJumpAnimation(INT Action)
{
    LastZipP = FVector(-10000000.f, 0.f, -10000000.f);
    UMeshInstance *Instance = MeshInstance;
    Instance->GetActiveAnimSequence(4);
    const FLOAT Frame = Instance->GetActiveAnimFrame(4);
    const FVector JumpVelocity = Velocity;
    BlendChangeTime = .05f;
    if (sqrt(JumpVelocity.X * JumpVelocity.X + JumpVelocity.Y * JumpVelocity.Y) <= 10.0) {
        if (!bWantsToCrouch) {
            if (Action == SA_JUMP_ST_0H)
                PlayAnim(0, AJumpStart, 1.f, 0.f);
            else
                PlayAnim(0, NAME_JumpStAlFL2, 1.f, 0.f);
        }
    } else if (!(Frame < .1f || Frame > .6f)) {
        bIsLeftPart = 1;
        if (Action == SA_JUMP_ST_0H)
            PlayAnim(0, AJumpForwardL, 1.f, 0.f);
        else
            PlayAnim(0, NAME_JumpStAlFL2, 1.f, 0.f);
    } else {
        bIsLeftPart = 0;
        if (Action == SA_JUMP_ST_0H)
            PlayAnim(0, AJumpForwardR, 1.f, 0.f);
        else
            PlayAnim(0, NAME_JumpStAlFR2, 1.f, 0.f);
    }
}
