// campaign_leaf_3317a0.cpp -- method at VA 0x10c317a0: after the method at VA 0x10c316c0, fills the
// last 0x78-byte entry of the array at 0x38 (count at 0x3c) with Kind, Id, Value, Value again when
// Kind is 3 (else 0) and the flag Enabled; for an enabled kind 3 entry also stores the value
// virtual slot 69 (vtable offset 0x114) of the object at 0x64 of the object at 0x41c of the object
// at 0x4c returns for 0, less 0.001, at least 0. The class, member, method and parameter names are
// invented; the offsets, the slot and the constants are the binary's.

class UnkType_10c317a0_Source
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
    virtual float VirtualSlot69(int Value);
};

class UnkType_10c317a0_Holder
{
public:
    char unk_0[0x64];
    UnkType_10c317a0_Source* unk_64;
};

class UnkType_10c317a0_Owner
{
public:
    char unk_0[0x41c];
    UnkType_10c317a0_Holder* unk_41c;
};

class UnkType_10c317a0_Entry
{
public:
    unsigned char unk_0;
    unsigned char unk_1;
    char unk_2[0x58 - 0x2];
    float unk_58;
    char unk_5c[0x60 - 0x5c];
    float unk_60;
    float unk_64;
    char unk_68[0x74 - 0x68];
    unsigned int unk_74_0 : 2;
    unsigned int unk_74_2 : 1;
};

class UnkType_10c317a0
{
public:
    void Unk_10c316c0();
    void Unk_10c317a0(unsigned char Id, int Kind, float Value, int Enabled);

private:
    char unk_0[0x38];
    UnkType_10c317a0_Entry* unk_38;
    int unk_3c;
    char unk_40[0x4c - 0x40];
    UnkType_10c317a0_Owner* unk_4c;
};

// UnkType_10c317a0::Unk_10c317a0
void UnkType_10c317a0::Unk_10c317a0(unsigned char Id, int Kind, float Value, int Enabled)
{
    UnkType_10c317a0_Entry* Entry;

    Unk_10c316c0();
    Entry = &unk_38[unk_3c - 1];
    Entry->unk_0 = Kind;
    Entry->unk_1 = Id;
    Entry->unk_58 = Value;
    Entry->unk_60 = Kind == 3 ? Value : 0.0f;
    Entry->unk_74_2 = Enabled;
    if ( Kind == 3 && Enabled )
    {
        UnkType_10c317a0_Source* Source = unk_4c->unk_41c->unk_64;

        if ( Source )
        {
            Entry->unk_64 = Source->VirtualSlot69(0) - 0.001;
        }
        if ( Entry->unk_64 < 0.0f )
        {
            Entry->unk_64 = 0.0f;
        }
    }
}
