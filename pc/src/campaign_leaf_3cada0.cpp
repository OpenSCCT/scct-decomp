// campaign_leaf_3cada0.cpp -- a free function at VA 0x10ccada0 that passes its destination buffer,
// its count, the first pointer of the argument list its third argument points to, and the address
// of the rest of that list to the free function at VA 0x10f33887, returning its result. guess: a
// wide-character vsnprintf over an argument list that starts with the format. The function and
// parameter names are invented; the addresses are the binary's.

int Unk_10f33887(unsigned short* Dest, int Count, const unsigned short* Format, char* Args);

// Unk_10ccada0
int Unk_10ccada0(unsigned short* Dest, int Count, const unsigned short** Args)
{
    return Unk_10f33887(Dest, Count, *Args, (char*)( Args + 1 ));
}
