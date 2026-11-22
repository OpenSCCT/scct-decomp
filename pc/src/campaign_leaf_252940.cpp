// campaign_leaf_252940.cpp -- a member function at VA 0x10b52940: when its own virtual slot 16
// returns true it calls its virtual slot 15 with 0. It does not read its argument. The class and
// method names are invented; the slots are the binary's.

class UnkType_10b52940
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
    virtual void VirtualSlot15(int Value);
    virtual bool VirtualSlot16();

    void Unk_10b52940(int Unused);
};

// UnkType_10b52940::Unk_10b52940
void UnkType_10b52940::Unk_10b52940(int Unused)
{
    if ( VirtualSlot16() )
    {
        VirtualSlot15(0);
    }
}
