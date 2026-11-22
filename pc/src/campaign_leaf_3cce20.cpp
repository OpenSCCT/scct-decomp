// campaign_leaf_3cce20.cpp -- one function at file offset 0x3cce20, preferred VA 0x10ccce20. It
// narrows a zero-terminated sixteen-bit string into the bytes at Dest, replacing characters
// above 0xff with 0x7f, and returns Dest; a null Source returns null. It has no this pointer. The
// function and parameter names are invented; the bytes are the binary's.

// Unk_10ccce20
char* Unk_10ccce20(char* Dest, const unsigned short* Source)
{
    int Index;

    if ( Source == 0 )
    {
        return 0;
    }
    for ( Index = 0; Source[Index] != 0; Index++ )
    {
        Dest[Index] = Source[Index] < 0x100 ? Source[Index] : 0x7f;
    }
    Dest[Index] = 0;
    return Dest;
}
