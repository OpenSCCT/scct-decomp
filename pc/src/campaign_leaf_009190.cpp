// campaign_leaf_009190.cpp -- one function at file offset 0x9190, preferred VA 0x10909190. It adds
// 0x20 to the values 0x41-0x5a and 0xc0-0xdd (the ASCII uppercase letters and the Latin-1 range above
// them), and returns every other value unchanged, widened to int. It has no this pointer. The class,
// method and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10909190
{
public:
    static int ToLowerChar(unsigned short Value);
};

// UnkType_10909190::ToLowerChar
int UnkType_10909190::ToLowerChar(unsigned short Value)
{
    if ( ( Value >= 0x41 && Value <= 0x5a ) || ( Value >= 0xc0 && Value <= 0xdd ) )
    {
        return Value + 0x20;
    }
    return Value;
}
