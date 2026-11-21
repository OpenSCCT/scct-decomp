// Work item 0326: Versus RVA 0x10c100-0x10c215.
//
// Three link-time generated (LTCG) members of a TArray whose 28-byte element
// has a destructor (0x10c140, thiscall). The element type is not recovered,
// so it is UnnamedElement_10c140.
//   0x10c100 TArray<T>::Empty(Slack)        this in ESI, ret 4
//   0x10c160 TArray<T>::~TArray()           this on the stack, ret 4
//   0x10c1d0 TArray<T>::Remove(Index,Count) Index in EDI, this on the stack, ret 8

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;

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
    void Empty(INT ElementSize, INT Slack);
    void Remove(INT Index, INT Count, INT ElementSize);
};

// 28-byte element; its destructor at 0x10c140 is called, not inlined.
struct UnnamedElement_10c140
{
    INT Fields[7];
    ~UnnamedElement_10c140();
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    __declspec(noinline) ~TArray()
    {
        Remove(0, ArrayNum);
    }
    __declspec(noinline) void Remove(INT Index, INT Count = 1)
    {
        for (INT i = Index; i < Index + Count; i++)
            (&(*this)(i))->~T();
        FArray::Remove(Index, Count, sizeof(T));
    }
    __declspec(noinline) void Empty(INT Slack = 0)
    {
        for (INT i = 0; i < ArrayNum; i++)
            (&(*this)(i))->~T();
        FArray::Empty(sizeof(T), Slack);
    }
};

template class TArray<UnnamedElement_10c140>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_10c100(TArray<UnnamedElement_10c140> *A, INT Slack) { A->Empty(Slack); }
void Driver_10c160(TArray<UnnamedElement_10c140> *A) { Escape(&GMalloc); A->~TArray(); }
void Driver_10c1d0(TArray<UnnamedElement_10c140> *A, INT Index, INT Count) { A->Remove(Index, Count); }
