// campaign_leaf_2a4120.cpp -- one function at file offset 0x2a4120, preferred VA 0x10ba4120. It
// scans the index array at offset 0x590 (count at 0x594) from its second entry for the first index
// whose 0x3c-byte entry, in the array at offset 0x68 of the object at offset 0x518, lacks bit
// 0x1000 in its word at offset 0x2c; it stores that index and its position through its two
// arguments and returns 1, else returns 0. The class, method and member names are invented; the
// offset and the bytes are the binary's.

struct UnkType_10ba4120_Entry
{
    unsigned char unk_0[0x2c];
    int unk_2c;
    unsigned char unk_30[0x3c - 0x30];
};

class UnkType_10ba4120_Table
{
public:
    unsigned char unk_0[0x68];
    UnkType_10ba4120_Entry* unk_68;
};

class UnkType_10ba4120
{
public:
    unsigned char unk_0[0x518];
    UnkType_10ba4120_Table* unk_518;
    unsigned char unk_51c[0x590 - 0x51c];
    int* unk_590;
    int unk_594;

    int Unk_10ba4120(int* OutIndex, int* OutPosition);
};

// UnkType_10ba4120::Unk_10ba4120
int UnkType_10ba4120::Unk_10ba4120(int* OutIndex, int* OutPosition)
{
    for ( int i = 1; i < unk_594; i++ )
    {
        if ( !( unk_518->unk_68[unk_590[i]].unk_2c & 0x1000 ) )
        {
            *OutIndex = unk_590[i];
            *OutPosition = i;
            return 1;
        }
    }
    return 0;
}
