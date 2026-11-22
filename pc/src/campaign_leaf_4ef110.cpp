// campaign_leaf_4ef110.cpp -- one function at file offset 0x4ef110, preferred VA 0x10def110.
// It makes the virtual call in slot 2 on the object at offset 4 and then clears that pointer.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10def110_Inner
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
};

class UnkType_10def110
{
public:
    int unk_0;
    UnkType_10def110_Inner* unk_4;

    void Unk_10def110();
};

// UnkType_10def110::Unk_10def110
void UnkType_10def110::Unk_10def110()
{
    unk_4->VirtualSlot2();
    unk_4 = 0;
}
