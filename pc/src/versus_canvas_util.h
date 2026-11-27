#ifndef VERSUS_CANVAS_UTIL_H
#define VERSUS_CANVAS_UTIL_H

#include "versus_build.h"
#ifndef UNREAL_CONTAINERS_H
#include "versus_arrays.h"
#endif
#include "versus_canvas_matrix.h"

class FRenderInterface;
class UMaterial;

struct FCanvasVertex {
    FLOAT X, Y, Z;
    FColor Color;
    FLOAT U, V;

    FCanvasVertex(FLOAT InX, FLOAT InY, FLOAT InZ, FColor InColor, FLOAT InU, FLOAT InV)
        : X(InX), Y(InY), Z(InZ), Color(InColor), U(InU), V(InV)
    {
    }
};

class FVertexStream {
public:
    virtual unsigned __int64 GetCacheId();
};

class FCanvasUtil : public FVertexStream {
public:
    INT PrimitiveType;
    UMaterial *Material;
    INT NumPrimitives;
    FRenderInterface *RI;
    FMatrix ScreenToCanvas;
    FMatrix CanvasToScreen;
    TArray<FCanvasVertex> Vertices;
    unsigned __int64 CacheId;

    void SetTransforms(FRenderInterface *InRI, FLOAT SizeX, FLOAT SizeY);
    void Flush();
    void DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1,
        FLOAT U2, FLOAT V2, FLOAT Z, UMaterial *Material, FColor Color);
};

#endif
