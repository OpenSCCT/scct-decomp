// campaign_leaf_06be00.cpp -- constructor at VA 0x1096be00 of a class whose vtable is at VA
// 0x110c06c0: runs the inline constructor of its base class, which runs the base constructor at
// VA 0x10cd7930, clears the value at 0x64 and sets the one at 0x68 to -1. The class and member
// names are invented; the offsets, the constants and the addresses are the binary's.

class UnkType_1096be00_Base
{
public:
    UnkType_1096be00_Base();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x60];
};

class UnkType_110bf470 : public UnkType_1096be00_Base
{
public:
    UnkType_110bf470()
    : unk_64(0)
    , unk_68(-1)
    {
    }

    virtual void VirtualSlot0();

private:
    int unk_64;
    int unk_68;
};

class UnkType_1096be00 : public UnkType_110bf470
{
public:
    UnkType_1096be00();
    virtual void VirtualSlot0();
};

// UnkType_1096be00::UnkType_1096be00
UnkType_1096be00::UnkType_1096be00()
{
}
