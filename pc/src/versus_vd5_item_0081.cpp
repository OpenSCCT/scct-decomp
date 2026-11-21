// RVA 0xab2a0: TArray<T>::~TArray for a 12-byte element type that holds a
// TArray of 4-byte items (element type not recovered; FElement_0ab310 is a
// neutral name, its destructor is at RVA 0xab310 and calls ~TArray at 0x17bf30). LTCG unit: the array arrives on the
// stack (ret 4); TArray::Remove (RVA 0xab250) takes Index in EDI.
typedef int INT;
typedef unsigned short TCHAR;

struct FMalloc {
    virtual void *Malloc(unsigned long Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, unsigned long Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray {
public:
    void Remove(INT Index, INT Count, INT ElementSize);
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
protected:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template <class T> class TArray : public FArray {
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1);
    ~TArray() { Remove(0, ArrayNum); }
};

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

struct FElement_0ab310 {
    INT A, B, C;
    ~FElement_0ab310();
};

template class TArray<FElement_0ab310>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_0ab2a0(TArray<FElement_0ab310> *A, INT I, INT N)
{
    Escape(&GMalloc);
    A->Remove(I, N);
    A->Remove(I + 1, N);
    A->Remove(I + 2, N);
    A->Remove(I + 3, N);
    A->Remove(I + 4, N);
    A->Remove(I + 5, N);
    A->~TArray<FElement_0ab310>();
}
