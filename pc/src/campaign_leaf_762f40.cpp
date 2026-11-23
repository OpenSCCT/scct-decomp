// campaign_leaf_762f40.cpp -- one function at file offset 0x762f40, preferred VA 0x11062f40. A
// constructor: it runs the base constructor at VA 0x110679f0, zeroes the words at 0x44, 0x4 and
// 0x60 and installs the vtable at VA 0x11176338. The class names are invented; the offsets and the
// addresses are the binary's.

class UnkType_11062f40_Base
{
public:
    UnkType_11062f40_Base();
    virtual ~UnkType_11062f40_Base();

    int unk_4;
    unsigned char unk_8[0x1c - 0x8];
    int unk_1c;
};

class UnkType_11062f40 : public UnkType_11062f40_Base
{
public:
    UnkType_11062f40();
    virtual ~UnkType_11062f40();

    unsigned char unk_20[0x44 - 0x20];
    int unk_44;
    unsigned char unk_48[0x60 - 0x48];
    int unk_60;
};

// UnkType_11062f40::UnkType_11062f40
UnkType_11062f40::UnkType_11062f40()
{
    unk_44 = 0;
    unk_4 = 0;
    unk_60 = 0;
}
