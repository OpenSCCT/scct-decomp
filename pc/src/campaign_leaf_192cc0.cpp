// campaign_leaf_192cc0.cpp -- one function at file offset 0x192cc0, preferred VA 0x10a92cc0.
// guess: passes its argument on by the mode byte at offset 0x4c (mode 2 to virtual slot 87, mode
// 5 to the method at VA 0x10a7fb50, mode 6 to the method at VA 0x10a928f0), then, when its
// object at 0x288 has a non-zero low word at 0x28, 0x2c or 0x30 and the flag at bit 24 of 0x2c
// is clear, to its method at VA 0x10a8b6c0.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a92cc0_Target
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    int unk_2c;
    int unk_30;
};

class UnkType_10a92cc0
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
    virtual void VirtualSlot87(float Value, int Flag);

    unsigned char unk_4[0x2c - 0x4];
    unsigned int unk_2c_0 : 24;
    unsigned int unk_2c_24 : 1;
    unsigned char unk_30[0x4c - 0x30];
    unsigned char unk_4c;
    unsigned char unk_4d[0x288 - 0x4d];
    UnkType_10a92cc0_Target* unk_288;

    void Unk_10a92cc0(float Value);
    void Unk_10a7fb50(float Value);
    void Unk_10a928f0(float Value);
    void Unk_10a8b6c0(float Value);
};

// UnkType_10a92cc0::Unk_10a92cc0
void UnkType_10a92cc0::Unk_10a92cc0(float Value)
{
    switch ( unk_4c )
    {
    case 2:
        VirtualSlot87(Value, 0);
        break;
    case 5:
        Unk_10a7fb50(Value);
        break;
    case 6:
        Unk_10a928f0(Value);
        break;
    }
    if ( unk_288
        && ((unk_288->unk_28 & 0xffff) || (unk_288->unk_2c & 0xffff) || (unk_288->unk_30 & 0xffff))
        && !unk_2c_24 )
    {
        Unk_10a8b6c0(Value);
    }
}
