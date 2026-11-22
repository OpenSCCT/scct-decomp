// campaign_leaf_29e450.cpp -- one function at file offset 0x29e450, preferred VA 0x10b9e450. When
// its argument is non-null and has bit 0x10 set in the flags at offset 0x2c, it returns the index
// of the first 0x64-byte entry of the array at offset 0x4f0 (count at 0x4f4) whose first word is
// the argument; otherwise -1. The class, method and member names are invented; the offset and the
// bytes are the binary's.

class UnkType_10b9e450;

struct UnkType_10b9e450_Entry
{
    UnkType_10b9e450* unk_0;
    unsigned char unk_4[0x64 - 0x4];
};

class UnkType_10b9e450
{
public:
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0x4f0 - 0x30];
    UnkType_10b9e450_Entry* unk_4f0;
    int unk_4f4;

    int Unk_10b9e450(UnkType_10b9e450* Other);
};

// UnkType_10b9e450::Unk_10b9e450
int UnkType_10b9e450::Unk_10b9e450(UnkType_10b9e450* Other)
{
    int Result = -1;
    if ( Other && ( Other->unk_2c & 0x10 ) )
    {
        for ( int i = 0; i < unk_4f4; i++ )
        {
            if ( unk_4f0[i].unk_0 == Other )
            {
                Result = i;
                break;
            }
        }
    }
    return Result;
}
