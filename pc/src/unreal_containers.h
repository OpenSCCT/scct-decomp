// unreal_containers.h -- the engine's dynamic array and string
#ifndef UNREAL_CONTAINERS_H
#define UNREAL_CONTAINERS_H

#include "unreal_types.h"

// The untyped storage of every dynamic array.
class FArray {
public:
    void *Data;
    INT   ArrayNum;
    INT   ArrayMax;
};

// A dynamic array of T. Its destructor removes the elements, then frees the storage.
template<class T> class TArray : public FArray {
public:
    ~TArray();
};

// A dynamic string: an array of TCHAR that includes the terminating zero.
class FString : public TArray<TCHAR> {
public:
    ~FString();
};

#endif // UNREAL_CONTAINERS_H
