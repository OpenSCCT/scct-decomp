// campaign_leaf_7684f0.cpp -- one function at file offset 0x7684f0, preferred VA 0x110684f0. A
// constructor: it runs the base constructor at VA 0x1105ee30, zeroes the words at 0x24, 0x2c, 0x28
// and 0x8, installs the vtable at VA 0x111766d8 and stores the address of the function at VA
// 0x110684d0 at 0x20. The class names are invented; the offsets and the addresses are the
// binary's.

void Unk_110684d0(void* Object);

class UnkType_110684f0_Base
{
public:
    UnkType_110684f0_Base();
    virtual ~UnkType_110684f0_Base();

    int unk_4;
    int unk_8;
    unsigned char unk_c[0x20 - 0xc];
};

class UnkType_110684f0 : public UnkType_110684f0_Base
{
public:
    UnkType_110684f0();
    virtual ~UnkType_110684f0();

    void (*unk_20)(void* Object);
    int unk_24;
    int unk_28;
    int unk_2c;
};

// UnkType_110684f0::UnkType_110684f0
UnkType_110684f0::UnkType_110684f0()
{
    unk_24 = 0;
    unk_2c = 0;
    unk_28 = 0;
    unk_8 = 0;
    unk_20 = Unk_110684d0;
}
