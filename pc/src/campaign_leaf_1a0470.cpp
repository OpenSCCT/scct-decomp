// campaign_leaf_1a0470.cpp -- free function at VA 0x10aa0470: calls the free function at VA
// 0x10d86a90 with the value of the global at VA 0x111fa6d8 and its argument, and returns the
// result. The function and global names are invented; the addresses are the binary's.

#include "campaign_global_111fa6d8.h"

int Unk_10d86a90(int Value, int Arg);

// Unk_10aa0470
int Unk_10aa0470(int Arg)
{
    return Unk_10d86a90(GUnk_111fa6d8, Arg);
}
