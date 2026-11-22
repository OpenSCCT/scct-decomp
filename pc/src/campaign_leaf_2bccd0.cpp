// campaign_leaf_2bccd0.cpp -- one function at file offset 0x2bccd0, preferred VA 0x10bbccd0. When
// its second argument is nonzero it stores its first argument at offset 0x614 if that slot is
// empty and the argument has bit 0x1 set in the byte at offset 0x36; otherwise it empties the slot
// if it holds the first argument. The class, method and member names are invented; the offset and
// the bytes are the binary's.

class UnkType_10bbccd0_Item
{
public:
    unsigned char unk_0[0x36];
    unsigned char unk_36;
};

class UnkType_10bbccd0
{
public:
    unsigned char unk_0[0x614];
    UnkType_10bbccd0_Item* unk_614;

    void Unk_10bbccd0(UnkType_10bbccd0_Item* Item, int Enable);
};

// UnkType_10bbccd0::Unk_10bbccd0
void UnkType_10bbccd0::Unk_10bbccd0(UnkType_10bbccd0_Item* Item, int Enable)
{
    if ( Enable )
    {
        if ( !unk_614 && ( Item->unk_36 & 1 ) )
        {
            unk_614 = Item;
        }
    }
    else if ( unk_614 == Item )
    {
        unk_614 = 0;
    }
}
