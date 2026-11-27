#ifndef VERSUS_PROJECTOR_BATCH_H
#define VERSUS_PROJECTOR_BATCH_H

#include "versus_build.h"
#include "unreal_types.h"

class UMaterial;
class FProjectorRenderInfo;
class FLevelSceneNode;
class FRenderInterface;

class FProjectorPrimitive {
public:
    virtual void GetIndices(_WORD *Dest, _WORD BaseVertex) = 0;
    virtual void GetVertices(void *Dest) = 0;
    INT NumIndices;
    INT NumVertices;
};

struct FProjectorPrimitiveChunk {
    INT FirstPrimitiveIndex;
    FProjectorPrimitive *Primitives[32];
    FProjectorPrimitiveChunk *Next;
};

class FProjectorPrimitiveList {
public:
    FProjectorPrimitiveChunk *FirstChunk;
    FProjectorPrimitiveChunk *LastChunk;
    INT NumPrimitives;
    FProjectorPrimitiveList()
    {
        FirstChunk = LastChunk = 0;
        NumPrimitives = 0;
    }
    void Add(FProjectorPrimitive *Primitive);
};

class FProjectorRenderBatch : public FProjectorPrimitiveList {
public:
    UMaterial *BaseMaterial;
    UMaterial *ProjectedMaterial;
    INT MaterialBlendingOp;
    INT FrameBufferBlendingOp;
    UBOOL bTwoSided;
    UBOOL bBorderClampMode;
    INT VertexStride;
    INT VertexDataSize;
    DWORD IndexDataSize;

    FProjectorRenderBatch(UMaterial *Base, FProjectorRenderInfo *Info, UBOOL TwoSided);
    void AddPrimitive(FProjectorPrimitive *Primitive)
    {
        Add(Primitive);
        VertexDataSize += Primitive->NumVertices * VertexStride;
        IndexDataSize += Primitive->NumIndices * sizeof(_WORD);
    }
    void Render(FLevelSceneNode *SceneNode, FRenderInterface *RI);
};

#endif
