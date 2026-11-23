// campaign_leaf_75f360.cpp -- one function at file offset 0x75f360, preferred VA 0x1105f360. A
// constructor: it runs the base constructor at VA 0x11060a10, zeroes the words at 0x58, 0x5c, 0x54
// and 0x60 and installs the vtable at VA 0x11175b2c. The class names are invented; the offsets and
// the addresses are the binary's.

class UnkType_1105f360_Base
{
public:
    UnkType_1105f360_Base();
    virtual ~UnkType_1105f360_Base();

    unsigned char unk_4[0x54 - 0x4];
};

class UnkType_1105f360 : public UnkType_1105f360_Base
{
public:
    UnkType_1105f360();
    virtual ~UnkType_1105f360();

    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
};

// UnkType_1105f360::UnkType_1105f360
UnkType_1105f360::UnkType_1105f360()
{
    unk_58 = 0;
    unk_5c = 0;
    unk_54 = 0;
    unk_60 = 0;
}
