// campaign_leaf_3eac50.cpp -- one function at file offset 0x3eac50, preferred VA 0x10ceac50. For
// each of the objects at 0x54 and 0x58 it passes the object to virtual slot 4 of Ar and Ar with
// null to virtual slot 29 of the object; it then sets the 16-bit size at 0x36 to 20, sets the
// 16-bit word at 0x44 to the result of virtual slot 22 of the object at 0x18 rounded up to a
// multiple of 4, and, unless bit 10 of the word at 0x38 is set, sets bit 17 of it. It never reads
// Previous. The class, method, member and parameter names are invented; the offsets, the
// constants, the slots and the bytes are the binary's.

class UnkType_10ceac50_Archive;

class UnkType_10ceac50_Inner
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
    virtual void VirtualSlot29(UnkType_10ceac50_Archive& Ar, UnkType_10ceac50_Inner* Previous);
};

class UnkType_10ceac50_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(UnkType_10ceac50_Inner* Object);
};

class UnkType_10ceac50_Outer
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
    virtual int VirtualSlot22();
};

class UnkType_10ceac50
{
public:
    void Unk_10ceac50(UnkType_10ceac50_Archive& Ar, UnkType_10ceac50_Inner* Previous);

    unsigned char unk_0[0x18];
    UnkType_10ceac50_Outer* unk_18;
    unsigned char unk_1c[0x1a];
    unsigned short unk_36;
    unsigned int unk_38;
    unsigned char unk_3c[0x8];
    unsigned short unk_44;
    unsigned char unk_46[0xe];
    UnkType_10ceac50_Inner* unk_54;
    UnkType_10ceac50_Inner* unk_58;
};

// UnkType_10ceac50::Unk_10ceac50
void UnkType_10ceac50::Unk_10ceac50(UnkType_10ceac50_Archive& Ar,
                                    UnkType_10ceac50_Inner* Previous)
{
    Ar.VirtualSlot4(unk_54);
    unk_54->VirtualSlot29(Ar, 0);
    Ar.VirtualSlot4(unk_58);
    unk_58->VirtualSlot29(Ar, 0);
    unk_36 = 20;
    unk_44 = (unk_18->VirtualSlot22() + 3) & ~3;
    if ( !(unk_38 & 0x400) )
    {
        unk_38 |= 0x20000;
    }
}
