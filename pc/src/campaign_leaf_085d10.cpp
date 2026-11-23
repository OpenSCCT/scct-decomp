// campaign_leaf_085d10.cpp -- method at VA 0x10985d10: stores its argument at 0x74; then stores the
// results of its virtual slots 12, 13 and 14 (vtable offsets 0x30-0x38) in the bytes at 0x48-0x4a,
// of slot 8 (offset 0x20) at 0x54 and 0x5c, and of slot 9 (offset 0x24) at 0x58 and 0x60; finally
// stores in the bytes at 0x50 and 0x51 what the free function at VA 0x10ccb8b0 returns for the
// values at 0x5c and 0x60. The class, member and method names are invented; the offsets, the slots
// and the address are the binary's.

class UnkType_10985d10_Arg
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
    virtual int VirtualSlot8();
    virtual int VirtualSlot9();
    virtual void VirtualSlot10();
    virtual void VirtualSlot11();
    virtual unsigned char VirtualSlot12();
    virtual unsigned char VirtualSlot13();
    virtual unsigned char VirtualSlot14();
};

unsigned char Unk_10ccb8b0(int Value);

class UnkType_10985d10
{
public:
    void Unk_10985d10(UnkType_10985d10_Arg* Arg);

private:
    unsigned char unk_00[0x48];
    unsigned char unk_48;
    unsigned char unk_49;
    unsigned char unk_4a;
    unsigned char unk_4b[5];
    unsigned char unk_50;
    unsigned char unk_51;
    unsigned char unk_52[2];
    int unk_54;
    int unk_58;
    int unk_5c;
    int unk_60;
    unsigned char unk_64[0x74 - 0x64];
    UnkType_10985d10_Arg* unk_74;
};

// UnkType_10985d10::Unk_10985d10
void UnkType_10985d10::Unk_10985d10(UnkType_10985d10_Arg* Arg)
{
    unk_74 = Arg;
    unk_48 = Arg->VirtualSlot12();
    unk_49 = unk_74->VirtualSlot13();
    unk_4a = unk_74->VirtualSlot14();
    unk_5c = unk_54 = unk_74->VirtualSlot8();
    unk_60 = unk_58 = unk_74->VirtualSlot9();
    unk_50 = Unk_10ccb8b0(unk_5c);
    unk_51 = Unk_10ccb8b0(unk_60);
}
