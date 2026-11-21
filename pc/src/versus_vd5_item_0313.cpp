// Work item w3 0313: Versus RVA 0x109630-0x1097b5 (LTCG objects, VC7.0 /GL).
// Six TArray<T>::Empty(INT Slack) instantiations (UE2 UnTemplate.h): destroy
// every element, then FArray::Empty(sizeof(T), Slack). After LTCG `this` is in
// ESI and Slack on the stack (ret 4). The element types are not recovered and
// carry neutral names after their size; their destructors live elsewhere.
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned char BYTE;

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
            GMalloc->Free(Data);
        Data = 0;
        ArrayNum = ArrayMax = 0;
    }
    void Empty(INT ElementSize, INT Slack);      // RVA 0x4550
};

template <class T> class TArray : public FArray
{
public:
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Empty(INT Slack = 0);
};

template <class T> __declspec(noinline) void TArray<T>::Empty(INT Slack)
{
    for (INT i = 0; i < ArrayNum; i++)
        (&(*this)(i))->~T();
    FArray::Empty(sizeof(T), Slack);
}

void Touch(void *);  // stand-in body helper only

// Element types (neutral names; size from the stride). The destructors are
// defined here only so the link gives each call its retail convention; their
// bodies are stand-ins, not matches. Retail's own destructors have exception
// frames (this on the stack); the one at 0xa8a40 takes this in EAX.
struct UnnamedMember { INT Value; ~UnnamedMember(); };
struct UnnamedElement_34 { BYTE Pad[0x34]; ~UnnamedElement_34(); };  // dtor RVA 0xa4770 (this in ECX)
struct UnnamedElement_38 { INT Pad0; UnnamedMember A; BYTE Pad8[0x28]; UnnamedMember B; INT Pad34; ~UnnamedElement_38(); };  // dtor RVA 0xa8c70
struct UnnamedElement_70 { INT Pad0; UnnamedMember A; BYTE Pad8[0x28]; UnnamedMember B; BYTE Pad34[0x3c]; ~UnnamedElement_70(); };  // dtor RVA 0xa8d90
struct UnnamedElement_a4 { INT Pad0; UnnamedMember A; BYTE Pad8[0x28]; UnnamedMember B; BYTE Pad34[0x70]; ~UnnamedElement_a4(); };  // dtor RVA 0xa9000
struct UnnamedElement_5c { BYTE Pad[0x5c]; ~UnnamedElement_5c(); };  // dtor RVA 0xa8a40 (this in EAX)
// 0x2c-byte element owning a raw allocation at +0x20, freed (not cleared)
// by its inline destructor.
struct UnnamedElement_2c
{
    BYTE Pad[0x20];
    void *Buffer;
    BYTE Pad24[0x8];
    ~UnnamedElement_2c()
    {
        if (Buffer)
            GMalloc->Free(Buffer);
    }
};

__declspec(noinline) UnnamedElement_38::~UnnamedElement_38() {}
__declspec(noinline) UnnamedElement_70::~UnnamedElement_70() {}
__declspec(noinline) UnnamedElement_a4::~UnnamedElement_a4() {}
__declspec(noinline) UnnamedElement_5c::~UnnamedElement_5c() { Touch(Pad + 4); Touch(Pad + 8); }

// RVA 0x109630
template void TArray<UnnamedElement_34>::Empty(INT);
// RVA 0x109670
template void TArray<UnnamedElement_38>::Empty(INT);
// RVA 0x1096b0
template void TArray<UnnamedElement_70>::Empty(INT);
// RVA 0x1096f0
template void TArray<UnnamedElement_a4>::Empty(INT);
// RVA 0x109730
template void TArray<UnnamedElement_5c>::Empty(INT);
// RVA 0x109770
template void TArray<UnnamedElement_2c>::Empty(INT);

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_109630(TArray<UnnamedElement_34> *A, INT S) { Escape(&GMalloc); A->Empty(S); A->Empty(S + 1); }
void Driver_109670(TArray<UnnamedElement_38> *A, INT S) { Escape(&GMalloc); A->Empty(S); A->Empty(S + 1); }
void Driver_1096b0(TArray<UnnamedElement_70> *A, INT S) { Escape(&GMalloc); A->Empty(S); A->Empty(S + 1); }
void Driver_1096f0(TArray<UnnamedElement_a4> *A, INT S) { Escape(&GMalloc); A->Empty(S); A->Empty(S + 1); }
void Driver_109730(TArray<UnnamedElement_5c> *A, INT S) { Escape(&GMalloc); A->Empty(S); A->Empty(S + 1); }
void Driver_109770(TArray<UnnamedElement_2c> *A, INT S) { Escape(&GMalloc); A->Empty(S); A->Empty(S + 1); }
