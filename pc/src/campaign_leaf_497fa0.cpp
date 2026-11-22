// campaign_leaf_497fa0.cpp -- constructor at VA 0x10d97fa0 of a polymorphic class whose vtable is at
// VA 0x1113d874; runs the base constructor at VA 0x10d97ef0 and sets the dword at offset 0x10
// to 1. All names are invented.

class UnkType_10d97ef0
{
public:
    UnkType_10d97ef0();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0xc];
};

class UnkType_10d97fa0 : public UnkType_10d97ef0
{
public:
    UnkType_10d97fa0();
    virtual void VirtualSlot0();

private:
    int unk_10;
};

// UnkType_10d97fa0::UnkType_10d97fa0
UnkType_10d97fa0::UnkType_10d97fa0()
{
    unk_10 = 1;
}
