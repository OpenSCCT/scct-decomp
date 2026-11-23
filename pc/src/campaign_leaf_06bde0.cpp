// campaign_leaf_06bde0.cpp -- constructor at VA 0x1096bde0 of a class whose vtable is at VA
// 0x110bf470: runs the base constructor at VA 0x10cd7930, clears the value at 0x64 and sets the
// one at 0x68 to -1. The class and member names are invented; the offsets, the constants and the
// addresses are the binary's.

class UnkType_1096bde0_Base
{
public:
    UnkType_1096bde0_Base();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x60];
};

class UnkType_1096bde0 : public UnkType_1096bde0_Base
{
public:
    UnkType_1096bde0();
    virtual void VirtualSlot0();

private:
    int unk_64;
    int unk_68;
};

// UnkType_1096bde0::UnkType_1096bde0
UnkType_1096bde0::UnkType_1096bde0()
: unk_64(0)
, unk_68(-1)
{
}
