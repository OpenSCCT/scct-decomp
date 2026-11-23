// campaign_leaf_08ad00.cpp -- method at VA 0x1098ad00: when the object at 0x28 is set, releases it
// (decrements its 16-bit count at 0x06, deleting it through its virtual destructor when that
// reaches 0), clears the pointer and calls the free function at VA 0x10ab6c00. The class, member
// and function names are invented; the offsets and the address are the binary's.

#include "campaign_global_111f6870.h"

void Unk_10ab6c00();

class UnkType_1098ad00
{
public:
    void Unk_1098ad00();

private:
    unsigned char unk_00[0x28];
    UnkType_111f6870* unk_28;
};

// UnkType_1098ad00::Unk_1098ad00
void UnkType_1098ad00::Unk_1098ad00()
{
    if ( unk_28 )
    {
        unk_28->Release();
        unk_28 = 0;
        Unk_10ab6c00();
    }
}
