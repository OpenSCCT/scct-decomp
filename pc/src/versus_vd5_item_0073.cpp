/* Work item w3 0073: two TArray<T>::~TArray / TArray<T>::Remove pairs and their element
   destructors (Unreal Engine 2 UnTemplate.h shapes), LTCG copies (this on the stack,
   Remove's Index in EDI). FArray::Remove is the published remove_array (0x119c0).
   The element types have no recovered names: Element_a8c70, Element_a8d90, Inner_c0e20
   and Pair_a8df0 are neutral. */
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

class UObject;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray
{
public:
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayMax = 0;
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);

    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

template<class T> class TArray : public FArray
{
public:
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    __declspec(noinline) void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

/* Versus array without a capacity field (published at 0xf2c0 for BYTE). */
class FSimpleArray
{
public:
    void *Data;
    INT ArrayNum;
};
template<class T> class TSimpleArray : public FSimpleArray
{
public:
    ~TSimpleArray();
};

/* 0x1ef20 is the published TArray<UObject*>::~TArray (ordinary thiscall copy). */
template<> class TArray<UObject *> : public FArray
{
public:
    ~TArray();
};

/* 0xc0e20: an LTCG array destructor (this on the stack); element type unknown. */
struct Inner_c0e20 { INT Fields[4]; ~Inner_c0e20(); };

struct Element_a8c70
{
    INT Field0;
    TArray<Inner_c0e20> Items;      /* +0x04 */
    INT Fields10[8];                /* +0x10 */
    TSimpleArray<BYTE> Bytes;       /* +0x30 */
};

struct Pair_a8df0
{
    INT Fields[6];
    ~Pair_a8df0();
};

struct Element_a8d90
{
    INT Fields0[2];
    TArray<UObject *> Objects;      /* +0x08 */
    INT Field14;
    Pair_a8df0 Pairs[2];            /* +0x18 */
    INT Fields48[10];
};

template class TArray<Element_a8c70>;
template class TArray<Element_a8d90>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a8bb0(TArray<Element_a8c70> *A, TArray<Element_a8c70> *B)
{
    Escape(&GMalloc);
    A->~TArray<Element_a8c70>();
    B->~TArray<Element_a8c70>();
}
void Driver_a8cd0(TArray<Element_a8d90> *A, TArray<Element_a8d90> *B)
{
    Escape(&GMalloc);
    A->~TArray<Element_a8d90>();
    B->~TArray<Element_a8d90>();
}
