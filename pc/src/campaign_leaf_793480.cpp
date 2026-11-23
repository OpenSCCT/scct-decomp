// campaign_leaf_793480.cpp -- one function at file offset 0x793480, preferred VA 0x11093480. When
// virtual slot 6 of the object at 0x8 returns zero, it copies the word at 0x10 to 0xc. The class,
// method and member names are invented; the offset is the binary's.

class UnkType_11093480_Object
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

    int unk_0;
    int unk_4;
    UnkType_11093480_Object* unk_8;
    int unk_c;
    int unk_10;
};

// UnkType_11093480::Unk_11093480
void UnkType_11093480::Unk_11093480()
{
    if ( unk_8->VirtualSlot6() == 0 )
    {
        unk_c = unk_10;
    }
}
