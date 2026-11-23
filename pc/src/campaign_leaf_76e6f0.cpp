// campaign_leaf_76e6f0.cpp -- one function at file offset 0x76e6f0, preferred VA 0x1106e6f0. A
// constructor: it runs the base constructor at VA 0x1105ee30, zeroes six words between 0x24 and
// 0x44 and installs the vtable at VA 0x11176c90. The class names are invented; the offsets and the
// addresses are the binary's.

class UnkType_1106e6f0_Base
{
public:
    UnkType_1106e6f0_Base();
    virtual ~UnkType_1106e6f0_Base();

    unsigned char unk_4[0x24 - 0x4];
};

class UnkType_1106e6f0 : public UnkType_1106e6f0_Base
{
public:
    UnkType_1106e6f0();
    virtual ~UnkType_1106e6f0();

    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    unsigned char unk_38[0x44 - 0x38];
    int unk_44;
};

// UnkType_1106e6f0::UnkType_1106e6f0
UnkType_1106e6f0::UnkType_1106e6f0()
{
    unk_24 = 0;
    unk_34 = 0;
    unk_2c = 0;
    unk_44 = 0;
    unk_30 = 0;
    unk_28 = 0;
}
