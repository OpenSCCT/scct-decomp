// campaign_leaf_72fdf0.cpp -- one function at file offset 0x72fdf0, preferred VA 0x1102fdf0. It
// passes the format string at VA 0x111e17a4 and the word at 0x10 to the variadic runtime function
// at VA 0x10f364f2. The class, method and member names are invented; the offset and the addresses
// are the binary's.

#include "campaign_global_111e17a4.h"

extern "C" int __cdecl Unk_10f364f2(const char* Format, ...);

class UnkType_1102fdf0
{
public:
    void Unk_1102fdf0();

    unsigned char unk_0[0x10];
    int unk_10;
};

// UnkType_1102fdf0::Unk_1102fdf0
void UnkType_1102fdf0::Unk_1102fdf0()
{
    Unk_10f364f2(&GUnk_111e17a4, unk_10);
}
