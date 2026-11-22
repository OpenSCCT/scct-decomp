// campaign_leaf_1aba50.cpp -- destructor at VA 0x10aaba50 of a class whose vtable (VA 0x110d9e18)
// holds one entry: frees the pointer at 0x08 through virtual slot 2 (vtable offset 0x08) of the
// object the global at VA 0x111c88a0 points to. The class, member and global names are invented;
// the offsets and the addresses are the binary's.

class UnkType_111c88a0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(void* Data);
};

extern UnkType_111c88a0* GUnk_111c88a0;

class UnkType_10aaba50
{
public:
    virtual ~UnkType_10aaba50();

private:
    int unk_04;
    void* unk_08;
};

// UnkType_10aaba50::~UnkType_10aaba50
UnkType_10aaba50::~UnkType_10aaba50()
{
    GUnk_111c88a0->VirtualSlot2(unk_08);
}
