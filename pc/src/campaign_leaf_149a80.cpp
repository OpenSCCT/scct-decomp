// campaign_leaf_149a80.cpp -- one function at file offset 0x149a80, preferred VA 0x10a49a80. It
// looks up the 16-bit key its argument points to in a chained hash: the bucket is the key masked
// by the bucket count at offset 0x10 less one, the bucket heads at offset 0xc, and the 8-byte
// entries (next index, key, value) at offset 0. It returns the address of the matching entry's
// value, or null. The class, method and member names are invented; the offset and the bytes are
// the binary's.

struct UnkHashEntry
{
    int unk_0;
    unsigned short unk_4;
    unsigned short unk_6;
};

class UnkType_10a49a80
{
public:
    UnkHashEntry* unk_0;
    int unk_4;
    int unk_8;
    int* unk_c;
    int unk_10;

    unsigned short* Unk_10a49a80(const unsigned short& Key);
};

// UnkType_10a49a80::Unk_10a49a80
unsigned short* UnkType_10a49a80::Unk_10a49a80(const unsigned short& Key)
{
    for ( int i = unk_c[Key & ( unk_10 - 1 )]; i != -1; i = unk_0[i].unk_0 )
    {
        if ( unk_0[i].unk_4 == Key )
        {
            return &unk_0[i].unk_6;
        }
    }
    return 0;
}
