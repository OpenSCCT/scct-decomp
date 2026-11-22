// campaign_leaf_305b90.cpp -- one function at file offset 0x305b90, preferred VA 0x10c05b90. When
// bit 0x1 of the byte at offset 0x358 is set, it clears the byte at offset 0x2e4 of every non-null
// entry of the pointer array at offset 0x34c (count at 0x350). The class, method and member names
// are invented; the offset and the bytes are the binary's.

class UnkItem
{
public:
    unsigned char unk_0[0x2e4];
    unsigned char unk_2e4;
};

class UnkType_10c05b90
{
public:
    unsigned char unk_0[0x34c];
    UnkItem** unk_34c;
    int unk_350;
    unsigned char unk_354[0x358 - 0x354];
    unsigned char unk_358;

    void Unk_10c05b90();
};

// UnkType_10c05b90::Unk_10c05b90
void UnkType_10c05b90::Unk_10c05b90()
{
    if ( unk_358 & 1 )
    {
        for ( int i = 0; i < unk_350; i++ )
        {
            if ( unk_34c[i] )
            {
                unk_34c[i]->unk_2e4 = 0;
            }
        }
    }
}
