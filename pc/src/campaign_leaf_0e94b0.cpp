// campaign_leaf_0e94b0.cpp -- free function at VA 0x109e94b0 taking an archive and a dynamic array
// of 48-byte elements (data pointer at 0x00, count at 0x04, capacity at 0x08): calls virtual slot 5
// of the archive with the byte sizes of the count and the capacity and passes the count to the
// function at VA 0x10cd80b0; when the word at 0x18 of the archive is set, makes the capacity the
// count and reallocates the data through virtual slot 1 of the allocator global at VA 0x111c88a0
// with the tag "FArray"; then writes or reads all the data through virtual slot 1 of the archive
// and returns it. The class, member and function names are invented; the offsets, the slots and the
// addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_109e94b0_Archive
{
public:
    virtual void Malloc();
    virtual void Realloc(void* Data, int Length);
    virtual void Free();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Count, int Max);

    unsigned char unk_04[0x18 - 0x04];
    int unk_18;
};

struct UnkType_109e94b0_Element
{
    unsigned char unk_00[0x30];
};

class UnkType_109e94b0
{
public:
    UnkType_109e94b0_Element* unk_00;
    int unk_04;
    int unk_08;
};

UnkType_109e94b0_Archive& Unk_10cd80b0(UnkType_109e94b0_Archive& Archive, int& Value);

// Unk_109e94b0
UnkType_109e94b0_Archive& Unk_109e94b0(UnkType_109e94b0_Archive& Archive, UnkType_109e94b0& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(UnkType_109e94b0_Element),
                         Array.unk_08 * sizeof(UnkType_109e94b0_Element));
    Unk_10cd80b0(Archive, Array.unk_04);
    if ( Archive.unk_18 )
    {
        Array.unk_08 = Array.unk_04;
        Array.unk_00 = (UnkType_109e94b0_Element*)GUnk_111c88a0->Realloc(
            Array.unk_00, Array.unk_04 * sizeof(UnkType_109e94b0_Element), L"FArray");
    }
    Archive.Realloc(Array.unk_00, Array.unk_04 * sizeof(UnkType_109e94b0_Element));
    return Archive;
}
