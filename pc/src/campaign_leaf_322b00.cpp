// campaign_leaf_322b00.cpp -- one function at file offset 0x322b00, preferred VA 0x10c22b00. It
// calls the method at 0x10c22910, empties the array at 0x94 (count at 0x98, capacity at 0x9c) by
// reallocating its data to zero bytes through virtual slot 1 of the allocator at 0x111c88a0 with
// the retail tag "FArray", and then, when the object at 0xa0 is set, calls its method at
// 0x10b7fd00 with 0 and with 1. The class, method and member names are invented; the offsets, the
// slot and the bytes are the binary's.

#include "campaign_global_111c88a0.h"

class UnkType_10c22b00_Child
{
public:
    void Unk_10b7fd00(int Value);
};

class UnkType_10c22b00
{
public:
    void Unk_10c22910();
    void Unk_10c22b00();

    unsigned char unk_0[0x94];
    void* unk_94;
    int unk_98;
    int unk_9c;
    UnkType_10c22b00_Child* unk_a0;
};

// UnkType_10c22b00::Unk_10c22b00
void UnkType_10c22b00::Unk_10c22b00()
{
    UnkType_10c22b00_Child* Child;

    Unk_10c22910();
    unk_98 = 0;
    unk_9c = 0;
    unk_94 = GUnk_111c88a0->Realloc(unk_94, 0, L"FArray");
    Child = unk_a0;
    if ( Child != 0 )
    {
        Child->Unk_10b7fd00(0);
        Child->Unk_10b7fd00(1);
    }
}
