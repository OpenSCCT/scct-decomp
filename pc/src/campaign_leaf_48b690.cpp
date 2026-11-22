// campaign_leaf_48b690.cpp -- constructor at VA 0x10d8b690 of a polymorphic class whose vtable is at
// VA 0x1113cdec; runs the base constructor at VA 0x10dbf2c0 and sets the dword at offset 0x20
// to 0. All names are invented.

class UnkType_10dbf2c0
{
public:
    UnkType_10dbf2c0();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x1c];
};

class UnkType_10d8b690 : public UnkType_10dbf2c0
{
public:
    UnkType_10d8b690();
    virtual void VirtualSlot0();

private:
    int unk_20;
};

// UnkType_10d8b690::UnkType_10d8b690
UnkType_10d8b690::UnkType_10d8b690()
{
    unk_20 = 0;
}
