// campaign_leaf_4efad0.cpp -- one function at file offset 0x4efad0, preferred VA 0x10defad0.
// The constructor runs the base constructor at 0x10def9d0 with 8 and 0x40 and installs the vtable
// at 0x11148924. The class names are invented; the offset and the bytes are the binary's.

class UnkType_10defad0_Base
{
public:
    UnkType_10defad0_Base(int Count, int Size);

    virtual void VirtualSlot0();
};

class UnkType_10defad0 : public UnkType_10defad0_Base
{
public:
    UnkType_10defad0();

    virtual void VirtualSlot0();
};

// UnkType_10defad0::UnkType_10defad0
UnkType_10defad0::UnkType_10defad0()
    : UnkType_10defad0_Base(8, 0x40)
{
}
