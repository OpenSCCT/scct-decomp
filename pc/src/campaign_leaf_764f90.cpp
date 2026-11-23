// campaign_leaf_764f90.cpp -- one function at file offset 0x764f90, preferred VA 0x11064f90. It
// returns whether both the function at VA 0x1106f4e0 and then the function at VA 0x1106ee00
// return non-zero. The function names are invented; the offset and the addresses are the
// binary's.

int Unk_1106f4e0();
int Unk_1106ee00();

// Unk_11064f90
int Unk_11064f90()
{
    int Result;

    Result = Unk_1106f4e0();
    if ( Result != 0 )
    {
        Result = Unk_1106ee00() != 0;
    }
    return Result;
}
