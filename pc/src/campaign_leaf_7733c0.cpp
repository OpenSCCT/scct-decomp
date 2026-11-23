// campaign_leaf_7733c0.cpp -- one function at file offset 0x7733c0, preferred VA 0x110733c0. A
// constructor: it runs the base constructor at VA 0x1106eb00, zeroes the words at 0x4c, 0x50 and
// 0x54 and installs the vtable at VA 0x11177210. The class names are invented; the offsets and the
// addresses are the binary's.

class UnkType_110733c0_Base
{
public:
    UnkType_110733c0_Base();
    virtual ~UnkType_110733c0_Base();

    unsigned char unk_4[0x4c - 0x4];
};

class UnkType_110733c0 : public UnkType_110733c0_Base
{
public:
    UnkType_110733c0();
    virtual ~UnkType_110733c0();

    int unk_4c;
    int unk_50;
    int unk_54;
};

// UnkType_110733c0::UnkType_110733c0
UnkType_110733c0::UnkType_110733c0()
{
    unk_4c = 0;
    unk_50 = 0;
    unk_54 = 0;
}
