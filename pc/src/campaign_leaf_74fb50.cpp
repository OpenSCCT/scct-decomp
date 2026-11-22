// campaign_leaf_74fb50.cpp -- one function at file offset 0x74fb50, preferred VA 0x1104fb50. It
// returns 2 when the function at VA 0x110583f0 returns non-zero for its argument, and 1
// otherwise. The function names are invented; the offset and the callee's address are the
// binary's.

int Unk_110583f0(int Value);

// Unk_1104fb50
int Unk_1104fb50(int Value)
{
    return Unk_110583f0(Value) ? 2 : 1;
}
