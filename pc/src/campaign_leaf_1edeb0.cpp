// campaign_leaf_1edeb0.cpp -- thiscall method at VA 0x10aedeb0 taking two controllers and a pawn.
// It keeps the controllers at 0x2c and 0x30, clears bit 0x400 and sets bit 0x800 of the pawn's
// flags at 0x2b8, sets its byte at 0x4c and the floats at 0x2f4 (420), 0x2e8 (400) and 0x300
// (2500), calls virtual slot 108 of both controllers, passes the pawn to the method at VA
// 0x10aedae0, calls virtual slot 109 of both controllers and returns that method's result. The
// class, method and member names are invented.

class UnkType_10aedeb0_Controller
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
};

struct UnkType_10aedeb0_Pawn
{
    char unk_000[0x4c];
    bool unk_04c;
    char unk_04d[0x2b8 - 0x4d];
    int unk_2b8;
    char unk_2bc[0x2e8 - 0x2bc];
    float unk_2e8;
    char unk_2ec[0x2f4 - 0x2ec];
    float unk_2f4;
    char unk_2f8[0x300 - 0x2f8];
    float unk_300;
};

class UnkType_10aedeb0
{
public:
    int Unk_10aedeb0(UnkType_10aedeb0_Controller* First, UnkType_10aedeb0_Controller* Second,
                     UnkType_10aedeb0_Pawn* Pawn);
    int Unk_10aedae0(UnkType_10aedeb0_Pawn* Pawn);

private:
    char unk_00[0x2c];
    UnkType_10aedeb0_Controller* unk_2c;
    UnkType_10aedeb0_Controller* unk_30;
};

// UnkType_10aedeb0::Unk_10aedeb0
int UnkType_10aedeb0::Unk_10aedeb0(UnkType_10aedeb0_Controller* First,
                                   UnkType_10aedeb0_Controller* Second,
                                   UnkType_10aedeb0_Pawn* Pawn)
{
    unk_2c = First;
    unk_30 = Second;
    Pawn->unk_04c = true;
    Pawn->unk_2f4 = 420.0f;
    Pawn->unk_2b8 &= ~0x400;
    Pawn->unk_2b8 |= 0x800;
    Pawn->unk_2e8 = 400.0f;
    Pawn->unk_300 = 2500.0f;
    unk_2c->VirtualSlot108();
    unk_30->VirtualSlot108();
    int Result = Unk_10aedae0(Pawn);
    unk_2c->VirtualSlot109();
    unk_30->VirtualSlot109();
    return Result;
}
