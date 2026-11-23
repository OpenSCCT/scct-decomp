// campaign_leaf_7709a0.cpp -- one function at file offset 0x7709a0, preferred VA 0x110709a0. A
// constructor: after the base constructor at VA 0x1105ee30 it installs the vtable at VA
// 0x11176f58, sets the word at 0x10 to 2 and clears the words at 0x20, 0x24, 0x30 to 0x3c, 0x44,
// 0x4c, 0x64, 0x74, 0xcc and 0xd0. For a count of at least 2 it then stores a changed count at
// 0x74 and passes 0 to the method at VA 0x11070190, and calls the method at VA 0x1106fa20. The
// class, method and member names are invented; the offsets and the addresses are the binary's.

class UnkType_110709a0_Base
{
public:
    UnkType_110709a0_Base();

    virtual void VirtualSlot0();

    int unk_4;
    int unk_8;
    int unk_c;
    int unk_10;
    unsigned char unk_14[0x20 - 0x14];
};

class UnkType_110709a0 : public UnkType_110709a0_Base
{
public:
    UnkType_110709a0(unsigned int Count);

    virtual void VirtualSlot0();

    void Unk_1106fa20();
    void Unk_11070190(int Value);

    int unk_20;
    int unk_24;
    unsigned char unk_28[0x30 - 0x28];
    int unk_30;
    int unk_34;
    int unk_38;
    int unk_3c;
    unsigned char unk_40[0x44 - 0x40];
    int unk_44;
    unsigned char unk_48[0x4c - 0x48];
    int unk_4c;
    unsigned char unk_50[0x64 - 0x50];
    int unk_64;
    unsigned char unk_68[0x74 - 0x68];
    unsigned int unk_74;
    unsigned char unk_78[0xcc - 0x78];
    int unk_cc;
    int unk_d0;
};

// UnkType_110709a0::UnkType_110709a0
UnkType_110709a0::UnkType_110709a0(unsigned int Count)
{
    unk_10 = 2;
    unk_24 = 0;
    unk_4c = 0;
    unk_44 = 0;
    unk_38 = 0;
    unk_34 = 0;
    unk_20 = 0;
    unk_30 = 0;
    unk_3c = 0;
    unk_cc = 0;
    unk_d0 = 0;
    unk_74 = 0;
    unk_64 = 0;
    if ( Count >= 2 )
    {
        if ( Count != unk_74 )
        {
            unk_74 = Count;
            Unk_11070190(0);
        }
        Unk_1106fa20();
    }
}
