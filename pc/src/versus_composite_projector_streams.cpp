#include "versus_composite_projector_streams.h"

enum EVertexComponentType {
    CT_Float3 = 1,
    CT_Float2 = 2,
    CT_Color = 4
};

enum EVertexComponentFunction {
    CF_Position = 0,
    CF_Diffuse = 2,
    CF_TexCoord0 = 4,
    CF_TexCoord1 = 5
};

INT FCompositeVertexStream::GetComponents(FVertexComponent *Components)
{
    Components[0].Type = CT_Float3;
    Components[0].Function = CF_Position;
    Components[1].Type = CT_Color;
    Components[1].Function = CF_Diffuse;
    Components[2].Type = CT_Float3;
    Components[2].Function = CF_TexCoord0;
    INT NumComponents = 3;
    if (Info->BaseMaterial) {
        Components[3].Type = CT_Float2;
        Components[3].Function = CF_TexCoord1;
        ++NumComponents;
    }
    return NumComponents;
}

void FCompositeVertexStream::GetRawStreamData(void **Dest, INT FirstVertex)
{
    *Dest = 0;
}

void FCompositeVertexStream::GetStreamData(void *Dest)
{
    FProjectorPrimitiveChunk *Chunk = Info->FirstChunk;
    INT Slot = 0;
    BYTE *Out = static_cast<BYTE *>(Dest);
    for (INT i = 0; i < Info->NumPrimitives; ++i) {
        FProjectorPrimitive *Primitive = Chunk->Primitives[Slot];
        Primitive->GetVertices(Out);
        Out += Primitive->NumVertices * Stride;
        if (++Slot >= 32) {
            Chunk = Chunk->Next;
            Slot = 0;
        }
    }
}

void FCompositeIndexBuffer::GetContents(void *Dest)
{
    _WORD *Out = static_cast<_WORD *>(Dest);
    FProjectorPrimitiveChunk *Chunk = Info->FirstChunk;
    INT Slot = 0;
    _WORD BaseVertex = 0;
    for (INT i = 0; i < Info->NumPrimitives; ++i) {
        FProjectorPrimitive *Primitive = Chunk->Primitives[Slot];
        Primitive->GetIndices(Out, BaseVertex);
        Out += Primitive->NumIndices;
        BaseVertex += Primitive->NumVertices;
        if (++Slot >= 32) {
            Chunk = Chunk->Next;
            Slot = 0;
        }
    }
}
