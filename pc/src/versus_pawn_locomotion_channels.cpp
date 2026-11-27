#include "versus_pawn_action_events.h"
#include "versus_mesh_instance_types.h"
#include "versus_skeletal_animation_types.h"
#include "versus_mesh_animation_channels.h"

template<class T> inline T *Cast(UObject *Object)
{
    if (Object) {
        for (UClass *C = Object->Class; C; C = (UClass *)C->SuperField)
            if (C == T::StaticClass())
                return static_cast<T *>(Object);
    }
    return 0;
}

#include "versus_skeletal_channel_alpha.inl"

void USkeletalMeshInstance::SetAnimSequence(INT Channel, FName Sequence)
{
    if (Channel >= 0 && Channel < Channels.ArrayNum) {
        MeshAnimChannel &C = static_cast<MeshAnimChannel *>(Channels.Data)[Channel];
        C.AnimSequence = Sequence;
        void *Anim = GetAnimNamed(Sequence);
        C.bNotifies = AnimGetNotifyCount(Anim) != 0;
        if (Anim)
            C.OrigRate = AnimGetRate(Anim) / AnimGetFrameCount(Anim);
        else
            C.OrigRate = 0.f;
    }
}

// SBase.u supplies the sequence fields. The two method names describe the channel sets they reset.
void ASBasePawn::ResetLocomotionChannels()
{
    USkeletalMeshInstance *Instance = Cast<USkeletalMeshInstance>(MeshInstance);
    Instance->SetAnimSequence(5, ForwardAnim);
    Instance->SetAnimSequence(6, ForwardAnim);
    Instance->SetAnimSequence(7, RightAnim);
    Instance->SetAnimSequence(8, RightAnim);
    Instance->SetAnimSequence(4, RunAnim);
    Instance->SetAnimSequence(10, CopyForwardAnim);
    Instance->SetAnimSequence(11, CopyForwardAnim);
    Instance->SetAnimSequence(12, CopyRightAnim);
    Instance->SetAnimSequence(13, CopyRightAnim);
    Instance->SetAnimSequence(9, CopyRunAnim);
    Instance->UpdateBlendAlpha(9, 1.f, 1.e9f);
    Instance->UpdateBlendAlpha(4, 1.f, 1.e9f);
    INT Channel = 4;
    do {
        Instance->UpdateBlendAlpha(Channel, 0.f, 1.e9f);
    } while (++Channel <= 8);
    for (INT Stage = 5; Stage <= 13; ++Stage)
        Instance->SetAnimFrame(Stage, 0.f, 0);
}

void ASBasePawn::ResetWalkingChannels()
{
    USkeletalMeshInstance *Instance = Cast<USkeletalMeshInstance>(MeshInstance);
    Instance->SetAnimSequence(5, ForwardAnim);
    Instance->SetAnimSequence(6, ForwardAnim);
    Instance->SetAnimSequence(7, RightAnim);
    Instance->SetAnimSequence(8, RightAnim);
    Instance->SetAnimSequence(4, RunAnim);
    Instance->UpdateBlendAlpha(4, 1.f, 1.e9f);
    for (INT Stage = 5; Stage <= 13; ++Stage)
        Instance->SetAnimFrame(Stage, 0.f, 0);
}
