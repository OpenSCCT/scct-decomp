// versus_static_mesh_arrays.h -- array storage for static-mesh lighting and geometry
#ifndef VERSUS_STATIC_MESH_ARRAYS_H
#define VERSUS_STATIC_MESH_ARRAYS_H

#include "versus_build.h"
#include "unreal_types.h"

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    INT Add(INT Count, INT ElementSize);                // RVA 0x44e0
    void Empty(INT ElementSize, INT Slack);             // RVA 0x4550
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
};

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
