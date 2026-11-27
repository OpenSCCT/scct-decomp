#include "versus_projector_primitives.h"

void FStaticProjectorPrimitive::GetIndices(_WORD *Dest, _WORD BaseVertex)
{
    for (INT Index = 0; Index < ProjectorInfo->Indices.Num(); ++Index)
        *Dest++ = BaseVertex + ProjectorInfo->Indices(Index);
}

void FBspStaticProjectorPrimitive::GetIndices(_WORD *Dest, _WORD BaseVertex)
{
    for (INT Vertex = 2; Vertex < ProjectorInfo->Vertices.Num(); ++Vertex) {
        *Dest++ = BaseVertex;
        *Dest++ = BaseVertex + Vertex - 1;
        *Dest++ = BaseVertex + Vertex;
    }
}
