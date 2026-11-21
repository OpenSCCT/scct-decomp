// Work item 0075 (w3): Versus RVA 0xa9060 and 0xa90d0.
// TArray<T>::~TArray and TArray<T>::Remove for a 0x34-byte element whose
// destructor is retail 0xa4770. The element type is not identified (no
// vtable label or string), so it has a neutral name. Retail built this unit
// with /GL and linked with /LTCG: the destructor takes `this` on the stack
// (ret 4), Remove takes Index in EDI and `this`, Count on the stack.

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

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize); // RVA 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    TArray() {}
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1);
};

// __declspec(noinline) stands in for retail call sites the LTCG inliner declined.
template <class T> __declspec(noinline) void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

// Neutral name: 0x34-byte element, destructor at retail 0xa4770.
class UnnamedElement_a4770
{
public:
    INT Pad[13];
    ~UnnamedElement_a4770(); // RVA 0xa4770
};

// RVA 0xa9060 is TArray<UnnamedElement_a4770>::~TArray,
// RVA 0xa90d0 is TArray<UnnamedElement_a4770>::Remove.
template class TArray<UnnamedElement_a4770>;

// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_a9060(TArray<UnnamedElement_a4770> *A)
{
    Escape(&GMalloc);
    A->~TArray();
}
