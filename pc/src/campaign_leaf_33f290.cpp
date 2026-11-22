// campaign_leaf_33f290.cpp -- a member function at VA 0x10c3f290 that calls the member at VA
// 0x10cd79f0; then, when bit 0 of the flags at 0x4c is set, it stores 2 in the byte at 0x48; it
// clears that bit. The class, method and member names are invented; the offsets and addresses are
// the binary's.

class UnkType_10c3f290
{
public:
    void Unk_10cd79f0();
    void Unk_10c3f290();

private:
    unsigned char unk_00[0x48];
    unsigned char unk_48;
    unsigned char unk_49[3];
    unsigned int unk_4c;
};

// UnkType_10c3f290::Unk_10c3f290
void UnkType_10c3f290::Unk_10c3f290()
{
    Unk_10cd79f0();
    if ( unk_4c & 1 )
    {
        unk_48 = 2;
    }
    unk_4c &= ~1;
}
