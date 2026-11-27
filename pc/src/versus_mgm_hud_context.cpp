#include "versus_mgm_hud_context.h"
#include "versus_pawn_action_events.h"
#include "versus_viewport_types.h"

UViewport *GetMgmViewport()
{
    return GMgmMenuSystem->Viewport;
}

APlayerController *GetMgmPlayerController()
{
    return GetMgmViewport()->Actor;
}

AGameReplicationInfo *GetMgmGameReplicationInfo()
{
    return GetMgmViewport()->Actor->GameReplicationInfo;
}
