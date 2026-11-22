// campaign_leaf_3bf4b0.cpp -- a free function at VA 0x10cbf4b0 that passes its three arguments and
// then 1 and 0 to the free function at VA 0x10cbeb90. The function and parameter names are
// invented; the addresses are the binary's.

void Unk_10cbeb90(int First, int Second, int Third, int Fourth, int Fifth);

// Unk_10cbf4b0
void Unk_10cbf4b0(int First, int Second, int Third)
{
    Unk_10cbeb90(First, Second, Third, 1, 0);
}
