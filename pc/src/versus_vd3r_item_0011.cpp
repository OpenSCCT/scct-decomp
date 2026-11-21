// Work item 0011 (LTCG retry): Versus RVA 0x4f90 (destructor) and 0x4ff0
// (constructor) of one class. Neutral names: no vtable label or string
// identifies these classes yet. Built with VC7.0 /GL and linked with /LTCG,
// which gives the custom register conventions seen in retail.
//
// Vtables: 0x10c0f280 (UnnamedNode_4cd0), 0x10c0f368 (UnnamedBase_4e70),
// 0x10c0e828 (UnnamedClass_4f90), 0x10c0f060 (UnnamedDelegate_4ed0). The
// first three share slot 5 = RVA 0x10b149e0, "release once". In the original
// the destructors make a virtual call to slot 5 and the optimiser forwards the
// vptr just stored, giving `call [vtable + 0x14]`. try_ltcg.py compares the
// contents of a compiler-generated vtable with retail when an address points
// inside it (which can never agree), so the slot-5 call is written here as a
// call through the slot's address: a __declspec(dllimport) member, which
// emits the same `call [slot]`.
typedef unsigned long DWORD;

// FArray from Unreal Engine 2: Add() is the published add_array at RVA 0x44e0.
class FArray {
public:
    int Add(int Count, int ElementSize);
    void **Data;
    int ArrayNum;
    int ArrayMax;
};

struct UnnamedOwner_4cd0 {
    int Reserved0[3];
    unsigned short Padding0c;
    unsigned short NextIndex;         // +0x0e
    int Reserved10[4];
    FArray Nodes;                     // +0x20
};

// Vtable 0x10c0f060: a 12-byte callback (object + function), passed by value.
struct UnnamedDelegate_4ed0
{
    UnnamedDelegate_4ed0() : Object(0), Func(0) {}
    virtual void Slot0();
    void *Object;
    void *Func;
};

extern void *GUnnamedDefaultOuter_4ed0;   // 0x10c91644

// Root of the chain; destructor at RVA 0x215970.
struct UnnamedRoot_4e70
{
    UnnamedRoot_4e70(UnnamedOwner_4cd0 *owner)
        : Value4(0), Value8(0), Index(0), Flags0e(0x2000), Owner(owner),
          Value18(0), Value1c(0), Value20(0), Value24(0), Value28(0), Value38(0)
    {
        Released = 0;
        BitB = 0;
    }
    virtual void Slot0();
    virtual ~UnnamedRoot_4e70();      // slot 1
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Release();           // slot 5 (RVA 0x10b149e0)
    int Value4;
    int Value8;
    unsigned short Index;             // +0x0c
    unsigned short Flags0e;           // +0x0e
    DWORD Released : 1;               // +0x10 bit 0
    DWORD BitB : 1;
    UnnamedOwner_4cd0 *Owner;         // +0x14
    int Value18, Value1c, Value20, Value24, Value28;
    int Value2c, Value30, Value34;
    int Value38;
};

// Vtable 0x10c0f280; constructor at RVA 0x4cd0 (owner in ECX, index in EDX).
struct UnnamedNode_4cd0 : UnnamedRoot_4e70
{
    UnnamedNode_4cd0(UnnamedOwner_4cd0 *owner, int index, void *outer);
    void *Outer;                      // +0x3c
};

UnnamedNode_4cd0::UnnamedNode_4cd0(UnnamedOwner_4cd0 *owner, int index, void *outer)
    : UnnamedRoot_4e70(owner), Outer(outer)
{
    Index = (unsigned short)(index ? index : owner->NextIndex++);
    FArray *nodes = &Owner->Nodes;
    nodes->Data[nodes->Add(1, sizeof(void *))] = this;
}

// Vtable 0x10c0f368; constructor at RVA 0x4ed0, destructor at RVA 0x4e70.
struct UnnamedBase_4e70 : UnnamedNode_4cd0
{
    UnnamedBase_4e70(UnnamedOwner_4cd0 *owner, int index, UnnamedDelegate_4ed0 d, void *outer = 0);
    ~UnnamedBase_4e70();
    __declspec(dllimport) void ReleaseSlot(); // vtable 0x10c0f368 slot 5
    UnnamedDelegate_4ed0 D0, D1, D2, D3, D4, D5;   // +0x40..+0x84
    DWORD Field88;
    DWORD Field8c;
    DWORD Field90;
};

UnnamedBase_4e70::UnnamedBase_4e70(UnnamedOwner_4cd0 *owner, int index, UnnamedDelegate_4ed0 d, void *outer)
    : UnnamedNode_4cd0(owner, index, outer ? outer : GUnnamedDefaultOuter_4ed0), D0(d), Field8c(0)
{
}

UnnamedBase_4e70::~UnnamedBase_4e70()
{
    if (!Released)
    {
        Released = 1;
        ReleaseSlot();
    }
}

// Vtable 0x10c0e828.
struct UnnamedClass_4f90 : UnnamedBase_4e70
{
    UnnamedClass_4f90(UnnamedOwner_4cd0 *owner, int index, UnnamedDelegate_4ed0 d, int value);
    ~UnnamedClass_4f90();
    __declspec(dllimport) void ReleaseSlot(); // vtable 0x10c0e828 slot 5
    DWORD Field94;
    int Value98;
};

// RVA 0x4ff0: `this` in EAX, arguments on the stack.
UnnamedClass_4f90::UnnamedClass_4f90(UnnamedOwner_4cd0 *owner, int index, UnnamedDelegate_4ed0 d, int value)
    : UnnamedBase_4e70(owner, index, d), Field94(0), Value98(value)
{
}

// RVA 0x4f90: `this` on the stack; releases once, then runs the base destructor.
UnnamedClass_4f90::~UnnamedClass_4f90()
{
    if (!Released)
    {
        Released = 1;
        ReleaseSlot();
    }
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned, void *where) { return where; }
void Escape(void *);
void Driver_4f90(UnnamedClass_4f90 *A, UnnamedClass_4f90 *B, UnnamedBase_4e70 *C)
{
    A->UnnamedClass_4f90::~UnnamedClass_4f90();
    B->UnnamedClass_4f90::~UnnamedClass_4f90();
    C->UnnamedBase_4e70::~UnnamedBase_4e70();
}
void Driver_4ff0(void *m1, void *m2, void *m3, UnnamedOwner_4cd0 *o, int i, UnnamedDelegate_4ed0 d, int v)
{
    Escape(&GUnnamedDefaultOuter_4ed0);
    new (m1) UnnamedClass_4f90(o, i, d, v);
    new (m2) UnnamedClass_4f90(o, i + 1, d, v);
    new (m3) UnnamedClass_4f90(o, i + 2, d, v);
}
