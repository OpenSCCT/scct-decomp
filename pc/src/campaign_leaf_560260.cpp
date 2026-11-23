// campaign_leaf_560260.cpp -- thiscall method at VA 0x10e60260: stores the value it is given at
// 0x94. When the object has an owner (member at 0x14), the owner is told through its fourth virtual
// method before the change and its third virtual method after it, each time with a 16-byte record
// the object fills through its eleventh virtual method. The class and method names are invented.

struct UnkType_10e60260_Record
{
    int unk_00[4];
};

class UnkType_10e60260;

class UnkType_10e60260_Owner
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(UnkType_10e60260* Item, UnkType_10e60260_Record* Record);
    virtual void VirtualSlot3(UnkType_10e60260* Item, UnkType_10e60260_Record* Record);
};

class UnkType_10e60260
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
    virtual void VirtualSlot10(UnkType_10e60260_Record* Record);

    void Unk_10e60260(int Value);

private:
    int unk_04[4];
    UnkType_10e60260_Owner* unk_14;
    int unk_18[31];
    int unk_94;
};

// UnkType_10e60260::Unk_10e60260
void UnkType_10e60260::Unk_10e60260(int Value)
{
    UnkType_10e60260_Record Record;
    if ( unk_14 )
    {
        VirtualSlot10(&Record);
        unk_14->VirtualSlot3(this, &Record);
        unk_94 = Value;
        VirtualSlot10(&Record);
        unk_14->VirtualSlot2(this, &Record);
    }
    else
    {
        unk_94 = Value;
    }
}
