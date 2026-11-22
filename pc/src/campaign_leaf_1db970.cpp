// campaign_leaf_1db970.cpp -- one function at file offset 0x1db970, preferred VA 0x10adb970. It
// searches the pointer array at offset 0x3c (count at 0x40) for a non-null entry whose word at
// offset 0x18 equals its argument and returns that entry's word at offset 0x14, or 0. The class,
// method and member names are invented; the offset and the bytes are the binary's.

class UnkItem
{
public:
    unsigned char unk_0[0x14];
    int unk_14;
    int unk_18;
};

class UnkType_10adb970
{
public:
    unsigned char unk_0[0x3c];
    UnkItem** unk_3c;
    int unk_40;

    int Unk_10adb970(int Key);
};

// UnkType_10adb970::Unk_10adb970
int UnkType_10adb970::Unk_10adb970(int Key)
{
    for ( int i = 0; i < unk_40; i++ )
    {
        UnkItem* Item = unk_3c[i];
        if ( Item && Item->unk_18 == Key )
        {
            return Item->unk_14;
        }
    }
    return 0;
}
