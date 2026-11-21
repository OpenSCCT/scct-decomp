// Work item 0270: Versus RVA 0x68dc0-0x68eed (D3D render device helpers).
// Retail built these with /GL + /LTCG: 0x68dc0 takes its array in ESI,
// 0x68e50 takes the copy source in EDI, 0x68eb0 takes its value in EAX.
// Class names are neutral except FD3DMaterialState (allocation tag
// L"D3DMaterialState", 0x10c74858).

typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef DWORD UBOOL;
typedef float FLOAT;

class FMalloc
{
public:
    virtual void *Malloc(DWORD Count, const TCHAR *Tag);
    virtual void *Realloc(void *Original, DWORD Count, const TCHAR *Tag);
    virtual void Free(void *Original);
};
extern FMalloc *GMalloc;

extern const TCHAR FArray_EmptyTag[];   // L"FArray::Empty" 0x10c10984
extern const TCHAR FArray_ReallocTag[]; // L"FArray"        0x10c10974
extern const TCHAR D3DMaterialStateTag[]; // L"D3DMaterialState" 0x10c74858

void *appMemcpy(void *Dest, const void *Src, INT Count); // 0x40a0

inline void *operator new(unsigned int Size, const TCHAR *Tag)
{
    return GMalloc->Malloc(Size, Tag);
}

class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;

    void Realloc(INT ElementSize)
    {
        if (Data == 0)
            Data = GMalloc->Malloc(ArrayMax * ElementSize, FArray_EmptyTag);
        else
            Data = GMalloc->Realloc(Data, ArrayMax * ElementSize, FArray_ReallocTag);
    }
    void Empty(INT ElementSize, INT Slack)
    {
        ArrayNum = 0;
        if (Slack != ArrayMax)
        {
            ArrayMax = Slack;
            Realloc(ElementSize);
        }
    }
    void Remove(INT Index, INT Count, INT ElementSize); // 0x119c0
};

// 16-byte element (FPlane-sized).
struct FPlane
{
    FLOAT X, Y, Z, W;
    FPlane() {}
    FPlane(const FPlane &P) : X(P.X), Y(P.Y), Z(P.Z), W(P.W) {}
};

// Neutral name: array of 16-byte elements reset to four slots of slack.
class UnnamedPlaneArray_68dc0 : public FArray
{
public:
    __declspec(noinline) void Reset();
};

void UnnamedPlaneArray_68dc0::Reset()
{
    Empty(sizeof(FPlane), 4);
}

// 0x68e00: forwards to a vtable slot 5 call on an interface at +0x14 of the
// object, dropping the third argument. Neutral names.
class UnnamedInterface_68e00
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5(void *Owner, INT A, INT B, INT D, INT E, FPlane P);
};
struct UnnamedOwner_68e00
{
    INT Pad[5];
    UnnamedInterface_68e00 *Interface;
};

__declspec(noinline) void __fastcall UnnamedForward_68e00(void *Unused, UnnamedOwner_68e00 *Owner, INT A, INT B, INT C, INT D, INT E, FPlane P)
{
    Owner->Interface->Slot5(Owner, A, B, D, E, P);
}

// 0x68e50: take a material state from the free list (or allocate one),
// optionally copy from a template, and mark it dirty.
class FD3DMaterialState
{
public:
    unsigned char Body[0x42c];
    INT Dirty;
    __declspec(noinline) FD3DMaterialState(); // 0x6ce90
};

class FD3DMaterialStateArray : public FArray
{
public:
    FD3DMaterialState *Get(FD3DMaterialState *Template);
};

__declspec(noinline) FD3DMaterialState *FD3DMaterialStateArray::Get(FD3DMaterialState *Template)
{
    FD3DMaterialState *State;
    if (ArrayNum)
    {
        INT Index = ArrayNum - 1;
        State = ((FD3DMaterialState **)Data)[Index];
        Remove(Index, 1, sizeof(FD3DMaterialState *));
    }
    else
    {
        State = new(D3DMaterialStateTag) FD3DMaterialState;
    }
    if (Template)
        appMemcpy(State, Template, sizeof(FD3DMaterialState));
    State->Dirty = 1;
    return State;
}

// 0x68eb0: map 2..8 to themselves, anything else to 1.
__declspec(noinline) INT UnnamedMap_68eb0(INT Value)
{
    switch (Value)
    {
    case 1: return 1;
    case 2: return 2;
    case 3: return 3;
    case 4: return 4;
    case 5: return 5;
    case 6: return 6;
    case 7: return 7;
    case 8: return 8;
    default: return 1;
    }
}

// Scaffolding for the link, not part of the unit.
void Escape(void *);
void Driver_68dc0(UnnamedPlaneArray_68dc0 *A, INT N)
{
    Escape(&GMalloc);
    for (INT i = 0; i < 12; i++)
    {
        A[i].Reset();
        Escape(&A[i + N]);
    }
    A[N].Reset(); A[N + 1].Reset(); A[N + 2].Reset(); A[N + 3].Reset();
    A[N + 5].Reset(); A[N + 7].Reset(); A[N + 9].Reset(); A[N + 11].Reset();
}
void Driver_68e00(UnnamedOwner_68e00 *O, INT A, INT B, INT C, INT D, INT E, FPlane P)
{
    Escape((void *)&UnnamedForward_68e00);
}
void Driver_68e50(FD3DMaterialStateArray *A, FD3DMaterialState *T, FD3DMaterialState **Out)
{
    Escape(&GMalloc);
    Out[0] = A->Get(T);
    Out[1] = A->Get(Out[0]);
    Out[2] = A->Get(0);
}
INT Driver_68eb0(INT V, INT W, INT X) { return UnnamedMap_68eb0(V) + UnnamedMap_68eb0(W) * UnnamedMap_68eb0(X); }
// Scaffolding: the constructor (RVA 0x6ce90, its own unit) is defined here
// only so the linker gives it retail's this-on-stack convention. Its body is
// an approximation of retail's (eight 0x7c-byte stages from +0x34).
struct UnnamedMatrix_6ce90 { FLOAT M[16]; };
extern UnnamedMatrix_6ce90 UnnamedIdentity_6ce90; // 0x10cc9560
struct UnnamedStage_6ce90
{
    INT A0, A1, A2, A3;
    FLOAT A4;
    INT A5, A6, A7, A8, A9, A10, A11, A12, A13, A14;
    UnnamedMatrix_6ce90 Matrix;
};
FD3DMaterialState::FD3DMaterialState()
{
    INT *I = (INT *)Body;
    UnnamedStage_6ce90 *Stage = (UnnamedStage_6ce90 *)(Body + 0x34);
    for (INT n = 8; n; n--, Stage++)
    {
        appMemcpy(&Stage->Matrix, &UnnamedIdentity_6ce90, sizeof(UnnamedMatrix_6ce90));
        Stage->A1 = Stage->A2 = Stage->A3 = 3;
        Stage->A5 = Stage->A6 = 2;
        Stage->A14 = Stage->A12 = Stage->A13 = 0;
        Stage->A4 = -1000.f;
        Stage->A0 = 0;
        Stage->A7 = Stage->A8 = Stage->A9 = Stage->A10 = Stage->A11 = 1;
    }
    I[3] = I[4] = 1;
    I[9] = 1;
    I[6] = I[8] = 2;
    I[0] = I[1] = 0;
    Body[8] = 0;
    I[5] = I[7] = I[12] = I[10] = 0;
    I[0x414 / 4] = I[0x418 / 4] = 0;
}
