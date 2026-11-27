// versus_static_mesh_arrays.h -- array storage for static-mesh lighting and geometry
#ifndef VERSUS_STATIC_MESH_ARRAYS_H
#define VERSUS_STATIC_MESH_ARRAYS_H

#include "versus_array_storage.h"

template <class T> class TArray : public FArray
{
public:
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
    INT Num() const { return ArrayNum; }
    using FArray::Empty;
    void Empty(INT Slack);
    void Remove(INT Index, INT Count = 1);
};

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

class AActor;

struct FStaticMeshLightInfo
{
    AActor *LightActor;             // +0x00
    TArray<BYTE> VisibilityBits;    // +0x04
    UBOOL Applied;                  // +0x10
    ~FStaticMeshLightInfo();
};

#endif
