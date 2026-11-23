// campaign_leaf_251780.cpp -- a member function at VA 0x10b51780 taking a flag and three ints: when
// the flag is clear it calls its own virtual slot 2. Otherwise it passes the three ints to its own
// virtual slot 1; passes the pointer at 0x12c of the object the pointer at 0xb0 refers to, when it
// is set, to the member at VA 0x10b75b50 of the member at 0x14, and the pointer at 0x08 to that
// member's member at VA 0x10b75f50 and to the free function at VA 0x10b75e90; then it stores in the
// byte at 0xa6 of the object the pointer at 0x08 refers to the difference of its ints at 0x70 and
// 0x6c divided by 60 (or 0 when the int at 0x6c is zero) and calls that object's member at VA
// 0x10d298a0. The class, method, member and parameter names are invented; the offsets, addresses,
// constant and slots are the binary's.

class UnkType_10b51780_Item
{
public:
    void Unk_10d298a0();

    unsigned char unk_00[0x6c];
    int unk_6c;
    int unk_70;
    unsigned char unk_74[0xa6 - 0x74];
    unsigned char unk_a6;
};

void __cdecl Unk_10b75e90(UnkType_10b51780_Item* Item);

class UnkType_10b51780_Source
{
public:
    unsigned char unk_000[0x12c];
    int unk_12c;
};

class UnkType_10b51780_List
{
public:
    void Unk_10b75b50(int Value);
    void Unk_10b75f50(UnkType_10b51780_Item* Item);

private:
    int unk_00;
};

class UnkType_10b51780
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(int First, int Second, int Third);
    virtual void VirtualSlot2();

    void Unk_10b51780(bool Flag, int First, int Second, int Third);

private:
    int unk_04;
    UnkType_10b51780_Item* unk_08;
    unsigned char unk_0c[0x14 - 0x0c];
    UnkType_10b51780_List unk_14;
    unsigned char unk_18[0xb0 - 0x18];
    UnkType_10b51780_Source* unk_b0;
};

// UnkType_10b51780::Unk_10b51780
void UnkType_10b51780::Unk_10b51780(bool Flag, int First, int Second, int Third)
{
    if ( Flag )
    {
        VirtualSlot1(First, Second, Third);
        if ( unk_b0->unk_12c )
        {
            unk_14.Unk_10b75b50(unk_b0->unk_12c);
        }
        unk_14.Unk_10b75f50(unk_08);
        Unk_10b75e90(unk_08);
        UnkType_10b51780_Item* Item = unk_08;
        if ( Item->unk_6c == 0 )
        {
            Item->unk_a6 = 0;
        }
        else
        {
            Item->unk_a6 = ( Item->unk_70 - Item->unk_6c ) / 60;
        }
        Item->Unk_10d298a0();
    }
    else
    {
        VirtualSlot2();
    }
}
