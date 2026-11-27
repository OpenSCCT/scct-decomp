#ifndef VERSUS_PROJECTOR_PRIMITIVES_H
#define VERSUS_PROJECTOR_PRIMITIVES_H

#include "versus_projector_batch.h"
#include "versus_static_mesh_arrays.h"

class FProjectorRenderInfo;

struct FStaticProjectorPoint;
struct FProjectorUV;

struct FStaticProjectorInfo {
    FProjectorRenderInfo *RenderInfo;
    UMaterial *BaseMaterial;
    TArray<FStaticProjectorPoint> Vertices;
    TArray<FProjectorUV> BaseUVs;
    TArray<_WORD> Indices;
};

class FStaticProjectorPrimitive : public FProjectorPrimitive {
public:
    FStaticProjectorInfo *ProjectorInfo;

    virtual void GetIndices(_WORD *Dest, _WORD BaseVertex);
    virtual void GetVertices(void *Dest);
};

class FBspStaticProjectorPrimitive : public FStaticProjectorPrimitive {
public:
    virtual void GetIndices(_WORD *Dest, _WORD BaseVertex);
};

#endif
