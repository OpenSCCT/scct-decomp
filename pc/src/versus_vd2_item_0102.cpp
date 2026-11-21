// Work item 0102: Versus RVA 0x180b0 (LTCG constructor).
// Class names are neutral: the vtable at 0x10c0cf98 is unlabelled.
// LTCG convention: `this` on the stack, Owner in ECX, ret 0x10.
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned int size_t;

inline void *operator new(size_t, void *Mem) { return Mem; }

class UnnamedOwner_180b0
{
public:
    virtual void Slot00();
    virtual void Slot04();
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();
    virtual void Register(class UnnamedBase_180b0 *Item); // +0x28
};

class UnnamedBase_180b0
{
public:
    INT V04, V08, V0c, V10, V14, V18, V1c, V20, V24, V28, V2c, V30, V34, V38, V3c;
    UnnamedBase_180b0()
        : V04(0xaf), V08(2000), V0c(0), V10(0), V14(0), V18(0), V1c(0),
          V20(1), V24(1), V28(1), V2c(0), V30(0), V34(3), V38(0), V3c(-1)
    {}
    virtual ~UnnamedBase_180b0();
};

class UnnamedDerived_180b0 : public UnnamedBase_180b0
{
public:
    INT V40;
    INT A;
    INT B;
    UnnamedOwner_180b0 *Owner;
    INT C;
    UnnamedDerived_180b0(INT InA, INT InB, UnnamedOwner_180b0 *InOwner, INT InC);
    virtual ~UnnamedDerived_180b0();
};

// RVA 0x180b0
UnnamedDerived_180b0::UnnamedDerived_180b0(INT InA, INT InB, UnnamedOwner_180b0 *InOwner, INT InC)
    : V40(0), A(InA), B(InB), Owner(InOwner), C(InC)
{
    Owner->Register(this);
}

// Scaffolding for the link, not part of the unit.
void Driver_180b0(void *Mem, INT A, INT B, UnnamedOwner_180b0 *O, INT C)
{
    new (Mem) UnnamedDerived_180b0(A, B, O, C);
}
