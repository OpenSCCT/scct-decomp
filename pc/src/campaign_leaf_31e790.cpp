// campaign_leaf_31e790.cpp -- one function at file offset 0x31e790, preferred VA 0x10c1e790. It
// returns the first 0x254-byte entry of the array at offset 0x880 (count at 0x884) of the object
// at offset 0x64 whose first byte equals its argument, or null. The class, method and member names
// are invented; the offset and the bytes are the binary's.

struct UnkEntry
{
    unsigned char unk_0;
    unsigned char unk_1[0x254 - 0x1];
};

class UnkList
{
public:
    unsigned char unk_0[0x880];
    UnkEntry* unk_880;
    int unk_884;
};

class UnkType_10c1e790
{
public:
    unsigned char unk_0[0x64];
    UnkList* unk_64;

    UnkEntry* Unk_10c1e790(int Value);
};

// UnkType_10c1e790::Unk_10c1e790
UnkEntry* UnkType_10c1e790::Unk_10c1e790(int Value)
{
    UnkList* List = unk_64;
    for ( int i = 0; i < List->unk_884; i++ )
    {
        if ( List->unk_880[i].unk_0 == Value )
        {
            return &List->unk_880[i];
        }
    }
    return 0;
}
