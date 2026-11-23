// campaign_leaf_35d2f0.cpp -- one function at file offset 0x35d2f0, preferred VA 0x10c5d2f0. It
// returns 0 when the method at 0x10bee910 fails for (Ar, Second); otherwise it passes each of the
// objects at 0x44c and 0x450 that is set and has its word at 0x1d0 set to the method at 0x10993620
// of Ar and returns 1. The class, method, member and parameter names are invented; the offsets
// and the bytes are the binary's.

class UnkType_10c5d2f0_Object
{
};

class UnkType_10c5d2f0_Item : public UnkType_10c5d2f0_Object
{
public:
    unsigned char unk_0[0x1d0];
    int unk_1d0;
};

class UnkType_10c5d2f0_Archive
{
public:
    void Unk_10993620(UnkType_10c5d2f0_Object* const& Object);
};

class UnkType_10c5d2f0
{
public:
    int Unk_10bee910(UnkType_10c5d2f0_Archive& Ar, int Second);
    int Unk_10c5d2f0(UnkType_10c5d2f0_Archive& Ar, int Second);

    unsigned char unk_0[0x44c];
    UnkType_10c5d2f0_Item* unk_44c;
    UnkType_10c5d2f0_Item* unk_450;
};

// UnkType_10c5d2f0::Unk_10c5d2f0
int UnkType_10c5d2f0::Unk_10c5d2f0(UnkType_10c5d2f0_Archive& Ar, int Second)
{
    if ( Unk_10bee910(Ar, Second) )
    {
        if ( unk_44c != 0 && unk_44c->unk_1d0 != 0 )
        {
            Ar.Unk_10993620(unk_44c);
        }
        if ( unk_450 != 0 && unk_450->unk_1d0 != 0 )
        {
            Ar.Unk_10993620(unk_450);
        }
        return 1;
    }
    return 0;
}
