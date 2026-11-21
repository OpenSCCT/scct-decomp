// Work item 0044 (LTCG retry): Versus RVA 0xc4e0-0xc6f2.
// UE2 dynamic arrays (UnTemplate.h) instantiated for TCHAR and FString:
//   0xc4e0 TArray<TCHAR>::~TArray
//   0xc550 TArray<FString>::TArray(const TArray&)   (Other in EDI, this on stack)
//   0xc5f0 TArray<FString>::~TArray
//   0xc660 TArray<FString>::Empty(Slack)            (this in ESI)
//   0xc6a0 TArray<FString>::operator=               (this in EAX, Other in EDI)
// 0xc7d0 is TArray<FString>::Remove (Index in EDI); it is defined here so the
// link gives it the same register convention.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

// Retail 0x10c10944.
extern const TCHAR FArray_ProtectedCstorTag[]; // L"Farray::protectedcstor"

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    FArray(INT InNum, INT ElementSize) : ArrayNum(InNum), ArrayMax(InNum)
    {
        if (!ArrayMax)
            Data = 0;
        else
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_ProtectedCstorTag);
    }
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
    TArray() {}
    TArray(const TArray &Other) : FArray(Other.ArrayNum, sizeof(T))
    {
        ArrayNum = 0;
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) T(((T *)Other.Data)[i]);
    }
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    const T &operator()(INT i) const { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1);
    void Empty(INT Slack = 0);
    TArray &operator=(const TArray &Other)
    {
        if (this != &Other)
        {
            Empty(Other.ArrayNum);
            for (INT i = 0; i < Other.ArrayNum; i++)
                new (*this) T(Other(i));
        }
        return *this;
    }
};

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template <class T> void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}

template <class T> inline void *operator new(unsigned int Size, TArray<T> &Array)
{
    INT Index = Array.FArray::Add(1, sizeof(T));
    return &Array(Index);
}

class FString : public TArray<TCHAR>
{
public:
    FString(const FString &Other); // RVA 0x4640
    ~FString();                    // RVA 0x48b0
};

// Explicit instantiations so the template members are emitted.
template class TArray<TCHAR>;
template class TArray<FString>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
TArray<FString> MakeList();
TArray<FString> Driver_c550(TArray<FString> &Local)
{
    Escape(&GMalloc);
    return Local;
}
void Driver_c6a0(TArray<FString> &Dest)
{
    Dest = MakeList();
}
void MayThrow(void *);
void Driver_c4e0()
{
    TArray<TCHAR> A;
    MayThrow(&A);
    TArray<FString> B;
    MayThrow(&B);
}
void Driver_c7d0(TArray<FString> &L, INT i, INT n)
{
    L.Remove(i, n);
    L.Remove(0, 2);
    L.Remove(i);
    L.Remove(n, i);
}
void Driver_c660(TArray<FString> &L, INT n)
{
    L.Empty(n);
    L.Empty();
    L.Empty(4);
}
