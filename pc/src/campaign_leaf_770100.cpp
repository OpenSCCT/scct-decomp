// campaign_leaf_770100.cpp -- one function at file offset 0x770100, preferred VA 0x11070100. It
// searches the 8-byte entries of the array at 0x30 (count at 0x74) for one whose first word is its
// argument, clears that word and returns 1; it returns 0 when there is none. The class, method and
// member names are invented; the offset and the bytes are the binary's.

struct UnkType_11070100_Entry
{
    void* unk_0;
    int unk_4;
};

class UnkType_11070100
{
public:
    int Unk_11070100(void* Value);

    unsigned char unk_0[0x30];
    UnkType_11070100_Entry* unk_30;
    unsigned char unk_34[0x74 - 0x34];
    unsigned int unk_74;
};

// UnkType_11070100::Unk_11070100
int UnkType_11070100::Unk_11070100(void* Value)
{
    unsigned int Index;

    for ( Index = 0; Index < unk_74; Index++ )
    {
        if ( unk_30[Index].unk_0 == Value )
        {
            unk_30[Index].unk_0 = 0;
            return 1;
        }
    }
    return 0;
}
