/* Work item 0368: TArray<36-byte element>::~TArray at 0xa36e0 (TArray::~TArray then FArray::~FArray, UnTemplate.h shapes).
   FArray::Remove is the published remove_array (0x119c0). The element type has no
   recovered name (Element_a36e0 is neutral). Retail is the LTCG copy of the destructor
   (this on the stack, ret 4). */
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
    ~TArray()
    {
        Remove(0, ArrayNum);
    }
    void Remove(INT Index, INT Count = 1)
    {
        FArray::Remove(Index, Count, sizeof(T));
    }
};

struct Element_a36e0 { INT Fields[9]; };

// Force the destructor body out of line so the linker emits it for the driver.
template class TArray<Element_a36e0>;

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_a36e0(TArray<Element_a36e0> *A, TArray<Element_a36e0> *B)
{
    Escape(&GMalloc);
    A->~TArray<Element_a36e0>();
    B->~TArray<Element_a36e0>();
}
