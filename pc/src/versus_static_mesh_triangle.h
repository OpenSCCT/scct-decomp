// versus_static_mesh_triangle.h -- static-mesh triangle archive layout
#ifndef VERSUS_STATIC_MESH_TRIANGLE_H
#define VERSUS_STATIC_MESH_TRIANGLE_H

#include "unreal_math.h"
#include "unreal_name.h"

struct FStaticMeshUV {
    FLOAT U, V;
};

// Legacy packages store a material name and flags in the final eight bytes of each triangle.
struct FStaticMeshTriangle {
    FVector Vertices[3];          // 0x00
    FStaticMeshUV UVs[3][8];      // 0x24
    FColor Colors[3];             // 0xe4
    INT MaterialIndex;            // 0xf0
    INT SmoothingMask;            // 0xf4
    INT NumUVs;                   // 0xf8
    FName LegacyMaterialName;     // 0xfc
    DWORD LegacyPolyFlags;        // 0x100
};

#endif
