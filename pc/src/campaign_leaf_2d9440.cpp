// campaign_leaf_2d9440.cpp -- one function at file offset 0x2d9440, preferred VA 0x10bd9440. It
// returns 0 when the object in the first word of a 0x64-byte entry of its argument's array at
// offset 0x4f0 (count at 0x4f4) has bit 0x40 set in its byte at offset 0x2c and bit 0x8 in its
// byte at offset 0x744; otherwise 1. It does not read its this pointer. The class, method and
// member names are invented; the offset and the bytes are the binary's.

class UnkItem
{
public:
    unsigned char unk_0[0x2c];
    unsigned char unk_2c;
    unsigned char unk_2d[0x744 - 0x2d];
    unsigned char unk_744;
};

struct UnkEntry
{
    UnkItem* unk_0;
    unsigned char unk_4[0x64 - 0x4];
};

class UnkType_10bd9440
{
public:
    unsigned char unk_0[0x4f0];
    UnkEntry* unk_4f0;
    int unk_4f4;

    int Unk_10bd9440(const UnkType_10bd9440* Object);
};

// UnkType_10bd9440::Unk_10bd9440
int UnkType_10bd9440::Unk_10bd9440(const UnkType_10bd9440* Object)
{
    int Result = 1;
    for ( int i = 0; i < Object->unk_4f4; i++ )
    {
        UnkItem* Item = Object->unk_4f0[i].unk_0;
        if ( ( Item->unk_2c & 0x40 ) && ( Item->unk_744 & 8 ) )
        {
            Result = 0;
            break;
        }
    }
    return Result;
}
