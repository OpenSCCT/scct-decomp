// Work item 0372: Versus RVA 0xa4060-0xa4306.
//   0xa4060  destructor of UnnamedClass_A4060 (a UObject subclass; neutral name,
//            no vtable label identifies it)
//   0xa4170  TArray<UnnamedElement_2C>::~TArray  (LTCG: this on stack, ret 4)
//   0xa41e0  TArray<UnnamedElement_2C>::Remove   (LTCG: Index in EDI, this on stack)
//   0xa4230  constructor of UnnamedStruct_A4230  (LTCG callee takes this in ESI)
//   0xa4250  TArray<UnnamedElement_5C>::~TArray  (LTCG: this on stack, ret 4)
//   0xa42c0  TArray<UnnamedElement_5C>::Remove   (LTCG: Index in EDI, this on stack)
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
    void Remove(INT Index, INT Count, INT ElementSize);  // 0x119c0
    ~FArray()
    {
        if (Data)
        {
            GMalloc->Free(Data);
            Data = 0;
        }
        ArrayNum = ArrayMax = 0;
    }
};

template <class T> class TArray : public FArray
{
public:
    ~TArray() { Remove(0, ArrayNum); }
    T &operator()(INT i) { return ((T *)Data)[i]; }
    void Remove(INT Index, INT Count = 1);
};

// Not inlined in retail (Index in EDI, this on the stack under LTCG).
template <class T> __declspec(noinline) void TArray<T>::Remove(INT Index, INT Count)
{
    for (INT i = Index; i < Index + Count; i++)
        (&(*this)(i))->~T();
    FArray::Remove(Index, Count, sizeof(T));
}

// Element types (neutral names). Their destructors were LTCG-rewritten to take
// `this` on the stack; they are declared here as __stdcall functions.
struct UnnamedElement_2C;
struct UnnamedElement_5C;
void __stdcall UnnamedElement_2C_Destroy(UnnamedElement_2C *Self); // 0x86010
void __stdcall UnnamedElement_5C_Destroy(UnnamedElement_5C *Self); // 0x861a0

struct UnnamedElement_2C
{
    DWORD Pad[11];
    ~UnnamedElement_2C() { UnnamedElement_2C_Destroy(this); }
};

struct UnnamedElement_5C
{
    DWORD Pad[23];
    ~UnnamedElement_5C() { UnnamedElement_5C_Destroy(this); }
};

// ---------------------------------------------------------------------------
// 0xa4060: destructor of a UObject subclass (vtable at 0x10c0a6b0).

// Member destructors, LTCG-rewritten to take `this` on the stack.
void __stdcall UnnamedArray_Release(void *Array);            // 0x17bf30
void __stdcall UnnamedMember_124_Destroy(void *Member);      // 0x1edf20
void __stdcall UnnamedMember_130_Destroy(void *Member);      // 0x1fb4d0
void __stdcall UnnamedMember_14C_Destroy(void *Member);      // 0x1ee510
void __stdcall UnnamedArray2C_Destroy(TArray<UnnamedElement_2C> *Array); // 0xa4170

struct UnnamedArray_Member
{
    DWORD Data[3];
    ~UnnamedArray_Member() { UnnamedArray_Release(this); }
};
struct UnnamedArray2C_Member
{
    DWORD Data[3];
    ~UnnamedArray2C_Member() { UnnamedArray2C_Destroy((TArray<UnnamedElement_2C> *)this); }
};
struct UnnamedMember_124
{
    DWORD Data[3];
    ~UnnamedMember_124() { UnnamedMember_124_Destroy(this); }
};
struct UnnamedMember_130
{
    DWORD Data[7];
    ~UnnamedMember_130() { UnnamedMember_130_Destroy(this); }
};
struct UnnamedMember_14C
{
    DWORD Data[9];
    ~UnnamedMember_14C() { UnnamedMember_14C_Destroy(this); }
};

