// campaign_leaf_317180.cpp -- one function at file offset 0x317180, preferred VA 0x10c17180. It
// returns 1 when bit 0x1 of the byte at offset 0x360 is set, or when an 8-byte entry of the array
// at offset 0x368 (count at 0x36c) has a non-null object, bit 0x1 set in its own flag byte, and
// both bits 0x1 and 0x2 set in the object's word at offset 0x41c; otherwise 0. The class, method
// and member names are invented; the offset and the bytes are the binary's.

class UnkType_10c17180_Item
{
public:
    unsigned char unk_0[0x41c];
    int unk_41c;
};

struct UnkType_10c17180_Entry
{
    UnkType_10c17180_Item* unk_0;
    unsigned char unk_4;
    unsigned char unk_5[3];
};

class UnkType_10c17180
{
public:
    unsigned char unk_0[0x360];
    unsigned char unk_360;
    unsigned char unk_361[0x368 - 0x361];
    UnkType_10c17180_Entry* unk_368;
    int unk_36c;

    int Unk_10c17180();
};

// UnkType_10c17180::Unk_10c17180
int UnkType_10c17180::Unk_10c17180()
{
    if ( unk_360 & 1 )
    {
        return 1;
    }
    for ( int i = 0; i < unk_36c; i++ )
    {
        UnkType_10c17180_Item* Item = unk_368[i].unk_0;
        if ( Item && ( unk_368[i].unk_4 & 1 ) && ( Item->unk_41c & 1 ) && ( Item->unk_41c & 2 ) )
        {
            return 1;
        }
    }
    return 0;
}
