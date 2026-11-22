// campaign_leaf_501c40.cpp -- free function at VA 0x10e01c40: calls the fourth virtual method of
// the object at offset 8 of its argument and returns the argument. All names are
// invented.

class UnkType_10e01c40_Obj
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
};

struct UnkType_10e01c40
{
    int unk_00;
    int unk_04;
    UnkType_10e01c40_Obj* unk_08;
};

// Unk_10e01c40
UnkType_10e01c40* Unk_10e01c40(UnkType_10e01c40* Value)
{
    Value->unk_08->VirtualSlot3();
    return Value;
}
