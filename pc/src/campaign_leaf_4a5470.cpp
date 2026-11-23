// campaign_leaf_4a5470.cpp -- one function at file offset 0x4a5470, preferred VA 0x10da5470.
// It clears the int at offset 0x64 of the object at offset 0x14, makes the virtual call in slot 2
// on that object and then clears the pointer. The class, method and member names are invented;
// the offset and the bytes are the binary's.

class UnkType_10da5470_Item
{
public:
    unsigned char unk_4[0x60];
    int unk_64;

    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
};

class UnkType_10da5470
{
public:
    unsigned char unk_0[0x14];
    UnkType_10da5470_Item* unk_14;

    void Unk_10da5470();
};

// UnkType_10da5470::Unk_10da5470
void UnkType_10da5470::Unk_10da5470()
{
    unk_14->unk_64 = 0;
    unk_14->VirtualSlot2();
    unk_14 = 0;
}
