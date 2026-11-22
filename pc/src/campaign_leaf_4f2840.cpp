// campaign_leaf_4f2840.cpp -- one function at file offset 0x4f2840, preferred VA 0x10df2840.
// It returns the int at offset 0 when the method at 0x10df2380 returns true, and 0 otherwise.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10df2840
{
public:
    int unk_0;

    bool Unk_10df2380();
    int Unk_10df2840();
};

// UnkType_10df2840::Unk_10df2840
int UnkType_10df2840::Unk_10df2840()
{
    if ( !Unk_10df2380() )
    {
        return 0;
    }
    return unk_0;
}
