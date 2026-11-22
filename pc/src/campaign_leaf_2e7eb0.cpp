// campaign_leaf_2e7eb0.cpp -- one function at file offset 0x2e7eb0, preferred VA 0x10be7eb0. It
// returns 1 when its argument is non-null and appears in the chain of objects that starts at
// offset 0x764 of the object at offset 0x78 and is linked through offset 0x270; otherwise 0. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10be7eb0_Link
{
public:
    unsigned char unk_0[0x270];
    UnkType_10be7eb0_Link* unk_270;
};

class UnkType_10be7eb0_Owner
{
public:
    unsigned char unk_0[0x764];
    UnkType_10be7eb0_Link* unk_764;
};

class UnkType_10be7eb0
{
public:
    unsigned char unk_0[0x78];
    UnkType_10be7eb0_Owner* unk_78;

    int Unk_10be7eb0(UnkType_10be7eb0_Link* Other);
};

// UnkType_10be7eb0::Unk_10be7eb0
int UnkType_10be7eb0::Unk_10be7eb0(UnkType_10be7eb0_Link* Other)
{
    if ( Other )
    {
        for ( UnkType_10be7eb0_Link* Link = unk_78->unk_764; Link; Link = Link->unk_270 )
        {
            if ( Other == Link )
            {
                return 1;
            }
        }
    }
    return 0;
}
