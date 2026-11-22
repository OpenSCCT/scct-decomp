// campaign_leaf_07e2c0.cpp -- method at VA 0x1097e2c0 taking one unused argument: if the pointer at
// 0x54 is set, calls virtual slot 7 (vtable offset 0x1c) on the object it points to. The class,
// member and method names are invented; the offsets are the binary's.

class UnkType_1097e2c0_54
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
};

class UnkType_1097e2c0
{
public:
    void Unk_1097e2c0(int Arg);

private:
    unsigned char unk_00[0x54];
    UnkType_1097e2c0_54* unk_54;
};

// UnkType_1097e2c0::Unk_1097e2c0
void UnkType_1097e2c0::Unk_1097e2c0(int Arg)
{
    if ( unk_54 )
    {
        unk_54->VirtualSlot7();
    }
}
