// campaign_leaf_0ad8b0.cpp -- constructor at VA 0x109ad8b0: runs the base class constructor at VA
// 0x10cd7930, installs this class's vtable (VA 0x110ccd68) and constructs the member at 0x84 with
// the constructor at VA 0x10aa6d50. The class names are invented; the offsets and the addresses are
// the binary's.

class UnkType_109ad8b0_10cd7930
{
public:
    UnkType_109ad8b0_10cd7930();

    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x80];
};

class UnkType_109ad8b0_10aa6d50
{
public:
    UnkType_109ad8b0_10aa6d50();

private:
    int unk_00;
};

class UnkType_109ad8b0 : public UnkType_109ad8b0_10cd7930
{
public:
    UnkType_109ad8b0();

private:
    UnkType_109ad8b0_10aa6d50 unk_84;
};

// UnkType_109ad8b0::UnkType_109ad8b0
UnkType_109ad8b0::UnkType_109ad8b0()
{
}
