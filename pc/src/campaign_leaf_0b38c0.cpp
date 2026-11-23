// campaign_leaf_0b38c0.cpp -- method at VA 0x109b38c0 taking an object (this is unused): returns 1
// when, for some entry of the object's array at 0xc8 (count at 0xcc), the function at VA 0x109b33f0
// returns an object with bit 1 of the flags at 0x38c set and a float at 0x378 above zero; otherwise
// returns 0. The class, member and method names are invented; the offsets and the address are the
// binary's.

class UnkType_109b38c0_Found
{
public:
    unsigned char unk_00[0x378];
    float unk_378;
    unsigned char unk_37c[0x38c - 0x37c];
    unsigned int unk_38c;
};

UnkType_109b38c0_Found* Unk_109b33f0(int Entry);

class UnkType_109b38c0_Source
{
public:
    unsigned char unk_00[0xc8];
    int* unk_c8;
    int unk_cc;
};

class UnkType_109b38c0
{
public:
    int Unk_109b38c0(UnkType_109b38c0_Source* Source);
};

// UnkType_109b38c0::Unk_109b38c0
int UnkType_109b38c0::Unk_109b38c0(UnkType_109b38c0_Source* Source)
{
    for ( int i = 0; i < Source->unk_cc; i++ )
    {
        UnkType_109b38c0_Found* Found = Unk_109b33f0(Source->unk_c8[i]);
        if ( Found && (Found->unk_38c & 1) && Found->unk_378 > 0.0f )
        {
            return 1;
        }
    }
    return 0;
}
