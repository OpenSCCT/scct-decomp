// campaign_leaf_2fb390.cpp -- method at VA 0x10bfb390 taking a flag and a value: stores the flag in bit
// 0 of the word at 0x408, then passes that bit and the value to virtual slot 174 (vtable offset
// 0x2b8) of every object in the pointer array at 0x3fc (count at 0x400) that is set. The class,
// member and method names are invented; the offsets and the slot are the binary's.

class UnkType_10bfb390_Item
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
    virtual void VirtualSlot169();
    virtual void VirtualSlot170();
    virtual void VirtualSlot171();
    virtual void VirtualSlot172();
    virtual void VirtualSlot173();
    virtual void VirtualSlot174(int Flag, int Value);
};

class UnkType_10bfb390
{
public:
    void Unk_10bfb390(int Flag, int Value);

private:
    unsigned char unk_00[0x3fc];
    UnkType_10bfb390_Item** unk_3fc;
    int unk_400;
    int unk_404;
    unsigned int unk_408 : 1;
};

// UnkType_10bfb390::Unk_10bfb390
void UnkType_10bfb390::Unk_10bfb390(int Flag, int Value)
{
    unk_408 = Flag;
    for ( int Index = 0; Index < unk_400; Index++ )
    {
        UnkType_10bfb390_Item* Item = unk_3fc[Index];
        if ( Item )
        {
            Item->VirtualSlot174(unk_408, Value);
        }
    }
}
