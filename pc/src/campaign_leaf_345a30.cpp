// campaign_leaf_345a30.cpp -- one function at file offset 0x345a30, preferred VA 0x10c45a30. It
// returns 0 when the method at 0x10bee910 fails for (Ar, Second); otherwise it passes every set
// object of the pointer array at 0x410 (count at 0x414) whose word at 0x1d0 is set to the method
// at 0x10993620 of Ar and returns 1. The class, method, member, local and parameter names are
// invented; the offsets and the bytes are the binary's.

class UnkType_10c45a30_Object
{
};

class UnkType_10c45a30_Item : public UnkType_10c45a30_Object
{
public:
    unsigned char unk_0[0x1d0];
    int unk_1d0;
};

class UnkType_10c45a30_Archive
{
public:
    void Unk_10993620(UnkType_10c45a30_Object* const& Object);
};

class UnkType_10c45a30
{
public:
    int Unk_10bee910(UnkType_10c45a30_Archive& Ar, int Second);
    int Unk_10c45a30(UnkType_10c45a30_Archive& Ar, int Second);

    unsigned char unk_0[0x410];
    UnkType_10c45a30_Item** unk_410;
    int unk_414;
};

// UnkType_10c45a30::Unk_10c45a30
int UnkType_10c45a30::Unk_10c45a30(UnkType_10c45a30_Archive& Ar, int Second)
{
    int Index;

    if ( Unk_10bee910(Ar, Second) )
    {
        for ( Index = 0; Index < unk_414; Index++ )
        {
            UnkType_10c45a30_Item* Item = unk_410[Index];

            if ( Item != 0 && Item->unk_1d0 != 0 )
            {
                Ar.Unk_10993620(Item);
            }
        }
        return 1;
    }
    return 0;
}
