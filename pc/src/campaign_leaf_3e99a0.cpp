// campaign_leaf_3e99a0.cpp -- one function at file offset 0x3e99a0, preferred VA 0x10ce99a0. For
// each of the word at 0x58 items it calls virtual slot 39 of the object at 0x54 with the item's
// place in First and, when Second is set, in Second (stride: that object's halfword at 0x36), and
// 0. Its third argument is unused. The class, method, member and parameter names are invented;
// the offsets, the slot and the bytes are the binary's.

class UnkType_10ce99a0_Device
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
    virtual void VirtualSlot7();
    virtual void VirtualSlot8();
    virtual void VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual void VirtualSlot12();
    virtual void VirtualSlot13();
    virtual void VirtualSlot14();
    virtual void VirtualSlot15();
    virtual void VirtualSlot16();
    virtual void VirtualSlot17();
    virtual void VirtualSlot18();
    virtual void VirtualSlot19();
    virtual void VirtualSlot20();
    virtual void VirtualSlot21();
    virtual void VirtualSlot22();
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual void VirtualSlot25();
    virtual void VirtualSlot26();
    virtual void VirtualSlot27();
    virtual void VirtualSlot28();
    virtual void VirtualSlot29();
    virtual void VirtualSlot30();
    virtual void VirtualSlot31();
    virtual void VirtualSlot32();
    virtual void VirtualSlot33();
    virtual void VirtualSlot34();
    virtual void VirtualSlot35();
    virtual void VirtualSlot36();
    virtual void VirtualSlot37();
    virtual void VirtualSlot38();
    virtual void VirtualSlot39(unsigned char* First, unsigned char* Second, int Flags);

    unsigned char unk_4[0x32];
    unsigned short unk_36;
};

class UnkType_10ce99a0
{
public:
    void Unk_10ce99a0(unsigned char* First, unsigned char* Second, int Unused);

    unsigned char unk_0[0x54];
    UnkType_10ce99a0_Device* unk_54;
    int unk_58;
};

// UnkType_10ce99a0::Unk_10ce99a0
void UnkType_10ce99a0::Unk_10ce99a0(unsigned char* First, unsigned char* Second, int Unused)
{
    int Index;

    for ( Index = 0; Index < unk_58; Index++ )
    {
        unk_54->VirtualSlot39(First + unk_54->unk_36 * Index,
                              Second ? Second + unk_54->unk_36 * Index : 0, 0);
    }
}
