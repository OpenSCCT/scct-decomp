// campaign_leaf_08b3d0.cpp -- method at VA 0x1098b3d0: calls the method at VA 0x10cd8ea0; then,
// when the object at 0x28 is set, releases it (decrements its 16-bit count at 0x06, deleting it
// through its virtual destructor when that reaches 0), clears the pointer and calls the free
// function at VA 0x10ab6c00. The class, member and function names are invented; the offsets and the
// addresses are the binary's.

#include "campaign_global_111f6870.h"

void Unk_10ab6c00();

class UnkType_1098b3d0
{
public:
    void Unk_1098b3d0();
    void Unk_10cd8ea0();

private:
    unsigned char unk_00[0x28];
    UnkType_111f6870* unk_28;
};

// UnkType_1098b3d0::Unk_1098b3d0
void UnkType_1098b3d0::Unk_1098b3d0()
{
    Unk_10cd8ea0();
    if ( unk_28 )
    {
        unk_28->Release();
        unk_28 = 0;
        Unk_10ab6c00();
    }
}
