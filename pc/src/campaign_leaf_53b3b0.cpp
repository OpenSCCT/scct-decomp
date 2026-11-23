// campaign_leaf_53b3b0.cpp -- cdecl function at VA 0x10e3b3b0: builds a four-word context from the
// record it is given (the object reached through its first member, its second and third members and
// the record itself) and calls the handler that the table at 0x218c of the dispatcher selects by
// the kinds (sixth virtual method) of that object and of the object its second argument holds,
// returning the handler's result. guess: a pairwise dispatch. All names are invented.

class UnkType_10e3b3b0_Object
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual int VirtualSlot5();
};

struct UnkType_10e3b3b0_Holder
{
    UnkType_10e3b3b0_Object* unk_00;
};

struct UnkType_10e3b3b0_Owner
{
    int unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e3b3b0_Object* unk_0c;
};

struct UnkType_10e3b3b0_Record
{
    UnkType_10e3b3b0_Owner* unk_00;
    int unk_04;
    int unk_08;
};

struct UnkType_10e3b3b0_Context
{
    UnkType_10e3b3b0_Object* unk_00;
    int unk_04;
    int unk_08;
    UnkType_10e3b3b0_Record* unk_0c;
};

struct UnkType_10e3b3b0_Dispatcher;

typedef int (*UnkType_10e3b3b0_Handler)(UnkType_10e3b3b0_Context* Context,
                                       UnkType_10e3b3b0_Holder* Holder,
                                       UnkType_10e3b3b0_Dispatcher* Dispatcher, int Value);

struct UnkType_10e3b3b0_Tables
{
    int unk_00[0x218c / 4];
    UnkType_10e3b3b0_Handler unk_218c[32][32];
};

struct UnkType_10e3b3b0_Dispatcher
{
    UnkType_10e3b3b0_Tables* unk_00;
};

// Unk_10e3b3b0
int Unk_10e3b3b0(UnkType_10e3b3b0_Record* Record, UnkType_10e3b3b0_Holder* Holder,
                 UnkType_10e3b3b0_Dispatcher* Dispatcher, int Value)
{
    UnkType_10e3b3b0_Context Context;
    Context.unk_08 = Record->unk_08;
    Context.unk_0c = Record;
    UnkType_10e3b3b0_Object* Object = Record->unk_00->unk_0c;
    Context.unk_04 = Record->unk_04;
    Context.unk_00 = Object;
    int Second = Holder->unk_00->VirtualSlot5();
    int First = Object->VirtualSlot5();
    return Dispatcher->unk_00->unk_218c[First][Second](&Context, Holder, Dispatcher, Value);
}
