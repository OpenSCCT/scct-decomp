#ifndef VERSUS_REGISTRATION_ARRAYS_H
#define VERSUS_REGISTRATION_ARRAYS_H

#include "unreal_types.h"

#include "versus_malloc.h"

extern const TCHAR FArrayAddTag[];      // L"FArray::Add"
extern const TCHAR FArrayTag[];         // L"FArray"

#include "versus_arrays.h"

template<class T> inline void TArray<T>::Empty()
{
    for (INT i = 0; i < ArrayNum; ++i)
        (*this)(i).~T();
    ArrayNum = 0;
    if (Data) {
        GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
    }
}

#endif
