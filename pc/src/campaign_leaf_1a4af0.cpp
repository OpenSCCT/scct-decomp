// campaign_leaf_1a4af0.cpp -- function at VA 0x10aa4af0 with no this pointer. Given a string and a
// flag it returns true when the string is 2 to 15 characters long (16 with the flag), starts with a
// letter unless the flag is set, and every character passes the function at VA 0x10aa4320 with
// the flag. The length comes from the function at VA 0x10ccadc0. The function name is invented.

int Unk_10ccadc0(const unsigned short* String);
bool Unk_10aa4320(unsigned short Character, bool Flag);

// Unk_10aa4af0
bool Unk_10aa4af0(const unsigned short* String, bool Flag)
{
    int Length = Unk_10ccadc0(String);
    if ( Length < 2 || Length > 15 + (Flag ? 1 : 0) )
    {
        return false;
    }
    if ( !Flag
         && !((String[0] >= 'a' && String[0] <= 'z') || (String[0] >= 'A' && String[0] <= 'Z')) )
    {
        return false;
    }
    for ( int i = 0; Length > i; i++ )
    {
        if ( !Unk_10aa4320(String[i], Flag) )
        {
            return false;
        }
    }
    return true;
}
