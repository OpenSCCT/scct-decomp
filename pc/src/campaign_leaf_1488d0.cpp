// campaign_leaf_1488d0.cpp -- one function at file offset 0x1488d0, preferred VA 0x10a488d0.
// guess: binds the object at its argument: stores the argument at offset 0x7c, clears the member
// at 0x9c and, if it has none yet, creates its helper object at 0x80 (allocated through the
// allocator at VA 0x111c88a0 with the tag "FCanvasUtil", constructor at VA 0x10aa7670) from the
// argument and the argument's member at 0x190.
// The class, member and callee names are invented; the offset and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

inline void* operator new(unsigned int Size, const unsigned short* Tag)
{
    return GUnk_111c88a0->Malloc(Size, Tag);
}

class UnkType_10a488d0_Owner
{
public:
    unsigned char unk_0[0x190];
    void* unk_190;
};

class UnkType_10a488d0_Helper
{
public:
    unsigned char unk_0[0xbc];

    UnkType_10a488d0_Helper(UnkType_10a488d0_Owner* Owner, void* Second);
};

class UnkType_10a488d0
{
public:
    unsigned char unk_0[0x7c];
    UnkType_10a488d0_Owner* unk_7c;
    UnkType_10a488d0_Helper* unk_80;
    unsigned char unk_84[0x9c - 0x84];
    int unk_9c;

    void Unk_10a488d0(UnkType_10a488d0_Owner* Owner);
};

// UnkType_10a488d0::Unk_10a488d0
void UnkType_10a488d0::Unk_10a488d0(UnkType_10a488d0_Owner* Owner)
{
    unk_7c = Owner;
    unk_9c = 0;
    if ( !unk_80 )
    {
        unk_80 = new(L"FCanvasUtil") UnkType_10a488d0_Helper(unk_7c, unk_7c->unk_190);
    }
}
