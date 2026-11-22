// campaign_leaf_793480.cpp -- thiscall method at VA 0x11093480: when the seventh virtual method of
// the object at 0x08 returns 0, copies the member at 0x10 to 0x0c. The class and method names are
// invented.

class UnkType_11093480_08
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual int VirtualSlot6();
};

class UnkType_11093480
{
public:
    void Unk_11093480();

private:
    int unk_00;
    int unk_04;
    UnkType_11093480_08* unk_08;
    int unk_0c;
    int unk_10;
};

// UnkType_11093480::Unk_11093480
void UnkType_11093480::Unk_11093480()
{
    if ( !unk_08->VirtualSlot6() )
    {
        unk_0c = unk_10;
    }
}
