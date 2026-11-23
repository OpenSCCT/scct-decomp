// campaign_leaf_7685a0.cpp -- one function at file offset 0x7685a0, preferred VA 0x110685a0. A
// constructor: it runs the base constructor at VA 0x1105ee30, zeroes the words at 0x24, 0x2c and
// 0x28, installs the vtable at VA 0x11176730 and stores the address of the function at VA
// 0x11068580 at 0x20. The class names are invented; the offsets and the addresses are the
// binary's.

void Unk_11068580(void* Object);

class UnkType_110685a0_Base
{
public:
    UnkType_110685a0_Base();
    virtual ~UnkType_110685a0_Base();

    unsigned char unk_4[0x20 - 0x4];
};

class UnkType_110685a0 : public UnkType_110685a0_Base
{
public:
    UnkType_110685a0();
    virtual ~UnkType_110685a0();

    void (*unk_20)(void* Object);
    int unk_24;
    int unk_28;
    int unk_2c;
};

// UnkType_110685a0::UnkType_110685a0
UnkType_110685a0::UnkType_110685a0()
{
    unk_24 = 0;
    unk_2c = 0;
    unk_28 = 0;
    unk_20 = Unk_11068580;
}
