// campaign_leaf_53b470.cpp -- cdecl function at VA 0x10e3b470: builds a four-word context from the
// record it is given (the object reached through its first member, its second and third members and
// the record itself) and calls the handler that the table at 0x318c of the dispatcher selects by
// the kinds (sixth virtual method) of that object and of the object its second argument holds,
// returning the handler's result. guess: a pairwise dispatch. All names are invented.

class UnkType_10e3b470_Object
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual int VirtualSlot5();
};

struct UnkType_10e3b470_Holder
{
    UnkType_10e3b470_Object* unk_00;
};

struct UnkType_10e3b470_Owner
{
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e3b470_Object* unk_0c;
};

struct UnkType_10e3b470_Record
{
    UnkType_10e3b470_Owner* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_10e3b470_Context
{
    UnkType_10e3b470_Object* unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e3b470_Record* unk_0c;
};

struct UnkType_10e3b470_Dispatcher;

typedef int (*UnkType_10e3b470_Handler)(UnkType_10e3b470_Context* Context,
                                       UnkType_10e3b470_Holder* Holder,
                                       UnkType_10e3b470_Dispatcher* Dispatcher,
                                       int First, int Second);

struct UnkType_10e3b470_Tables
{
    int unk_00[0x318c / 4];
    UnkType_10e3b470_Handler unk_318c[32][32];
};

struct UnkType_10e3b470_Dispatcher
{
    UnkType_10e3b470_Tables* unk_00;
};

// Unk_10e3b470
int Unk_10e3b470(UnkType_10e3b470_Record* Record, UnkType_10e3b470_Holder* Holder,
                 UnkType_10e3b470_Dispatcher* Dispatcher, int First, int Second)
{
    UnkType_10e3b470_Context Context;
    Context.unk_08 = Record->unk_08;
    Context.unk_0c = Record;
    UnkType_10e3b470_Object* Object = Record->unk_00->unk_0c;
    Context.unk_04 = Record->unk_04;
    Context.unk_00 = Object;
    int HolderKind = Holder->unk_00->VirtualSlot5();
    int ObjectKind = Object->VirtualSlot5();
    return Dispatcher->unk_00->unk_318c[ObjectKind][HolderKind](&Context, Holder, Dispatcher,
                                                          First, Second);
}
