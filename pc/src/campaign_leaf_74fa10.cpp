// campaign_leaf_74fa10.cpp -- one function at file offset 0x74fa10, preferred VA 0x1104fa10. It
// returns 2 when the function at VA 0x110583f0 returns non-zero for its argument, and 1
// otherwise. The function names are invented; the offset and the callee's address are the
// binary's.

int Unk_110583f0(int Value);

// Unk_1104fa10
int Unk_1104fa10(int Value)
{
    return Unk_110583f0(Value) ? 2 : 1;
}
