// campaign_leaf_770090.cpp -- one function at file offset 0x770090, preferred VA 0x11070090. For
// the row of 8-byte entries at its argument's index in the table at 0x38, it fills every entry's
// second word with a running offset (starting at the word at 0xa0 and growing by the sizes in the
// matching record of the table at 0x34) and copies it to the entry's first word; the count is at
// 0x74. The class, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkType_11070090_Sizes
{
    int unk_0;
    int unk_4;
    int unk_8[1];
};

struct UnkType_11070090_Record
{
    int unk_0;
    UnkType_11070090_Sizes* unk_4;
};

struct UnkType_11070090_Entry
{
    int unk_0;
    int unk_4;
};

class UnkType_11070090
{
public:
    void Unk_11070090(int Index);

    unsigned char unk_0[0x34];
    UnkType_11070090_Record* unk_34;
    UnkType_11070090_Entry** unk_38;
    unsigned char unk_3c[0x74 - 0x3c];
    unsigned int unk_74;
    unsigned char unk_78[0xa0 - 0x78];
    int unk_a0;
};

// UnkType_11070090::Unk_11070090
void UnkType_11070090::Unk_11070090(int Index)
{
    unsigned int Entry;

    for ( Entry = 0; Entry < unk_74; Entry++ )
    {
        if ( Entry == 0 )
        {
            unk_38[Index][0].unk_4 = unk_a0;
            unk_38[Index][0].unk_0 = unk_38[Index][0].unk_4;
        }
        else
        {
            unk_38[Index][Entry].unk_4 =
                unk_38[Index][Entry - 1].unk_4 + unk_34[Index].unk_4->unk_8[Entry];
            unk_38[Index][Entry].unk_0 = unk_38[Index][Entry].unk_4;
        }
    }
}
