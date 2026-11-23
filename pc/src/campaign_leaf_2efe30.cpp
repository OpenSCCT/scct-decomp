// campaign_leaf_2efe30.cpp -- method at VA 0x10befe30 taking an object: picks the object's 12 bytes at
// 0xe8 when bit 5 of its word at 0x2c is set, else those at 0x858 of its object at 0x2b4 when bit
// 6 is set, else returns 0; passes them with 0 to the method at VA 0x10befc90, and returns the word
// at 0x284 of the object at 0x404 for a result of 1 or of the object at 0x408 for 2, when that
// object is set; otherwise 0. The class, member and method names are invented; the offsets and the
// address are the binary's.

class UnkType_10befe30_2b4
{
public:
    unsigned char unk_00[0x858];
    int unk_858[3];
};

class UnkType_10befe30_Other
{
public:
    unsigned char unk_00[0x2c];
    int unk_2c;
    unsigned char unk_30[0xe8 - 0x30];
    int unk_e8[3];
    unsigned char unk_f4[0x2b4 - 0xf4];
    UnkType_10befe30_2b4* unk_2b4;
};

class UnkType_10befe30_Side
{
public:
    unsigned char unk_00[0x284];
    int unk_284;
};

class UnkType_10befe30
{
public:
    int Unk_10befe30(UnkType_10befe30_Other* Other);
    int Unk_10befc90(int* Location, int Flag);

private:
    unsigned char unk_00[0x404];
    UnkType_10befe30_Side* unk_404;
    UnkType_10befe30_Side* unk_408;
};

// UnkType_10befe30::Unk_10befe30
int UnkType_10befe30::Unk_10befe30(UnkType_10befe30_Other* Other)
{
    int Side;
    if ( Other->unk_2c & 0x20 )
    {
        Side = Unk_10befc90(Other->unk_e8, 0);
    }
    else if ( Other->unk_2c & 0x40 )
    {
        Side = Unk_10befc90(Other->unk_2b4->unk_858, 0);
    }
    else
    {
        return 0;
    }
    if ( Side == 1 )
    {
        if ( unk_404 )
        {
            return unk_404->unk_284;
        }
    }
    else if ( Side == 2 )
    {
        if ( unk_408 )
        {
            return unk_408->unk_284;
        }
    }
    return 0;
}
