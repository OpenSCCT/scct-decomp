#ifndef VERSUS_ANSI_FSTRING_H
#define VERSUS_ANSI_FSTRING_H

#include "versus_build.h"
#include "unreal_types.h"

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
};
extern FMalloc *GMalloc;

class FArray {
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (ArrayNum == 0)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayNum * ElementSize, L"Farray::protectedcstor");
    }
    ~FArray();
};

template<class T> class TArray : public FArray {
public:
    TArray() {}
    TArray(INT InNum) : FArray(InNum, sizeof(T)) {}
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

class FString : public TArray<TCHAR> {
public:
    FString() {}
    FString(const ANSICHAR *In);
    ~FString();
    FString &operator=(const FString &Other);
};

#endif
