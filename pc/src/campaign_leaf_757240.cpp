// campaign_leaf_757240.cpp -- one function at file offset 0x757240, preferred VA 0x11057240. It
// returns 0xffff0000 when the object at 0xc of the record is missing, and otherwise the result of
// that object's eighth virtual method. The type and function names are invented; the offsets are
// the binary's.

class UnkType_11057240_Object
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual int VirtualSlot7();
};

struct UnkType_11057240
{
    int unk_0;
    int unk_4;
    int unk_8;
    UnkType_11057240_Object* unk_c;
};

// Unk_11057240
int __stdcall Unk_11057240(UnkType_11057240* Record)
{
    if ( Record->unk_c == 0 )
    {
        return 0xffff0000;
    }
    return Record->unk_c->VirtualSlot7();
}
