// campaign_leaf_475360.cpp -- one function at file offset 0x475360, preferred VA 0x10d75360. It
// counts the 0x18-byte entries at 0x28 (count at 0x30) whose two object pointers at 0x4 and 0x8
// are both set and disagree in their words at 0x1c, stores the count through Count when that is
// not null, and returns 1 when every entry was counted. The class, method, structure, member and
// parameter names are invented; the offsets and the bytes are the binary's.

struct UnkObject
{
    unsigned char unk_0[0x1c];
    int unk_1c;
};

struct UnkEntry
{
    int unk_0;
    UnkObject* unk_4;
    UnkObject* unk_8;
    unsigned char unk_c[0xc];
};

class UnkType_10d75360
{
public:
    int Unk_10d75360(unsigned int* Count) const;

    unsigned char unk_0[0x28];
    UnkEntry* unk_28;
    int unk_2c;
    unsigned int unk_30;
};

// UnkType_10d75360::Unk_10d75360
int UnkType_10d75360::Unk_10d75360(unsigned int* Count) const
{
    unsigned int Found = 0;
    unsigned int Index;

    for ( Index = 0; Index < unk_30; Index++ )
    {
        if ( unk_28[Index].unk_4 != 0 && unk_28[Index].unk_8 != 0
            && unk_28[Index].unk_4->unk_1c != unk_28[Index].unk_8->unk_1c )
        {
            Found++;
        }
    }
    if ( Count != 0 )
    {
        *Count = Found;
    }
    return Found == unk_30;
}
