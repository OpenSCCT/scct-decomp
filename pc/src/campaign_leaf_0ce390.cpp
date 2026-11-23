// campaign_leaf_0ce390.cpp -- free function at VA 0x109ce390 taking an archive and a record: passes
// the three 16-bit counts at 0x00, 0x02 and 0x04 to virtual slot 1 of the archive with the size 2;
// when the word at 0x18 of the archive is set, allocates their sum in bytes for the pointer at 0x08
// through virtual slot 0 of the allocator global at VA 0x111c88a0 with the tag "AnalogTrackSmall";
// then passes that block and its size to slot 1. Returns the archive. The class, member and
// function names are invented; the offsets, the slots and the address are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109ce390_Archive
{
public:
    virtual void VirtualSlot0();
    virtual void VirtualSlot1(void* Data, int Length);

    unsigned char unk_04[0x18 - 0x04];
    int unk_18;
};

struct UnkType_109ce390
{
    unsigned short unk_00;
    unsigned short unk_02;
    unsigned short unk_04;
    void* unk_08;
};

// Unk_109ce390
UnkType_109ce390_Archive& Unk_109ce390(UnkType_109ce390_Archive& Archive, UnkType_109ce390& Track)
{
    Archive.VirtualSlot1(&Track.unk_00, sizeof(Track.unk_00));
    Archive.VirtualSlot1(&Track.unk_02, sizeof(Track.unk_02));
    Archive.VirtualSlot1(&Track.unk_04, sizeof(Track.unk_04));
    int Size = Track.unk_04 + Track.unk_02 + Track.unk_00;
    if ( Archive.unk_18 )
    {
        Track.unk_08 = GUnk_111c88a0->Malloc(Size, L"AnalogTrackSmall");
    }
    Archive.VirtualSlot1(Track.unk_08, Size);
    return Archive;
}
