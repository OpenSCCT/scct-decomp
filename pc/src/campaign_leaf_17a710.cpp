// campaign_leaf_17a710.cpp -- AActor::execLinkSkelAnim
#include "unreal_script.h"
#include "unreal_class.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execLinkSkelAnim
void AActor::execLinkSkelAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UMeshAnimation, Anim);
    P_FINISH;
    if (Mesh && Mesh->IsA(USkeletalMesh::StaticClass()))
    {
        if (!Anim)
        {
            USkeletalMesh *SkelMesh = (USkeletalMesh *)Mesh;
            ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->LinkSkelAnim(SkelMesh->unk_210);
        }
        ((USkeletalMeshInstance *)Mesh->MeshGetInstance(this))->LinkSkelAnim(Anim);
    }
}
