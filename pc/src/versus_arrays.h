#ifndef VERSUS_ARRAYS_H
#define VERSUS_ARRAYS_H

#include "unreal_types.h"

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    void Empty(INT ElementSize, INT Slack);
    INT Add(INT Count, INT ElementSize);
    INT __stdcall AddZeroed(INT ElementSize, INT Count);
};

template<class T> class TArray : public FArray {
public:
    ~TArray();
    T &operator()(INT Index) { return ((T *)Data)[Index]; }
    INT Num() const { return ArrayNum; }
    INT AddItem(const T &Item)
    {
        INT Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
    void Empty();
    void Empty(INT Slack) { FArray::Empty(sizeof(T), Slack); }
    INT AddUniqueItem(const T &Item)
    {
        INT Index;
        for (Index = 0; Index < Num(); Index++)
            if ((*this)(Index) == Item)
                return Index;
        Index = Add(1, sizeof(T));
        (*this)(Index) = Item;
        return Index;
    }
};

class FString : public TArray<TCHAR> {
public:
    ~FString();
    FString &operator=(const FString &Other);
};

#endif
