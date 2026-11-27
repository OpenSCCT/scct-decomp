#include "versus_build.h"
#include "unreal_containers.h"
#include "unreal_object.h"
#include "versus_octree_bounds.h"

static UBOOL __fastcall BoxContainsNode(const FOctreeNodeBounds *Bounds, const FBox *Box)
{
    if (Bounds->Center.X - Bounds->HalfExtent < Box->Min.X ||
        Bounds->Center.X + Bounds->HalfExtent > Box->Max.X ||
        Bounds->Center.Y - Bounds->HalfExtent < Box->Min.Y ||
        Bounds->Center.Y + Bounds->HalfExtent > Box->Max.Y ||
        Bounds->Center.Z - Bounds->HalfExtent < Box->Min.Z ||
        Bounds->Center.Z + Bounds->HalfExtent > Box->Max.Z)
        return 0;
    return 1;
}

class AActor : public UObject {
public:
    BYTE unk_28[0xc8 - sizeof(UObject)];
    FBox OctreeBox;
};
class FCollisionOctree;
class FOctreeNode {
public:
    TArray<AActor *> Actors;
    FOctreeNode *Children;

    void StoreActor(AActor *Actor, FCollisionOctree *Octree, const FOctreeNodeBounds *Bounds);
    void MultiNodeFilter(AActor *Actor, FCollisionOctree *Octree, const FOctreeNodeBounds *Bounds);
};

void FOctreeNode::MultiNodeFilter(AActor *Actor, FCollisionOctree *Octree, const FOctreeNodeBounds *Bounds)
{
    if (Children && !BoxContainsNode(Bounds, &Actor->OctreeBox)) {
        INT OverlappingChildren[8];
        INT Count = GetOverlappingChildren(Bounds, &Actor->OctreeBox, OverlappingChildren);
        for (INT i = 0; i < Count; i++) {
            INT Index = OverlappingChildren[i];
            FOctreeNodeBounds Child(*Bounds, Index);
            Children[Index].MultiNodeFilter(Actor, Octree, &Child);
        }
    } else {
        StoreActor(Actor, Octree, Bounds);
    }
}
