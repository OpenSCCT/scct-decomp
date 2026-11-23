// campaign_leaf_76f520.cpp -- one function at file offset 0x76f520, preferred VA 0x1106f520. A
// constructor: it runs the base constructor at VA 0x11064ff0, zeroes the words at 0x24 and 0x40,
// installs the vtable at VA 0x11176e40 and stores the address of the function at VA 0x1106f500
// at 0x20. The class names are invented; the offsets and the addresses are the binary's.

void Unk_1106f500(void* Object);

class UnkType_1106f520_Base
{
public:
    UnkType_1106f520_Base();
    virtual ~UnkType_1106f520_Base();

    unsigned char unk_4[0x20 - 0x4];
    void (*unk_20)(void* Object);
};

class UnkType_1106f520 : public UnkType_1106f520_Base
{
public:
    UnkType_1106f520();
    virtual ~UnkType_1106f520();

    int unk_24;
    unsigned char unk_28[0x40 - 0x28];
    int unk_40;
};

// UnkType_1106f520::UnkType_1106f520
UnkType_1106f520::UnkType_1106f520()
{
    unk_24 = 0;
    unk_40 = 0;
    unk_20 = Unk_1106f500;
}
