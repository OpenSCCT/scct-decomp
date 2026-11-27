#include "versus_build.h"
#include "unreal_math.h"
#include "unreal_name.h"
#include "versus_static_mesh_arrays.h"
#include "versus_lazy_archive.h"

// The pose occupies +8 through +0x33 in a 0x40-byte reference skeleton bone.
struct FReferenceBonePose
{
    FQuat Orientation;
    FVector Position;
    FLOAT Length, XSize, YSize, ZSize;
};

struct FMeshBone
{
    FName Name;
    DWORD Flags;
    FReferenceBonePose BonePos;
    INT ParentIndex, NumChildren, Depth;
};

inline FArchive &operator<<(FArchive &Ar, DWORD &Value)
{
    Ar.Serialize(&Value, sizeof(Value));
    return Ar;
}
inline FArchive &operator<<(FArchive &Ar, FQuat &Q)
{
    return Ar << Q.X << Q.Y << Q.Z << Q.W;
}
inline FArchive &operator<<(FArchive &Ar, FVector &V)
{
    return Ar << V.X << V.Y << V.Z;
}

FArchive &operator<<(FArchive &Ar, FReferenceBonePose &Pose)
{
    // Both archive fields select XSize in the shipped format.
    return Ar << Pose.Orientation << Pose.Position << Pose.Length
              << Pose.XSize << Pose.XSize << Pose.ZSize;
}

inline FArchive &operator<<(FArchive &Ar, FMeshBone &Bone)
{
    return Ar << Bone.Name << Bone.Flags << Bone.BonePos << Bone.NumChildren << Bone.ParentIndex;
}

inline void *operator new(unsigned int, TArray<FMeshBone> &Array)
{
    INT Index = Array.Add(1, sizeof(FMeshBone));
    return &Array(Index);
}

FArchive &operator<<(FArchive &Ar, TArray<FMeshBone> &Array)
{
    Ar.CountBytes(Array.ArrayNum * sizeof(FMeshBone), Array.ArrayMax * sizeof(FMeshBone));
    if (Ar.IsLoading()) {
        INT Count;
        Ar << AR_INDEX(Count);
        Array.FArray::Empty(sizeof(FMeshBone), Count);
        for (INT Index = 0; Index < Count; ++Index)
            Ar << *new(Array) FMeshBone;
    } else {
        Ar << AR_INDEX(Array.ArrayNum);
        for (INT Index = 0; Index < Array.ArrayNum; ++Index)
            Ar << Array(Index);
    }
    return Ar;
}
