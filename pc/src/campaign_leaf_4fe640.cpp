// campaign_leaf_4fe640.cpp -- method at VA 0x10dfe640: builds a key from virtual slot 14 of its
// first argument and its second argument; when the map at 0x08 lacks the key (method at VA
// 0x10dfe2a0) it sets the count the method at VA 0x10dfe5a0 returns to 1, else increments it. The
// class, method and member names are invented; the offsets, slot and addresses are the binary's.

class UnkType_10dfe640_Key
{
public:
    int unk_00;
    int unk_04;
};

class UnkType_10dfe640_Map
{
public:
    int* Unk_10dfe2a0(const UnkType_10dfe640_Key& Key);
    int* Unk_10dfe5a0(const UnkType_10dfe640_Key& Key);
    void Unk_10dfe760(const UnkType_10dfe640_Key& Key);
};

class UnkType_10dfe640
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
    virtual int VirtualSlot14(int Arg);

    void Unk_10dfe640(int Arg0, int Arg1);

    int unk_04;
    UnkType_10dfe640_Map unk_08;
};

// UnkType_10dfe640::Unk_10dfe640
void UnkType_10dfe640::Unk_10dfe640(int Arg0, int Arg1)
{
    UnkType_10dfe640_Key Key;
    Key.unk_00 = VirtualSlot14(Arg0);
    Key.unk_04 = Arg1;
    if ( !unk_08.Unk_10dfe2a0(Key) )
    {
        *unk_08.Unk_10dfe5a0(Key) = 1;
    }
    else
    {
        ( *unk_08.Unk_10dfe5a0(Key) )++;
    }
}
