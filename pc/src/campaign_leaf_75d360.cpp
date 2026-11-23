// campaign_leaf_75d360.cpp -- one function at file offset 0x75d360, preferred VA 0x1105d360. It
// returns 0 when the count at 0xc is positive. Otherwise it releases the entries at 0x1c through
// the stdcall function at VA 0x1103c870, allocates room for the given number of 8-byte entries
// through the stdcall function at VA 0x1103c830 (returning 0 when that fails), stores each given
// word in the first word of an entry, stores the number at 0x20 and the first argument at 0x14,
// and returns 1. The class and member names are invented; the offsets and the addresses are the
// binary's.

void __stdcall Unk_1103c870(void* Pointer);
void* __stdcall Unk_1103c830(unsigned int Size);

struct UnkType_1105d360_Entry
{
    int unk_0;
    int unk_4;
};

class UnkType_1105d360
{
public:
    int Unk_1105d360(int Value, int* Words, unsigned int Count);

    unsigned char unk_0[0xc];
    int unk_c;
    unsigned char unk_10[0x14 - 0x10];
    int unk_14;
    unsigned char unk_18[0x1c - 0x18];
    UnkType_1105d360_Entry* unk_1c;
    unsigned int unk_20;
};

// UnkType_1105d360::Unk_1105d360
int UnkType_1105d360::Unk_1105d360(int Value, int* Words, unsigned int Count)
{
    unsigned int Index;

    if ( unk_c > 0 )
    {
        return 0;
    }
    if ( unk_1c != 0 )
    {
        Unk_1103c870(unk_1c);
        unk_1c = 0;
        unk_20 = 0;
    }
    unk_1c = (UnkType_1105d360_Entry*)Unk_1103c830(Count * sizeof(UnkType_1105d360_Entry));
    if ( unk_1c == 0 )
    {
        return 0;
    }
    for ( Index = 0; Index < Count; Index++ )
    {
        unk_1c[Index].unk_0 = Words[Index];
    }
    unk_20 = Count;
    unk_14 = Value;
    return 1;
}
