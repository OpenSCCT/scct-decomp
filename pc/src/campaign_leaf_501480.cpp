// campaign_leaf_501480.cpp -- one function at file offset 0x501480, preferred VA 0x10e01480. It
// finds Key in an open-addressed table of words at 0x0 (index mask at 0x8, probing from
// (Key >> 4) * 0x9e3779b1) and, when found, stores the value kept mask + 1 words after the key's
// slot in Value and returns 0; it returns 1 when Key is absent. The class, method, member and
// parameter names are invented; the offsets, the constant and the bytes are the binary's.

class UnkType_10e01480
{
public:
    int UnkFind(unsigned int Key) const
    {
        int Slot = ( Key >> 4 ) * 0x9e3779b1 & unk_8;

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

    int Unk_10e01480(unsigned int Key, unsigned int* Value) const;

    unsigned int* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10e01480::Unk_10e01480
int UnkType_10e01480::Unk_10e01480(unsigned int Key, unsigned int* Value) const
{
    int Slot = UnkFind(Key);

    if ( Slot <= unk_8 )
    {
        *Value = unk_0[unk_8 + Slot + 1];
        return 0;
    }
    return 1;
}
