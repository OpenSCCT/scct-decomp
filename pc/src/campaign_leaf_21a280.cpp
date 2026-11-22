// campaign_leaf_21a280.cpp -- one function at file offset 0x21a280, preferred VA 0x10b1a280. It
// returns the ones' complement of the ones'-complement sum of the 16-bit words of its buffer (an
// odd trailing byte added as is), folded to 16 bits: the Internet checksum. It has no this
// pointer. The function and parameter names are invented; the offset and the bytes are the
// binary's.

// Unk_10b1a280
unsigned short Unk_10b1a280(const unsigned short* Data, int Length)
{
    unsigned int Sum = 0;
    while ( Length > 1 )
    {
        Sum += *Data++;
        Length -= 2;
    }
    if ( Length )
    {
        Sum += *(const unsigned char*)Data;
    }
    Sum = ( Sum >> 16 ) + ( Sum & 0xffff );
    Sum += Sum >> 16;
    return (unsigned short)~Sum;
}
