// campaign_leaf_1d0ff0.cpp -- destructor at VA 0x10ad0ff0. The body passes the blocks at 0x10 and
// 0x0c, when set, with the function at VA 0x10ad0c00 to the functions at VA 0x10eaab98 and VA
// 0x10eaab68; the array at 0x00 is then destroyed: its method at VA 0x10ad0e80 removes all its
// 0x34-byte elements, its data is freed through slot 2 of the allocator at VA 0x111c88a0, and its
// three words are cleared. The class, function and member names are invented.

#include "campaign_global_111c88a0.h"

void Unk_10ad0c00(void* Block);
void Unk_10eaab98(void* Block, void (*Callback)(void*));
void Unk_10eaab68(void* Block, void (*Callback)(void*));

class UnkType_10ad0e80
{
public:
    // UnkType_10ad0e80::~UnkType_10ad0e80
    ~UnkType_10ad0e80()
    {
        Unk_10ad0e80(0, unk_4, 0x34);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    void Unk_10ad0e80(int Index, int Count, int ElementSize);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10ad0ff0
{
public:
    ~UnkType_10ad0ff0();

private:
    UnkType_10ad0e80 unk_00;
    void* unk_0c;
    void* unk_10;
};

// UnkType_10ad0ff0::~UnkType_10ad0ff0
UnkType_10ad0ff0::~UnkType_10ad0ff0()
{
    if ( unk_10 )
    {
        Unk_10eaab98(unk_10, Unk_10ad0c00);
    }
    if ( unk_0c )
    {
        Unk_10eaab68(unk_0c, Unk_10ad0c00);
    }
}
