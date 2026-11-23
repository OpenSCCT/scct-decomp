// campaign_leaf_1e9ad0.cpp -- thiscall method at VA 0x10ae9ad0 taking an index and a flag. It
// returns null for a negative index or one past the end of the chosen array: the array of 8-byte
// entries at 0x88 (count at 0x8c) when the flag is set, the one at 0x7c (count at 0x80) when it
// is clear. Otherwise it looks the entry's first word up through the method at VA 0x10a759d0 of
// the global object at VA 0x111fa2e0 and returns the result. The class, method and member names
// are invented.

#include "campaign_global_111fa2e0.h"

struct UnkType_10ae9ad0_Entry
{
    int unk_0;
    int unk_4;
};

class UnkType_10ae9ad0
{
public:
    void* Unk_10ae9ad0(int Index, bool bFlag);

private:
    char unk_00[0x7c];
    UnkType_10ae9ad0_Entry* unk_7c;
    int unk_80;
    int unk_84;
    UnkType_10ae9ad0_Entry* unk_88;
    int unk_8c;
};

// UnkType_10ae9ad0::Unk_10ae9ad0
void* UnkType_10ae9ad0::Unk_10ae9ad0(int Index, bool bFlag)
{
    if ( Index < 0 )
    {
        return 0;
    }
    if ( bFlag )
    {
        if ( Index >= unk_8c )
        {
            return 0;
        }
        return GUnk_111fa2e0.Unk_10a759d0(unk_88[Index].unk_0);
    }
    if ( Index >= unk_80 )
    {
        return 0;
    }
    return GUnk_111fa2e0.Unk_10a759d0(unk_7c[Index].unk_0);
}
