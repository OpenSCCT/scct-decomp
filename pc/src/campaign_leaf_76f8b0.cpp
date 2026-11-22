// campaign_leaf_76f8b0.cpp -- one function at file offset 0x76f8b0, preferred VA 0x1106f8b0. A
// constructor: it runs the base constructor at VA 0x1105ee30, installs the vtable at VA
// 0x11176f10 and zeroes the word at 0x20. The class names are invented; the offset and the
// addresses are the binary's.

class UnkType_1105ee30
{
public:
    UnkType_1105ee30();
    virtual ~UnkType_1105ee30();
};

class UnkType_1106f8b0 : public UnkType_1105ee30
{
public:
    UnkType_1106f8b0();
    virtual ~UnkType_1106f8b0();

    unsigned char unk_4[0x20 - 0x4];
    int unk_20;
};

// UnkType_1106f8b0::UnkType_1106f8b0
UnkType_1106f8b0::UnkType_1106f8b0()
{
    unk_20 = 0;
}
