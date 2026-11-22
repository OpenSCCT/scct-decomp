// campaign_leaf_3e9350.cpp -- one function at file offset 0x3e9350, preferred VA 0x10ce9350. It
// returns 1 when the words First and Second point to agree in the bits of the mask at 0x54, a
// null Second standing for 0. The class, method, member and parameter names are invented; the
// offsets and the bytes are the binary's.

class UnkType_10ce9350
{
public:
    int Unk_10ce9350(const unsigned int* First, const unsigned int* Second) const;

    unsigned char unk_0[0x54];
    unsigned int unk_54;
};

// UnkType_10ce9350::Unk_10ce9350
int UnkType_10ce9350::Unk_10ce9350(const unsigned int* First, const unsigned int* Second) const
{
    return ( ( *First ^ ( Second != 0 ? *Second : 0 ) ) & unk_54 ) == 0;
}
