// Work item 0012 (LTCG retry): Versus RVA 0x50a0 (FUN_109050a0), destructor
// of an unnamed record class. Its base destructor is RVA 0x215970, the
// destructor of the node class with vtable 0x10c0f280 (UnnamedNode_4cd0 in
// item 0011), which unregisters the node from its owner's list and then runs
// the root destructor at RVA 0x2146b0. Neutral names: no string or vtable
// label identifies these classes. Built with VC7.0 /GL and linked with /LTCG,
// which gave both destructors `this` on the stack and `ret 4`.
//
// Vtable 0x10c0ef78; slot 5 (0x10c0ef8c) is the "release once" hook guarded
// by flag bit 0 at +0x10. Retail calls it as `call [vtable + 0x14]` (the
// optimiser forwarded the vptr just stored), so the slot is declared as a
// __declspec(dllimport) member here to give the same indirect call.

typedef unsigned long DWORD;

class UnnamedNode_4cd0;

// Owner's node list (TArray<UnnamedNode_4cd0*> at owner +0x20).
class UnnamedNodeList_4cd0
{
public:
    void RemoveItem(UnnamedNode_4cd0 *const &Item); // RVA 0x20bd60, array in EDI
    void **Data;
    int ArrayNum;
    int ArrayMax;
};

struct UnnamedOwner_4cd0
{
    int Reserved[8];
    UnnamedNodeList_4cd0 Nodes;             // +0x20
};

// Root of the chain; destructor at RVA 0x2146b0.
class UnnamedRoot_2146b0
{
public:
    virtual void Slot0();
    virtual void *DeletingDestructor(unsigned int Flags); // slot 1
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Release();                 // slot 5
    ~UnnamedRoot_2146b0();

    DWORD Fields[3];
    DWORD Flags;                            // +0x10, bit 0 = released
};

// Vtable 0x10c0f280; destructor at RVA 0x215970.
class UnnamedNode_4cd0 : public UnnamedRoot_2146b0
{
public:
    ~UnnamedNode_4cd0();
    UnnamedOwner_4cd0 *Owner;               // +0x14
};

// Vtable 0x10c0ef78.
class UnnamedRecord_50a0 : public UnnamedNode_4cd0
{
public:
    ~UnnamedRecord_50a0();
    __declspec(dllimport) void ReleaseSlot(); // vtable 0x10c0ef78 slot 5
};

// RVA 0x50a0: `this` on the stack; releases once, then runs the base destructor.
UnnamedRecord_50a0::~UnnamedRecord_50a0()
{
    if (!(Flags & 1))
    {
        Flags |= 1;
        ReleaseSlot();
    }
}

// Scaffolding for the link, not part of the unit: the base destructor
// (RVA 0x215970, its own unit) is defined here so the linker sees it as a
// local function and gives it the same `this`-on-stack convention as retail.
UnnamedNode_4cd0::~UnnamedNode_4cd0()
{
    if (Owner)
        Owner->Nodes.RemoveItem(this);
}

void Driver_50a0(UnnamedRecord_50a0 *A, UnnamedRecord_50a0 *B, UnnamedRecord_50a0 *C)
{
    A->UnnamedRecord_50a0::~UnnamedRecord_50a0();
    B->UnnamedRecord_50a0::~UnnamedRecord_50a0();
    C->UnnamedRecord_50a0::~UnnamedRecord_50a0();
}
