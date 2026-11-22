// campaign_leaf_4f7750.cpp -- one function at file offset 0x4f7750, preferred VA 0x10df7750.
// It returns the int at offset 0 when the method at 0x10df7400 returns true, and 0 otherwise.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10df7750
{
public:
    int unk_0;

    bool Unk_10df7400();
    int Unk_10df7750();
};

// UnkType_10df7750::Unk_10df7750
int UnkType_10df7750::Unk_10df7750()
{
    if ( !Unk_10df7400() )
    {
        return 0;
    }
    return unk_0;
}
