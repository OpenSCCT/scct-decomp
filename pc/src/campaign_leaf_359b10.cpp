// campaign_leaf_359b10.cpp -- one function at file offset 0x359b10, preferred VA 0x10c59b10. It
// wraps an integer into the range 0-0xffff by adding or removing whole multiples of 0x10000. It
// has no this pointer. The function and parameter names are invented; the bytes are the
// binary's.

// Unk_10c59b10
int Unk_10c59b10(int Value)
{
    int Result = Value;

    if ( Value < 0 )
    {
        Result = Value + ( (unsigned int)( -1 - Value ) / 0x10000 + 1 ) * 0x10000;
    }
    if ( Result >= 0x10000 )
    {
        Result -= ( (unsigned int)Result / 0x10000 ) * 0x10000;
    }
    return Result;
}
