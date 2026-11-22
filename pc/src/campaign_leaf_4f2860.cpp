// campaign_leaf_4f2860.cpp -- one function at file offset 0x4f2860, preferred VA 0x10df2860.
// It returns the int at offset 0 when the method at 0x10df2380 returns true, and 0 otherwise;
// the same bytes as 0x4f2840. The class, method and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10df2860
{
public:
    int unk_0;

    bool Unk_10df2380();
    int Unk_10df2860();
};

// UnkType_10df2860::Unk_10df2860
int UnkType_10df2860::Unk_10df2860()
{
    if ( !Unk_10df2380() )
    {
        return 0;
    }
    return unk_0;
}
