// campaign_leaf_19fcb0.cpp -- free function at VA 0x10a9fcb0: calls the free function at VA
// 0x10d86a90 with the value of the global at VA 0x111fa6d4 and its argument, and returns the
// result. The function and global names are invented; the addresses are the binary's.

#include "campaign_global_111fa6d4.h"

int Unk_10d86a90(int Value, int Arg);

// Unk_10a9fcb0
int Unk_10a9fcb0(int Arg)
{
    return Unk_10d86a90(GUnk_111fa6d4, Arg);
}
