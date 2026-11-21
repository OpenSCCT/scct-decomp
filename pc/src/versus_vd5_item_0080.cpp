// Work item 0080 (wave 3): Versus RVA 0xab180, TArray<T>::~TArray for a
// 0x48-byte element type, compiled with VC7.0 /GL and linked with /LTCG
// (`this` on the stack, ret 4). The element type is unnamed: nothing in the
// retail code names it (its destructor is retail 0x109ab240).
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

// FArray from Unreal Engine 2; Remove is retail 0x109119c0.
class FArray
{
public:
    void* Data;
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
    void Remove(INT Index, INT Count, INT ElementSize);
};

// The 0x48-byte element (neutral name); destructor at retail 0x109ab240.
struct UnnamedElement_ab240
{
    DWORD Fields[18];
    ~UnnamedElement_ab240();
};

template<class T> class TArray : public FArray
{
public:
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    T& operator()(INT i) { return ((T*)Data)[i]; }
    // Retail 0x109ab1f0 (Index in EDI, this and Count on the stack).
    __declspec(noinline) void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};

template class TArray<UnnamedElement_ab240>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_ab180(TArray<UnnamedElement_ab240>* A)
{
    Escape(&GMalloc);
    A->~TArray();
}
