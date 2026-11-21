// Work item 0257: Versus RVA 0x603d0, 0x60430, 0x60470 (Unreal Engine 2 UnTemplate.h shapes).
//
// All three are link-time generated (/GL + /LTCG): 0x603d0 and 0x60470 take
// `this` on the stack (ret 4), 0x60430 takes `this` in EDI.
// - 0x60470 is TArray<T>::~TArray for a 0x42c-byte element (type unknown).
// - 0x60430 destroys an array of owned allocations: every element is freed
//   with GMalloc, then the TArray<void*> base destructor (retail 0x7bf30,
//   itself LTCG with `this` on the stack) runs.
// - 0x603d0 is the destructor of a large object (unnamed) whose only
//   destructible members are that owned-pointer array at +0x2b348 and a
//   TArray<BYTE> at +0x2b358 (destroyed by retail 0xf250, thiscall).
// 0x60430 has no exception frame although it runs a base destructor after
// its body: the free loop sits in a throw() helper, so the body cannot throw.
// All three MATCH with try_ltcg.py /O2 /Gy /GX (roots Driver_60470 and
// Driver_603d0).
typedef unsigned char BYTE;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short TCHAR;

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
    __declspec(noinline) ~TArray()
    {
        Remove(0, ArrayNum);
    }
    void Remove(INT Index, INT Count = 1)
    {
        FArray::Remove(Index, Count, sizeof(T));
    }
    T &operator()(INT i) { return ((T *)Data)[i]; }
};

// Retail 0xf250 (non-LTCG object): declared, not defined here.
extern template TArray<BYTE>::~TArray();

struct FUnnamedElement_42c { BYTE Bytes[0x42c]; }; // real type unknown

// Retail RVA 0x60470.
template TArray<FUnnamedElement_42c>::~TArray();

// Array of blocks owned by the array (neutral name; UE2 name not recovered).
class TOwnedPointerArray : public TArray<void *>
{
public:
    void FreeElements() throw()
    {
        for (INT i = 0; i < ArrayNum; i++)
            GMalloc->Free((*this)(i));
    }
    __declspec(noinline) ~TOwnedPointerArray()
    {
        FreeElements();
    }
};

// Object with members at +0x2b348 / +0x2b358 (unnamed).
struct UnnamedObject_603d0
{
    BYTE Pad[0x2b348];
    TOwnedPointerArray Blocks;   // 0x2b348
    INT Unknown2b354;
    TArray<BYTE> Bytes;          // 0x2b358
    __declspec(noinline) ~UnnamedObject_603d0() {}
};

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_60470(TArray<FUnnamedElement_42c> *A) { Escape(&GMalloc); A->~TArray(); }
void Driver_60430(TOwnedPointerArray *A) { Escape(&GMalloc); A->~TOwnedPointerArray(); }
void Driver_603d0(UnnamedObject_603d0 *O) { Escape(&GMalloc); O->~UnnamedObject_603d0(); }