inline void *operator new(unsigned int, void *Mem) { return Mem; }

enum { INDEX_NONE = -1 };
enum
{
    RF_Destroyed    = 0x00800000,
    RF_DebugDestroy = 0x80000000,
};

// Base class (destructor at 0xa3f50). UObject layout for the first fields.
class UnnamedBase_A3F50
{
public:
    INT Index;          // 0x04
    DWORD Pad08[5];
    DWORD ObjectFlags;  // 0x1c
    DWORD Pad20[0x35];
    __declspec(dllimport) void Destroy();
    virtual ~UnnamedBase_A3F50();
    void ConditionalDestroy()
    {
        if (Index != INDEX_NONE && !(ObjectFlags & RF_Destroyed))
        {
            ObjectFlags |= RF_Destroyed;
            ObjectFlags &= ~RF_DebugDestroy;
            Destroy();
        }
    }
};

class UnnamedClass_A4060 : public UnnamedBase_A3F50
{
public:
    UnnamedArray_Member ArrayF4;      // 0xf4
    UnnamedArray_Member Array100;     // 0x100
    UnnamedArray_Member Array10C;     // 0x10c
    UnnamedArray2C_Member Array118;   // 0x118
    UnnamedMember_124 Member124;      // 0x124
    UnnamedMember_130 Member130;      // 0x130
    UnnamedMember_14C Member14C;      // 0x14c
    UnnamedElement_2C Elements[4];    // 0x170
    ~UnnamedClass_A4060();
};

UnnamedClass_A4060::~UnnamedClass_A4060()
{
    ConditionalDestroy();
}

// ---------------------------------------------------------------------------
// 0xa4230: constructor of UnnamedStruct_A4230 (neutral name). Its member at +4
// is built by 0x1126e0, which LTCG rewrote to take `this` in ESI; that
// constructor sets a vtable (0x10c037f4), clears three fields and bumps a
// 64-bit global counter. Only its shape matters here: it is defined (not
// inlined) so the link gives it the retail register convention.
extern void *const UnnamedMember_1126E0_vftable[];
extern unsigned __int64 UnnamedMember_1126E0_Counter; // 0x10c96930
#pragma pack(push, 4)
struct UnnamedMember_1126E0
{
    void *const *VfTable;
    DWORD Field04;
    DWORD Field08;
    DWORD Field0C;
    unsigned __int64 Id;   // 0x10
    DWORD Field18;
    __declspec(noinline) UnnamedMember_1126E0()
    {
        VfTable = UnnamedMember_1126E0_vftable;
        Field04 = 0;
        Field08 = 0;
        Field0C = 0;
        Id = UnnamedMember_1126E0_Counter++ * 0x100 + 0xe2;
        Field18 = 0;
    }
};
#pragma pack(pop)

struct UnnamedStruct_A4230
{
    DWORD Field00;
    UnnamedMember_1126E0 Member;          // 0x04
    TArray<UnnamedElement_2C> Array;      // 0x20 (element type unknown)
    UnnamedStruct_A4230();
};

__declspec(noinline) UnnamedStruct_A4230::UnnamedStruct_A4230()
{
    Array.Data = 0;
    Array.ArrayNum = 0;
    Array.ArrayMax = 0;
}

// ---------------------------------------------------------------------------
// Scaffolding for the LTCG link, not part of the unit.
void Escape(void *);
void Driver_a4170(TArray<UnnamedElement_2C> *Array)
{
    Escape(&GMalloc);
    Array->~TArray();
}
void Driver_a4250(TArray<UnnamedElement_5C> *Array)
{
    Escape(&GMalloc);
    Array->~TArray();
}
// 0xa4230 keeps thiscall in retail (it has callers outside the LTCG set), so
// the constructor itself is also passed as a link root.
UnnamedStruct_A4230 *Driver_a4230(UnnamedStruct_A4230 *Mem)
{
    return new (Mem) UnnamedStruct_A4230;
}
