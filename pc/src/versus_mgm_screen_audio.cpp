#include "versus_pawn_action_events.h"
#include "versus_viewport_types.h"
#include "versus_scene_level_types.h"
#include "versus_native_subsystem.h"
#include "versus_mgm_hud_context.h"
#include "versus_mgm_hud_pages.h"

class UAudioSubsystem : public USubsystem {
public:
    virtual void VirtualSlot23();
    virtual void SetViewport(UViewport *Viewport);
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual UBOOL PlaySound(AActor *Actor, INT Id, USound *Sound, const FVector &Location,
                            FLOAT Volume, FLOAT Radius, FLOAT Pitch, INT Flags,
                            FLOAT FadeDuration, FLOAT Priority, INT Bone);
};

class UClient;
class UEngine : public USubsystem {
public:
    BYTE Unknown28[0x30 - 0x28];
    UClient *Client;
    UAudioSubsystem *Audio;
};

enum ESoundFlags { SF_No3D = 0x10 };
extern const FVector &GMath_Zero;

void MgmScreen::PlaySound(USound *Sound)
{
    APlayerController *Actor = GMgmMenuSystem->Viewport->Actor;
    if (Actor && Actor->XLevel && Actor->XLevel->Engine && Actor->XLevel->Engine->Audio) {
        Actor->XLevel->Engine->Audio->PlaySound(0, 0, Sound, GMath_Zero, 1.f, 4096.f, 1.f,
                                                SF_No3D, 0.f, 0.f, -1);
    }
}
