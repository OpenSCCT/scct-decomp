// campaign_leaf_065920.cpp -- one function at file offset 0x65920, preferred VA 0x10965920. It
// returns 1 when its unsigned short argument is an ASCII digit, and 0 otherwise. It has no this
// pointer. The class, method and parameter names are invented; the offset and the bytes are the
// binary's.

class UnkType_10965920
{
public:
    static int UnkIsDigit(unsigned short Value);
};

// UnkType_10965920::UnkIsDigit
int UnkType_10965920::UnkIsDigit(unsigned short Value)
{
    if ( Value >= 0x30 && Value <= 0x39 )
    {
        return 1;
    }
    return 0;
}
