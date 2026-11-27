#include "versus_d3d_vertex_stream.h"

// Near miss: block order and the hash-slot address match retail, but VC7
// caches 0 in ESI (push esi / xor esi,esi) and aligns both loops, where
// retail uses immediates and test eax,eax with unaligned loops.
FD3DResource::~FD3DResource() throw()
{
    // Remove this resource from the device's resource list.
    if (RenDev->ResourceList != this) {
        FD3DResource *ResourcePtr = RenDev->ResourceList;
        while (ResourcePtr && ResourcePtr->NextResource != this)
            ResourcePtr = ResourcePtr->NextResource;
        if (ResourcePtr)
            ResourcePtr->NextResource = NextResource;
    } else {
        RenDev->ResourceList = NextResource;
    }
    NextResource = 0;

    // Remove this resource from the device's resource hash.
    FD3DResource **HashPtr = &RenDev->ResourceHash[HashIndex];
    if (*HashPtr != this) {
        FD3DResource *ResourcePtr = *HashPtr;
        while (ResourcePtr && ResourcePtr->HashNext != this)
            ResourcePtr = ResourcePtr->HashNext;
        if (ResourcePtr)
            ResourcePtr->HashNext = HashNext;
    } else {
        *HashPtr = HashNext;
    }
    HashNext = 0;
}
