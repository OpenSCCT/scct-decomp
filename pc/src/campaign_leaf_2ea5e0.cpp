// campaign_leaf_2ea5e0.cpp -- method at VA 0x10bea5e0 taking two values: returns 0 unless the
// method at VA 0x10991680 accepts them; otherwise passes the first to virtual slot 28 (vtable
// offset 0x70) of the object at 0x3d4 when that is set, and to the method at VA 0x109b7870 of the
// pointer of every 12-byte entry of the array at 0x31c (count at 0x320) that is set, and returns 1.
// The class, member and method names are invented; the offsets, the slot and the addresses are the
// binary's.

class UnkType_10bea5e0_3d4
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
    virtual void VirtualSlot28(int Value);
};

class UnkType_10bea5e0_Item
{
public:
    void Unk_109b7870(int Value);
};

class UnkType_10bea5e0_Entry
{
public:
    UnkType_10bea5e0_Item* unk_00;
    unsigned char unk_04[0x0c - 0x04];
};

class UnkType_10bea5e0
{
public:
    int Unk_10bea5e0(int Value, int Second);
    int Unk_10991680(int Value, int Second);

private:
    unsigned char unk_00[0x31c];
    UnkType_10bea5e0_Entry* unk_31c;
    int unk_320;
    unsigned char unk_324[0x3d4 - 0x324];
    UnkType_10bea5e0_3d4* unk_3d4;
};

// UnkType_10bea5e0::Unk_10bea5e0
int UnkType_10bea5e0::Unk_10bea5e0(int Value, int Second)
{
    if ( Unk_10991680(Value, Second) )
    {
        if ( unk_3d4 )
        {
            unk_3d4->VirtualSlot28(Value);
        }
        for ( int Index = 0; Index < unk_320; Index++ )
        {
            UnkType_10bea5e0_Entry* Entry = &unk_31c[Index];
            if ( Entry->unk_00 )
            {
                Entry->unk_00->Unk_109b7870(Value);
            }
        }
        return 1;
    }
    return 0;
}
