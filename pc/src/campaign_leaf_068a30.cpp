// campaign_leaf_068a30.cpp -- free function at VA 0x10968a30: serialises the array of 2-byte
// elements its second argument refers to (data at 0x00, count at 0x04, capacity at 0x08) through
// the archive its first argument refers to: virtual slot 5 (vtable offset 0x14) with the byte sizes
// of the count and the capacity, the count through the free function at VA 0x10cd80b0, a
// reallocation to the count through virtual slot 1 of the allocator the global at VA 0x111c88a0
// points to (tagged "FArray::_WORD") when the archive's value at 0x18 is set, and virtual slot 1
// (vtable offset 0x04) with the data; returns the archive. The class, member and function names are
// invented; the offsets, the slots, the size, the tag and the addresses are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10968a30_Archive
{
public:
    virtual void Malloc();
    virtual void Realloc(void* Data, int Size);
    virtual void Free();
    virtual void VirtualSlot3();
    virtual void VirtualSlot4();
    virtual void VirtualSlot5(int Size, int MaxSize);

    unsigned char unk_04[0x14];
    int unk_18;
};

class UnkType_10968a30
{
public:
    unsigned short* unk_00;
    int unk_04;
    int unk_08;
};

void Unk_10cd80b0(UnkType_10968a30_Archive& Archive, int& Count);

// Unk_10968a30
UnkType_10968a30_Archive& Unk_10968a30(UnkType_10968a30_Archive& Archive, UnkType_10968a30& Array)
{
    Archive.VirtualSlot5(Array.unk_04 * sizeof(unsigned short),
                         Array.unk_08 * sizeof(unsigned short));
    Unk_10cd80b0(Archive, Array.unk_04);
    if ( Archive.unk_18 )
    {
        Array.unk_08 = Array.unk_04;
        Array.unk_00 = static_cast<unsigned short*>(GUnk_111c88a0->Realloc(
            Array.unk_00, Array.unk_04 * sizeof(unsigned short), L"FArray::_WORD"));
    }
    Archive.Realloc(Array.unk_00, Array.unk_04 * sizeof(unsigned short));
    return Archive;
}
