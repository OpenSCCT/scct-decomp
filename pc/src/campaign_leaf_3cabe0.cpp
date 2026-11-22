// campaign_leaf_3cabe0.cpp -- a free function at VA 0x10ccabe0 that returns whether the function at
// VA 0x10f330c5 returns 1 for its double argument. The function names are invented; the addresses
// are the binary's.

int Unk_10f330c5(double Value);

// Unk_10ccabe0
int Unk_10ccabe0(double Value)
{
    return Unk_10f330c5(Value) == 1;
}
