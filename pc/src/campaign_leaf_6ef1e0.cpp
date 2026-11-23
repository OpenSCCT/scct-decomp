// campaign_leaf_6ef1e0.cpp -- thiscall method at VA 0x10fef1e0: copies the XML declaration
// string into a local buffer and passes the buffer and its length without the terminator to
// virtual slot 2 (vtable offset 0x08) of the object at 0x08. guess: the object is an output
// stream and slot 2 writes bytes. The class, method and member names are invented; the offsets
// and the string are the binary's.

class UnkType_10fef1e0_Target
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2(const char* Data, int Length);
};

class UnkType_10fef1e0
{
public:
    void Unk_10fef1e0();

private:
    unsigned char unk_0[0x8];
    UnkType_10fef1e0_Target* unk_8;
};

// UnkType_10fef1e0::Unk_10fef1e0
void UnkType_10fef1e0::Unk_10fef1e0()
{
    char Declaration[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";

    unk_8->VirtualSlot2(Declaration, sizeof(Declaration) - 1);
}
