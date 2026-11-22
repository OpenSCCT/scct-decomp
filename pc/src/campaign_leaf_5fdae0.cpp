// campaign_leaf_5fdae0.cpp -- thiscall method at VA 0x10efdae0: calls its second virtual method,
// clears the member at 0x0c and returns true. The class and method names are invented.

class UnkType_10efdae0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();

    bool Unk_10efdae0();

private:
    int unk_04;
    int unk_08;
    int unk_0c;
};

// UnkType_10efdae0::Unk_10efdae0
bool UnkType_10efdae0::Unk_10efdae0()
{
    VirtualSlot1();
    unk_0c = 0;
    return true;
}
