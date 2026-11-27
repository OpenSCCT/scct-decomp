// Work item 0386: Versus RVA 0xa6330, 0xa63a0 and 0xa6400, LTCG template
// array functions (VC7.0 /GL, linked /LTCG: `this` on the stack, the index
// in EDI). The skeletal mesh groups vertex indices by bone-influence count.
typedef unsigned long DWORD;
typedef unsigned short TCHAR;
typedef int INT;

class FMalloc
{
public:
    virtual void* Malloc(DWORD Count, const TCHAR* Tag) = 0;
    virtual void* Realloc(void* Original, DWORD Count, const TCHAR* Tag) = 0;
    virtual void Free(void* Original) = 0;
};
extern FMalloc* GMalloc;

// FArray from Unreal Engine 2; Remove is retail 0x109119c0 (remove_array).
class FArray
{
public:
    void* Data;
    INT ArrayNum;
    INT ArrayMax;
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

template<class T> class TArray : public FArray
{
public:
    T& operator()(INT i) { return ((T*)Data)[i]; }
    __declspec(noinline) ~TArray()
    {
        Remove(0, ArrayNum);
    }
    // Retail callers live in other objects; noinline stands in for them.
    __declspec(noinline) void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

// The group serializer at 0xc1330 writes the vertex indices before the weight index.
class UnnamedElement_a63a0
{
public:
    TArray<unsigned short> Vertices;
    INT WeightIndex;
    ~UnnamedElement_a63a0();
};

// A two-word array (data, count) whose Remove is retail 0x10911aa0
// (remove_simple_array).
class FSimpleArray
{
public:
    void* Data;
    INT ArrayNum;
    ~FSimpleArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);
};

// The 48-byte element of the simple array at 0xa6400.
class UnnamedElement_a6400
{
public:
    DWORD Fields[12];
};

template<class T> class TSimpleArray : public FSimpleArray
{
public:
    // Retail callers live in other objects; noinline stands in for them.
    __declspec(noinline) ~TSimpleArray()
    {
        Remove(0, ArrayNum);
    }
    void Remove(INT Index, INT Count)
    {
        FSimpleArray::Remove(Index, Count, sizeof(T));
    }
};

template class TArray<UnnamedElement_a63a0>;

// Scaffolding for the link, not part of the unit.
void Escape(void*);
void Driver_a63a0(TArray<UnnamedElement_a63a0>* A, INT Index, INT Count)
{
    A->Remove(Index, Count);
}
void Driver_a6330(TArray<UnnamedElement_a63a0>* A)
{
    Escape(&GMalloc);
    A->~TArray<UnnamedElement_a63a0>();
}
void Driver_a6400(TSimpleArray<UnnamedElement_a6400>* A)
{
    Escape(&GMalloc);
    A->~TSimpleArray<UnnamedElement_a6400>();
}
