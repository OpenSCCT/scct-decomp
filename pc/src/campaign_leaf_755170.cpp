// campaign_leaf_755170.cpp -- one function at file offset 0x755170, preferred VA 0x11055170. It
// passes the first word of each 0x14-byte entry of the array at 0x40 of the record, whose count
// is the word at 0x44, and its second argument to the function at VA 0x11049920. The type and
// function names are invented; the offsets and the callee's address are the binary's.

struct UnkType_11055170_Entry
{
    void* unk_0;
    unsigned char unk_4[0x14 - 0x4];
};

struct UnkType_11055170
{
    unsigned char unk_0[0x40];
    UnkType_11055170_Entry* unk_40;
    int unk_44;
};

void Unk_11049920(void* Object, int* Flags);

// Unk_11055170
void Unk_11055170(UnkType_11055170* Record, int* Flags)
{
    UnkType_11055170_Entry* Entry;
    int Index;

    Entry = Record->unk_40;
    for ( Index = 0; Index < Record->unk_44; Index++, Entry++ )
    {
        Unk_11049920(Entry->unk_0, Flags);
    }
}
