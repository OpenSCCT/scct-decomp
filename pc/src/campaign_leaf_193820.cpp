// campaign_leaf_193820.cpp -- free function at VA 0x10a93820: returns true when the byte at 0x2e4
// of its argument is set, and otherwise whether the float at 0x24c is above 2^-23 (the float
// epsilon). The class, member and function names are invented; the offsets and the constant are
// the binary's.

class UnkType_10a93820
{
public:
    char unk_0[0x24c];
    float unk_24c;
    char unk_250[0x2e4 - 0x250];
    unsigned char unk_2e4;
};

// Unk_10a93820
bool Unk_10a93820(UnkType_10a93820* Object)
{
    if ( Object->unk_2e4 )
    {
        return true;
    }
    return Object->unk_24c > 1.1920929e-07f;
}
