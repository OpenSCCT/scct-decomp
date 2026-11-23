// campaign_leaf_7637c0.cpp -- one function at file offset 0x7637c0, preferred VA 0x110637c0. When
// the handle at 0xa4 is -1 it stores there the result of the method at VA 0x1106d940 of the
// object at 0x78 on the word at 0x68 and its argument; when the word at 0x44 is set and the
// handle at 0xa8 is -1 it stores there the result of the first virtual method of the object at
// 0x84 on the word at 0x6c. It returns 0 when either result is -1 and 1 otherwise. The class,
// method and member names are invented; the offsets and the addresses are the binary's.

class UnkType_110637c0_Opener
{
public:
    int Unk_1106d940(int Context, int Value);
};

class UnkType_110637c0_Source
{
public:
    virtual int VirtualSlot0(int Context);
};

class UnkType_110637c0
{
public:
    int Unk_110637c0(int Value);

    unsigned char unk_0[0x44];
    int unk_44;
    unsigned char unk_48[0x68 - 0x48];
    int unk_68;
    int unk_6c;
    unsigned char unk_70[0x78 - 0x70];
    UnkType_110637c0_Opener* unk_78;
    unsigned char unk_7c[0x84 - 0x7c];
    UnkType_110637c0_Source* unk_84;
    unsigned char unk_88[0xa4 - 0x88];
    int unk_a4;
    int unk_a8;
};

// UnkType_110637c0::Unk_110637c0
int UnkType_110637c0::Unk_110637c0(int Value)
{
    if ( unk_a4 == -1 )
    {
        unk_a4 = unk_78->Unk_1106d940(unk_68, Value);
        if ( unk_a4 == -1 )
        {
            return 0;
        }
    }
    if ( unk_44 != 0 && unk_a8 == -1 )
    {
        unk_a8 = unk_84->VirtualSlot0(unk_6c);
        if ( unk_a8 == -1 )
        {
            return 0;
        }
    }
    return 1;
}
