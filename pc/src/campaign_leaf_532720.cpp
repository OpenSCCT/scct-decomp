// campaign_leaf_532720.cpp -- thiscall method at VA 0x10e32720: calls the sixth virtual method of
// the object at 0x0c, then deletes this object through its virtual destructor. The class and method
// names are invented.

class UnkType_10e32720_0c
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
};

class UnkType_10e32720
{
public:
    virtual ~UnkType_10e32720();

    void Unk_10e32720();

private:
    int unk_04;
    int unk_08;
    UnkType_10e32720_0c* unk_0c;
};

// UnkType_10e32720::Unk_10e32720
void UnkType_10e32720::Unk_10e32720()
{
    unk_0c->VirtualSlot5();
    delete this;
}
