// campaign_leaf_7914a0.cpp -- one function at file offset 0x7914a0, preferred VA 0x110914a0. It
// searches the 8-byte entries of the array at 0x4 (count at 0x8) for one whose first word is its
// first argument; when found it stores the entry's second word through its second argument and
// returns 0, otherwise it returns 1. The class, method and member names are invented; the offset
// and the bytes are the binary's.

struct UnkType_110914a0_Entry
{
    int unk_0;
    int unk_4;
};

class UnkType_110914a0
{
public:
    int Unk_110914a0(int Key, int* Value);

    int unk_0;
    UnkType_110914a0_Entry* unk_4;
    int unk_8;
};

// UnkType_110914a0::Unk_110914a0
int UnkType_110914a0::Unk_110914a0(int Key, int* Value)
{
    int Index;

    for ( Index = 0; Index < unk_8; Index++ )
    {
        if ( unk_4[Index].unk_0 == Key )
        {
            *Value = unk_4[Index].unk_4;
            return 0;
        }
    }
    return 1;
}
