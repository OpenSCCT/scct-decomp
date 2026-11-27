// versus_mesh_lazy_archive.cpp -- archive serialization of skeletal-mesh lazy arrays
#include "versus_build.h"
#include "unreal_containers.h"
#include "versus_lazy_archive.h"

struct FSkeletalVertexInfluence;
struct FMeshFace;
FArchive& operator<<(FArchive& Ar, TArray<FSkeletalVertexInfluence>& Array);
FArchive& operator<<(FArchive& Ar, TArray<FMeshFace>& Array);
FArchive& SerializeIndex(FArchive& Ar, INT& Value);

// operator<< forwards compact indices to their period implementation.
inline FArchive& operator<<(FArchive& Ar, FCompactIndex& Index) {
    return SerializeIndex(Ar, Index.Value);
}

// Link root for FStaticLODModel serializing the influence array at RVA 0xc278e.
FArchive& SerializeMeshInfluences(FArchive& Ar, TLazyArray<FSkeletalVertexInfluence>& Influences) {
    return Ar << Influences;
}

// Link root for FStaticLODModel serializing the face array at RVA 0xc27a8.
FArchive& SerializeMeshFaces(FArchive& Ar, TLazyArray<FMeshFace>& Faces) {
    return Ar << Faces;
}
