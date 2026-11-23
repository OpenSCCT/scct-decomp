// campaign_leaf_061670.cpp -- method at VA 0x10961670: calls virtual slot 8 (vtable offset 0x20),
// sets the byte at 0x15 to 5 and the value at 0x18 to -1, and returns the address of offset 0x08 in
// the object the pointer at 0x00 of the object at 0x20 points to. The class, member and method
// names are invented; the offsets, the constants and the slot are the binary's.

class UnkType_10961670_Data
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10961670_20
{
public:
    UnkType_10961670_Data* unk_00;
};

class UnkType_10961670
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
    virtual void VirtualSlot8();

    int* Unk_10961670();

private:
    unsigned char unk_04[0x11];
    unsigned char unk_15;
    unsigned char unk_16[2];
    int unk_18;
    int unk_1c;
    UnkType_10961670_20* unk_20;
};

// UnkType_10961670::Unk_10961670
int* UnkType_10961670::Unk_10961670()
{
    VirtualSlot8();
    unk_15 = 5;
    unk_18 = -1;
    return &unk_20->unk_00->unk_08;
}
