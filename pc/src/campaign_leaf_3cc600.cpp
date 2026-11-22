// campaign_leaf_3cc600.cpp -- a free function at VA 0x10ccc600 that passes the wide string
// L"Errors", its three arguments, 0 and 0 to the free function at VA 0x10ccc4b0. The function and
// parameter names are invented; the addresses and the string are the binary's.

void Unk_10ccc4b0(const unsigned short* Section, int First, int Second, int Third, int Fourth,
    int Fifth);

// Unk_10ccc600
void Unk_10ccc600(int First, int Second, int Third)
{
    Unk_10ccc4b0(L"Errors", First, Second, Third, 0, 0);
}
