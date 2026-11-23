// campaign_leaf_17b900.cpp -- AActor::execAnimIsInGroup
#include "unreal_script.h"
#include "unreal_actor.h"
#include "campaign_mesh_classes.h"

// AActor::execAnimIsInGroup
void AActor::execAnimIsInGroup(FFrame &Stack, RESULT_DECL)
{
    P_GET_INT(Channel);
    P_GET_NAME(GroupName);
    P_FINISH;
    *(DWORD *)Result = 0;
    if (Mesh)
    {
        Mesh->MeshGetInstance(this);
        FName Sequence;
        if ((Sequence = MeshInstance->GetActiveAnimSequence(Channel)) != NAME_None)
        {
            void *Anim = MeshInstance->FindAnim(Sequence);
            if (Anim)
                *(DWORD *)Result = MeshInstance->AnimIsInGroup(Anim, GroupName) != 0;
        }
    }
}
