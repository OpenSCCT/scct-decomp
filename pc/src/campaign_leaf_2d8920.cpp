// campaign_leaf_2d8920.cpp -- one function at file offset 0x2d8920, preferred VA 0x10bd8920. When
// its argument has bit 0x20 set in the flags at offset 0x2c it returns the word at offset 0x3c of
// whichever of the two 0x58-byte entries at offset 0x320 holds the argument in its first word, or
// 0; when it has bit 0x40 set instead it returns the argument's word at offset 0x428; otherwise 0.
// The class, method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10bd8920_Item
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0x428 - 0x30];
    int unk_428;
};

struct UnkType_10bd8920_Entry
{
    UnkType_10bd8920_Item* unk_0;
    unsigned char unk_4[0x3c - 0x4];
    int unk_3c;
    unsigned char unk_40[0x58 - 0x40];
};

class UnkType_10bd8920
{
public:
    unsigned char unk_0[0x320];
    UnkType_10bd8920_Entry unk_320[2];

    int Unk_10bd8920(UnkType_10bd8920_Item* Item);
};

// UnkType_10bd8920::Unk_10bd8920
int UnkType_10bd8920::Unk_10bd8920(UnkType_10bd8920_Item* Item)
{
    if ( Item->unk_2c & 0x20 )
    {
        for ( int i = 0; i < 2; i++ )
        {
            if ( unk_320[i].unk_0 == Item )
            {
                return unk_320[i].unk_3c;
            }
        }
    }
    else if ( Item->unk_2c & 0x40 )
    {
        return Item->unk_428;
    }
    return 0;
}
