template<class T> inline void *operator new(unsigned int, TArray<T> &Array) {
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

template<class T> void TArray<T>::Empty(INT Slack) {
    for (INT i = 0; i < ArrayNum; ++i)
        (*this)(i).~T();
    FArray::Empty(sizeof(T), Slack);
}

template<class T> FArchive &operator<<(FArchive &Ar, TArray<T> &Array) {
    Ar.CountBytes(Array.ArrayNum * sizeof(T), Array.ArrayMax * sizeof(T));
    if (Ar.IsLoading()) {
        INT Count;
        Ar << AR_INDEX(Count);
        Array.Empty(Count);
        for (INT i = 0; i < Count; ++i)
            Ar << *new(Array) T;
    } else {
        Ar << AR_INDEX(Array.ArrayNum);
        for (INT i = 0; i < Array.ArrayNum; ++i)
            Ar << Array(i);
    }
    return Ar;
}
