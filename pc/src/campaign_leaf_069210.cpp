// campaign_leaf_069210.cpp -- constructor at VA 0x10969210: runs the base class constructor at VA
// 0x10cd7930, installs this class's vtable (VA 0x110befd0) and constructs the 12-byte member at
// 0x2c, whose inline constructor zeroes its three values. The class names are invented; the offsets
// and the addresses are the binary's.

class UnkType_1090ba70_069210
{
public:
    UnkType_1090ba70_069210()
    : unk_00(0)
    , unk_04(0)
    , unk_08(0)
    {
    }

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10969210_10cd7930
{
public:
    UnkType_10969210_10cd7930();

    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x28];
};

class UnkType_10969210 : public UnkType_10969210_10cd7930
{
public:
    UnkType_10969210();

private:
    UnkType_1090ba70_069210 unk_2c;
};

// UnkType_10969210::UnkType_10969210
UnkType_10969210::UnkType_10969210()
{
}
