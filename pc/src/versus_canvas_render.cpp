#include "versus_build.h"
#include "versus_canvas_util.h"
#include "versus_material.h"

template<class T> inline void *operator new(size_t, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

void FCanvasUtil::DrawTile(FLOAT X1, FLOAT Y1, FLOAT X2, FLOAT Y2, FLOAT U1, FLOAT V1,
    FLOAT U2, FLOAT V2, FLOAT Z, UMaterial *InMaterial, FColor Color)
{
    if (PrimitiveType != 0 || Material != InMaterial || Vertices.ArrayNum + 6 > 1362) {
        Flush();
        PrimitiveType = 0;
        Material = InMaterial;
    }
    INT USize, VSize;
    if (InMaterial) {
        USize = InMaterial->MaterialUSize();
        VSize = InMaterial->MaterialVSize();
    } else {
        USize = 1;
        VSize = 1;
    }
    FLOAT UScale = 1.0f / USize;
    FLOAT VScale = 1.0f / VSize;
    new (Vertices) FCanvasVertex(X1, Y1, Z, Color, U1 * UScale, V1 * VScale);
    new (Vertices) FCanvasVertex(X2, Y1, Z, Color, U2 * UScale, V1 * VScale);
    new (Vertices) FCanvasVertex(X2, Y2, Z, Color, U2 * UScale, V2 * VScale);
    new (Vertices) FCanvasVertex(X1, Y1, Z, Color, U1 * UScale, V1 * VScale);
    new (Vertices) FCanvasVertex(X2, Y2, Z, Color, U2 * UScale, V2 * VScale);
    new (Vertices) FCanvasVertex(X1, Y2, Z, Color, U1 * UScale, V2 * VScale);
    NumPrimitives += 2;
}
