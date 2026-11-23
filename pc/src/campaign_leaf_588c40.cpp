// campaign_leaf_588c40.cpp -- cdecl function at VA 0x10e88c40: returns the single instance held in
// the global at VA 0x1131c0d4, creating it on first use (16 bytes from the allocator with tag 5)
// and passing it with the global's address to the cdecl function at VA 0x10e7eda0. The class has a
// base at 0x00 and a reference-counted base at 0x08 (one reference, count at 0x0e), whose inline
// constructor installs the vtable at VA 0x1114fec8; its own vtables are at VA 0x1114fef0 and VA
// 0x1114feec. All names are invented.

#include "campaign_global_1131b3d8.h"
#include "campaign_global_1131c0d4.h"

class UnkType_10e88c40_Base0
{
public:
    virtual void VirtualSlot0();

private:
    int unk_04;
};

struct UnkType_10e88c40_Count
{
    // UnkType_10e88c40_Count::UnkType_10e88c40_Count
    UnkType_10e88c40_Count()
        : unk_02(1)
    {
    }

    unsigned short unk_00;
    short unk_02;
};

class UnkType_10e88c40_Counted : public UnkType_10e88c40_Count
{
public:
    virtual void VirtualSlot0();
};

class UnkType_1131c0d4 : public UnkType_10e88c40_Base0, public UnkType_10e88c40_Counted
{
public:
    // UnkType_1131c0d4::operator new
    // guess: allocates from the allocator with tag 5 and records the size in the 16-bit word at
    // 0x04 of the new block.
    static void* operator new(unsigned int Size)
    {
        void* Block = GUnk_1131b3d8->VirtualSlot4(Size, 5);
        ((unsigned short*)Block)[2] = (unsigned short)Size;
        return Block;
    }

};

void Unk_10e7eda0(UnkType_10e88c40_Counted* Object, UnkType_1131c0d4** Slot);

// Unk_10e88c40
UnkType_1131c0d4* Unk_10e88c40()
{
    if ( !GUnk_1131c0d4 )
    {
        GUnk_1131c0d4 = new UnkType_1131c0d4;
        Unk_10e7eda0(GUnk_1131c0d4, &GUnk_1131c0d4);
    }
    return GUnk_1131c0d4;
}
