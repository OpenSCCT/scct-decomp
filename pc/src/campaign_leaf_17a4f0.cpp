// campaign_leaf_17a4f0.cpp -- AActor::execIsTweening
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execIsTweening
void AActor::execIsTweening(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Channel);
    P_FINISH;
    *(DWORD *)Result = 0;
    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        *(DWORD *)Result = MeshInstance->IsAnimTweening(Channel) != 0;
    }
}
