// campaign_leaf_589550.cpp -- cdecl function at VA 0x10e89550: returns the single instance held in
// the global at VA 0x1131c0ec, creating it on first use (16 bytes from the allocator with tag 5)
// and passing it with the global's address to the cdecl function at VA 0x10e7eda0. The class has a
// reference-counted base at 0x00 (one reference, count at 0x06) and a second base at 0x08 whose
// inline constructor installs the vtable at VA 0x1114ffa4; its own vtables are at VA 0x1114ffc4 and
// VA 0x1114ffbc. All names are invented.

#include "campaign_global_1131b3d8.h"
#include "campaign_global_1131c0ec.h"

struct UnkType_10e89550_Count
{
    // UnkType_10e89550_Count::UnkType_10e89550_Count
    UnkType_10e89550_Count()
        : unk_02(1)
    {
    }

    unsigned short unk_00;
    short unk_02;
};

class UnkType_10e89550_Counted : public UnkType_10e89550_Count
{
public:
    virtual void VirtualSlot0();
};

class UnkType_10e89550_Base8
{
public:
    // UnkType_10e89550_Base8::UnkType_10e89550_Base8
    UnkType_10e89550_Base8()
    {
    }

    virtual void VirtualSlot0();
};

class UnkType_1131c0ec : public UnkType_10e89550_Counted, public UnkType_10e89550_Base8
{
public:
    // UnkType_1131c0ec::operator new
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

void Unk_10e7eda0(UnkType_10e89550_Counted* Object, UnkType_1131c0ec** Slot);

// Unk_10e89550
UnkType_1131c0ec* Unk_10e89550()
{
    if ( !GUnk_1131c0ec )
    {
        GUnk_1131c0ec = new UnkType_1131c0ec;
        Unk_10e7eda0(GUnk_1131c0ec, &GUnk_1131c0ec);
    }
    return GUnk_1131c0ec;
}
