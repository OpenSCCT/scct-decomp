// campaign_leaf_433af0.cpp -- thiscall at VA 0x10d33af0: clears bit 3 of the byte at offset 0x4c,
// passes the object to the seventeenth virtual method of the object at offset 8, then calls the
// method at VA 0x10d33740. All names are invented.

class UnkType_10d33af0;

class UnkType_10d33af0_Obj
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
    virtual void VirtualSlot16(UnkType_10d33af0* Object);
};

class UnkType_10d33af0
{
public:
    void Unk_10d33740();
    void Unk_10d33af0();

private:
    int unk_00;
    int unk_04;
    UnkType_10d33af0_Obj* unk_08;
    unsigned char unk_0c[0x40];
    unsigned char unk_4c;
};

// UnkType_10d33af0::Unk_10d33af0
void UnkType_10d33af0::Unk_10d33af0()
{
    unk_4c &= ~8;
    unk_08->VirtualSlot16(this);
    Unk_10d33740();
}
