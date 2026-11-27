#ifndef VERSUS_PROJECTOR_PRIMITIVES_H
#define VERSUS_PROJECTOR_PRIMITIVES_H

#include "versus_projector_batch.h"
#if !defined(VERSUS_ARRAYS_H)
#include "versus_static_mesh_arrays.h"
#endif

class FProjectorRenderInfo;

struct FStaticProjectorPoint;
struct FProjectorUV;

struct FStaticProjectorInfo {
    FProjectorRenderInfo *RenderInfo;
    UMaterial *BaseMaterial;
    TArray<FStaticProjectorPoint> Vertices;
    TArray<FProjectorUV> BaseUVs;
    TArray<_WORD> Indices;
    UBOOL bTwoSided;

    ~FStaticProjectorInfo();
};

class FStaticProjectorPrimitive : public FProjectorPrimitive {
public:
    FStaticProjectorInfo *ProjectorInfo;

    FStaticProjectorPrimitive(FStaticProjectorInfo *Info) : ProjectorInfo(Info)
    {
        NumVertices = Info->Vertices.Num();
        NumIndices = Info->Indices.Num();
    }

    virtual void GetIndices(_WORD *Dest, _WORD BaseVertex);
    virtual void GetVertices(void *Dest);
};

class FBspStaticProjectorPrimitive : public FStaticProjectorPrimitive {
public:
    virtual void GetIndices(_WORD *Dest, _WORD BaseVertex);
};

#endif
