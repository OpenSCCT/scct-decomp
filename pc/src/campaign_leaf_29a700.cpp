// campaign_leaf_29a700.cpp -- one function at file offset 0x29a700, preferred VA 0x10b9a700. It
// returns 1 when its argument is non-null and appears in the chain of objects that starts at
// offset 0x764 of the object at offset 0x78 and is linked through offset 0x270; otherwise 0. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkLink
{
public:
    unsigned char unk_0[0x270];
    UnkLink* unk_270;
};

class UnkOwner
{
public:
    unsigned char unk_0[0x764];
    UnkLink* unk_764;
};

class UnkType_10b9a700
{
public:
    unsigned char unk_0[0x78];
    UnkOwner* unk_78;

    int Unk_10b9a700(UnkLink* Other);
};

// UnkType_10b9a700::Unk_10b9a700
int UnkType_10b9a700::Unk_10b9a700(UnkLink* Other)
{
    if ( Other )
    {
        for ( UnkLink* Link = unk_78->unk_764; Link; Link = Link->unk_270 )
        {
            if ( Other == Link )
            {
                return 1;
            }
        }
    }
    return 0;
}
