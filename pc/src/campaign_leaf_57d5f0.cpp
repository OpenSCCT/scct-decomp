// campaign_leaf_57d5f0.cpp -- thiscall method at VA 0x10e7d5f0: creates the helper object at 0x154
// on first use (0x9c bytes from the allocator, constructor at VA 0x10e7c100), registers it through
// the method at VA 0x10e7d4a0 and drops the creation reference, then passes its two arguments to
// the helper's method at VA 0x10e7bfd0. All names are invented.

#include "campaign_global_1131b3d8.h"

class UnkType_10e7d5f0_Helper
{
public:
    // UnkType_10e7d5f0_Helper::operator new
    // guess: allocates from the allocator with tag 0x22 and records the size at 0x04.
    static void* operator new(unsigned int Size)
    {
        UnkType_10e7d5f0_Helper* Helper =
            (UnkType_10e7d5f0_Helper*)GUnk_1131b3d8->VirtualSlot4(Size, 0x22);
        Helper->unk_04 = (unsigned short)Size;
        return Helper;
    }

    UnkType_10e7d5f0_Helper();
    virtual ~UnkType_10e7d5f0_Helper();

    void Unk_10e7bfd0(int First, int Second);

    // UnkType_10e7d5f0_Helper::Release
    void Release()
    {
        unk_06--;
        if ( unk_06 == 0 )
        {
            delete this;
        }
    }

    unsigned short unk_04;
    short unk_06;
    int unk_08[0x94 / 4];
};

class UnkType_10e7d5f0
{
public:
    void Unk_10e7d4a0(UnkType_10e7d5f0_Helper* Helper);
    void Unk_10e7d5f0(int First, int Second);

private:
    int unk_00[0x154 / 4];
    UnkType_10e7d5f0_Helper* unk_154;
};

// UnkType_10e7d5f0::Unk_10e7d5f0
void UnkType_10e7d5f0::Unk_10e7d5f0(int First, int Second)
{
    if ( !unk_154 )
    {
        unk_154 = new UnkType_10e7d5f0_Helper;
        Unk_10e7d4a0(unk_154);
        unk_154->Release();
    }
    unk_154->Unk_10e7bfd0(First, Second);
}
