// campaign_leaf_145910.cpp -- method at VA 0x10a45910: stores the value virtual slot 52 (vtable
// offset 0xd0) of the object at 0x28 of the object at 0x18 returns at 0x178, the double at 0xc4 of
// the object at 0x7c of the object at 0x30 at 0x180, whether First is set at 0x19c, 0x10000 at 0xb8
// when the value at 0x428 of the object at 0x30 is 4 or 2 (else 0), counts at 0xa8, then stores at
// 0x190 what virtual slot 58 (vtable offset 0xe8) of the object at 0x60 returns for this, First and
// Second, 0x10 at 0x194, and returns whether that value is set. The class, member, method and
// parameter names are invented; the offsets, the slots and the constants are the binary's.

class UnkType_10a45910;

class UnkType_10a45910_Clock
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
    virtual double VirtualSlot52();
};

class UnkType_10a45910_Source
{
public:
    char unk_0[0x28];
    UnkType_10a45910_Clock* unk_28;
};

#pragma pack(push, 4)
class UnkType_10a45910_Settings
{
public:
    char unk_0[0xc4];
    double unk_c4;
};
#pragma pack(pop)

class UnkType_10a45910_Owner
{
public:
    char unk_0[0x7c];
    UnkType_10a45910_Settings* unk_7c;
    char unk_80[0x428 - 0x80];
    int unk_428;
};

class UnkType_10a45910_Handler
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
    virtual int VirtualSlot58(UnkType_10a45910* Caller, int First, int Second);
};

class UnkType_10a45910
{
public:
    int Unk_10a45910(int First, int Second);

private:
    char unk_0[0x18];
    UnkType_10a45910_Source* unk_18;
    char unk_1c[0x30 - 0x1c];
    UnkType_10a45910_Owner* unk_30;
    char unk_34[0x60 - 0x34];
    UnkType_10a45910_Handler* unk_60;
    char unk_64[0xa8 - 0x64];
    int unk_a8;
    char unk_ac[0xb8 - 0xac];
    int unk_b8;
    char unk_bc[0x178 - 0xbc];
    double unk_178;
    double unk_180;
    char unk_188[0x190 - 0x188];
    int unk_190;
    int unk_194;
    char unk_198[0x19c - 0x198];
    int unk_19c;
};

// UnkType_10a45910::Unk_10a45910
int UnkType_10a45910::Unk_10a45910(int First, int Second)
{
    unk_178 = unk_18->unk_28->VirtualSlot52();
    unk_180 = unk_30->unk_7c->unk_c4;
    unk_19c = First != 0;
    unk_b8 = unk_30->unk_428 == 4 || unk_30->unk_428 == 2 ? 0x10000 : 0;
    unk_a8++;
    unk_190 = unk_60->VirtualSlot58(this, First, Second);
    unk_194 = 0x10;
    return unk_190 != 0;
}
