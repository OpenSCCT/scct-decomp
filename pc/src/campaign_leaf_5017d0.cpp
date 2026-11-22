// campaign_leaf_5017d0.cpp -- one function at file offset 0x5017d0, preferred VA 0x10e017d0.
// It passes Item to the virtual method in slot 1 of the object at offset 8 and returns Item. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10e017d0_Inner
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Item);
};

class UnkType_10e017d0
{
public:
    int unk_0;
    int unk_4;
    UnkType_10e017d0_Inner* unk_8;

    void* Unk_10e017d0(void* Item);
};

// UnkType_10e017d0::Unk_10e017d0
void* UnkType_10e017d0::Unk_10e017d0(void* Item)
{
    unk_8->VirtualSlot1(Item);
    return Item;
}
