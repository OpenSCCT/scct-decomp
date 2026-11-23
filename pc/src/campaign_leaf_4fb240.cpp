// campaign_leaf_4fb240.cpp -- method at VA 0x10dfb240: releases the handle at 0x10 through virtual
// slot 3 of the object at 0x0c (after the method at VA 0x10dfae70 when the method at VA 0x10dfac70
// says so), opens a new one with its argument through slot 1, clears 0x230 and 0x234 on success and
// returns whether it succeeded. The class, method and member names are invented; the offsets, slots
// and addresses are the binary's.

class UnkType_10dfb240_Device
{
public:
    virtual void VirtualSlot0();
    virtual int VirtualSlot1(int Arg);
    virtual void VirtualSlot2();
    virtual void VirtualSlot3(int Handle);
};

class UnkType_10dfb240
{
public:
    bool Unk_10dfb240(int Arg);
    bool Unk_10dfac70();
    void Unk_10dfae70();

    unsigned char unk_00[0x0c];
    UnkType_10dfb240_Device* unk_0c;
    int unk_10;
    unsigned char unk_14[0x21c];
    int unk_230;
    int unk_234;
};

// UnkType_10dfb240::Unk_10dfb240
bool UnkType_10dfb240::Unk_10dfb240(int Arg)
{
    if ( unk_10 )
    {
        if ( Unk_10dfac70() )
        {
            Unk_10dfae70();
        }
        unk_0c->VirtualSlot3(unk_10);
        unk_10 = 0;
    }
    unk_10 = unk_0c->VirtualSlot1(Arg);
    if ( unk_10 )
    {
        unk_230 = 0;
        unk_234 = 0;
    }
    return unk_10 != 0;
}
