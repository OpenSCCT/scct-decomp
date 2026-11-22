// campaign_leaf_3d0d10.cpp -- one function at file offset 0x3d0d10, preferred VA 0x10cd0d10. It
// narrows Count sixteen-bit characters from Source into the bytes at Dest and returns Dest; a
// null Source leaves an empty string. It has no this pointer. The function and parameter names
// are invented; the bytes are the binary's.

// Unk_10cd0d10
char* Unk_10cd0d10(char* Dest, const unsigned short* Source, int Count)
{
    int Index;

    if ( Source != 0 )
    {
        for ( Index = 0; Index < Count; Index++ )
        {
            Dest[Index] = (char)Source[Index];
        }
        return Dest;
    }
    *Dest = 0;
    return Dest;
}
