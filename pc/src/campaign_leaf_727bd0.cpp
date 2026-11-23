// campaign_leaf_727bd0.cpp -- one function at file offset 0x727bd0, preferred VA 0x11027bd0. It
// passes the format string at VA 0x111e12c8 and the word at 0xc to the variadic runtime function
// at VA 0x10f364f2. The class, method and member names are invented; the offset and the addresses
// are the binary's.

#include "campaign_global_111e12c8.h"

extern "C" int __cdecl Unk_10f364f2(const char* Format, ...);

class UnkType_11027bd0
{
public:
    void Unk_11027bd0();

    unsigned char unk_0[0xc];
    int unk_c;
};

// UnkType_11027bd0::Unk_11027bd0
void UnkType_11027bd0::Unk_11027bd0()
{
    Unk_10f364f2(&GUnk_111e12c8, unk_c);
}
