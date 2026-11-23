// campaign_leaf_349550.cpp -- one function at file offset 0x349550, preferred VA 0x10c49550. It
// returns 0 when the method at 0x10bee910 fails for (Ar, Second); otherwise it passes every set
// object of the pointer array at 0x47c (count at 0x480) whose word at 0x1d0 is set to the method
// at 0x10993620 of Ar and returns 1. The class, method, member, local and parameter names are
// invented; the offsets and the bytes are the binary's.

class UnkType_10c49550_Object
{
};

class UnkType_10c49550_Item : public UnkType_10c49550_Object
{
public:
    unsigned char unk_0[0x1d0];
    int unk_1d0;
};

class UnkType_10c49550_Archive
{
public:
    void Unk_10993620(UnkType_10c49550_Object* const& Object);
};

class UnkType_10c49550
{
public:
    int Unk_10bee910(UnkType_10c49550_Archive& Ar, int Second);
    int Unk_10c49550(UnkType_10c49550_Archive& Ar, int Second);

    unsigned char unk_0[0x47c];
    UnkType_10c49550_Item** unk_47c;
    int unk_480;
};

// UnkType_10c49550::Unk_10c49550
int UnkType_10c49550::Unk_10c49550(UnkType_10c49550_Archive& Ar, int Second)
{
    int Index;

    if ( Unk_10bee910(Ar, Second) )
    {
        for ( Index = 0; Index < unk_480; Index++ )
        {
            UnkType_10c49550_Item* Item = unk_47c[Index];

            if ( Item != 0 && Item->unk_1d0 != 0 )
            {
                Ar.Unk_10993620(Item);
            }
        }
        return 1;
    }
    return 0;
}
