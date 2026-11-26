// campaign_leaf_409ad0.cpp -- thiscall at VA 0x10d09ad0: passes the handle at offset 4, 0x406, 1
// and its two words packed low and high to the stdcall function pointer at VA 0x110b7408 when
// the global at VA 0x112327f8 is set, else to the one at VA 0x110b7404, and returns the result.
// All names are invented.

#include "campaign_leaf_409ad0.h"

class UnkType_10d09ad0
{
public:
    int Unk_10d09ad0(unsigned short Low, unsigned short High);

private:
    int unk_00;
    int unk_04;
};

// UnkType_10d09ad0::Unk_10d09ad0
int UnkType_10d09ad0::Unk_10d09ad0(unsigned short Low, unsigned short High)
{
    if (GUnk_112327f8) {
        return GUnk_110b7408(unk_04, 0x406, 1, (long)(Low | ((unsigned long)High << 16)));
    }
    return GUnk_110b7404(unk_04, 0x406, 1, (long)(Low | ((unsigned long)High << 16)));
}
