// campaign_leaf_3e9760.cpp -- one function at file offset 0x3e9760, preferred VA 0x10ce9760. For
// each of the word at 0x58 elements it passes the element of First and the element of Second (or
// null when Second is null), each the 16-bit size at 0x36 of the object at 0x54 apart, to virtual
// slot 30 of that object, and returns 0 at the first that fails; otherwise it returns 1. The
// class, method, member, local and parameter names are invented; the offsets, the slot and the
// bytes are the binary's.

class UnkType_10ce9760_Inner
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
    virtual int VirtualSlot30(unsigned char* First, unsigned char* Second);

    unsigned char unk_4[0x32];
    unsigned short unk_36;
};

class UnkType_10ce9760
{
public:
    int Unk_10ce9760(unsigned char* First, unsigned char* Second);

    unsigned char unk_0[0x54];
    UnkType_10ce9760_Inner* unk_54;
    int unk_58;
};

// UnkType_10ce9760::Unk_10ce9760
int UnkType_10ce9760::Unk_10ce9760(unsigned char* First, unsigned char* Second)
{
    int Index;

    for ( Index = 0; Index < unk_58; Index++ )
    {
        if ( !unk_54->VirtualSlot30(First + Index * unk_54->unk_36,
                                    Second ? Second + Index * unk_54->unk_36 : 0) )
        {
            return 0;
        }
    }
    return 1;
}
