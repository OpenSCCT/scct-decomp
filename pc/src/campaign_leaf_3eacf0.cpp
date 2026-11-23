// campaign_leaf_3eacf0.cpp -- one function at file offset 0x3eacf0, preferred VA 0x10ceacf0. It
// passes the object at 0x54 to virtual slot 4 of Ar, copies that object's 16-bit size at 0x4c to
// 0x36, sets the 16-bit word at 0x44 to the result of virtual slot 22 of the object at 0x18
// rounded up to the size's alignment (2 for a size of 2, 1 below 4, otherwise 4), and, when the
// word at 0x68 of the object at 0x54 is set and bit 10 of the word at 0x38 is clear, sets bit 17
// of it. It never reads Previous. The class, method, member, local and parameter names are
// invented; the offsets, the constants, the slots and the bytes are the binary's.

class UnkType_10ceacf0_Inner
{
public:
    unsigned char unk_0[0x4c];
    unsigned short unk_4c;
    unsigned char unk_4e[0x1a];
    int unk_68;
};

class UnkType_10ceacf0_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(UnkType_10ceacf0_Inner* Object);
};

class UnkType_10ceacf0_Outer
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

class UnkType_10ceacf0
{
public:
    void Unk_10ceacf0(UnkType_10ceacf0_Archive& Ar, UnkType_10ceacf0_Inner* Previous);

    unsigned char unk_0[0x18];
    UnkType_10ceacf0_Outer* unk_18;
    unsigned char unk_1c[0x1a];
    unsigned short unk_36;
    unsigned int unk_38;
    unsigned char unk_3c[0x8];
    unsigned short unk_44;
    unsigned char unk_46[0xe];
    UnkType_10ceacf0_Inner* unk_54;
};

// UnkType_10ceacf0::Unk_10ceacf0
void UnkType_10ceacf0::Unk_10ceacf0(UnkType_10ceacf0_Archive& Ar,
                                    UnkType_10ceacf0_Inner* Previous)
{
    int Alignment;

    Ar.VirtualSlot4(unk_54);
    unk_36 = unk_54->unk_4c;
    Alignment = unk_36 == 2 ? 2 : unk_36 < 4 ? 1 : 4;
    unk_44 = (unk_18->VirtualSlot22() + Alignment - 1) & ~(Alignment - 1);
    if ( unk_54->unk_68 != 0 && !(unk_38 & 0x400) )
    {
        unk_38 |= 0x20000;
    }
}
