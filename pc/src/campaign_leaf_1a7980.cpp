// campaign_leaf_1a7980.cpp -- destructor at VA 0x10aa7980. It installs the class's vtable (VA
// 0x110d9a98), calls the class's method at VA 0x10aa5e30 with 0, then destroys the array at 0xb0:
// the array's method at VA 0x10aa60d0 removes all its 0x18-byte elements, its data is freed through
// slot 2 of the allocator at VA 0x111c88a0, and its three words are cleared. The class, method and
// member names are invented.

#include "campaign_global_111c88a0.h"

class UnkType_10aa60d0
{
public:
    // UnkType_10aa60d0::~UnkType_10aa60d0
    ~UnkType_10aa60d0()
    {
        Unk_10aa60d0(0, unk_4, 0x18);
        if ( unk_0 )
        {
            GUnk_111c88a0->Free(unk_0);
        }
        unk_0 = 0;
        unk_4 = unk_8 = 0;
    }

    void Unk_10aa60d0(int Index, int Count, int ElementSize);

private:
    void* unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10aa7980
{
public:
    virtual ~UnkType_10aa7980();

    void Unk_10aa5e30(int Value);

private:
    char unk_04[0xb0 - 0x04];
    UnkType_10aa60d0 unk_b0;
};

// UnkType_10aa7980::~UnkType_10aa7980
UnkType_10aa7980::~UnkType_10aa7980()
{
    Unk_10aa5e30(0);
}
