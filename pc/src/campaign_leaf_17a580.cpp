// campaign_leaf_17a580.cpp -- AActor::execHasAnim
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execHasAnim
void AActor::execHasAnim(FFrame &Stack, RESULT_DECL)
{
    P_GET_NAME(Sequence);
    P_FINISH;
    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        *(DWORD *)Result = MeshInstance->FindAnim(Sequence) != 0;
    }
    else
        Stack.Logf(L"HasAnim: No mesh");
}
