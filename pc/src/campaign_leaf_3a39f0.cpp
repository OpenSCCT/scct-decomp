// campaign_leaf_3a39f0.cpp -- one function at file offset 0x3a39f0, preferred VA 0x10ca39f0. It
// packs an array of Count flags into a bit mask, bit i set when flag i is nonzero. It has no this
// pointer. The function and parameter names are invented; the bytes are the binary's.

// Unk_10ca39f0
int Unk_10ca39f0(const int* Flags, int Count)
{
    int Mask = 0;
    int Index;

    for ( Index = 0; Index < Count; Index++ )
    {
        if ( Flags[Index] != 0 )
        {
            Mask |= 1 << Index;
        }
    }
    return Mask;
}
