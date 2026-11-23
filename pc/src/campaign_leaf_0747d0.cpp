// campaign_leaf_0747d0.cpp -- method at VA 0x109747d0: when the value at 0xf4 is set and bit 0 of
// the value at 0xf8 is clear, calls virtual slot 4 (vtable offset 0x10) of the object its argument
// points to with two scratch values and the addresses of 0xfc and 0x100, then its virtual slot 104
// (vtable offset 0x1a0) with this object, sets bit 0 of the value at 0xf8 and returns 1; otherwise
// returns 0. The class, member and method names are invented; the offsets, the bit and the slots
// are the binary's.

class UnkType_109747d0;

class UnkType_109747d0_Arg
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4(int* Out0, int* Out1, int* Out2, int* Out3);
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
    virtual void VirtualSlot63();
    virtual void VirtualSlot64();
    virtual void VirtualSlot65();
    virtual void VirtualSlot66();
    virtual void VirtualSlot67();
    virtual void VirtualSlot68();
    virtual void VirtualSlot69();
    virtual void VirtualSlot70();
    virtual void VirtualSlot71();
    virtual void VirtualSlot72();
    virtual void VirtualSlot73();
    virtual void VirtualSlot74();
    virtual void VirtualSlot75();
    virtual void VirtualSlot76();
    virtual void VirtualSlot77();
    virtual void VirtualSlot78();
    virtual void VirtualSlot79();
    virtual void VirtualSlot80();
    virtual void VirtualSlot81();
    virtual void VirtualSlot82();
    virtual void VirtualSlot83();
    virtual void VirtualSlot84();
    virtual void VirtualSlot85();
    virtual void VirtualSlot86();
    virtual void VirtualSlot87();
    virtual void VirtualSlot88();
    virtual void VirtualSlot89();
    virtual void VirtualSlot90();
    virtual void VirtualSlot91();
    virtual void VirtualSlot92();
    virtual void VirtualSlot93();
    virtual void VirtualSlot94();
    virtual void VirtualSlot95();
    virtual void VirtualSlot96();
    virtual void VirtualSlot97();
    virtual void VirtualSlot98();
    virtual void VirtualSlot99();
    virtual void VirtualSlot100();
    virtual void VirtualSlot101();
    virtual void VirtualSlot102();
    virtual void VirtualSlot103();
    virtual void VirtualSlot104(UnkType_109747d0* Object);
};

class UnkType_109747d0
{
public:
    int Unk_109747d0(UnkType_109747d0_Arg* Arg);

private:
    unsigned char unk_000[0xf4];
    int unk_0f4;
    unsigned int unk_0f8;
    int unk_0fc;
    int unk_100;
};

// UnkType_109747d0::Unk_109747d0
int UnkType_109747d0::Unk_109747d0(UnkType_109747d0_Arg* Arg)
{
    if ( !unk_0f4 || ( unk_0f8 & 1 ) )
    {
        return 0;
    }
    int Out0;
    int Out1;
    Arg->VirtualSlot4(&Out0, &Out1, &unk_0fc, &unk_100);
    Arg->VirtualSlot104(this);
    unk_0f8 |= 1;
    return 1;
}
