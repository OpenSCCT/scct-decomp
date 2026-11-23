// campaign_leaf_1e1150.cpp -- thiscall method at VA 0x10ae1150. It calls its own virtual slot 1,
// frees every pointer held in the array at 0x08 (data, count, capacity) through slot 2 of the
// allocator at VA 0x111c88a0, then empties the array: count and capacity cleared and the data
// reallocated to zero bytes with the tag "FArray::AABTObject*". The class, method and member names
// are invented; the tag is the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10ae1150
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1();

    void Unk_10ae1150();

private:
    int unk_04;
    void** unk_08;
    int unk_0c;
    int unk_10;
};

// UnkType_10ae1150::Unk_10ae1150
void UnkType_10ae1150::Unk_10ae1150()
{
    VirtualSlot1();
    for ( int i = 0; i < unk_0c; i++ )
    {
        GUnk_111c88a0->Free(unk_08[i]);
    }
    unk_0c = 0;
    unk_10 = 0;
    unk_08 = (void**)GUnk_111c88a0->Realloc(unk_08, 0, L"FArray::AABTObject*");
}
