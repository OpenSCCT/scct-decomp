// Work item 0216: Versus RVA 0xe97d0, LTCG.
// 0xe97d0 is the member-wise assignment operator of an unidentified 0x44-byte
// record (this in ESI, Other in EBX): FString, FString, INT, FString,
// TArray<FString>, FString, INT. Class and field names are neutral; no
// vtable or string evidence names it.
// The TArray/FString declarations are copied from the published unit for
// 0xc4e0-0xc7d0 so the link gives TArray<FString>::operator= (0xc6a0) its
// retail convention (this in EAX, Other in EDI); it matches 0xc6a0 too.
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
    TArray &operator=(const TArray &Other);
};
template <class T> __declspec(noinline) TArray<T> &TArray<T>::operator=(const TArray<T> &Other)
{
    if (this != &Other)
    {
        Empty(Other.ArrayNum);
        for (INT i = 0; i < Other.ArrayNum; i++)
            new (*this) T(Other(i));
    }
    return *this;
}

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

template <class T> __declspec(noinline) void TArray<T>::Empty(INT Slack)
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
    FString &operator=(const FString &Other); // RVA 0x4800
};

// Unidentified record (neutral name).
class UnnamedRecord_e97d0
{
public:
    FString String0;         // 0x00
    FString String1;         // 0x0c
    INT Value0;              // 0x18
    FString String2;         // 0x1c
    TArray<FString> Strings; // 0x28
    FString String3;         // 0x34
    INT Value1;              // 0x40

    UnnamedRecord_e97d0 &operator=(const UnnamedRecord_e97d0 &Other);
};

__declspec(noinline) UnnamedRecord_e97d0 &UnnamedRecord_e97d0::operator=(const UnnamedRecord_e97d0 &Other)
{
    String0 = Other.String0;
    String1 = Other.String1;
    Value0 = Other.Value0;
    String2 = Other.String2;
    Strings = Other.Strings;
    String3 = Other.String3;
    Value1 = Other.Value1;
    return *this;
}

// Explicit instantiations so the template members are emitted.
template class TArray<TCHAR>;
template class TArray<FString>;

// Scaffolding for the link, not part of the unit.
void Driver_e97d0(UnnamedRecord_e97d0 &A, const UnnamedRecord_e97d0 &B)
{
    A = B;
}
