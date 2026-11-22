// campaign_leaf_3d2320.cpp -- a free function at VA 0x10cd2320 that passes its argument and the
// constant 0x23 to the function at VA 0x10cd0f40. The names are invented; the addresses and the
// constant are the binary's.

void Unk_10cd0f40(int Value, int Code);

// Unk_10cd2320
void Unk_10cd2320(int Value)
{
    Unk_10cd0f40(Value, 0x23);
}
