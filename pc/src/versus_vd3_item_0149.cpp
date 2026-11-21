// Work item 0149: Versus RVA 0x401b0-0x40265 (UE2 UnTemplate.h shapes, LTCG).
//   0x401b0 TArray<FUnnamedRecord_44>::~TArray (LTCG: this on the stack, ret 4)
//   0x40220 TArray<FUnnamedRecord_44>::Remove (LTCG: Index in EDI, this and
//           Count on the stack, ret 8)
// The element type (0x44 bytes, destructor at 0xa79000) has no recovered
// name: FUnnamedRecord_44 is neutral.
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
extern FMalloc *GMalloc;                 // 0x10c73bf0

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    void Remove(INT Index, INT Count, INT ElementSize);   // 0x119c0
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
};

struct FUnnamedRecord_44
{
    INT Fields[17];
    ~FUnnamedRecord_44();                // 0xa79000
};

template <class T> class TArray : public FArray
{
public:
    ~TArray() { Remove(0, ArrayNum); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count);
};

template <class T> void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_401b0(TArray<FUnnamedRecord_44> *A, TArray<FUnnamedRecord_44> *B, INT I, INT N)
{
    Escape(&GMalloc);
    B->Remove(I, N);
    B->Remove(N, I);
    A->~TArray();
}
