#include "versus_build.h"
#include "versus_mesh_animation.h"

FMeshAnimSeq *UMeshAnimation::FindAnimSeq(FName Name)
{
    for (INT Index = 0; Index < AnimSeqs.Num(); ++Index) {
        FMeshAnimSeq &Sequence = AnimSeqs(Index);
        if (Name == Sequence.Name)
            return &Sequence;
    }
    return 0;
}

MotionChunk *UMeshAnimation::FindMotionChunk(FName Name)
{
    for (INT Index = 0; Index < AnimSeqs.Num(); ++Index)
        if (Name == AnimSeqs(Index).Name)
            return &Moves(Index);
    return 0;
}
