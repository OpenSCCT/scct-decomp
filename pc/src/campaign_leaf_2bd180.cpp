// campaign_leaf_2bd180.cpp -- one function at file offset 0x2bd180, preferred VA 0x10bbd180. It
// resets the counter at offset 0x5b4 to zero when it is nonzero and bit 0x40 of the flags at
// offset 0x398 is clear, then increments the counter and sets that bit. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkType_10bbd180
{
public:
    unsigned char unk_0[0x398];
    int unk_398;
    unsigned char unk_39c[0x5b4 - 0x39c];
    int unk_5b4;

    void Unk_10bbd180();
};

// UnkType_10bbd180::Unk_10bbd180
void UnkType_10bbd180::Unk_10bbd180()
{
    if ( unk_5b4 && !( unk_398 & 0x40 ) )
    {
        unk_5b4 = 0;
    }
    unk_5b4++;
    unk_398 |= 0x40;
}
