// Work item 0380: Versus RVA 0xa51e0, an LTCG TArray<T>::~TArray (`this` on
// the stack, `ret 4`). It calls TArray<T>::Remove(0, ArrayNum) (RVA 0xa5250,
// LTCG: Index in EDI, this and Count on the stack), and the FArray destructor
// is inlined. The 24-byte element type (destructor RVA 0xa52a0, which
// neighbours release_sound_cache) is not named, so its name is neutral.
typedef int INT;
typedef unsigned long DWORD;

class FMalloc {
public:
    virtual void *Malloc(DWORD Count, const unsigned short *Tag) = 0;
    virtual void *Realloc(void *Original, DWORD Count, const unsigned short *Tag) = 0;
    virtual void Free(void *Original) = 0;
};
extern FMalloc *GMalloc;

class FArray {
public:
    FArray() : Data(0), ArrayNum(0), ArrayMax(0) {}
    ~FArray()
    {
        if (Data) {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
    void Remove(INT Index, INT Count, INT ElementSize);   // RVA 0x119c0
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
};

struct UnnamedElement_0a52a0 {
    ~UnnamedElement_0a52a0();   // RVA 0xa52a0
    INT Pad[6];
};

template <class T> class TArray : public FArray {
public:
    ~TArray() { Remove(0, ArrayNum); }
    __declspec(noinline) void Remove(INT Index, INT Count)
    {
        for (INT i = Index; i < Index + Count; i++)
            ((T *)Data)[i].~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
};
typedef TArray<UnnamedElement_0a52a0> UnnamedArray_0a51e0;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a51e0(UnnamedArray_0a51e0 *A, UnnamedArray_0a51e0 *B)
{
    Escape(&GMalloc);
    A->~TArray();
    B->~TArray();
}
