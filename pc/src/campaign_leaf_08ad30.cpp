// campaign_leaf_08ad30.cpp -- method at VA 0x1098ad30: when the global at VA 0x111f6870 is set,
// releases the object at 0x28 (decrements its 16-bit count at 0x06, deleting it through its
// virtual destructor when that reaches 0), clears it and calls the free function at VA
// 0x10ab6c00; then moves the global into 0x28 and clears it, and releases the object the global
// at VA 0x111f6874 points to the same way and clears that global. The class, member and function
// names are invented; the offsets and the addresses are the binary's.

#include "campaign_global_111f6870.h"
#include "campaign_global_111f6874.h"

void Unk_10ab6c00();

class UnkType_1098ad30
{
public:
    void Unk_1098ad30();

private:
    unsigned char unk_00[0x28];
    UnkType_111f6870* unk_28;
};

// UnkType_1098ad30::Unk_1098ad30
void UnkType_1098ad30::Unk_1098ad30()
{
    if ( GUnk_111f6870 )
    {
        if ( unk_28 )
        {
            unk_28->Release();
            unk_28 = 0;
            Unk_10ab6c00();
        }
        unk_28 = GUnk_111f6870;
        GUnk_111f6870 = 0;
        if ( GUnk_111f6874 )
        {
            GUnk_111f6874->Release();
            GUnk_111f6874 = 0;
        }
    }
}
