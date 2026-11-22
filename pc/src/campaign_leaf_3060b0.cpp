// campaign_leaf_3060b0.cpp -- one function at file offset 0x3060b0, preferred VA 0x10c060b0. When
// its argument is non-null it finds the 0x34-byte entry of the array at offset 0x378 (count at
// 0x37c) whose first word equals the argument's word at offset 0x4, stores the entry's index at
// offset 0x374 and copies the entry's word at offset 0xc to offset 0x35c. The class, method and
// member names are invented; the offset and the bytes are the binary's.

struct UnkType_10c060b0_Entry
{
    int unk_0;
    unsigned char unk_4[0xc - 0x4];
    int unk_c;
    unsigned char unk_10[0x34 - 0x10];
};

class UnkType_10c060b0_Item
{
public:
    int unk_0;
    int unk_4;
};

class UnkType_10c060b0
{
public:
    unsigned char unk_0[0x35c];
    int unk_35c;
    unsigned char unk_360[0x374 - 0x360];
    int unk_374;
    UnkType_10c060b0_Entry* unk_378;
    int unk_37c;

    UnkType_10c060b0_Entry* GetUnk378(int Index)
    {
        return ( Index >= 0 && Index < unk_37c ) ? &unk_378[Index] : 0;
    }

    void Unk_10c060b0(const UnkType_10c060b0_Item* Item);
};

// UnkType_10c060b0::Unk_10c060b0
void UnkType_10c060b0::Unk_10c060b0(const UnkType_10c060b0_Item* Item)
{
    if ( Item )
    {
        for ( int i = 0; i < unk_37c; i++ )
        {
            if ( unk_378[i].unk_0 == Item->unk_4 )
            {
                unk_374 = i;
                UnkType_10c060b0_Entry* Entry = GetUnk378(i);
                if ( Entry )
                {
                    unk_35c = Entry->unk_c;
                }
                return;
            }
        }
    }
}
