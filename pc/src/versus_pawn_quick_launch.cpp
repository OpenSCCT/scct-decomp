#include "versus_pawn_action_events.h"

class USkeletalMeshInstance {
public:
    void BlendToAlpha(INT Channel, FLOAT TargetAlpha, FLOAT Seconds);
};

void ASBasePawn::eventNotifyQuickLaunch()
{
    ProcessEvent(FindFunctionChecked(NAME_NotifyQuickLaunch, 0), 0, 0);
}

namespace ReconstructedCallers {

// ExecuteAction repeats this sequence at six movement transitions. This link context
// represents those inlined sites without assigning the sequence a separate retail address.
void ExecuteActionQuickLaunch(ASBasePawn *Pawn, USkeletalMeshInstance *MeshInstance)
{
    if (Pawn->bQuickGadgetHasBegun) {
        MeshInstance->BlendToAlpha(22, 0.f, .1f);
        Pawn->bQuickGadgetHasBegun = 0;
        Pawn->eventNotifyQuickLaunch();
    }
}

}
