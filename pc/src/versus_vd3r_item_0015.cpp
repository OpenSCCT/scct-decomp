// Work item 0015 (LTCG retry): Versus RVA 0x52b0 and 0x5330.
// Class names are neutral: no vtable label or string identifies these classes.
// 0x52b0 is the destructor the scalar deleting destructor at 0x5420 calls;
// 0x5330 is the matching constructor. Both came out of link-time code
// generation (`this` on the stack, ret 4 / ret 8; 0x5330 also takes the
// owner in ECX).
typedef unsigned short TCHAR;
typedef int INT;
typedef unsigned long DWORD;
typedef unsigned short WORD;
extern "C" __declspec(dllimport) TCHAR *__cdecl wcscpy(TCHAR *, const TCHAR *);

// Untyped dynamic array (RVA 0x44e0 is Add).
class FArray
{
public:
    void *Data;
    INT ArrayNum;
    INT ArrayMax;
    INT Add(INT Count, INT ElementSize);
};

// Root of the node classes (vtable 0x10c0f458); destructor at RVA 0x2146b0.
// Slot 5 is called through the vtable in retail; declaring it dllimport
// reproduces the indirect call the optimiser emitted after forwarding the vptr.
class UnnamedRoot_2146b0
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    __declspec(dllimport) virtual void Destroy();
    DWORD Field4;
    DWORD Field8;
    WORD Index;
    WORD ChildIndex;
    DWORD Flags;
    UnnamedRoot_2146b0 *Owner;
    DWORD Field18;
    DWORD Field1C;
    FArray Children;
    DWORD Field2C;
    DWORD Field30;
    DWORD Field34;
    DWORD Field38;

    UnnamedRoot_2146b0(UnnamedRoot_2146b0 *InOwner, DWORD InField8)
    {
        Field4 = 0;
        Field8 = InField8;
        Index = 0;
        ChildIndex = 0x2000;
        Flags &= ~3;
        Owner = InOwner;
        Field18 = 0;
        Field1C = 0;
        Children.Data = 0;
        Children.ArrayNum = 0;
        Children.ArrayMax = 0;
        Field38 = 0;
    }
    ~UnnamedRoot_2146b0(); // RVA 0x2146b0
};

// Base of 0x52b0's class (vtable 0x10c0da20); destructor at RVA 0x5150.
class UnnamedNode_5150 : public UnnamedRoot_2146b0
{
public:
    UnnamedNode_5150(UnnamedRoot_2146b0 *InOwner, DWORD InField8)
        : UnnamedRoot_2146b0(InOwner, InField8) {}
    ~UnnamedNode_5150()
    {
        if (!(Flags & 1))
        {
            Flags |= 1;
            Destroy();
        }
    }
};

// Second base at +0x3c (vtable 0x10c0e3f8).
class UnnamedInterface_5330
{
public:
    virtual void ISlot0();
    virtual void ISlot1();
};

// Base of the member at +0x40 (vtable 0x10c0f280); constructor at RVA 0x4cd0,
// destructor at RVA 0x50a0.
class UnnamedChild_4cd0 : public UnnamedRoot_2146b0
{
public:
    void *Context;

    UnnamedChild_4cd0(INT InIndex, UnnamedRoot_2146b0 *InOwner, void *InContext)
        : UnnamedRoot_2146b0(InOwner, 0)
    {
        Context = InContext;
        if (!InIndex)
            InIndex = Owner->ChildIndex++;
        Index = (WORD)InIndex;
        FArray &List = Owner->Children;
        ((UnnamedChild_4cd0 **)List.Data)[List.Add(1, 4)] = this;
    }
    ~UnnamedChild_4cd0(); // RVA 0x50a0
};

// Small polymorphic pair stored inside the member (vtable 0x10c0f060).
class UnnamedPair_5330
{
public:
    virtual void Slot0();
    DWORD A;
    DWORD B;
    UnnamedPair_5330() : A(0), B(0) {}
};

// Member at +0x40 (vtable 0x10c0ed78); destructor at RVA 0x5200.
class UnnamedMember_5200 : public UnnamedChild_4cd0
{
public:
    UnnamedPair_5330 PairA;
    UnnamedPair_5330 PairB;
    UnnamedRoot_2146b0 *Parent;
    UnnamedMember_5200(UnnamedRoot_2146b0 *InParent, void *InContext)
        : UnnamedChild_4cd0(0, InParent, InContext), Parent(InParent) {}
    ~UnnamedMember_5200()
    {
        if (!(Flags & 1))
        {
            Flags |= 1;
            Destroy();
        }
    }
};

extern void *GUnnamed_10c91c14;

class UnnamedClass_52b0 : public UnnamedNode_5150, public UnnamedInterface_5330
{
public:
    UnnamedMember_5200 Member;
    DWORD Field9C;
    DWORD FieldA0;
    DWORD FieldA4;
    TCHAR Text[256];
    DWORD Field2A8;

    UnnamedClass_52b0(UnnamedRoot_2146b0 *InOwner, DWORD InField8);
    ~UnnamedClass_52b0();
};

// RVA 0x5330
UnnamedClass_52b0::UnnamedClass_52b0(UnnamedRoot_2146b0 *InOwner, DWORD InField8)
    : UnnamedNode_5150(InOwner, InField8), Member(this, GUnnamed_10c91c14)
{
    Field9C = 0;
    FieldA0 = 0x100;
    FieldA4 = 0x40;
    Field2A8 = 0;
    wcscpy(Text, L">");
}

// RVA 0x52b0
UnnamedClass_52b0::~UnnamedClass_52b0()
{
    if (!(Flags & 1))
    {
        Flags |= 1;
        Destroy();
    }
}

// Status: 0x52b0 matches (ltcg, /O2 /Gy /GX). 0x5330 is a near miss: same
// instructions apart from scheduling (the `and edx, ~3` on the flags is placed
// right after its load instead of after the word stores, so `push edi` moves
// up), the global loaded into EDX instead of EAX, and LTCG giving the 0x4cd0
// constructor's index/owner arguments in ECX/EDX where retail uses EDX/ECX.
// Escaping GUnnamed_10c91c14 makes it worse (vptr stores move before the load).

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *P) { return P; }
inline void operator delete(void *, void *) {}
void Driver_52b0(UnnamedClass_52b0 *P) { P->~UnnamedClass_52b0(); }
UnnamedClass_52b0 *Driver_5330(void *Mem, UnnamedRoot_2146b0 *Owner, DWORD F)
{
    return new (Mem) UnnamedClass_52b0(Owner, F);
}
