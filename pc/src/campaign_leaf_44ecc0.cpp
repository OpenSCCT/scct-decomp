// campaign_leaf_44ecc0.cpp -- constructor at VA 0x10d4ecc0 of a polymorphic class whose vtable is at
// VA 0x1113ad04; constructs the member at offset 4 with the constructor at VA 0x10d282a0 and
// clears the bytes at offsets 0x18 and 0x19. All names are invented.

class UnkType_10d282a0
{
public:
    UnkType_10d282a0();

private:
    int unk_00;
};

class UnkType_10d4ecc0
{
public:
    UnkType_10d4ecc0();
    virtual void VirtualSlot0();

private:
    UnkType_10d282a0 unk_04;
    unsigned char unk_08[0x10];
    unsigned char unk_18;
    unsigned char unk_19;
};

// UnkType_10d4ecc0::UnkType_10d4ecc0
UnkType_10d4ecc0::UnkType_10d4ecc0()
{
    unk_18 = 0;
    unk_19 = 0;
}
