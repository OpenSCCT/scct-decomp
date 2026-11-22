// campaign_leaf_43a380.cpp -- constructor at VA 0x10d3a380 of a polymorphic class whose vtable is at
// VA 0x1113a9b4; constructs the member at offset 4 with the constructor at VA 0x10d282a0 and
// clears the dword at offset 0x18. All names are invented.

class UnkType_10d282a0
{
public:
    UnkType_10d282a0();

private:
    int unk_00;
};

class UnkType_10d3a380
{
public:
    UnkType_10d3a380();
    virtual void VirtualSlot0();

private:
    UnkType_10d282a0 unk_04;
    unsigned char unk_08[0x10];
    int unk_18;
};

// UnkType_10d3a380::UnkType_10d3a380
UnkType_10d3a380::UnkType_10d3a380()
{
    unk_18 = 0;
}
