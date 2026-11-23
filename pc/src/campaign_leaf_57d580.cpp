// campaign_leaf_57d580.cpp -- thiscall method at VA 0x10e7d580: creates the helper object at 0x150
// on first use (0x28 bytes from the allocator, constructor at VA 0x10e71560), registers it through
// the method at VA 0x10e7d4a0 and drops the creation reference, then passes its two arguments to
// the helper's method at VA 0x10e71400. All names are invented.

#include "campaign_global_1131b3d8.h"

class UnkType_10e7d580_Helper
{
public:
    // UnkType_10e7d580_Helper::operator new
    // guess: allocates from the allocator with tag 0x22 and records the size at 0x04.
    static void* operator new(unsigned int Size)
    {
        UnkType_10e7d580_Helper* Helper =
            (UnkType_10e7d580_Helper*)GUnk_1131b3d8->VirtualSlot4(Size, 0x22);
        Helper->unk_04 = (unsigned short)Size;
        return Helper;
    }

    UnkType_10e7d580_Helper();
    virtual ~UnkType_10e7d580_Helper();

    void Unk_10e71400(int First, int Second);

    // UnkType_10e7d580_Helper::Release
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
    int unk_08[0x20 / 4];
};

class UnkType_10e7d580
{
public:
    void Unk_10e7d4a0(UnkType_10e7d580_Helper* Helper);
    void Unk_10e7d580(int First, int Second);

private:
    int unk_00[0x150 / 4];
    UnkType_10e7d580_Helper* unk_150;
};

// UnkType_10e7d580::Unk_10e7d580
void UnkType_10e7d580::Unk_10e7d580(int First, int Second)
{
    if ( !unk_150 )
    {
        unk_150 = new UnkType_10e7d580_Helper;
        Unk_10e7d4a0(unk_150);
        unk_150->Release();
    }
    unk_150->Unk_10e71400(First, Second);
}
