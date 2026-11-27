#ifndef VERSUS_PROJECTOR_BATCH_H
#define VERSUS_PROJECTOR_BATCH_H

#include "versus_build.h"
#include "unreal_types.h"

class UMaterial;
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

class FProjectorRenderBatch {
public:
    FProjectorPrimitiveChunk *FirstChunk;
    FProjectorPrimitiveChunk *LastChunk;
    INT NumPrimitives;
    UMaterial *BaseMaterial;
    UMaterial *ProjectedMaterial;
    INT MaterialBlendingOp;
    INT FrameBufferBlendingOp;
    UBOOL bTwoSided;
    UBOOL bBorderClampMode;
    INT VertexStride;
    INT VertexDataSize;
    DWORD IndexDataSize;

    void Render(FLevelSceneNode *SceneNode, FRenderInterface *RI);
};

#endif
