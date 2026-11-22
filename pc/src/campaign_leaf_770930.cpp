// campaign_leaf_770930.cpp -- one function at file offset 0x770930, preferred VA 0x11070930. Given
// a non-null value and an index below the count at 0x74, it stores the value in the first word of
// the 8-byte entry at that index of the array at 0x30 when that word is zero, and returns 1;
// otherwise it returns 0. The class, method and member names are invented; the offset and the
// bytes are the binary's.

struct UnkType_11070930_Entry
{
    void* unk_0;
    int unk_4;
};

class UnkType_11070930
{
public:
    int Unk_11070930(void* Value, unsigned int Index);

    unsigned char unk_0[0x30];
    UnkType_11070930_Entry* unk_30;
    unsigned char unk_34[0x74 - 0x34];
    unsigned int unk_74;
};

// UnkType_11070930::Unk_11070930
int UnkType_11070930::Unk_11070930(void* Value, unsigned int Index)
{
    if ( Value != 0 && Index < unk_74 && unk_30[Index].unk_0 == 0 )
    {
        unk_30[Index].unk_0 = Value;
        return 1;
    }
    return 0;
}
