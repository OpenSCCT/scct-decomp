// campaign_leaf_0c4110.cpp -- method at VA 0x109c4110 returning a 64-byte record: when the global
// at VA 0x11232794 is set, returns what the method at VA 0x1092bcd0 returns; otherwise, unless the
// byte at 0x2f4 is set, stores that result at 0x2b4 and sets the byte, then returns the record at
// 0x2b4. guess: a cached matrix. The class, structure and method names are invented; the offsets
// and the addresses are the binary's.

#include "campaign_global_11232794.h"

struct UnkType_109c4110_Matrix
{
    float unk_00[16];
};

class UnkType_109c4110
{
public:
    UnkType_109c4110_Matrix Unk_109c4110();
    UnkType_109c4110_Matrix Unk_1092bcd0();

private:
    unsigned char unk_00[0x2b4];
    UnkType_109c4110_Matrix unk_2b4;
    unsigned char unk_2f4;
};

// UnkType_109c4110::Unk_109c4110
UnkType_109c4110_Matrix UnkType_109c4110::Unk_109c4110()
{
    if ( GUnk_11232794 )
    {
        return Unk_1092bcd0();
    }
    if ( !unk_2f4 )
    {
        unk_2b4 = Unk_1092bcd0();
        unk_2f4 = 1;
    }
    return unk_2b4;
}
