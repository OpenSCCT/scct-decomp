// campaign_leaf_0a4d00.cpp -- one function at file offset 0xa4d00, preferred VA 0x109a4d00. For
// every non-null entry of the pointer array at offset 0x2b4 (count at 0x2b8) it clears the words at
// offsets 0x244 and 0x240 and the three lowest bits of the word at offset 0x128 and sets the word
// at offset 0x35c to 1; then it clears bit field 1 and sets bit field 0 of the word at offset
// 0x2dc. The class, method and member names are invented; the offset and the bytes are the
// binary's.

class UnkType_109a4d00_Item
{
public:
    unsigned char unk_0[0x128];
    int unk_128;
    unsigned char unk_12c[0x240 - 0x12c];
    int unk_240;
    int unk_244;
    unsigned char unk_248[0x35c - 0x248];
    int unk_35c;
};

class UnkType_109a4d00
{
public:
    unsigned char unk_0[0x2b4];
    UnkType_109a4d00_Item** unk_2b4;
    int unk_2b8;
    unsigned char unk_2bc[0x2dc - 0x2bc];
    unsigned int unk_2dc_0 : 1;
    unsigned int unk_2dc_1 : 1;

    void Unk_109a4d00();
};

// UnkType_109a4d00::Unk_109a4d00
void UnkType_109a4d00::Unk_109a4d00()
{
    for ( int i = 0; i < unk_2b8; i++ )
    {
        UnkType_109a4d00_Item* Item = unk_2b4[i];
        if ( Item )
        {
            Item->unk_244 = 0;
            Item->unk_240 = 0;
            Item->unk_128 &= ~7;
            Item->unk_35c = 1;
        }
    }
    unk_2dc_1 = 0;
    unk_2dc_0 = 1;
}
