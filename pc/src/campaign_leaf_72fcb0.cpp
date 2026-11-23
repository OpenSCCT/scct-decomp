// campaign_leaf_72fcb0.cpp -- one function at file offset 0x72fcb0, preferred VA 0x1102fcb0. It
// passes the format string at VA 0x111e12c8 and the word at 0xc to the variadic runtime function
// at VA 0x10f364f2; the function at 0x727bd0 has the same body. The class, method and member names
// are invented; the offset and the addresses are the binary's.

#include "campaign_global_111e12c8.h"

extern "C" int __cdecl Unk_10f364f2(const char* Format, ...);

class UnkType_1102fcb0
{
public:
    void Unk_1102fcb0();

    unsigned char unk_0[0xc];
    int unk_c;
};

// UnkType_1102fcb0::Unk_1102fcb0
void UnkType_1102fcb0::Unk_1102fcb0()
{
    Unk_10f364f2(&GUnk_111e12c8, unk_c);
}
