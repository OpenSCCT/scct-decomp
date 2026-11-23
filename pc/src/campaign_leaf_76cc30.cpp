// campaign_leaf_76cc30.cpp -- one function at file offset 0x76cc30, preferred VA 0x1106cc30. A
// constructor: it runs the base constructor at VA 0x1105ee30, zeroes the words at 0x20 to 0x30
// and installs the vtable at VA 0x11176b50. The class names are invented; the offsets and the
// addresses are the binary's.

class UnkType_1106cc30_Base
{
public:
    UnkType_1106cc30_Base();
    virtual ~UnkType_1106cc30_Base();

    unsigned char unk_4[0x20 - 0x4];
};

class UnkType_1106cc30 : public UnkType_1106cc30_Base
{
public:
    UnkType_1106cc30();
    virtual ~UnkType_1106cc30();

    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
};

// UnkType_1106cc30::UnkType_1106cc30
UnkType_1106cc30::UnkType_1106cc30()
{
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = 0;
    unk_2c = 0;
    unk_30 = 0;
}
