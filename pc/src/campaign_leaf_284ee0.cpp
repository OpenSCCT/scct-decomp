// campaign_leaf_284ee0.cpp -- method at VA 0x10b84ee0: passes this object to virtual slot 33 (vtable
// offset 0x84) of the object at 0x184, looks the word at 0x64 up with the function at VA
// 0x109353f0, and returns 1 when the result's method at VA 0x109d5380 returns more than 0.0001 for
// any of 2, 3 and 5; otherwise returns 0. The class, member and method names are invented; the
// offsets, the slot and the addresses are the binary's.

class UnkType_10b84ee0;

class UnkType_10b84ee0_184
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
    virtual void VirtualSlot33(UnkType_10b84ee0* Owner);
};

class UnkType_10b84ee0_Found
{
public:
    float Unk_109d5380(int Index);
};

UnkType_10b84ee0_Found* Unk_109353f0(int Key);

class UnkType_10b84ee0
{
public:
    int Unk_10b84ee0();

private:
    unsigned char unk_00[0x64];
    int unk_64;
    unsigned char unk_68[0x184 - 0x68];
    UnkType_10b84ee0_184* unk_184;
};

// UnkType_10b84ee0::Unk_10b84ee0
int UnkType_10b84ee0::Unk_10b84ee0()
{
    unk_184->VirtualSlot33(this);
    UnkType_10b84ee0_Found* Found = Unk_109353f0(unk_64);
    if ( Found->Unk_109d5380(2) > 0.0001f || Found->Unk_109d5380(3) > 0.0001f
        || Found->Unk_109d5380(5) > 0.0001f )
    {
        return 1;
    }
    return 0;
}
