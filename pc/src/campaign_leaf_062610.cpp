// campaign_leaf_062610.cpp -- free function at VA 0x10962610 taking two values: when the object the
// global at VA 0x111f559c points to exists with its byte at 0x38 set, the free function at VA
// 0x109624d0 returns nonzero and the free function at VA 0x1095dee0 accepts the two values (with 0
// and 1), calls the free function at VA 0x1095b910 with 0 and the method at VA 0x10a3d2b0 of the
// object the global at VA 0x111f5554 points to, and returns the free function at VA 0x1095f180;
// otherwise returns 0. The class and function names are invented; the offsets and the addresses are
// the binary's.

#include "campaign_global_111f559c.h"
#include "campaign_global_111f5554.h"

class UnkType_10962610_111f559c
{
public:
    unsigned char unk_00[0x38];
    unsigned char unk_38;
};

class UnkType_10962610_111f5554
{
public:
    void Unk_10a3d2b0();
};

int Unk_109624d0();
int Unk_1095dee0(int Arg0, int Arg1, int Arg2, int Arg3);
void Unk_1095b910(int Value);
int Unk_1095f180();

// Unk_10962610
int Unk_10962610(int Arg0, int Arg1)
{
    UnkType_10962610_111f559c* Info = static_cast<UnkType_10962610_111f559c*>(GUnk_111f559c);
    if ( Info && Info->unk_38 && Unk_109624d0() && Unk_1095dee0(Arg0, Arg1, 0, 1) )
    {
        Unk_1095b910(0);
        static_cast<UnkType_10962610_111f5554*>(GUnk_111f5554)->Unk_10a3d2b0();
        return Unk_1095f180();
    }
    return 0;
}
