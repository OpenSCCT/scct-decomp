// campaign_leaf_08fc90.cpp -- method at VA 0x1098fc90: takes the float that virtual slot 77 (vtable
// offset 0x134) of the object reached through the pointers at 0x7c, 0x38 and 0x48 returns for the
// byte at 0x4f; when the float at 0xa0 is nonzero and the float at 0x430 of the object at 0x78
// minus the float at 0x344 is below it, returns that float scaled by the ratio of the two, and
// otherwise returns it unchanged. The class, member and method names are invented; the offsets and
// the slot are the binary's.

class UnkType_1098fc90_48
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
    virtual float VirtualSlot77(unsigned char Value);
};

class UnkType_1098fc90_38
{
public:
    unsigned char unk_00[0x48];
    UnkType_1098fc90_48* unk_48;
};

class UnkType_1098fc90_7c
{
public:
    unsigned char unk_00[0x38];
    UnkType_1098fc90_38* unk_38;
};

class UnkType_1098fc90_78
{
public:
    unsigned char unk_000[0x430];
    float unk_430;
};

class UnkType_1098fc90
{
public:
    float Unk_1098fc90();

private:
    unsigned char unk_000[0x4f];
    unsigned char unk_04f;
    unsigned char unk_050[0x78 - 0x50];
    UnkType_1098fc90_78* unk_078;
    UnkType_1098fc90_7c* unk_07c;
    unsigned char unk_080[0xa0 - 0x80];
    float unk_0a0;
    unsigned char unk_0a4[0x344 - 0xa4];
    float unk_344;
};

// UnkType_1098fc90::Unk_1098fc90
float UnkType_1098fc90::Unk_1098fc90()
{
    float Value = unk_07c->unk_38->unk_48->VirtualSlot77(unk_04f);
    if ( unk_0a0 != 0.0f )
    {
        float Elapsed = unk_078->unk_430 - unk_344;
        if ( Elapsed < unk_0a0 )
        {
            return Value * ( Elapsed / unk_0a0 );
        }
    }
    return Value;
}
