// campaign_leaf_501440.cpp -- one function at file offset 0x501440, preferred VA 0x10e01440. It
// finds Key in an open-addressed table of words at 0x0 whose index mask is at 0x8, starting at
// the slot (Key >> 4) * 0x9e3779b1 and probing linearly; it returns the slot, or mask + 1 when an
// empty slot ends the search. The class, method, member and parameter names are invented; the
// offsets, the constant and the bytes are the binary's.

class UnkType_10e01440
{
public:
    unsigned int Unk_10e01440(unsigned int Key) const;

    unsigned int* unk_0;
    int unk_4;
    unsigned int unk_8;
};

// UnkType_10e01440::Unk_10e01440
unsigned int UnkType_10e01440::Unk_10e01440(unsigned int Key) const
{
    unsigned int Slot = ( Key >> 4 ) * 0x9e3779b1 & unk_8;

    while ( unk_0[Slot] != 0 )
    {
        if ( unk_0[Slot] == Key )
        {
            return Slot;
        }
        Slot = ( Slot + 1 ) & unk_8;
    }
    return unk_8 + 1;
}
