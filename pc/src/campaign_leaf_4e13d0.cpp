// campaign_leaf_4e13d0.cpp -- one function at file offset 0x4e13d0, preferred VA 0x10de13d0.
// The constructor runs the base constructor at 0x10ddc930 with 1 and installs the vtable at
// 0x11147000. The class names are invented; the offset and the bytes are the binary's.

class UnkType_10ddc930
{
public:
    virtual void VirtualSlot0();

    UnkType_10ddc930(int Value);
};

class UnkType_10de13d0 : public UnkType_10ddc930
{
public:
    UnkType_10de13d0();

    virtual void VirtualSlot0();
};

// UnkType_10de13d0::UnkType_10de13d0
UnkType_10de13d0::UnkType_10de13d0()
    : UnkType_10ddc930(1)
{
}
