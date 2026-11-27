#ifndef VERSUS_INTERACTION_ARRAY_H
#define VERSUS_INTERACTION_ARRAY_H

#include "versus_array_storage.h"

template<class T> class TArray;

template<class T> inline void *operator new(unsigned int Size, TArray<T> &Array);

template<class T> class TArray : public FArray
{
public:
    TArray() {}
    TArray(const TArray &Other);
    ~TArray();

    INT Num() const { return ArrayNum; }
    T &operator()(INT Index) { return static_cast<T *>(Data)[Index]; }
    const T &operator()(INT Index) const { return static_cast<const T *>(Data)[Index]; }

    void Empty(INT Slack)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (*this)(i).~T();
        FArray::Empty(sizeof(T), Slack);
    }

    TArray &operator=(const TArray &Other);
};

template<class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

template<class T> TArray<T> &TArray<T>::operator=(const TArray &Other)
{
    if (this != &Other) {
        Empty(Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) T(Other(i));
    }
    return *this;
}

template<class T> TArray<T>::~TArray()
{
    for (INT i = 0; i < ArrayNum; i++)
        (*this)(i).~T();
    FArray::Remove(0, ArrayNum, sizeof(T));
}

#endif
