// Work item w3 0136: Versus RVA 0xc0d80-0xc0ef4.
// Array helpers from an LTCG object (custom calling conventions):
//  0xc0d80  FSArray-style Add for 0x30-byte elements (this in ESI, Count in EAX)
//  0xc0de0  TArray<T>::Empty for a 0x68-byte element with a virtual destructor
//  0xc0e20  TArray<T>::~TArray for a trivial 0x28-byte element
//  0xc0e90  TArray<T>::~TArray for a trivial 0x40-byte element
// Element types are unnamed (neutral names); the "FSArray" allocation tags
// come from retail strings.
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

// Small array (Data, Num) with exact-size allocation; element of 0x30 bytes.
struct UnnamedElement_c0d80 { INT Pad[12]; };

class FSArray_c0d80
{
public:
    void *Data;
    INT ArrayNum;
    INT Add(INT Count);
};

// RVA 0xc0d80
__declspec(noinline) INT FSArray_c0d80::Add(INT Count)
{
    INT Index = ArrayNum;
    ArrayNum += Count;
    INT Bytes = ArrayNum * sizeof(UnnamedElement_c0d80);
    if (Data == 0)
        Data = Bytes > 0 ? GMalloc->Malloc(Bytes, L"FSArray::Add") : 0;
    else
        Data = GMalloc->Realloc(Data, Bytes, L"FSArray");
    return Index;
}

// 0x68-byte element with a virtual destructor.
class UnnamedElement_c0de0
{
public:
    virtual ~UnnamedElement_c0de0();
    INT Pad[25];
};

class TArray_c0de0 : public FArray
{
public:
    void Empty(INT Slack);
};

// RVA 0xc0de0
__declspec(noinline) void TArray_c0de0::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&((UnnamedElement_c0de0 *)Data)[i])->~UnnamedElement_c0de0();
    FArray::Empty(sizeof(UnnamedElement_c0de0), Slack);
}

struct UnnamedElement_c0e20 { INT Pad[10]; };
struct UnnamedElement_c0e90 { INT Pad[16]; };

class TArray_c0e20 : public FArray
{
public:
    __declspec(noinline) ~TArray_c0e20() { Remove(0, ArrayNum, sizeof(UnnamedElement_c0e20)); }
};

class TArray_c0e90 : public FArray
{
public:
    __declspec(noinline) ~TArray_c0e90() { Remove(0, ArrayNum, sizeof(UnnamedElement_c0e90)); }
};

// Scaffolding for the link, not part of the unit.
void Escape(void *);
INT Driver_c0d80(FSArray_c0d80 *A, INT N) { Escape(&GMalloc); return A->Add(N); }
void Driver_c0de0(TArray_c0de0 *A, INT S) { Escape(&GMalloc); A->Empty(S); }
void Driver_c0e20(TArray_c0e20 *A) { Escape(&GMalloc); A->~TArray_c0e20(); }
void Driver_c0e90(TArray_c0e90 *A) { Escape(&GMalloc); A->~TArray_c0e90(); }
