#ifndef VERSUS_OCTREE_BOUNDS_H
#define VERSUS_OCTREE_BOUNDS_H

#include "versus_build.h"
#include "unreal_math.h"

struct FBox {
    FVector Min;
    FVector Max;
    FVector GetCenter() const { return (Min + Max) * 0.5f; }
};

struct FOctreeNodeBounds {
    FVector Center;
    FLOAT HalfExtent;

    FOctreeNodeBounds(const FOctreeNodeBounds &Parent, INT Index)
    {
        HalfExtent = Parent.HalfExtent * 0.5f;
        Center.X = (((Index >> 1) & 2) - 1) * HalfExtent + Parent.Center.X;
        Center.Y = ((Index & 2) - 1) * HalfExtent + Parent.Center.Y;
        Center.Z = ((Index & 1) * 2 - 1) * HalfExtent + Parent.Center.Z;
    }
};

inline INT GetOverlappingChildren(const FOctreeNodeBounds *Bounds, const FBox *Box, INT *Out)
{
    INT Count = 0;
    if (Box->Max.X > Bounds->Center.X) {
        if (Box->Max.Y > Bounds->Center.Y) {
            if (Box->Max.Z > Bounds->Center.Z) Out[Count++] = 7;
            if (Box->Min.Z < Bounds->Center.Z) Out[Count++] = 6;
        }
        if (Box->Min.Y < Bounds->Center.Y) {
            if (Box->Max.Z > Bounds->Center.Z) Out[Count++] = 5;
            if (Box->Min.Z < Bounds->Center.Z) Out[Count++] = 4;
        }
    }
    if (Box->Min.X < Bounds->Center.X) {
        if (Box->Max.Y > Bounds->Center.Y) {
            if (Box->Max.Z > Bounds->Center.Z) Out[Count++] = 3;
            if (Box->Min.Z < Bounds->Center.Z) Out[Count++] = 2;
        }
        if (Box->Min.Y < Bounds->Center.Y) {
            if (Box->Max.Z > Bounds->Center.Z) Out[Count++] = 1;
            if (Box->Min.Z < Bounds->Center.Z) Out[Count++] = 0;
        }
    }
    return Count;
}

#endif
