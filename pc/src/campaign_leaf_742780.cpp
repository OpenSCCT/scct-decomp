// campaign_leaf_742780.cpp -- one function at file offset 0x742780, preferred VA 0x11042780. It
// calls the function at VA 0x11042250 with its argument and two zeros. The function names are
// invented; the offset and the callee's address are the binary's.

void Unk_11042250(int First, int Second, int Third);

// Unk_11042780
void Unk_11042780(int Value)
{
    Unk_11042250(Value, 0, 0);
}
