#include "versus_mgm_hud_context.h"
#include "versus_canvas_viewport.h"

struct MgmMenuSystem {
    BYTE UnknownBeforeViewport[0x38];
    UViewport *Viewport;
};
extern MgmMenuSystem *GMgmMenuSystem;

UViewport *GetMgmViewport()
{
    return GMgmMenuSystem->Viewport;
}

APlayerController *GetMgmPlayerController()
{
    return GetMgmViewport()->Actor;
}
