// campaign_leaf_6155f0.cpp -- thiscall method at VA 0x10f155f0: calls the method at VA 0x10f14470
// with -1, then the sixth virtual method of the object at 0x10, and returns true. The class and
// method names are invented.

class UnkType_10f155f0_10
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
};

class UnkType_10f155f0
{
public:
    void Unk_10f14470(int Value);
    bool Unk_10f155f0();

private:
    int unk_00;
    int unk_04;
    int unk_08;
    int unk_0c;
    UnkType_10f155f0_10* unk_10;
};

// UnkType_10f155f0::Unk_10f155f0
bool UnkType_10f155f0::Unk_10f155f0()
{
    Unk_10f14470(-1);
    unk_10->VirtualSlot5();
    return true;
}
