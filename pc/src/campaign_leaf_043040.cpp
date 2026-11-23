// campaign_leaf_043040.cpp -- method at VA 0x10943040: calls the method at VA 0x1092cb60, clears
// bits 7 and 14 (mask 0x4080) of the value at 0xbfc and bit 29 (0x20000000) of the value at 0xc00;
// then, when the object at 0x3f8 exists and the value at 0x318 of the object its pointer at 0x424
// points to equals its value at 0x41c, clears that value. The class, member and method names are
// invented; the offsets, the bits and the address are the binary's.

class UnkType_10943040_424
{
public:
    unsigned char unk_000[0x318];
    int unk_318;
};

class UnkType_10943040_3f8
{
public:
    unsigned char unk_000[0x41c];
    int unk_41c;
    int unk_420;
    UnkType_10943040_424* unk_424;
};

class UnkType_10943040
{
public:
    void Unk_10943040();
    void Unk_1092cb60();

private:
    unsigned char unk_000[0x3f8];
    UnkType_10943040_3f8* unk_3f8;
    unsigned char unk_3fc[0xbfc - 0x3fc];
    unsigned int unk_bfc;
    unsigned int unk_c00;
};

// UnkType_10943040::Unk_10943040
void UnkType_10943040::Unk_10943040()
{
    Unk_1092cb60();
    unk_bfc &= ~0x4080;
    unk_c00 &= ~0x20000000;
    UnkType_10943040_3f8* Other = unk_3f8;
    if ( Other && Other->unk_424->unk_318 == Other->unk_41c )
    {
        Other->unk_424->unk_318 = 0;
    }
}
