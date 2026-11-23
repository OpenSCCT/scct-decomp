// campaign_leaf_584e00.cpp -- thiscall method at VA 0x10e84e00: looks Key up with the method at VA
// 0x10e84cf0; when it is found, frees the matching entry of the array at 0x14 through the
// allocator's second virtual method, calls the method at VA 0x10e07450 on the matching entry of the
// array at 0x08, and removes both entries by moving each array's last entry into their place.
// Removed is set to whether Key was found, and returned. All names are invented; the addresses are
// the binary's.

#include "campaign_global_1131b3d8.h"

class UnkType_10e84e00_Entry
{
public:
    void Unk_10e07450();
};

class UnkType_10e84e00
{
public:
    bool* Unk_10e84e00(bool* Removed, int Key);

private:
    int Unk_10e84cf0(int Key);

    int unk_00;
    int unk_04;
    UnkType_10e84e00_Entry** unk_08;
    int unk_0c;
    int unk_10;
    void** unk_14;
    int unk_18;
};

// UnkType_10e84e00::Unk_10e84e00
bool* UnkType_10e84e00::Unk_10e84e00(bool* Removed, int Key)
{
    int Index = Unk_10e84cf0(Key);

    if ( Index == -1 )
    {
        *Removed = false;
        return Removed;
    }
    GUnk_1131b3d8->VirtualSlot1(unk_14[Index]);
    unk_08[Index]->Unk_10e07450();
    unk_18--;
    unk_14[Index] = unk_14[unk_18];
    unk_0c--;
    unk_08[Index] = unk_08[unk_0c];
    *Removed = true;
    return Removed;
}
