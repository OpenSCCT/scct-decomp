// Refresh the skeletal pose through GetFrame for bone queries.
#include "versus_skeletal_animation_instance.h"

void USkeletalMeshInstance::ForceBoneRefresh()
{
    AActor *owner = GetActor();
    if (owner) {
        INT unusedVertexCount;
        GetFrame(owner, 0, 0, 0, unusedVertexCount, GetFrame_Bones);
    }
}
