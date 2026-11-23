// campaign_leaf_771710.cpp -- one function at file offset 0x771710, preferred VA 0x11071710. A
// constructor: it runs the base constructor at VA 0x1105ee30, zeroes the words at 0x20 to 0x38
// and installs the vtable at VA 0x11177180. The class names are invented; the offsets and the
// addresses are the binary's.

class UnkType_11071710_Base
{
public:
    UnkType_11071710_Base();
    virtual ~UnkType_11071710_Base();

    unsigned char unk_4[0x20 - 0x4];
};

class UnkType_11071710 : public UnkType_11071710_Base
{
public:
    UnkType_11071710();
    virtual ~UnkType_11071710();

    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    int unk_38;
};

// UnkType_11071710::UnkType_11071710
UnkType_11071710::UnkType_11071710()
{
    unk_20 = 0;
    unk_2c = 0;
    unk_30 = 0;
    unk_34 = 0;
    unk_38 = 0;
    unk_24 = 0;
    unk_28 = 0;
}
