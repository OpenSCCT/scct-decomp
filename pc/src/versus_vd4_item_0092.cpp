// Work item 0092: Versus RVA 0x159d0-0x15ae1.
// Class names are neutral: no vtable labels or strings identify them.

// 0x159d0: walk a chain linked through the field at +0x18.
struct UnnamedChain_159d0
{
    char Pad[0x18];
    UnnamedChain_159d0 *Next;

    int IsInChain(UnnamedChain_159d0 *Target);
};

int UnnamedChain_159d0::IsInChain(UnnamedChain_159d0 *Target)
{
    for (UnnamedChain_159d0 *Link = Next; Link; Link = Link->Next)
        if (Link == Target)
            return 1;
    return Target == 0;
}

// 0x159f0: constructor of an iterator-like object over an owner.
struct UnnamedOwner_159f0
{
    char Pad[0x24];
    int Value;
};

struct UnnamedBase_159f0
{
    int Owned;
    UnnamedOwner_159f0 *Owner;
    int A;
    int B;

    UnnamedBase_159f0(UnnamedOwner_159f0 *InOwner)
        : Owned(InOwner ? InOwner->Value : 0), Owner(InOwner), A(0), B(0) {}
    virtual void Dummy();
};

struct UnnamedIter_159f0 : public UnnamedBase_159f0
{
    int C;
    int Current;
    int Index0;
    int Index1;

    UnnamedIter_159f0(UnnamedOwner_159f0 *InOwner);
    virtual void Dummy();
};

UnnamedIter_159f0::UnnamedIter_159f0(UnnamedOwner_159f0 *InOwner)
    : UnnamedBase_159f0(InOwner), C(0), Current(InOwner->Value), Index0(-1), Index1(-1)
{
}

// 0x15a40: destructor of an object with three FString/TArray-like members
// and one other member.
struct UnnamedArray_48b0
{
    void *Data; int Num; int Max;
    ~UnnamedArray_48b0();
};
struct UnnamedMember_c5f0
{
    void *Data; int Num; int Max;
    ~UnnamedMember_c5f0();
};
struct UnnamedBase_5ee0
{
    int Handle;
    char Pad[0x14];
    unsigned long Flags;
    char Pad2[0x10];
    ~UnnamedBase_5ee0();
    virtual void Dummy();
};

__declspec(dllimport) void UnnamedRelease_cef4();

struct UnnamedObject_15a40 : public UnnamedBase_5ee0
{
    UnnamedArray_48b0 A;
    UnnamedArray_48b0 B;
    UnnamedArray_48b0 C;
    UnnamedMember_c5f0 D;
    ~UnnamedObject_15a40();
    virtual void Dummy();
};

UnnamedObject_15a40::~UnnamedObject_15a40()
{
    if (Handle != -1 && !(Flags & 0x800000)) {
        Flags = (Flags & 0x7f7fffff) | 0x800000;
        UnnamedRelease_cef4();
    }
}

// Scaffolding for the link, not part of the unit.
inline void *operator new(unsigned int, void *Mem) { return Mem; }
void Escape(void *);
void Driver_159d0(UnnamedChain_159d0 **Objs, UnnamedChain_159d0 *Target)
{
    Escape((void *)Objs[0]->IsInChain(Target));
    Escape((void *)Objs[1]->IsInChain(Objs[2]));
    Escape((void *)Objs[3]->IsInChain(Target));
    Escape((void *)Objs[4]->IsInChain(Objs[5]));
    Escape((void *)Objs[6]->IsInChain(Target));
    Escape((void *)Objs[7]->IsInChain(Objs[8]));
}
void Driver_159f0(UnnamedIter_159f0 *Mem, UnnamedOwner_159f0 **Owners)
{
    Escape(new (Mem) UnnamedIter_159f0(Owners[0]));
    Escape(new (Mem + 1) UnnamedIter_159f0(Owners[1]));
    Escape(new (Mem + 2) UnnamedIter_159f0(Owners[2]));
    Escape(new (Mem + 3) UnnamedIter_159f0(Owners[3]));
    Escape(new (Mem + 4) UnnamedIter_159f0(Owners[4]));
    Escape(new (Mem + 5) UnnamedIter_159f0(Owners[5]));
}
