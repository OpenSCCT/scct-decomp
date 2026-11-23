// campaign_leaf_17ae70.cpp -- AActor::execEnableChannelNotify
#include "unreal_script.h"
#include "unreal_class.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execEnableChannelNotify
void AActor::execEnableChannelNotify(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Channel);
    P_GET_INT_OPTX(Switch, 1);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->EnableChannelNotify(Channel, Switch);
    }
}
