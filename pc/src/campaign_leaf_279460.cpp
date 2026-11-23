// campaign_leaf_279460.cpp -- function at VA 0x10b79460 taking a pointer slot by address and a
// value: when the slot is empty, allocates 0x54 bytes tagged L"CBriefing" through slot 0 of the
// allocator at VA 0x111c88a0, constructs the object there with the value through the constructor at
// VA 0x10b781b0 (null when the allocation fails), stores it in the slot, and calls its method at VA
// 0x10b78c60. The class and function names are invented; the size, the string and the addresses are
// the binary's.

#include "campaign_global_111c88a0.h"

// operator new
inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

class UnkType_10b79460_Briefing
{
public:
    UnkType_10b79460_Briefing(int Value);

    void Unk_10b78c60();

private:
    unsigned char unk_00[0x54];
};

// Unk_10b79460
void Unk_10b79460(UnkType_10b79460_Briefing*& Briefing, int Value)
{
    if ( !Briefing )
    {
        Briefing = new(L"CBriefing") UnkType_10b79460_Briefing(Value);
        Briefing->Unk_10b78c60();
    }
}
