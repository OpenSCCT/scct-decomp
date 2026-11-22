// campaign_leaf_5ea2f0.cpp -- one function at file offset 0x5ea2f0, preferred VA 0x10eea2f0. It
// maps 'A'-'Z' to 0-25, 'a'-'z' to 26-51 and '0'-'9' to 52-61, and every other character to 0:
// the base64 digit values without '+' and '/'. It does not read its this pointer. The class,
// method and parameter names are invented; the offset and the bytes are the binary's.

class UnkType_10eea2f0
{
public:
    int Unk_10eea2f0(char Digit);
};

// UnkType_10eea2f0::Unk_10eea2f0
int UnkType_10eea2f0::Unk_10eea2f0(char Digit)
{
    if ( Digit >= 'A' && Digit <= 'Z' )
    {
        return Digit - 'A';
    }
    if ( Digit >= 'a' && Digit <= 'z' )
    {
        return Digit - 'a' + 26;
    }
    if ( Digit >= '0' && Digit <= '9' )
    {
        return Digit - '0' + 52;
    }
    return 0;
}
