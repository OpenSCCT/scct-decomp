// campaign_leaf_25d7d0.cpp -- the destructor at VA 0x10b5d7d0: it installs the class's virtual
// tables at 0x00, 0x08 and 0x10; when the byte at 0x40 is set it calls the member at VA 0x10b65820,
// clears the int at 0x44 and the byte at 0x41, sets the ints at 0x48 and 0x4c to -1, calls virtual
// slot 14 of the object the pointer at 0x50 refers to and clears the byte at 0x40. It then deletes
// that object through its virtual destructor, clears the pointer and runs the base destructor at VA
// 0x10b65af0. The class, method and member names are invented; the offsets, addresses and slot are
// the binary's.

class UnkType_10b5d7d0_Face0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5d7d0_Face8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b5d7d0_Face10
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10b5d7d0_Base : public UnkType_10b5d7d0_Face0,
                              public UnkType_10b5d7d0_Face8,
                              public UnkType_10b5d7d0_Face10
{
public:
    ~UnkType_10b5d7d0_Base();

    void Unk_10b65820();

private:
    unsigned char unk_14[0x40 - 0x14];
};

class UnkType_10b5d7d0_Item
{
public:
    virtual ~UnkType_10b5d7d0_Item();
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
};

class UnkType_10b5d7d0 : public UnkType_10b5d7d0_Base
{
public:
    ~UnkType_10b5d7d0();

private:
    bool unk_40;
    bool unk_41;
    int unk_44;
    int unk_48;
    int unk_4c;
    UnkType_10b5d7d0_Item* unk_50;
};

// UnkType_10b5d7d0::~UnkType_10b5d7d0
UnkType_10b5d7d0::~UnkType_10b5d7d0()
{
    if ( unk_40 )
    {
        Unk_10b65820();
        unk_44 = 0;
        unk_41 = false;
        unk_48 = -1;
        unk_4c = -1;
        unk_50->VirtualSlot14();
        unk_40 = false;
    }
    delete unk_50;
    unk_50 = 0;
}
