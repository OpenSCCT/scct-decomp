// campaign_leaf_38de60.cpp -- one function at file offset 0x38de60, preferred VA 0x10c8de60. When
// entry Index of the table at 0x74dc differs from the word at 0x56f0, it stores it there; then,
// when entry Index of the table at 0x73cc is set, it stores that entry at 0x74d4, and otherwise
// clears 0x74d4 and passes the new value to stdcall virtual slot 107 of the device at 0x4d3c.
// Either way it sets the word at 0x74d8 to 1. The class, method, member and parameter names are
// invented; the offsets, the slot and the bytes are the binary's.

class UnkType_10c8de60_Device
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
    virtual void VirtualSlot104();
    virtual void VirtualSlot105();
    virtual void VirtualSlot106();
    virtual long __stdcall VirtualSlot107(int Value);
};

class UnkType_10c8de60
{
public:
    void Unk_10c8de60(int Index);

    unsigned char unk_0[0x4d3c];
    UnkType_10c8de60_Device* unk_4d3c;
    unsigned char unk_4d40[0x9b0];
    int unk_56f0;
    unsigned char unk_56f4[0x1cd8];
    int unk_73cc[0x42];
    int unk_74d4;
    int unk_74d8;
    int unk_74dc[0x42];
};

// UnkType_10c8de60::Unk_10c8de60
void UnkType_10c8de60::Unk_10c8de60(int Index)
{
    int Value = unk_74dc[Index];

    if ( Value != unk_56f0 )
    {
        unk_56f0 = Value;
        if ( unk_73cc[Index] != 0 )
        {
            unk_74d4 = unk_73cc[Index];
            unk_74d8 = 1;
        }
        else
        {
            unk_74d4 = 0;
            unk_4d3c->VirtualSlot107(Value);
            unk_74d8 = 1;
        }
    }
}
