// campaign_leaf_771110.cpp -- one function at file offset 0x771110, preferred VA 0x11071110. A
// constructor: it runs the base constructor at VA 0x1105ee30, zeroes the words at 0x20 to 0x2c
// and installs the vtable at VA 0x11177138. The class names are invented; the offsets and the
// addresses are the binary's.

class UnkType_11071110_Base
{
public:
    UnkType_11071110_Base();
    virtual ~UnkType_11071110_Base();

    unsigned char unk_4[0x20 - 0x4];
};

class UnkType_11071110 : public UnkType_11071110_Base
{
public:
    UnkType_11071110();
    virtual ~UnkType_11071110();

    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
};

// UnkType_11071110::UnkType_11071110
UnkType_11071110::UnkType_11071110()
{
    unk_20 = 0;
    unk_24 = 0;
    unk_28 = 0;
    unk_2c = 0;
}
