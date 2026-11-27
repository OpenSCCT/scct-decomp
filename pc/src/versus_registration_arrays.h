#ifndef VERSUS_REGISTRATION_ARRAYS_H
#define VERSUS_REGISTRATION_ARRAYS_H

#include "unreal_types.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};

extern FMalloc *GMalloc;
extern const TCHAR FArrayAddTag[];      // L"FArray::Add"
extern const TCHAR FArrayTag[];         // L"FArray"

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    void Empty(INT ElementSize, INT Slack);
    INT Add(INT Count, INT ElementSize)
    {
        INT Index = ArrayNum;
        if ((ArrayNum += Count) > ArrayMax) {
            ArrayMax = ArrayNum + 3 * ArrayNum / 8 + 32;
            if (Data == 0)
                Data = GMalloc->Malloc(ArrayMax * ElementSize, FArrayAddTag);
            else
                Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, FArrayTag);
        }
        return Index;
    }
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
    void Empty()
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
};

#endif
