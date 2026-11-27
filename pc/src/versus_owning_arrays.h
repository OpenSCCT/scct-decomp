#ifndef VERSUS_OWNING_ARRAYS_H
#define VERSUS_OWNING_ARRAYS_H

#include "unreal_types.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum, ArrayMax;

    ~FArray() {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray {
public:
    ~TArray() {
        for (INT i = 0; i < ArrayNum; ++i)
            ((T *)Data)[i].~T();
        FArray::Remove(0, ArrayNum, sizeof(T));
    }
};

#endif
