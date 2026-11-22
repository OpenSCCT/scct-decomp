// campaign_leaf_462240.cpp -- constructor at VA 0x10d62240 of a polymorphic class whose vtable is at
// VA 0x1113b6f8; runs the base constructor at VA 0x10d5af50, clears the dword at offset 0x50 and
// sets the byte at offset 0x54. All names are invented.

class UnkType_10d5af50
{
public:
    UnkType_10d5af50();
    virtual void VirtualSlot0();

private:
    unsigned char unk_04[0x4c];
};

class UnkType_10d62240 : public UnkType_10d5af50
{
public:
    UnkType_10d62240();
    virtual void VirtualSlot0();

private:
    int unk_50;
    bool unk_54;
};

// UnkType_10d62240::UnkType_10d62240
UnkType_10d62240::UnkType_10d62240()
{
    unk_50 = 0;
    unk_54 = true;
}
