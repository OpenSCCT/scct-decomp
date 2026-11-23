// campaign_leaf_015d80.cpp -- method at VA 0x10915d80: calls the method at VA 0x1090ec40, then
// appends this object to the pointer array the global at VA 0x11317078 holds, growing its
// capacity to the new count plus three eighths plus 2 and reallocating its data through virtual
// slot 1 of the allocator the global at VA 0x111c88a0 points to, tagged "FArray", when the count
// passes it. The class and method names are invented; the constants and the addresses are the
// binary's.

#include "campaign_global_111c88a0.h"
#include "campaign_global_11317078.h"

class UnkType_10915d80
{
public:
    void Unk_10915d80();
    void Unk_1090ec40();
};

// UnkType_10915d80::Unk_10915d80
void UnkType_10915d80::Unk_10915d80()
{
    Unk_1090ec40();
    int Index = GUnk_11317078.unk_04++;
    if ( GUnk_11317078.unk_04 > GUnk_11317078.unk_08 )
    {
        GUnk_11317078.unk_08 = GUnk_11317078.unk_04 + 3 * GUnk_11317078.unk_04 / 8 + 2;
        GUnk_11317078.unk_00 = static_cast<void**>(GUnk_111c88a0->Realloc(
            GUnk_11317078.unk_00, GUnk_11317078.unk_08 * sizeof(void*), L"FArray"));
    }
    GUnk_11317078.unk_00[Index] = this;
}
