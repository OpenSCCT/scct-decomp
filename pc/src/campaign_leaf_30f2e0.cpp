// campaign_leaf_30f2e0.cpp -- one function at file offset 0x30f2e0, preferred VA 0x10c0f2e0. It
// builds a function-local static name once from the retail string "SRABegin" and 2 (constructor at
// 0x10cd4790); when the object at 0x2bc is set it sets bit 1 of the word at 0x2b8, passes the name
// with two zeros to virtual slot 13 of that object and returns 1, otherwise 0. The class, method,
// member and local names are invented; the offsets, the slot, the string and the bytes are the
// binary's.

class UnkType_10c0f2e0_Name
{
public:
    UnkType_10c0f2e0_Name(const unsigned short* Text, int Flags);

    int unk_0;
};

class UnkType_10c0f2e0_Target
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
    virtual void VirtualSlot13(UnkType_10c0f2e0_Name Name, int First, int Second);
};

class UnkType_10c0f2e0
{
public:
    int Unk_10c0f2e0();

    unsigned char unk_0[0x2b8];
    int unk_2b8;
    UnkType_10c0f2e0_Target* unk_2bc;
};

// UnkType_10c0f2e0::Unk_10c0f2e0
int UnkType_10c0f2e0::Unk_10c0f2e0()
{
    static UnkType_10c0f2e0_Name BeginName(L"SRABegin", 2);
    if ( unk_2bc == 0 )
    {
        return 0;
    }
    unk_2b8 |= 2;
    unk_2bc->VirtualSlot13(BeginName, 0, 0);
    return 1;
}
