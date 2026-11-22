// campaign_leaf_3d7ac0.cpp -- a member function at VA 0x10cd7ac0: when the global pointer at VA
// 0x11230560 is not null and bit 0 of the flags at 0x1c is set, it calls virtual slot 0 of the
// global's object with this. The class, method, member and global names are invented; the offsets,
// addresses and slot are the binary's.

class UnkType_10cd7ac0;

class UnkType_11230560
{
public:
    virtual void VirtualSlot0(UnkType_10cd7ac0* Item);
};

extern UnkType_11230560* GUnk_11230560;

class UnkType_10cd7ac0
{
public:
    void Unk_10cd7ac0();

private:
    unsigned char unk_00[0x1c];
    unsigned int unk_1c;
};

// UnkType_10cd7ac0::Unk_10cd7ac0
void UnkType_10cd7ac0::Unk_10cd7ac0()
{
    if ( GUnk_11230560 && ( unk_1c & 1 ) )
    {
        GUnk_11230560->VirtualSlot0(this);
    }
}
