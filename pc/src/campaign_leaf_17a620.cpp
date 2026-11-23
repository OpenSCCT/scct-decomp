// campaign_leaf_17a620.cpp -- AActor::execSetMesh
#include "unreal_script.h"
#include "unreal_class.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execSetMesh
void AActor::execSetMesh(FFrame &Stack, RESULT_DECL)
{
    P_GET_OBJECT(UMesh, NewMesh);
    P_GET_UBOOL(bKeepAnim);
    P_FINISH;
    if (Mesh == NewMesh)
        return;
    if (NewMesh && NewMesh->IsA(USkeletalMesh::StaticClass()) && bKeepAnim)
        Mesh->MeshGetInstance(this)->SetMesh(NewMesh);
    Mesh = NewMesh;
}
