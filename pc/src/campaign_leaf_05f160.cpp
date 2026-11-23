// campaign_leaf_05f160.cpp -- free function at VA 0x1095f160: calls the free function at VA
// 0x1095de00 with the pointer held by the global at VA 0x111f55a8 and its argument, and returns 1.
// The function and global names are invented; the addresses are the binary's.

#include "campaign_global_111f55a8.h"

void Unk_1095de00(void* Object, int Arg);

// Unk_1095f160
int Unk_1095f160(int Arg)
{
    Unk_1095de00(GUnk_111f55a8, Arg);
    return 1;
}
