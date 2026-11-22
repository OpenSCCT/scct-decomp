// campaign_leaf_2d5f70.cpp -- one function at file offset 0x2d5f70, preferred VA 0x10bd5f70. It
// selects the 0x58-byte entry of the array at offset 0x2b4 by the word its argument points to, and
// returns 1 when a non-null entry of that entry's pointer array at offset 0x24 (count at 0x28) has
// bit 0x2 set in its byte at offset 0x3d8, else 0. The class, method and member names are
// invented; the offset and the bytes are the binary's.

class UnkType_10bd5f70_Item
{
public:
    unsigned char unk_0[0x3d8];
    unsigned char unk_3d8;
};

struct UnkType_10bd5f70_Group
{
    unsigned char unk_0[0x24];
    UnkType_10bd5f70_Item** unk_24;
    int unk_28;
    unsigned char unk_2c[0x58 - 0x2c];
};

class UnkType_10bd5f70
{
public:
    unsigned char unk_0[0x2b4];
    UnkType_10bd5f70_Group* unk_2b4;

    int Unk_10bd5f70(const int& Index);
};

// UnkType_10bd5f70::Unk_10bd5f70
int UnkType_10bd5f70::Unk_10bd5f70(const int& Index)
{
    UnkType_10bd5f70_Group* Group = &unk_2b4[Index];
    for ( int i = 0; i < Group->unk_28; i++ )
    {
        if ( Group->unk_24[i] && ( Group->unk_24[i]->unk_3d8 & 2 ) )
        {
            return 1;
        }
    }
    return 0;
}
