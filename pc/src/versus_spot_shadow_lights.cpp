#include "versus_build.h"
#include "versus_arrays.h"
#include "versus_pawn_action_events.h"
#include "versus_level_render_state.h"
#include "versus_canvas_matrix.h"
#include "versus_dynamic_light.h"
#include "versus_mem_stack.h"

void InsertSortedLight(TList<FSpotShadowLight *> **List, FSpotShadowLight *Light)
{
    while (*List && Light->ShadowSlot >= (*List)->Element->ShadowSlot)
        List = &(*List)->Next;
    *List = new(GSceneMem) TList<FSpotShadowLight *>(Light, *List);
}

INT AssignLightSlots(TList<FSpotShadowLight *> *Node)
{
    if (!Node)
        return 0;
    INT Slot = AssignLightSlots(Node->Next);
    if (Node->Element->ShadowSlot == 0)
    {
        Node->Element->ShadowSlot = Slot;
        if (Slot == 3 || Slot == -2)
            return -2;
        return Slot + 1;
    }
    return Slot;
}

enum { LE_ESpotShadow = 22, MaxSpotShadowLights = 20 };

void CollectSpotShadowLights(FLevelRenderState *Context, const FConvexVolume &ViewVolume,
                            INT &NumLights, INT &NumBeamLights)
{
    NumLights = 0;
    NumBeamLights = 0;
    for (TList<FDynamicActor *> *Node = Context->LightBeamActors; Node; Node = Node->Next) {
        AActor *Actor = Node->Element->Actor;
        if (Actor->LightEffect == LE_ESpotShadow && Actor->LightType && Actor->LightBrightness != 0.0f) {
            FDynamicLight *Light = Actor->GetLightRenderData();
            Light->unk_34_b7 = 1;
            Light->Visible = 1;
        }
    }
    for (TList<AActor *> *Node = Context->LightActors; Node; Node = Node->Next) {
        AActor *Actor = Node->Element;
        if (Actor->LightEffect == LE_ESpotShadow && !Actor->bDeleteMe && Actor->LightRenderData) {
            FSpotShadowLight *Light = static_cast<FSpotShadowLight *>(Actor->LightRenderData);
            if (IsLightVisibleInContext(Light, Context, ViewVolume) && NumLights < MaxSpotShadowLights) {
                UBOOL Beam = Light->Actor->UsesLightBeam;
                if (Beam) {
                    Beam = 0;
                    for (TList<FDynamicActor *> *Candidate = Context->LightBeamActors; Candidate; Candidate = Candidate->Next)
                        if (Candidate->Element->Actor == Light->Actor) {
                            Beam = 1;
                            break;
                        }
                }
                if (Beam) {
                    Light->ShadowSlot = 0;
                    NumBeamLights++;
                } else {
                    Light->ShadowSlot = -1;
                }
                Light->InLightList = 1;
                InsertSortedLight(&Context->SpotShadowLights, Light);
                NumLights++;
            } else {
                Light->ShadowSlot = -2;
            }
        }
    }
    AssignLightSlots(Context->SpotShadowLights);
}
