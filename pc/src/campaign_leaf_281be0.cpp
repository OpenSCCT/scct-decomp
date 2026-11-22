// campaign_leaf_281be0.cpp -- one function at file offset 0x281be0, preferred VA 0x10b81be0. It
// returns 1 when a non-null entry of the pointer array at offset 0x11c (count at 0x120) has bit
// 0x8000 set in its flags at offset 0x2c and bit 0x8000000 in its flags at offset 0x28, is not the
// object at offset 0x6ec, and has a word other than -1 at offset 0x144; otherwise 0. The class,
// method and member names are invented; the offset and the bytes are the binary's.

class UnkType_10b81be0_Item
{
public:
    unsigned char unk_0[0x28];
    int unk_28;
    int unk_2c;
    unsigned char unk_30[0x144 - 0x30];
    int unk_144;
};

class UnkType_10b81be0
{
public:
    unsigned char unk_0[0x11c];
    UnkType_10b81be0_Item** unk_11c;
    int unk_120;
    unsigned char unk_124[0x6ec - 0x124];
    UnkType_10b81be0_Item* unk_6ec;

    int Unk_10b81be0();
};

// UnkType_10b81be0::Unk_10b81be0
int UnkType_10b81be0::Unk_10b81be0()
{
    for ( int i = 0; i < unk_120; i++ )
    {
        UnkType_10b81be0_Item* Item = unk_11c[i];
        if ( Item && ( Item->unk_2c & 0x8000 ) && ( Item->unk_28 & 0x8000000 ) && Item != unk_6ec
            && Item->unk_144 != -1 )
        {
            return 1;
        }
    }
    return 0;
}
