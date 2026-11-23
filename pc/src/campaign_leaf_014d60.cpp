// campaign_leaf_014d60.cpp -- method at VA 0x10914d60: calls virtual slot 12 (vtable offset 0x30)
// with 0 on the object at 0xc8 and clears the pointer; when its argument is set and the method at
// VA 0x10d09f20 of the member at 0x40 returns a positive count, stores at 0xc8 what virtual slot 63
// (vtable offset 0xfc) returns for the result of that member's method at VA 0x10d09d00; finally
// calls virtual slot 11 (vtable offset 0x2c) of the object at 0xc8, if any. The class, member and
// method names are invented; the offsets, the slots and the addresses are the binary's.

class UnkType_10914d60_c8
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
    virtual void VirtualSlot12(int Value);
};

class UnkType_10914d60_40
{
public:
    int Unk_10d09f20();
    int Unk_10d09d00();
};

class UnkType_10914d60
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
    virtual void VirtualSlot62();
    virtual UnkType_10914d60_c8* VirtualSlot63(int Value);

    void Unk_10914d60(int Flag);

private:
    unsigned char unk_04[0x3c];
    UnkType_10914d60_40 unk_40;
    unsigned char unk_41[0xc8 - 0x41];
    UnkType_10914d60_c8* unk_c8;
};

// UnkType_10914d60::Unk_10914d60
void UnkType_10914d60::Unk_10914d60(int Flag)
{
    if ( unk_c8 )
    {
        unk_c8->VirtualSlot12(0);
    }
    unk_c8 = 0;
    if ( Flag && unk_40.Unk_10d09f20() > 0 )
    {
        unk_c8 = VirtualSlot63(unk_40.Unk_10d09d00());
    }
    if ( unk_c8 )
    {
        unk_c8->VirtualSlot11();
    }
}
