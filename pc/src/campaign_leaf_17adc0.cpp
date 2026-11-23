// campaign_leaf_17adc0.cpp -- AActor::execGetNotifyChannel
#include "unreal_script.h"
#include "unreal_class.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execGetNotifyChannel
void AActor::execGetNotifyChannel(FFrame &Stack, RESULT_DECL)
{
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        USkeletalMeshInstance *Instance = (USkeletalMeshInstance *)Mesh->MeshGetInstance(this);
        *(INT *)Result = Instance->unk_bc;
    }
    else
        *(INT *)Result = 0;
}
