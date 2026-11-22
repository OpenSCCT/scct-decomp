// campaign_leaf_4c2780.cpp -- one function at file offset 0x4c2780, preferred VA 0x10dc2780. It
// reduces a flag word to one representative flag: 0x80 or 0x100 when set, 1 or 0x40 when the
// word is exactly that, 4 when no bit outside 0xc is set, 2 when none outside 0xf is, 0x10 when
// none outside 0x7c is, otherwise 0x100. It has no this pointer. The function and parameter
// names are invented; the bytes are the binary's.

// Unk_10dc2780
int Unk_10dc2780(int Flags)
{
    if ( Flags & 0x80 )
    {
        return 0x80;
    }
    if ( Flags & 0x100 )
    {
        return 0x100;
    }
    if ( Flags == 1 )
    {
        return 1;
    }
    if ( Flags == 0x40 )
    {
        return 0x40;
    }
    if ( ( Flags | 0xc ) == 0xc )
    {
        return 4;
    }
    if ( ( Flags | 0xf ) == 0xf )
    {
        return 2;
    }
    return ( Flags | 0x7c ) == 0x7c ? 0x10 : 0x100;
}
