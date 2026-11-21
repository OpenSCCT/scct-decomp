// Versus RVA 0x11a70: reallocates a simple array (Data, Num) to Num * ElementSize
// bytes through GMalloc, tagged "FSArray". LTCG: this in ESI, ElementSize on the stack.
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
extern FMalloc *GMalloc;
extern const TCHAR FSArray_Tag[]; // L"FSArray"

// Neutral name: a simple array with only Data and Num.
class FSArray
{
public:
    void *Data;
    INT ArrayNum;
    void Realloc(INT ElementSize);
};

__declspec(noinline) void FSArray::Realloc(INT ElementSize)
{
    Data = GMalloc->Realloc(Data, ArrayNum * ElementSize, FSArray_Tag);
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_11a70(FSArray *A, FSArray *B, FSArray *C, INT ElementSize)
{
    Escape(&GMalloc);
    A->Realloc(ElementSize);
    Escape(A);
    B->Realloc(ElementSize);
    Escape(B);
    C->Realloc(ElementSize);
    Escape(C);
    A->Realloc(ElementSize);
    Escape(A);
    B->Realloc(ElementSize);
    Escape(B);
    C->Realloc(ElementSize);
    Escape(C);
    A->Realloc(ElementSize);
    Escape(A);
    B->Realloc(ElementSize);
    Escape(B);
}
