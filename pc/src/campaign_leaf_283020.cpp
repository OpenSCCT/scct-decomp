// campaign_leaf_283020.cpp -- method at VA 0x10b83020 taking three values, of which it reads the
// third: returns 1 when bit 25 of the word at 0x748 is clear, the word at 0x6ec and the object at
// 0x184 are set, that object's method at VA 0x10907890 accepts what the method at VA 0x10906db0
// returns, the function at VA 0x109353f0 finds something for what the object's virtual slot 33
// (vtable offset 0x84) returns for this one, and either the third value is set or the found
// object's virtual slot 60 (vtable offset 0xf0) rejects 0; otherwise returns 0. The class, member
// and method names are invented; the offsets, the slots and the addresses are the binary's.

class UnkType_10b83020;

class UnkType_10b83020_Found
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
    virtual int VirtualSlot60(int Value);
};

UnkType_10b83020_Found* Unk_109353f0(int Key);

class UnkType_10b83020_184
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
    virtual int VirtualSlot33(UnkType_10b83020* Owner);

    int Unk_10907890(int Value);
};

class UnkType_10b83020
{
public:
    int Unk_10b83020(int First, int Second, int Third);
    int Unk_10906db0();

private:
    unsigned char unk_00[0x184];
    UnkType_10b83020_184* unk_184;
    unsigned char unk_188[0x6ec - 0x188];
    int unk_6ec;
    unsigned char unk_6f0[0x748 - 0x6f0];
    int unk_748;
};

// UnkType_10b83020::Unk_10b83020
int UnkType_10b83020::Unk_10b83020(int First, int Second, int Third)
{
    if ( !( unk_748 & 0x2000000 ) && unk_6ec && unk_184
        && unk_184->Unk_10907890(Unk_10906db0()) )
    {
        UnkType_10b83020_Found* Found = Unk_109353f0(unk_184->VirtualSlot33(this));
        if ( Found && ( Third || !Found->VirtualSlot60(0) ) )
        {
            return 1;
        }
    }
    return 0;
}
