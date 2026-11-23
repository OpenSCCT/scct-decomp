// campaign_leaf_33f7a0.cpp -- one function at file offset 0x33f7a0, preferred VA 0x10c3f7a0. When
// the words at 0x2c and 0x30 are both set, it passes their addresses and Arg to virtual slot 169
// of the object reached through the pointers at 0x5c and 0x78, and clears the word at 0x2c when
// bit 0 of the byte at 0x38 is set. It returns 1. The class, method, member and parameter names
// are invented; the offsets, the slot and the bytes are the binary's.

class UnkType_10c3f7a0_Device
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
    virtual void VirtualSlot107();
    virtual void VirtualSlot108();
    virtual void VirtualSlot109();
    virtual void VirtualSlot110();
    virtual void VirtualSlot111();
    virtual void VirtualSlot112();
    virtual void VirtualSlot113();
    virtual void VirtualSlot114();
    virtual void VirtualSlot115();
    virtual void VirtualSlot116();
    virtual void VirtualSlot117();
    virtual void VirtualSlot118();
    virtual void VirtualSlot119();
    virtual void VirtualSlot120();
    virtual void VirtualSlot121();
    virtual void VirtualSlot122();
    virtual void VirtualSlot123();
    virtual void VirtualSlot124();
    virtual void VirtualSlot125();
    virtual void VirtualSlot126();
    virtual void VirtualSlot127();
    virtual void VirtualSlot128();
    virtual void VirtualSlot129();
    virtual void VirtualSlot130();
    virtual void VirtualSlot131();
    virtual void VirtualSlot132();
    virtual void VirtualSlot133();
    virtual void VirtualSlot134();
    virtual void VirtualSlot135();
    virtual void VirtualSlot136();
    virtual void VirtualSlot137();
    virtual void VirtualSlot138();
    virtual void VirtualSlot139();
    virtual void VirtualSlot140();
    virtual void VirtualSlot141();
    virtual void VirtualSlot142();
    virtual void VirtualSlot143();
    virtual void VirtualSlot144();
    virtual void VirtualSlot145();
    virtual void VirtualSlot146();
    virtual void VirtualSlot147();
    virtual void VirtualSlot148();
    virtual void VirtualSlot149();
    virtual void VirtualSlot150();
    virtual void VirtualSlot151();
    virtual void VirtualSlot152();
    virtual void VirtualSlot153();
    virtual void VirtualSlot154();
    virtual void VirtualSlot155();
    virtual void VirtualSlot156();
    virtual void VirtualSlot157();
    virtual void VirtualSlot158();
    virtual void VirtualSlot159();
    virtual void VirtualSlot160();
    virtual void VirtualSlot161();
    virtual void VirtualSlot162();
    virtual void VirtualSlot163();
    virtual void VirtualSlot164();
    virtual void VirtualSlot165();
    virtual void VirtualSlot166();
    virtual void VirtualSlot167();
    virtual void VirtualSlot168();
    virtual void VirtualSlot169(int* First, int* Second, int Arg);
};

class UnkType_10c3f7a0_Owner
{
public:
    unsigned char unk_0[0x78];
    UnkType_10c3f7a0_Device* unk_78;
};

class UnkType_10c3f7a0
{
public:
    int Unk_10c3f7a0(int Arg);

    unsigned char unk_0[0x2c];
    int unk_2c;
    int unk_30;
    unsigned char unk_34[0x4];
    unsigned char unk_38;
    unsigned char unk_39[0x23];
    UnkType_10c3f7a0_Owner* unk_5c;
};

// UnkType_10c3f7a0::Unk_10c3f7a0
int UnkType_10c3f7a0::Unk_10c3f7a0(int Arg)
{
    if ( unk_2c != 0 && unk_30 != 0 )
    {
        unk_5c->unk_78->VirtualSlot169(&unk_2c, &unk_30, Arg);
        if ( unk_38 & 1 )
        {
            unk_2c = 0;
        }
    }
    return 1;
}
