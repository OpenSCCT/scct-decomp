// campaign_leaf_3bf490.cpp -- a free function at VA 0x10cbf490 that passes its three arguments and
// then 0 and 0 to the free function at VA 0x10cbeb90. The function and parameter names are
// invented; the addresses are the binary's.

void Unk_10cbeb90(int First, int Second, int Third, int Fourth, int Fifth);

// Unk_10cbf490
void Unk_10cbf490(int First, int Second, int Third)
{
    Unk_10cbeb90(First, Second, Third, 0, 0);
}
