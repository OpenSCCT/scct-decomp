#include "versus_pawn_action_events.h"
#include "versus_mesh_instance_types.h"
#include "versus_skeletal_animation_types.h"

// The animation and property names come from FName::StaticInit and the SBase package.
// The seven method names describe their uses in ASBasePawn::ExecuteAction.
void ASBasePawn::SetLedgeAnimations()
{
    fBlendCoeffWalkAnim = 80.f;
    RightAnim = NAME_LedgStAlRt0;
    LeftAnim = NAME_LedgStAlLt0;
}

void ASBasePawn::SetFenceAnimations()
{
    fBlendCoeffWalkAnim = 120.f;
    fRunSpeedLimit = fWalkSpeedLimit = 1000.f;
    RightAnim = NAME_FencStAlRt0;
    ForwardAnim = NAME_FencStAlUp0;
}

void ASBasePawn::SetHorizontalPipeAnimations()
{
    fBlendCoeffWalkAnim = 126.f;
    ForwardAnim = NAME_PipHStAlFdRL;
}

void ASBasePawn::SetProneHorizontalPipeAnimations()
{
    fBlendCoeffWalkAnim = 113.f;
    ForwardAnim = NAME_PipHPrAlFd0;
}

void ASBasePawn::PlayAnimBlendingWithC0(INT Channel, FName Sequence, FLOAT BlendTime, FLOAT Rate)
{
    if (Rate == 0.f)
        Rate = 1.f;
    PlayAnim(Channel, Sequence, Rate, 0.f);
    fBlendTimeWithC0 = BlendTime;
    ChannelForBlendWithC0 = Channel;
}

void ASBasePawn::PlayRollAnimation()
{
    UMeshInstance *Instance = MeshInstance;
    Instance->GetActiveAnimSequence(4);
    FLOAT Frame = Instance->GetActiveAnimFrame(4);
    bIsRolling = 1;
    if (!(Frame < 0.1 || Frame > 0.6))
        PlayAnimBlendingWithC0(15, NAME_RollStAlFdL, 0.1f, 1.f);
    else
        PlayAnimBlendingWithC0(15, NAME_RollStAlFdR, 0.1f, 1.f);
}

void ASBasePawn::PlayRollUpAnimation()
{
    UMeshInstance *Instance = MeshInstance;
    Instance->GetActiveAnimSequence(4);
    FLOAT Frame = Instance->GetActiveAnimFrame(4);
    bIsRolling = 1;
    if (!(Frame < 0.1 || Frame > 0.6))
        PlayAnimBlendingWithC0(15, NAME_RollStJpFdL, 0.1f, 1.f);
    else
        PlayAnimBlendingWithC0(15, NAME_RollStJpFdR, 0.1f, 1.f);
}

enum {
    SA_ONLEDGE = 112, SA_ONFENCE = 128, SA_ROLLING = 130, SA_ROLLINGUP = 131,
    SA_ON_PIPEH = 207, SA_ON_PIPEH_4 = 209
};
enum { PHYS_Walking = 1, PHYS_OnVerticalPlane = 8, PHYS_Ledge = 9, PHYS_OnPipeH = 14 };
enum { NoPipHFire = 1, PipH4NoFire = 4 };

// Partial reconstruction of the dispatcher at 0x1d6840. These six cases provide
// the retail call sites for the animation helpers. The dispatcher has no receipt.
void ASBasePawn::ExecuteAction(INT Action)
{
    BYTE PreviousBTW = BTW;
    BlendChangeTime = .25f;
    fBlendTimeWithC0 = 0.f;
    if (!Mesh || !Mesh->IsA(&USkeletalMesh::PrivateStaticClass))
        return;
    Mesh->MeshGetInstance(this);
    USkeletalMeshInstance *Instance = static_cast<USkeletalMeshInstance *>(MeshInstance);

    switch (Action) {
    case SA_ONLEDGE:
        setPhysics(PHYS_Ledge, 0, GMath_UnitZ);
        Instance->ApplyBlendParams(15, 0.f, 0.f, 0.f, NAME_None, 0);
        PlayAnim(0, NAME_LedgStAlNt0, 1.f, 0.f, 1);
        BlendChangeTime = .15f;
        bBeginSpecial12Anim = 1;
        SetLedgeAnimations();
        break;
    case SA_ONFENCE:
        setPhysics(PHYS_OnVerticalPlane, 0, GMath_UnitZ);
        PlayAnim(0, NAME_FencStAlNt0, 1.f, 0.f, 1);
        SetFenceAnimations();
        break;
    case SA_ROLLING:
        setPhysics(PHYS_Walking, 0, GMath_UnitZ);
        PlayRollAnimation();
        break;
    case SA_ROLLINGUP:
        setPhysics(PHYS_Walking, 0, GMath_UnitZ);
        PlayRollUpAnimation();
        break;
    case SA_ON_PIPEH:
        setPhysics(PHYS_OnPipeH, 0, GMath_UnitZ);
        PipHFire = NoPipHFire;
        SetHorizontalPipeAnimations();
        PlayAnim(0, NAME_PipHStAlNt0, 1.f, 0.f, 1);
        break;
    case SA_ON_PIPEH_4:
        setPhysics(PHYS_OnPipeH, 0, GMath_UnitZ);
        PipHFire = PipH4NoFire;
        SetProneHorizontalPipeAnimations();
        PlayAnim(0, NAME_PipHPrAlNt0, 1.f, 0.f, 1);
        break;
    }
    if (!PreviousBTW && BTW)
        initSlowReplication = 1;
}
