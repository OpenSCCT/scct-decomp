#ifndef VERSUS_CANVAS_UTIL_H
#define VERSUS_CANVAS_UTIL_H

#include "versus_build.h"
#include "unreal_containers.h"
#include "unreal_math.h"

class FRenderInterface;
class UMaterial;

struct FCanvasVertex {
    FLOAT X, Y, Z;
    FColor Color;
    FLOAT U, V;
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
    FLOAT ScreenToCanvas[4][4];
    FLOAT CanvasToScreen[4][4];
    TArray<FCanvasVertex> Vertices;
    unsigned __int64 CacheId;

    void DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1,
        FLOAT U2, FLOAT V2, FLOAT Z, UMaterial *Material, FColor Color);
};

#endif
