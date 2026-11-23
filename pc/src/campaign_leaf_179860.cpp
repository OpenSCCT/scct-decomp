// campaign_leaf_179860.cpp -- one function at file offset 0x179860, preferred VA 0x10a79860.
// guess: when its object at offset 0x2b4 has a controller (member at 0x184), it notifies the
// controller (virtual slot 33) and returns false only when the object's check at VA 0x1098dbc0
// accepts the argument and the object's member at 0x64 rejects it (virtual slot 63). Otherwise
// it returns true.
// The class, member, parameter and callee names are invented; the offset and the bytes are the
// binary's.

class UnkType_10a79860_Pawn;

class UnkType_10a79860_Controller
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
    virtual void VirtualSlot33(UnkType_10a79860_Pawn* Pawn);
};

class UnkType_10a79860_Level
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
    virtual int VirtualSlot63(void* Arg);
};

class UnkType_10a79860_Pawn
{
public:
    unsigned char unk_0[0x64];
    UnkType_10a79860_Level* unk_64;
    unsigned char unk_68[0x184 - 0x68];
    UnkType_10a79860_Controller* unk_184;

    int Unk_1098dbc0(void* Arg);
};

class UnkType_10a79860
{
public:
    unsigned char unk_0[0x2b4];
    UnkType_10a79860_Pawn* unk_2b4;

    int Unk_10a79860(void* Arg);
};

// UnkType_10a79860::Unk_10a79860
int UnkType_10a79860::Unk_10a79860(void* Arg)
{
    if ( !unk_2b4 || !unk_2b4->unk_184 )
    {
        return 1;
    }
    unk_2b4->unk_184->VirtualSlot33(unk_2b4);
    if ( unk_2b4->Unk_1098dbc0(Arg) && !unk_2b4->unk_64->VirtualSlot63(Arg) )
    {
        return 0;
    }
    return 1;
}
