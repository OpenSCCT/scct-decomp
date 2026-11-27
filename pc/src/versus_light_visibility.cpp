#include "versus_build.h"
#include "versus_arrays.h"
#include "versus_pawn_action_events.h"
#include "versus_viewport_types.h"
#include "versus_scene_node_types.h"
#include "versus_level_render_state.h"
#include "versus_dynamic_light.h"

UBOOL FZoneVisibility::FilterBounds(const FLightFrustum &Frustum) const
{
    for (TList<FConvexVolume *> *Portal = Portals; Portal; Portal = Portal->Next) {
        if (IntersectsFrustumFaces(Frustum, *Portal->Element))
            return 1;
    }
    return 0;
}

UBOOL IsLightVisibleInContext(FSpotShadowLight *Light, FLevelRenderState *Context, const FConvexVolume &ViewVolume)
{
    if (Context->SceneNode->Viewport->Precaching)
        return 1;
    if (!Light->unk_34_b7 || !Light->Visible)
        return 0;
    if (Light->Actor->bDynamicLight)
    {
        for (TList<INT> *Z = Context->VisibleZones; Z; Z = Z->Next)
            if (Context->Zones[Z->Element].FilterBounds(Light->Frustum))
                return 1;
        return 0;
    }
    if (Light->unk_34_b6 && Context->SceneNode->ViewZone)
    {
        Light->Visible = 0;
        for (TList<INT> *Z = Context->VisibleZones; Z; Z = Z->Next)
        {
            for (INT i = 0; i < Light->Zones.Num(); i++)
            {
                if (Z->Element == Light->Zones(i))
                {
                    if (Context->Zones[Z->Element].FilterBounds(Light->Frustum))
                    {
                        Light->Visible = 1;
                        goto Done;
                    }
                    break;
                }
            }
        }
    }
    else
    {
        Light->Visible = 1;
    }
Done:
    return Light->Visible;
}
