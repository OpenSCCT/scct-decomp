// campaign_leaf_0c1b60.cpp -- constructor at VA 0x109c1b60: runs the base class constructor at VA
// 0x10aa79d0, installs this class's vtable (VA 0x110ce278) and zeroes the value at 0x2c. The class
// names are invented; the offsets and the addresses are the binary's.

class UnkType_109c1b60_10aa79d0
{
public:
    UnkType_109c1b60_10aa79d0();

    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x28];
};

class UnkType_109c1b60 : public UnkType_109c1b60_10aa79d0
{
public:
    UnkType_109c1b60();

private:
    int unk_2c;
};

// UnkType_109c1b60::UnkType_109c1b60
UnkType_109c1b60::UnkType_109c1b60()
{
    unk_2c = 0;
}
