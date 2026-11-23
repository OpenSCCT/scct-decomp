// campaign_leaf_583c70.cpp -- thiscall method at VA 0x10e83c70: returns the first entry of the
// pointer array at 0xe4 whose name (0x08) the function at VA 0x10dffc00 reports equal to Name, or
// to the string that VA 0x10dffe20 makes from the result of VA 0x10e00090 for Name (freed through
// the allocator's second virtual method after the test); null when none matches. guess: a lookup
// by name that also tries a converted spelling. All names are invented; the addresses are the
// binary's.

#include "campaign_global_1131b3d8.h"

int Unk_10dffc00(const unsigned short* First, const unsigned short* Second);
const unsigned short* Unk_10e00090(const unsigned short* Name);
unsigned short* Unk_10dffe20(const unsigned short* Text);

struct UnkType_10e83c70_Entry
{
    int unk_00;
    int unk_04;
    const unsigned short* unk_08;
};

struct UnkType_10e83c70_Array
{
    UnkType_10e83c70_Entry** unk_00;
    int unk_04;
    int unk_08;

    // UnkType_10e83c70_Array::Begin
    UnkType_10e83c70_Entry** Begin()
    {
        return unk_00;
    }

    // UnkType_10e83c70_Array::End
    UnkType_10e83c70_Entry** End()
    {
        return unk_00 + unk_04;
    }
};

class UnkType_10e83c70
{
public:
    UnkType_10e83c70_Entry* Unk_10e83c70(const unsigned short* Name);

private:
    int unk_00[0xe4 / 4];
    UnkType_10e83c70_Array unk_e4;
};

// UnkType_10e83c70::Unk_10e83c70
UnkType_10e83c70_Entry* UnkType_10e83c70::Unk_10e83c70(const unsigned short* Name)
{
    for ( UnkType_10e83c70_Entry** Entry = unk_e4.Begin(); Entry < unk_e4.End(); Entry++ )
    {
        const unsigned short* EntryName = (*Entry)->unk_08;

        if ( Unk_10dffc00(EntryName, Name) == 0 )
        {
            return *Entry;
        }

        unsigned short* Converted = Unk_10dffe20(Unk_10e00090(Name));

        EntryName = (*Entry)->unk_08;
        if ( Unk_10dffc00(EntryName, Converted) == 0 )
        {
            GUnk_1131b3d8->VirtualSlot1(Converted);
            return *Entry;
        }
        GUnk_1131b3d8->VirtualSlot1(Converted);
    }
    return 0;
}
