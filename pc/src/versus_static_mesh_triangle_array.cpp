#include "versus_build.h"
#include "versus_static_mesh_arrays.h"
#include "versus_static_mesh_triangle.h"
#include "versus_lazy_archive.h"

FArchive& operator<<(FArchive& Ar, FStaticMeshTriangle& Triangle);

template<class T> inline void* operator new(unsigned int, TArray<T>& Array) {
    return &Array(Array.Add(1, sizeof(T)));
}

FArchive& operator<<(FArchive& Ar, TArray<FStaticMeshTriangle>& Triangles) {
    Ar.CountBytes(Triangles.ArrayNum * sizeof(FStaticMeshTriangle), Triangles.ArrayMax * sizeof(FStaticMeshTriangle));
    if (Ar.IsLoading()) {
        INT Count;
        Ar << AR_INDEX(Count);
        Triangles.Empty(sizeof(FStaticMeshTriangle), Count);
        for (INT i = 0; i < Count; i++)
            Ar << *new(Triangles) FStaticMeshTriangle;
    } else {
        Ar << AR_INDEX(Triangles.ArrayNum);
        for (INT i = 0; i < Triangles.ArrayNum; i++)
            Ar << Triangles(i);
    }
    return Ar;
}

// UStaticMesh serializes its lazy triangle arrays at RVAs 0xcb924 and 0xcbbc9.
FArchive& SerializeStaticMeshTriangles(FArchive& Ar, TLazyArray<FStaticMeshTriangle>& Triangles) {
    return Ar << Triangles;
}
