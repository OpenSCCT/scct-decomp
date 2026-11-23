// campaign_leaf_768e60.cpp -- one function at file offset 0x768e60, preferred VA 0x11068e60. A
// constructor: after the base constructor at VA 0x1105ee30 it installs the vtable at VA
// 0x111768b0, sets the word at 0x6c to -1 and the word at 0x7c to 1, clears the other words from
// 0x20 to 0x78, and stores at 0x80 the result of the function at VA 0x11058700. The class and
// function names are invented; the offsets and the addresses are the binary's.

int Unk_11058700();

class UnkType_11068e60_Base
{
public:
    UnkType_11068e60_Base();

    virtual void VirtualSlot0();

    unsigned char unk_4[0x20 - 0x4];
};

class UnkType_11068e60 : public UnkType_11068e60_Base
{
public:
    UnkType_11068e60();

    virtual void VirtualSlot0();

    int unk_20;
    int unk_24;
    int unk_28;
    int unk_2c;
    int unk_30;
    int unk_34;
    unsigned char unk_38[0x48 - 0x38];
    int unk_48;
    int unk_4c;
    int unk_50;
    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
    unsigned char unk_64[0x68 - 0x64];
    int unk_68;
    int unk_6c;
    int unk_70;
    int unk_74;
    int unk_78;
    int unk_7c;
    int unk_80;
};

// UnkType_11068e60::UnkType_11068e60
UnkType_11068e60::UnkType_11068e60()
{
    unk_6c = -1;
    unk_24 = 0;
    unk_70 = 0;
    unk_48 = 0;
    unk_54 = 0;
    unk_4c = 0;
    unk_50 = 0;
    unk_5c = 0;
    unk_58 = 0;
    unk_28 = 0;
    unk_2c = 0;
    unk_30 = 0;
    unk_34 = 0;
    unk_60 = 0;
    unk_68 = 0;
    unk_74 = 0;
    unk_78 = 0;
    unk_7c = 1;
    unk_20 = 0;
    unk_80 = Unk_11058700();
}
