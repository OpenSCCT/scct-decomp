// campaign_leaf_57f2d0.cpp -- cdecl function at VA 0x10e7f2d0: returns the single instance held in
// the global at VA 0x1131c09c, creating it on first use (16 bytes from the allocator with tag 5)
// and passing it with the global's address to the cdecl function at VA 0x10e7eda0. The class has a
// base at 0x00 and a reference-counted base at 0x08 (one reference, count at 0x0e), whose inline
// constructor installs the vtable at VA 0x1114ef28; its own vtables are at VA 0x1114ef30 and VA
// 0x1114ef2c. All names are invented.

#include "campaign_global_1131b3d8.h"
#include "campaign_global_1131c09c.h"

class UnkType_10e7f2d0_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

struct UnkType_10e7f2d0_Count
{
    // UnkType_10e7f2d0_Count::UnkType_10e7f2d0_Count
    UnkType_10e7f2d0_Count()
        : unk_02(1)
    {
    }

    unsigned short unk_00;
    short unk_02;
};

class UnkType_10e7f2d0_Counted : public UnkType_10e7f2d0_Count
{
public:
    virtual void VirtualSlot0();
};

class UnkType_1131c09c : public UnkType_10e7f2d0_Base0, public UnkType_10e7f2d0_Counted
{
public:
    // UnkType_1131c09c::operator new
    // guess: allocates from the allocator with tag 5 and records the size in the 16-bit word at
    // 0x04 of the new block.
    static void* operator new(unsigned int Size)
    {
        void* Block = GUnk_1131b3d8->VirtualSlot4(Size, 5);
        ((unsigned short*)Block)[2] = (unsigned short)Size;
        return Block;
    }

};

void Unk_10e7eda0(UnkType_10e7f2d0_Counted* Object, UnkType_1131c09c** Slot);

// Unk_10e7f2d0
UnkType_1131c09c* Unk_10e7f2d0()
{
    if ( !GUnk_1131c09c )
    {
        GUnk_1131c09c = new UnkType_1131c09c;
        Unk_10e7eda0(GUnk_1131c09c, &GUnk_1131c09c);
    }
    return GUnk_1131c09c;
}
