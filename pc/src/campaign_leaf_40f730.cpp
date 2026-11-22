// campaign_leaf_40f730.cpp -- one function at file offset 0x40f730, preferred VA 0x10d0f730. It
// returns 1 when either pointer array (data at 0x2c, count at 0x30; data at 0x38, count at 0x3c)
// holds an entry whose words at 0x4 and 0x0 equal First and Second. The class, method,
// structure, member and parameter names are invented; the offsets and the bytes are the
// binary's.

struct UnkType_10d0f730_Entry
{
    int unk_0;
    int unk_4;
};

class UnkType_10d0f730
{
public:
    int Unk_10d0f730(int First, int Second) const;

    unsigned char unk_0[0x2c];
    UnkType_10d0f730_Entry** unk_2c;
    int unk_30;
    int unk_34;
    UnkType_10d0f730_Entry** unk_38;
    int unk_3c;
};

// UnkType_10d0f730::Unk_10d0f730
int UnkType_10d0f730::Unk_10d0f730(int First, int Second) const
{
    int Index;

    for ( Index = 0; Index < unk_30; Index++ )
    {
        if ( unk_2c[Index]->unk_4 == First && unk_2c[Index]->unk_0 == Second )
        {
            return 1;
        }
    }
    for ( Index = 0; Index < unk_3c; Index++ )
    {
        if ( unk_38[Index]->unk_4 == First && unk_38[Index]->unk_0 == Second )
        {
            return 1;
        }
    }
    return 0;
}
