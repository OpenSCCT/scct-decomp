// campaign_leaf_721180.cpp -- one function at file offset 0x721180, preferred VA 0x11021180. When
// the flag at 0x54 is set it calls the methods at VA 0x11021080 and VA 0x1101fb20 and clears the
// flag; it always returns true. The class, method and member names are invented; the offsets and
// the addresses are the binary's.

class UnkType_11021180
{
public:
    void Unk_1101fb20();
    void Unk_11021080();
    bool Unk_11021180();

    unsigned char unk_0[0x54];
    bool unk_54;
};

// UnkType_11021180::Unk_11021180
bool UnkType_11021180::Unk_11021180()
{
    if ( unk_54 )
    {
        Unk_11021080();
        Unk_1101fb20();
        unk_54 = false;
    }
    return true;
}
