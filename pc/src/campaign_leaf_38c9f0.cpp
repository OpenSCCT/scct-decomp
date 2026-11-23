// campaign_leaf_38c9f0.cpp -- one function at file offset 0x38c9f0, preferred VA 0x10c8c9f0. It
// decrements the word at 0x10; when the interface at 0x24 is set it passes the address of the
// slot at 0x2c to the method at 0x10c89740 of the object at 0x4; it then releases the interfaces
// at 0x24, 0x28, 0x30, 0x2c and 0x34 that are set through stdcall virtual slot 2 and clears their
// slots. The class, method and member names are invented; the offsets, the slot and the bytes
// are the binary's.

class UnkType_10c8c9f0_Interface
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual unsigned long __stdcall VirtualSlot2();
};

class UnkType_10c8c9f0_Device
{
public:
    void Unk_10c89740(UnkType_10c8c9f0_Interface** Slot);
};

class UnkType_10c8c9f0
{
public:
    void Unk_10c8c9f0();

    unsigned char unk_0[0x4];
    UnkType_10c8c9f0_Device* unk_4;
    unsigned char unk_8[0x8];
    int unk_10;
    unsigned char unk_14[0x10];
    UnkType_10c8c9f0_Interface* unk_24;
    UnkType_10c8c9f0_Interface* unk_28;
    UnkType_10c8c9f0_Interface* unk_2c;
    UnkType_10c8c9f0_Interface* unk_30;
    UnkType_10c8c9f0_Interface* unk_34;
};

// UnkType_10c8c9f0::Unk_10c8c9f0
void UnkType_10c8c9f0::Unk_10c8c9f0()
{
    unk_10--;
    if ( unk_24 != 0 )
    {
        unk_4->Unk_10c89740(&unk_2c);
    }
    if ( unk_24 != 0 )
    {
        unk_24->VirtualSlot2();
    }
    if ( unk_28 != 0 )
    {
        unk_28->VirtualSlot2();
    }
    unk_24 = 0;
    unk_28 = 0;
    if ( unk_30 != 0 )
    {
        unk_30->VirtualSlot2();
        unk_30 = 0;
    }
    if ( unk_2c != 0 )
    {
        unk_2c->VirtualSlot2();
        unk_2c = 0;
    }
    if ( unk_34 != 0 )
    {
        unk_34->VirtualSlot2();
    }
    unk_34 = 0;
}
