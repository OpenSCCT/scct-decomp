// campaign_leaf_17a3a0.cpp -- AActor::execStopAnimating
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execStopAnimating
void AActor::execStopAnimating(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        MeshInstance->StopAnimating();
    }
}
