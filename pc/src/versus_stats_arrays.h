#ifndef VERSUS_STATS_ARRAYS_H
#define VERSUS_STATS_ARRAYS_H

#include "versus_malloc.h"

inline void *operator new(unsigned int Size) { return GMalloc->Malloc(Size, L"new"); }
void operator delete(void *Block);

class FArray {
public:
    void *Data;
    INT ArrayNum, ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray() { if (Data) GMalloc->Free(Data); }
    void Remove(INT Index, INT Count, INT ElementSize);
    INT Add(INT Count, INT ElementSize);
    INT __stdcall AddZeroed(INT ElementSize, INT Count);
};

template<class T> class TArray : public FArray {
public:
    ~TArray() {
        for (INT i = 0; i < ArrayNum; ++i)
            (*this)(i).~T();
        FArray::Remove(0, ArrayNum, sizeof(T));
    }
    INT Num() const { return ArrayNum; }
    const T &operator()(INT i) const { return ((const T *)Data)[i]; }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Empty() {
        for (INT i = 0; i < ArrayNum; ++i)
            (*this)(i).~T();
        ArrayNum = 0;
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
            ArrayMax = 0;
        }
    }
    INT AddZeroed(INT Count) { return FArray::AddZeroed(sizeof(T), Count); }
    INT AddItem(const T &Item) {
        INT i = FArray::Add(1, sizeof(T));
        (*this)(i) = Item;
        return i;
    }
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const TCHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
    FString &operator=(const TCHAR *Other);
    const TCHAR *operator*() const { return Num() ? &(*this)(0) : L""; }
    static FString __cdecl Printf(const TCHAR *Format, ...);
};

#endif
