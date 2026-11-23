// campaign_leaf_2628b0.cpp -- a member function at VA 0x10b628b0: when the byte at 0x3c is set it
// calls the member at VA 0x10b64690, clears the ints at 0x78 to 0x98 and 0xac to 0xb8 and clears
// the byte at 0x3c. It returns true. The class, method and member names are invented; the offsets
// and addresses are the binary's.

class UnkType_10b628b0
{
public:
    void Unk_10b64690();
    bool Unk_10b628b0();

private:
    unsigned char unk_00[0x3c];
    bool unk_3c;
    unsigned char unk_3d[0x78 - 0x3d];
    int unk_78;
    int unk_7c;
    int unk_80;
    int unk_84;
    int unk_88;
    int unk_8c;
    int unk_90;
    int unk_94;
    int unk_98;
    unsigned char unk_9c[0xac - 0x9c];
    int unk_ac;
    int unk_b0;
    int unk_b4;
    int unk_b8;
};

// UnkType_10b628b0::Unk_10b628b0
bool UnkType_10b628b0::Unk_10b628b0()
{
    if ( unk_3c )
    {
        Unk_10b64690();
        unk_78 = 0;
        unk_7c = 0;
        unk_80 = 0;
        unk_84 = 0;
        unk_88 = 0;
        unk_8c = 0;
        unk_90 = 0;
        unk_94 = 0;
        unk_98 = 0;
        unk_ac = 0;
        unk_b0 = 0;
        unk_b4 = 0;
        unk_b8 = 0;
        unk_3c = false;
    }
    return true;
}
