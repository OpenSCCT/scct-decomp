// Work item 0175 (wave 3): Versus RVA 0xdef50 / 0xdefc0.
// 0xdef50 is TArray<T>::~TArray for a 0x1c-byte element type and 0xdefc0 is the
// TArray<T>::Remove it calls (element destructors, then FArray::Remove). Both
// are link-time generated (/GL + /LTCG): Remove takes Index in EDI, the
// destructor takes `this` on the stack. The element type is not identified,
// so it is UnnamedElement_df010 (its destructor is retail 0xdf010, this in EAX).
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
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize); // retail 0x119c0
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    __declspec(noinline) void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    __declspec(noinline) ~TArray() { Remove(0, ArrayNum); }
};

void UnnamedElement_df010_Cleanup(void *P);
struct UnnamedElement_df010
{
    INT Unknown[7];
    __declspec(noinline) ~UnnamedElement_df010() { UnnamedElement_df010_Cleanup(this); }
};

template class TArray<UnnamedElement_df010>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_def50(TArray<UnnamedElement_df010> *A)
{
    Escape(&GMalloc);
    A->~TArray();
}
