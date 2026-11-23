// campaign_leaf_4adb90.cpp -- one function at file offset 0x4adb90, preferred VA 0x10dadb90.
// It holds a local object built with the constructor at 0x10d97ff0 from 2 while it passes Value to
// the virtual method in slot 6, then destroys it with the destructor at 0x10d98020. The class,
// method, variable and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10dadb90_Guard
{
public:
    int unk_0;

    UnkType_10dadb90_Guard(int Kind);
    ~UnkType_10dadb90_Guard();
};

class UnkType_10dadb90
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6(int Value);

    void Unk_10dadb90(int Value);
};

// UnkType_10dadb90::Unk_10dadb90
void UnkType_10dadb90::Unk_10dadb90(int Value)
{
    UnkType_10dadb90_Guard Guard(2);

    VirtualSlot6(Value);
}
