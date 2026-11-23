// campaign_leaf_1355b0.cpp -- one function at file offset 0x1355b0, preferred VA 0x10a355b0.
// It returns 1 when the word at offset 0xee4 is set, the object at offset 0xea0 exists and has an
// object at offset 0x30 without bit 0x10 in its word at offset 0x398 and an object at offset 0x60
// whose virtual slot 56 returns false, and the count at offset 0xedc is at least 30; otherwise 0.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10a355b0_Owner
{
public:
    unsigned char unk_0[0x398];
    int unk_398;
};

class UnkType_10a355b0_Check
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
    virtual bool VirtualSlot56();
};

class UnkType_10a355b0_Target
{
public:
    unsigned char unk_0[0x30];
    UnkType_10a355b0_Owner* unk_30;
    unsigned char unk_34[0x60 - 0x34];
    UnkType_10a355b0_Check* unk_60;
};

class UnkType_10a355b0
{
public:
    unsigned char unk_0[0xea0];
    UnkType_10a355b0_Target* unk_ea0;
    unsigned char unk_ea4[0xedc - 0xea4];
    int unk_edc;
    unsigned char unk_ee0[0xee4 - 0xee0];
    int unk_ee4;

    int Unk_10a355b0();
};

// UnkType_10a355b0::Unk_10a355b0
int UnkType_10a355b0::Unk_10a355b0()
{
    if ( unk_ee4 && unk_ea0 && unk_ea0->unk_30 && !( unk_ea0->unk_30->unk_398 & 0x10 )
        && unk_ea0->unk_60 && !unk_ea0->unk_60->VirtualSlot56() && unk_edc >= 30 )
    {
        return 1;
    }
    return 0;
}
