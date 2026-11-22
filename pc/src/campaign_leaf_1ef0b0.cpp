// campaign_leaf_1ef0b0.cpp -- constructor at VA 0x10aef0b0: runs the base class constructor at VA
// 0x10aee9a0 and installs this class's vtable (VA 0x110dc2c8). The class names are invented; the
// addresses are the binary's.

class UnkType_10aee9a0
{
public:
    UnkType_10aee9a0();

    virtual void VirtualSlot0();
};

class UnkType_10aef0b0 : public UnkType_10aee9a0
{
public:
    UnkType_10aef0b0();
};

// UnkType_10aef0b0::UnkType_10aef0b0
UnkType_10aef0b0::UnkType_10aef0b0()
{
}
