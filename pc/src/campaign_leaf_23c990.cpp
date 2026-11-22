// campaign_leaf_23c990.cpp -- a member function at VA 0x10b3c990 that calls the member at VA
// 0x10b3c870, passes the pointer at 0x04 to virtual slot 2 of the allocator object the global
// pointer at VA 0x111c88a0 refers to, and clears the pointer. guess: frees an owned block. The
// class, method, member and global names are invented; the offsets, addresses and slot are the
// binary's.

class UnkType_111c88a0
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(void* Data);
};

extern UnkType_111c88a0* GUnk_111c88a0;

class UnkType_10b3c990
{
public:
    void Unk_10b3c870();
    void Unk_10b3c990();

private:
    int unk_00;
    void* unk_04;
};

// UnkType_10b3c990::Unk_10b3c990
void UnkType_10b3c990::Unk_10b3c990()
{
    Unk_10b3c870();
    GUnk_111c88a0->VirtualSlot2(unk_04);
    unk_04 = 0;
}
