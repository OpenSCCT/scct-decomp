// Work item 0324: Versus RVA 0x10bd60-0x10bdf3 (LTCG object).
// 0x10bd60 is TArray<T>::RemoveItem for a 4-byte element (array in EDI).
// 0x10bda0 constructs an unidentified FArray-derived container with an
// initial capacity of 4 sixteen-byte elements (neutral name).
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

// Allocation tag at 0x10c10984 (kept in writable .data by VC7.0).
extern const TCHAR UnnamedArray_10bda0_Tag[];

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    FArray(INT InMax) : Data(0), ArrayNum(0), ArrayMax(InMax) {}
    INT Num() const { return ArrayNum; }
    void Remove(INT Index, INT Count, INT ElementSize);   // RVA 0x119c0
    ~FArray()
    {
        if (Data)
            GMalloc->Free(Data);
        Data = 0;
        ArrayMax = 0;
        ArrayNum = 0;
    }
};

template<class T> class TArray : public FArray
{
public:
    TArray() : FArray(0) {}
    T &operator()(INT i) { return ((T *)Data)[i]; }
    INT RemoveItem(const T &Item)
    {
        INT OriginalNum = ArrayNum;
        for (INT Index = 0; Index < ArrayNum; Index++)
            if ((*this)(Index) == Item)
                Remove(Index--, 1, sizeof(T));
        return OriginalNum - ArrayNum;
    }
};

// RVA 0x10bd60
template INT TArray<INT>::RemoveItem(const INT &Item);

struct FElement16_10bda0 { DWORD A, B, C, D; };

// RVA 0x10bda0: neutral name; capacity of four 16-byte elements up front.
class UnnamedArray_10bda0 : public FArray
{
public:
    UnnamedArray_10bda0() : FArray(4)
    {
        Data = GMalloc->Malloc(ArrayMax * sizeof(FElement16_10bda0), UnnamedArray_10bda0_Tag);
    }
};

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
INT Driver_10bd60(TArray<INT> *A, INT *Item) { return A->RemoveItem(*Item); }
void Driver_10bda0(void *Mem) { Escape(&GMalloc); new(Mem) UnnamedArray_10bda0; }
