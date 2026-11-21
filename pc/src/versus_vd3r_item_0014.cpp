// Versus RVA 0x5200 (FUN_10905200): destructor of an unnamed record class.
// Its base destructor is RVA 0x50a0, which has the same shape one level up
// (its own base destructor is RVA 0x215970). Link-time code generation gave
// these destructors `this` on the stack and `ret 4`.
// Names are neutral: no string or label identifies the classes.
//
// Vtable at 0x10c0ed78: slot 1 is the scalar deleting destructor (RVA 0x5260),
// slot 5 the shutdown hook the destructor calls once (flag bit 0 at +0x10).
// Retail calls slot 5 through memory (`call [vftable+0x14]`), so the table's
// contents were not visible to the optimiser; the slot is declared dllimport
// here to reproduce that indirect call.

typedef unsigned long DWORD;

class UnnamedRecordRoot_215970
{
public:
    ~UnnamedRecordRoot_215970();
};

class UnnamedRecordBase_50a0 : public UnnamedRecordRoot_215970
{
public:
    virtual void Slot0();
    virtual void *DeletingDestructor(unsigned int Flags);
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    __declspec(dllimport) virtual void Shutdown();
    ~UnnamedRecordBase_50a0();

    DWORD Fields[3];
    DWORD Flags;
};

class UnnamedRecord_5200 : public UnnamedRecordBase_50a0
{
public:
    __declspec(dllimport) virtual void Shutdown();
    ~UnnamedRecord_5200();
};

UnnamedRecordBase_50a0::~UnnamedRecordBase_50a0()
{
    if (!(Flags & 1))
    {
        Flags |= 1;
        Shutdown();
    }
}

UnnamedRecord_5200::~UnnamedRecord_5200()
{
    if (!(Flags & 1))
    {
        Flags |= 1;
        Shutdown();
    }
}

// Scaffolding for the link, not part of the unit.
void Driver_5200(UnnamedRecord_5200 *R) { R->~UnnamedRecord_5200(); }
