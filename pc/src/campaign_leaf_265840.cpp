// campaign_leaf_265840.cpp -- a member function at VA 0x10b65840 taking a flag: when the pointer at
// 0x38 is set and the flag is set, it returns when its own virtual slot 16 returns true, and
// otherwise passes the pointer to the free function at VA 0x10d249e0 and calls the member at VA
// 0x10ad5820 of the object the pointer at 0x14 refers to with the pointer, 1, 1 and 0. When the
// flag is clear and slot 16 returns true it calls that member with the pointer, 0, 1 and 0. The
// class, function, method, member and parameter names are invented; the offsets, addresses and
// slot are the binary's.

class UnkType_10b65840_Item;

void Unk_10d249e0(UnkType_10b65840_Item* Item);

class UnkType_10b65840_Owner
{
public:
    void Unk_10ad5820(UnkType_10b65840_Item* Item, int Second, int Third, int Fourth);
};

class UnkType_10b65840
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
    virtual bool VirtualSlot16();

    void Unk_10b65840(bool Flag);

private:
    unsigned char unk_04[0x14 - 0x04];
    UnkType_10b65840_Owner* unk_14;
    unsigned char unk_18[0x38 - 0x18];
    UnkType_10b65840_Item* unk_38;
};

// UnkType_10b65840::Unk_10b65840
void UnkType_10b65840::Unk_10b65840(bool Flag)
{
    if ( !unk_38 )
    {
        return;
    }
    if ( Flag )
    {
        if ( VirtualSlot16() )
        {
            return;
        }
        Unk_10d249e0(unk_38);
        unk_14->Unk_10ad5820(unk_38, 1, 1, 0);
    }
    else
    {
        if ( !VirtualSlot16() )
        {
            return;
        }
        unk_14->Unk_10ad5820(unk_38, 0, 1, 0);
    }
}
