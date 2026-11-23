// campaign_leaf_583880.cpp -- cdecl function at VA 0x10e83880: returns the single instance held in
// the global at VA 0x1131c0bc, creating it on first use (16 bytes from the allocator with tag 5)
// and passing it with the global's address to the cdecl function at VA 0x10e7eda0. The class has a
// reference-counted base at 0x00 (one reference, count at 0x06) and a second base at 0x08 whose
// inline constructor installs the vtable at VA 0x1114f580; its own vtables are at VA 0x1114f5d0 and
// VA 0x1114f5c8. All names are invented.

#include "campaign_global_1131b3d8.h"
#include "campaign_global_1131c0bc.h"

struct UnkType_10e83880_Count
{
    // UnkType_10e83880_Count::UnkType_10e83880_Count
    UnkType_10e83880_Count()
        : unk_02(1)
    {
    }

    unsigned short unk_00;
    short unk_02;
};

class UnkType_10e83880_Counted : public UnkType_10e83880_Count
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10e83880_Base8
{
public:
    // UnkType_10e83880_Base8::UnkType_10e83880_Base8
    UnkType_10e83880_Base8()
    {
    }

    virtual void VirtualSlot0();
};

class UnkType_1131c0bc : public UnkType_10e83880_Counted, public UnkType_10e83880_Base8
{
public:
    // UnkType_1131c0bc::operator new
    // guess: allocates from the allocator with tag 5 and records the size in the 16-bit word at
    // 0x04 of the new block.
    static void* operator new(unsigned int Size)
    {
        void* Block = GUnk_1131b3d8->VirtualSlot4(Size, 5);
        ((unsigned short*)Block)[2] = (unsigned short)Size;
        return Block;
    }


private:
    int unk_0c;
};

void Unk_10e7eda0(UnkType_10e83880_Counted* Object, UnkType_1131c0bc** Slot);

// Unk_10e83880
UnkType_1131c0bc* Unk_10e83880()
{
    if ( !GUnk_1131c0bc )
    {
        GUnk_1131c0bc = new UnkType_1131c0bc;
        Unk_10e7eda0(GUnk_1131c0bc, &GUnk_1131c0bc);
    }
    return GUnk_1131c0bc;
}
