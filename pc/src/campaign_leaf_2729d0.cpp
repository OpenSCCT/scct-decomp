// campaign_leaf_2729d0.cpp -- method at VA 0x10b729d0 taking three arguments, of which it reads the
// first: stores it plus 2 at 0x0c when the word at 0x04 is zero, else stores 0 for 0 and the value
// plus 1 otherwise; copies that to 0x1c of the object at 0x10 and, when that object's pointer at
// 0x08 is set, passes the word reached through it to virtual slot 9 (vtable offset 0x24); finally
// calls the method at VA 0x10b762a0 on the object at 0x08 when it is set. The class, member and
// method names are invented; the offsets, the slot and the address are the binary's.

class UnkType_10b729d0_18
{
public:
    unsigned char unk_00[0x12c];
    int unk_12c;
};

class UnkType_10b729d0_08
{
public:
    unsigned char unk_00[0x18];
    UnkType_10b729d0_18* unk_18;
};

class UnkType_10b729d0_10
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
    virtual void VirtualSlot9(int Value);

    int unk_04;
    UnkType_10b729d0_08* unk_08;
    unsigned char unk_0c[0x1c - 0x0c];
    int unk_1c;
};

class UnkType_10b729d0_Other
{
public:
    void Unk_10b762a0();
};

class UnkType_10b729d0
{
public:
    void Unk_10b729d0(int Value, int Second, int Third);

private:
    int unk_00;
    int unk_04;
    UnkType_10b729d0_Other* unk_08;
    int unk_0c;
    UnkType_10b729d0_10* unk_10;
};

// UnkType_10b729d0::Unk_10b729d0
void UnkType_10b729d0::Unk_10b729d0(int Value, int Second, int Third)
{
    if ( unk_04 )
    {
        if ( Value == 0 )
        {
            unk_0c = 0;
        }
        else
        {
            unk_0c = Value + 1;
        }
    }
    else
    {
        unk_0c = Value + 2;
    }
    UnkType_10b729d0_10* Child = unk_10;
    if ( Child )
    {
        Child->unk_1c = unk_0c;
        if ( Child->unk_08 )
        {
            Child->VirtualSlot9(Child->unk_08->unk_18->unk_12c);
        }
    }
    if ( unk_08 )
    {
        unk_08->Unk_10b762a0();
    }
}
