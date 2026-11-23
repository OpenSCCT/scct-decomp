// campaign_leaf_01ca00.cpp -- constructor at VA 0x1091ca00 of a class whose vtable is at VA
// 0x110ba9c0: runs the inline constructor of its base class, which runs the base constructor at VA
// 0x1091c7c0 and clears the values at 0xf4-0x100. The class and member names are invented; the
// offsets and the addresses are the binary's.

class UnkType_1091ca00_Base
{
public:
    UnkType_1091ca00_Base();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0xf0];
};

class UnkType_1091c7c0_01ca00 : public UnkType_1091ca00_Base
{
public:
    UnkType_1091c7c0_01ca00()
    : unk_f4(0)
    , unk_f8(0)
    , unk_fc(0)
    , unk_100(0)
    {
    }

    virtual void VirtualSlot0();

private:
    int unk_f4;
    int unk_f8;
    int unk_fc;
    int unk_100;
};

class UnkType_1091ca00 : public UnkType_1091c7c0_01ca00
{
public:
    UnkType_1091ca00();
    virtual void VirtualSlot0();
};

// UnkType_1091ca00::UnkType_1091ca00
UnkType_1091ca00::UnkType_1091ca00()
{
}
