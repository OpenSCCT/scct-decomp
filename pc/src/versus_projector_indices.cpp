#include "versus_projector_primitives.h"

void FBspStaticProjectorPrimitive::GetIndices(_WORD *Dest, _WORD BaseVertex)
{
    for (INT Vertex = 2; Vertex < ProjectorInfo->Vertices.Num(); ++Vertex) {
        *Dest++ = BaseVertex;
        *Dest++ = BaseVertex + Vertex - 1;
        *Dest++ = BaseVertex + Vertex;
    }
}
