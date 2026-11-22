// campaign_leaf_305a50.cpp -- one function at file offset 0x305a50, preferred VA 0x10c05a50. For
// every non-null entry of the pointer array at offset 0x34c (count at 0x350) it sets the byte at
// offset 0x2e4 to that entry's byte at offset 0x354 when its argument is nonzero, else to 0. The
// class, method and member names are invented; the offset and the bytes are the binary's.

class UnkItem
{
public:
    unsigned char unk_0[0x2e4];
    unsigned char unk_2e4;
    unsigned char unk_2e5[0x354 - 0x2e5];
    unsigned char unk_354;
};

class UnkType_10c05a50
{
public:
    unsigned char unk_0[0x34c];
    UnkItem** unk_34c;
    int unk_350;

    void Unk_10c05a50(int Enable);
};

// UnkType_10c05a50::Unk_10c05a50
void UnkType_10c05a50::Unk_10c05a50(int Enable)
{
    for ( int i = 0; i < unk_350; i++ )
    {
        UnkItem* Item = unk_34c[i];
        if ( Item )
        {
            Item->unk_2e4 = Enable ? Item->unk_354 : 0;
        }
    }
}
