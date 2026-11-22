// campaign_leaf_764f90.cpp -- free function at VA 0x11064f90: returns 0 when the function at
// VA 0x1106f4e0 returns 0, otherwise whether the function at VA 0x1106ee00 returns nonzero. All
// names are invented.

int Unk_1106f4e0();
int Unk_1106ee00();

// Unk_11064f90
int Unk_11064f90()
{
    int Result = Unk_1106f4e0();

    if ( Result )
    {
        Result = Unk_1106ee00() != 0;
    }
    return Result;
}
