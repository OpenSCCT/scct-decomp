// campaign_leaf_33f1b0.cpp -- one function at file offset 0x33f1b0, preferred VA 0x10c3f1b0. It
// passes (First, Second) to the method at 0x10beaf70; when First is 0 it passes a function-local
// static name, built once from the retail string "s_Off" and 2 (constructor at 0x10cd4790), and
// 0 to virtual slot 12. The class, method, local and parameter names are invented; the slot, the
// string and the bytes are the binary's.

class UnkType_10c3f1b0_Name
{
public:
    UnkType_10c3f1b0_Name(const unsigned short* Text, int Flags);

    int unk_0;
};

class UnkType_10c3f1b0
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
    virtual void VirtualSlot12(UnkType_10c3f1b0_Name Name, int Value);
    void Unk_10beaf70(int First, int Second);
    void Unk_10c3f1b0(int First, int Second);
};

// UnkType_10c3f1b0::Unk_10c3f1b0
void UnkType_10c3f1b0::Unk_10c3f1b0(int First, int Second)
{
    Unk_10beaf70(First, Second);
    static UnkType_10c3f1b0_Name OffName(L"s_Off", 2);
    if ( First == 0 )
    {
        VirtualSlot12(OffName, 0);
    }
}
