// campaign_leaf_4be5c0.cpp -- one function at file offset 0x4be5c0, preferred VA 0x10dbe5c0.
// It makes the virtual call in slot 1, repeats the virtual call in slot 2 until the int at offset
// 8 is set, and then makes the virtual call in slot 3; the argument is unused. The class, method,
// member and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10dbe5c0
{
public:
    int unk_4;
    int unk_8;

    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();

    void Unk_10dbe5c0(int Unused);
};

// UnkType_10dbe5c0::Unk_10dbe5c0
void UnkType_10dbe5c0::Unk_10dbe5c0(int Unused)
{
    VirtualSlot1();
    while ( unk_8 == 0 )
    {
        VirtualSlot2();
    }
    VirtualSlot3();
}
