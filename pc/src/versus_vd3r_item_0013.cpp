// Versus RVA 0x5150 (FUN_10905150): destructor of an unnamed record class.
// Its base destructor is RVA 0x2146b0 (FUN_10b146b0). Link-time code
// generation gave the destructor `this` on the stack and `ret 4`; it is
// called from the scalar deleting destructor (RVA 0x51b0), from a derived
// destructor (RVA 0x52xx) and from constructor unwind funclets.
// Names are neutral: no string or label identifies the classes.
//
// Vtable at 0x10c0da20: slot 1 is the scalar deleting destructor (RVA 0x51b0),
// slot 5 the shutdown hook the destructor calls once (flag bit 0 at +0x10).
// Retail calls slot 5 through memory (`call [vftable+0x14]`), so the table's
// contents were not visible to the optimiser; the slot is declared dllimport
// here to reproduce that indirect call (same shape as RVA 0x5200).

typedef unsigned long DWORD;

class UnnamedRecordRoot_2146b0
{
public:
    virtual void Slot0();
    virtual void *DeletingDestructor(unsigned int Flags);
    ~UnnamedRecordRoot_2146b0();
};

class UnnamedRecord_5150 : public UnnamedRecordRoot_2146b0
{
public:
    virtual void Slot0();
    virtual void *DeletingDestructor(unsigned int Flags);
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    __declspec(dllimport) virtual void Shutdown();
    ~UnnamedRecord_5150();

    DWORD Fields[3];
    DWORD Flags;
};

UnnamedRecord_5150::~UnnamedRecord_5150()
{
    if (!(Flags & 1))
    {
        Flags |= 1;
        Shutdown();
    }
}

// Scaffolding for the link, not part of the unit.
void Driver_5150(UnnamedRecord_5150 *R) { R->~UnnamedRecord_5150(); }
