// campaign_leaf_17aa60.cpp -- AActor::execLockRootTrack
#include "unreal_script.h"
#include "unreal_class.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execLockRootTrack
void AActor::execLockRootTrack(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT_OPTX(Option, 1);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        Mesh->MeshGetInstance(this);
        ((USkeletalMeshInstance *)MeshInstance)->LockRootTrack(Option);
    }
}
