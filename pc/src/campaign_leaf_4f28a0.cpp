// campaign_leaf_4f28a0.cpp -- one function at file offset 0x4f28a0, preferred VA 0x10df28a0.
// It returns the int at offset 0 when the method at 0x10df2550 returns true, and 0 otherwise.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10df28a0
{
public:
    int unk_0;

    bool Unk_10df2550();
    int Unk_10df28a0();
};

// UnkType_10df28a0::Unk_10df28a0
int UnkType_10df28a0::Unk_10df28a0()
{
    if ( !Unk_10df2550() )
    {
        return 0;
    }
    return unk_0;
}
