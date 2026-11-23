// campaign_leaf_256da0.cpp -- the destructor at VA 0x10b56da0: it installs the class's virtual
// tables at 0x00, 0x08 and 0x10; when the byte at 0x3c is set it calls the member at VA 0x10b65820,
// clears the int at 0x44, calls virtual slot 14 of the object the pointer at 0x40 refers to and
// clears the byte. It then deletes that object through its virtual destructor, clears the pointer
// and runs the base destructor at VA 0x10b65af0. The class, method and member names are invented;
// the offsets, addresses and slot are the binary's.

class UnkType_10b56da0_Face0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b56da0_Face8
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

class UnkType_10b56da0_Face10
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10b56da0_Base : public UnkType_10b56da0_Face0,
                              public UnkType_10b56da0_Face8,
                              public UnkType_10b56da0_Face10
{
public:
    ~UnkType_10b56da0_Base();

    void Unk_10b65820();

private:
    unsigned char unk_14[0x3c - 0x14];

public:
    bool unk_3c;

private:
    unsigned char unk_3d[0x40 - 0x3d];
};

class UnkType_10b56da0_Item
{
public:
    virtual ~UnkType_10b56da0_Item();
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

class UnkType_10b56da0 : public UnkType_10b56da0_Base
{
public:
    ~UnkType_10b56da0();

private:
    UnkType_10b56da0_Item* unk_40;
    int unk_44;
};

// UnkType_10b56da0::~UnkType_10b56da0
UnkType_10b56da0::~UnkType_10b56da0()
{
    if ( unk_3c )
    {
        Unk_10b65820();
        unk_44 = 0;
        unk_40->VirtualSlot14();
        unk_3c = false;
    }
    delete unk_40;
    unk_40 = 0;
}
