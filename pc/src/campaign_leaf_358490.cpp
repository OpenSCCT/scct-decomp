// campaign_leaf_358490.cpp -- one function at file offset 0x358490, preferred VA 0x10c58490. It
// returns 0 when the method at 0x10bee910 fails for (Ar, Second); otherwise it passes each of the
// objects at 0x454 and 0x458 that is set and has its word at 0x1d0 set to the method at 0x10993620
// of Ar and returns 1. The class, method, member and parameter names are invented; the offsets
// and the bytes are the binary's.

class UnkType_10c58490_Object
{
};

class UnkType_10c58490_Item : public UnkType_10c58490_Object
{
public:
    unsigned char unk_0[0x1d0];
    int unk_1d0;
};

class UnkType_10c58490_Archive
{
public:
    void Unk_10993620(UnkType_10c58490_Object* const& Object);
};

class UnkType_10c58490
{
public:
    int Unk_10bee910(UnkType_10c58490_Archive& Ar, int Second);
    int Unk_10c58490(UnkType_10c58490_Archive& Ar, int Second);

    unsigned char unk_0[0x454];
    UnkType_10c58490_Item* unk_454;
    UnkType_10c58490_Item* unk_458;
};

// UnkType_10c58490::Unk_10c58490
int UnkType_10c58490::Unk_10c58490(UnkType_10c58490_Archive& Ar, int Second)
{
    if ( Unk_10bee910(Ar, Second) )
    {
        if ( unk_454 != 0 && unk_454->unk_1d0 != 0 )
        {
            Ar.Unk_10993620(unk_454);
        }
        if ( unk_458 != 0 && unk_458->unk_1d0 != 0 )
        {
            Ar.Unk_10993620(unk_458);
        }
        return 1;
    }
    return 0;
}
