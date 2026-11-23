// campaign_leaf_3ed7c0.cpp -- one function at file offset 0x3ed7c0, preferred VA 0x10ced7c0. It
// asks the function at 0x1091acb0 for the object behind Previous; when virtual slot 25 of the
// object at 0x18 succeeds and that object has any of bits 0 to 30 set in its word at 0x54, it
// copies Previous's 16-bit word at 0x44 and doubles the found word into 0x54; otherwise it sets
// the 16-bit word at 0x44 to the result of virtual slot 22 of the object at 0x18 rounded up to a
// multiple of 4 and the word at 0x54 to 1. Either way the 16-bit size at 0x36 becomes 4. It
// never reads Ar. The class, function, member, local and parameter names are invented; the
// offsets, the constants, the slots and the bytes are the binary's.

class UnkType_10ced7c0_Found
{
public:
    unsigned char unk_0[0x54];
    unsigned int unk_54;
};

class UnkType_10ced7c0_Outer
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
    virtual void VirtualSlot23();
    virtual void VirtualSlot24();
    virtual int VirtualSlot25();
};

class UnkType_10ced7c0
{
public:
    void Unk_10ced7c0(void* Ar, UnkType_10ced7c0* Previous);

    unsigned char unk_0[0x18];
    UnkType_10ced7c0_Outer* unk_18;
    unsigned char unk_1c[0x1a];
    unsigned short unk_36;
    unsigned char unk_38[0xc];
    unsigned short unk_44;
    unsigned char unk_46[0xe];
    unsigned int unk_54;
};

UnkType_10ced7c0_Found* Unk_1091acb0(UnkType_10ced7c0* Object);

// UnkType_10ced7c0::Unk_10ced7c0
void UnkType_10ced7c0::Unk_10ced7c0(void* Ar, UnkType_10ced7c0* Previous)
{
    UnkType_10ced7c0_Found* Found = Unk_1091acb0(Previous);

    if ( unk_18->VirtualSlot25() && Found != 0 && (Found->unk_54 & 0x7fffffff) )
    {
        unk_44 = Previous->unk_44;
        unk_54 = Found->unk_54 << 1;
        unk_36 = 4;
    }
    else
    {
        unk_44 = (unk_18->VirtualSlot22() + 3) & ~3;
        unk_54 = 1;
        unk_36 = 4;
    }
}
