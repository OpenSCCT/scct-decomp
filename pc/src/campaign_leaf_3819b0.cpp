// campaign_leaf_3819b0.cpp -- one function at file offset 0x3819b0, preferred VA 0x10c819b0. It
// clears the words at 0x56d0, 0x5688, 0x56d8, 0x40ac and 0x40b0, deletes the object at 0xa8 for
// as long as one is there, copies the word at 0x40b4 to 0x58 and calls virtual slot 61. It never
// reads Unused. The class, method, member and parameter names are invented; the offsets, the
// slot and the bytes are the binary's.

class UnkType_10c819b0_Child
{
public:
    virtual ~UnkType_10c819b0_Child();
};

class UnkType_10c819b0
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
    virtual void VirtualSlot39();
    virtual void VirtualSlot40();
    virtual void VirtualSlot41();
    virtual void VirtualSlot42();
    virtual void VirtualSlot43();
    virtual void VirtualSlot44();
    virtual void VirtualSlot45();
    virtual void VirtualSlot46();
    virtual void VirtualSlot47();
    virtual void VirtualSlot48();
    virtual void VirtualSlot49();
    virtual void VirtualSlot50();
    virtual void VirtualSlot51();
    virtual void VirtualSlot52();
    virtual void VirtualSlot53();
    virtual void VirtualSlot54();
    virtual void VirtualSlot55();
    virtual void VirtualSlot56();
    virtual void VirtualSlot57();
    virtual void VirtualSlot58();
    virtual void VirtualSlot59();
    virtual void VirtualSlot60();
    virtual void VirtualSlot61();
    void Unk_10c819b0(int Unused);

    unsigned char unk_4[0x54];
    int unk_58;
    unsigned char unk_5c[0x4c];
    UnkType_10c819b0_Child* unk_a8;
    unsigned char unk_ac[0x4000];
    int unk_40ac;
    int unk_40b0;
    int unk_40b4;
    unsigned char unk_40b8[0x15d0];
    int unk_5688;
    unsigned char unk_568c[0x44];
    int unk_56d0;
    int unk_56d4;
    int unk_56d8;
};

// UnkType_10c819b0::Unk_10c819b0
void UnkType_10c819b0::Unk_10c819b0(int Unused)
{
    unk_56d0 = 0;
    unk_5688 = 0;
    unk_56d8 = 0;
    unk_40ac = 0;
    unk_40b0 = 0;
    while ( unk_a8 != 0 )
    {
        delete unk_a8;
    }
    unk_58 = unk_40b4;
    VirtualSlot61();
}
