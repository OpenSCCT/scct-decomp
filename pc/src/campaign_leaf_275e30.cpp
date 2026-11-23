// campaign_leaf_275e30.cpp -- method at VA 0x10b75e30 taking an object and a value: when the object
// is set and its vector of 60-byte entries at 0x68 holds any (count taken as a short), takes the
// entry at the short index at 0xa8 and, when that entry's member at 0x1c is set, stores the object
// at 0x10 and the value at 0x14 and calls the member's virtual slot 6 (vtable offset 0x18). The
// vector never allocates here, so the default allocator stands in. The class, member and method
// names are invented; the offsets, the slot and the vector of the compiler's library are the
// binary's.

#include <vector>

class UnkType_10b75e30_Handler
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5();
    virtual void VirtualSlot6();
};

class UnkType_10b75e30_Entry
{
public:
    unsigned char unk_00[0x1c];
    UnkType_10b75e30_Handler* unk_1c;
    unsigned char unk_20[0x3c - 0x20];
};

class UnkType_10b75e30_Object
{
public:
    unsigned char unk_00[0x68];
    std::vector<UnkType_10b75e30_Entry> unk_68;
    unsigned char unk_78[0xa8 - 0x78];
    short unk_a8;
};

class UnkType_10b75e30
{
public:
    void Unk_10b75e30(UnkType_10b75e30_Object* Object, int Value);

private:
    unsigned char unk_00[0x10];
    UnkType_10b75e30_Object* unk_10;
    int unk_14;
};

// UnkType_10b75e30::Unk_10b75e30
void UnkType_10b75e30::Unk_10b75e30(UnkType_10b75e30_Object* Object, int Value)
{
    if ( Object && (short)Object->unk_68.size() )
    {
        UnkType_10b75e30_Handler* Handler = Object->unk_68[Object->unk_a8].unk_1c;
        if ( Handler )
        {
            unk_10 = Object;
            unk_14 = Value;
            Handler->VirtualSlot6();
        }
    }
}
