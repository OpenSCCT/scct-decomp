// campaign_leaf_0013c0.cpp -- one function at file offset 0x13c0, preferred VA 0x109013c0. It
// subtracts 0x20 from the values 0x61-0x7a and 0xe0-0xfd (the ASCII lowercase letters and the
// Latin-1 range above them), and returns every other value unchanged, widened to int. It has no this
// pointer. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_109013c0
{
public:
    static int ToUpperChar(unsigned short Value);
};

// UnkType_109013c0::ToUpperChar
int UnkType_109013c0::ToUpperChar(unsigned short Value)
{
    if ( Value >= 0x61 && ( Value <= 0x7a || Value >= 0xe0 ) && Value <= 0xfd )
    {
        return Value - 0x20;
    }
    return Value;
}
