// campaign_leaf_29a680.cpp -- method at VA 0x10b9a680 taking an object: returns 1 when the object is
// set, bit 4 of its word at 0x2c is set, and either its word at 0x420 is not positive, its method
// at VA 0x10cd72b0 accepts a name built from L"s_Unconscious" by the constructor at VA 0x10cd4790,
// or bit 6 of 0x2c is set and the object at 0x161c has bit 1 of its word at 0x514 set; otherwise
// returns 0. The class, member and method names are invented; the offsets, the string and the
// addresses are the binary's.

class UnkType_10b9a680_Name
{
public:
    UnkType_10b9a680_Name(const unsigned short* Text, int Mode);

private:
    int unk_00;
};

class UnkType_10b9a680_161c
{
public:
    unsigned char unk_00[0x514];
    int unk_514;
};

class UnkType_10b9a680_Other
{
public:
    int Unk_10cd72b0(const UnkType_10b9a680_Name& Name);

    unsigned char unk_00[0x2c];
    int unk_2c;
    unsigned char unk_30[0x420 - 0x30];
    int unk_420;
    unsigned char unk_424[0x161c - 0x424];
    UnkType_10b9a680_161c* unk_161c;
};

class UnkType_10b9a680
{
public:
    int Unk_10b9a680(UnkType_10b9a680_Other* Other);
};

// UnkType_10b9a680::Unk_10b9a680
int UnkType_10b9a680::Unk_10b9a680(UnkType_10b9a680_Other* Other)
{
    if ( Other && ( Other->unk_2c & 0x10 ) )
    {
        if ( Other->unk_420 > 0 )
        {
            UnkType_10b9a680_Name Name(L"s_Unconscious", 1);
            if ( !Other->Unk_10cd72b0(Name)
                && !( ( Other->unk_2c & 0x40 ) && Other->unk_161c
                      && ( Other->unk_161c->unk_514 & 2 ) ) )
            {
                return 0;
            }
        }
        return 1;
    }
    return 0;
}
