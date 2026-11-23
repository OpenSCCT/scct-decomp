// campaign_leaf_1ce020.cpp -- thiscall method at VA 0x10ace020. When the byte at 0x84 is set, it
// decrements the count at 0x8c, deletes its argument (destructor at VA 0x10ad1180, memory freed
// through slot 2 of the allocator at VA 0x111c88a0), and when the global word at VA 0x11232828 and
// the words at 0x8c and 0x88 are all zero calls the method at VA 0x10acde30 and the function at VA
// 0x10acdfa0. The class, function and member names are invented.

#include "campaign_global_111c88a0.h"
#include "campaign_global_11232828.h"

inline void operator delete(void* Original)
{
    GUnk_111c88a0->Free(Original);
}

class UnkType_10ace020_Item
{
public:
    ~UnkType_10ace020_Item();
};

void Unk_10acdfa0();

class UnkType_10ace020
{
public:
    void Unk_10ace020(UnkType_10ace020_Item* Item);
    void Unk_10acde30();

private:
    char unk_00[0x84];
    bool unk_84;
    int unk_88;
    int unk_8c;
};

// UnkType_10ace020::Unk_10ace020
void UnkType_10ace020::Unk_10ace020(UnkType_10ace020_Item* Item)
{
    if ( unk_84 )
    {
        unk_8c--;
        delete Item;
        if ( GUnk_11232828 == 0 && unk_8c == 0 && unk_88 == 0 )
        {
            Unk_10acde30();
            Unk_10acdfa0();
        }
    }
}
