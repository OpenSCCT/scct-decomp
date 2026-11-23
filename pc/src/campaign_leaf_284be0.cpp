// campaign_leaf_284be0.cpp -- method at VA 0x10b84be0: passes this object to virtual slot 33 (vtable
// offset 0x84) of the object at 0x184, looks the word at 0x64 up with the function at VA
// 0x109353f0, and returns 1 when the result is set and either of its methods at VA 0x109d5380 and
// VA 0x109d53b0, called with 9, returns more than 0.99; otherwise returns 0. The class, member and
// method names are invented; the offsets, the slot and the addresses are the binary's.

class UnkType_10b84be0;

class UnkType_10b84be0_184
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
    virtual void VirtualSlot33(UnkType_10b84be0* Owner);
};

class UnkType_10b84be0_Found
{
public:
    float Unk_109d5380(int Index);
    float Unk_109d53b0(int Index);
};

UnkType_10b84be0_Found* Unk_109353f0(int Key);

class UnkType_10b84be0
{
public:
    int Unk_10b84be0();

private:
    unsigned char unk_00[0x64];
    int unk_64;
    unsigned char unk_68[0x184 - 0x68];
    UnkType_10b84be0_184* unk_184;
};

// UnkType_10b84be0::Unk_10b84be0
int UnkType_10b84be0::Unk_10b84be0()
{
    unk_184->VirtualSlot33(this);
    UnkType_10b84be0_Found* Found = Unk_109353f0(unk_64);
    if ( Found && ( Found->Unk_109d5380(9) > 0.99f || Found->Unk_109d53b0(9) > 0.99f ) )
    {
        return 1;
    }
    return 0;
}
