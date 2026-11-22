// campaign_leaf_19f210.cpp -- free function at VA 0x10a9f210: calls the free function at VA
// 0x10d86a90 with the value of the global at VA 0x111fa6d0 and its argument, and returns the
// result. The function and global names are invented; the addresses are the binary's.

extern int GUnk_111fa6d0;

int Unk_10d86a90(int Value, int Arg);

// Unk_10a9f210
int Unk_10a9f210(int Arg)
{
    return Unk_10d86a90(GUnk_111fa6d0, Arg);
}
