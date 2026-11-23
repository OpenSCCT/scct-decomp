// campaign_leaf_1ad160.cpp -- thiscall method at VA 0x10aad160. It allocates an 8-byte record
// through slot 0 of the allocator at VA 0x111c88a0 (tag "Stream") with both words zeroed. When its
// fourth argument indexes the pointer array at 0x00 (count at 0x04), it stores that element in the
// record's second word and the result of the element's virtual slot 3, called with the first three
// arguments, in the first. It returns the record. The class, method and member names are
// invented.

#include "campaign_global_111c88a0.h"

// operator new
inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

class UnkType_10aad160_Item
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();
    virtual void VirtualSlot2();
    virtual int VirtualSlot3(int First, int Second, int Third);
};

struct UnkType_10aad160_Record
{
    // UnkType_10aad160_Record::UnkType_10aad160_Record
    UnkType_10aad160_Record()
        : unk_0(0), unk_4(0)
    {
    }

    int unk_0;
    UnkType_10aad160_Item* unk_4;
};

class UnkType_10aad160
{
public:
    UnkType_10aad160_Record* Unk_10aad160(int First, int Second, int Third, int Index);

private:
    UnkType_10aad160_Item** unk_00;
    int unk_04;
};

// UnkType_10aad160::Unk_10aad160
UnkType_10aad160_Record* UnkType_10aad160::Unk_10aad160(int First, int Second, int Third,
                                                        int Index)
{
    UnkType_10aad160_Record* Record = new(L"Stream") UnkType_10aad160_Record;
    if ( unk_04 > Index )
    {
        UnkType_10aad160_Item* Item = unk_00[Index];
        Record->unk_4 = Item;
        Record->unk_0 = Item->VirtualSlot3(First, Second, Third);
    }
    return Record;
}
