// campaign_leaf_497a80.cpp -- constructor at VA 0x10d97a80 of a polymorphic class whose vtable is at
// VA 0x1113d82c; runs the base constructor at VA 0x10d97ef0, sets the dword at offset 0x10 to 2
// and clears the byte at offset 0x14. All names are invented.

class UnkType_10d97ef0
{
public:
    UnkType_10d97ef0();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0xc];
};

class UnkType_10d97a80 : public UnkType_10d97ef0
{
public:
    UnkType_10d97a80();
    virtual void VirtualSlot0();

private:
    int unk_10;
    unsigned char unk_14;
};

// UnkType_10d97a80::UnkType_10d97a80
UnkType_10d97a80::UnkType_10d97a80()
{
    unk_10 = 2;
    unk_14 = 0;
}
