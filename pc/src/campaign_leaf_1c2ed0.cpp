// campaign_leaf_1c2ed0.cpp -- one function at file offset 0x1c2ed0, preferred VA 0x10ac2ed0. It
// returns 0 when its first argument has bit 0x400000 set in the flags at offset 0x34 or its
// pointer array at offset 0x1f0 (count at 0x1f4) contains the second argument; otherwise 1. It has
// no this pointer. The class, method and member names are invented; the offset and the bytes are
// the binary's.

class UnkType_10ac2ed0
{
public:
    unsigned char unk_0[0x34];
    int unk_34;
    unsigned char unk_38[0x1f0 - 0x38];
    void** unk_1f0;
    int unk_1f4;

    static int Unk_10ac2ed0(UnkType_10ac2ed0* Object, void* Item);
};

// UnkType_10ac2ed0::Unk_10ac2ed0
int UnkType_10ac2ed0::Unk_10ac2ed0(UnkType_10ac2ed0* Object, void* Item)
{
    if ( Object->unk_34 & 0x400000 )
    {
        return 0;
    }
    for ( int i = 0; i < Object->unk_1f4; i++ )
    {
        if ( Object->unk_1f0[i] == Item )
        {
            return 0;
        }
    }
    return 1;
}
