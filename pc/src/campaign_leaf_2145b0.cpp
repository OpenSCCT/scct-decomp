// campaign_leaf_2145b0.cpp -- a member function at VA 0x10b145b0 taking a visitor: when the
// visitor's ints at 0x18 and 0x1c are both zero, it passes the address of each non-null entry of
// the array at 0x478 (as many as the byte at 0x470 counts) to the visitor's virtual slot 6, then
// calls itself with the visitor on each of the two non-null children at 0x47c. guess: visits a
// tree. The class, method, member and parameter names are invented; the offsets, addresses and
// slot are the binary's.

class UnkType_10b145b0_Entry;

class UnkType_10b145b0_Visitor
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6(UnkType_10b145b0_Entry** Entry);

    unsigned char unk_04[0x18 - 0x04];
    int unk_18;
    int unk_1c;
};

class UnkType_10b145b0
{
public:
    void Unk_10b145b0(UnkType_10b145b0_Visitor* Visitor);

private:
    unsigned char unk_000[0x470];
    unsigned char unk_470;
    unsigned char unk_471[0x478 - 0x471];
    UnkType_10b145b0_Entry** unk_478;
    UnkType_10b145b0* unk_47c[2];
};

// UnkType_10b145b0::Unk_10b145b0
void UnkType_10b145b0::Unk_10b145b0(UnkType_10b145b0_Visitor* Visitor)
{
    if ( Visitor->unk_18 == 0 && Visitor->unk_1c == 0 )
    {
        int i;
        for ( i = 0; i < unk_470; i++ )
        {
            if ( unk_478[i] )
            {
                Visitor->VirtualSlot6(&unk_478[i]);
            }
        }
        for ( i = 0; i < 2; i++ )
        {
            if ( unk_47c[i] )
            {
                unk_47c[i]->Unk_10b145b0(Visitor);
            }
        }
    }
}
