// campaign_leaf_7556c0.cpp -- one function at file offset 0x7556c0, preferred VA 0x110556c0. It
// passes the first word of each 0x10-byte entry of the array at 0x30 of the record, whose count
// is the word at 0x34, and its second argument to the function at VA 0x11049920. The type and
// function names are invented; the offsets and the callee's address are the binary's.

struct UnkType_110556c0_Entry
{
    void* unk_0;
    unsigned char unk_4[0x10 - 0x4];
};

struct UnkType_110556c0
{
    unsigned char unk_0[0x30];
    UnkType_110556c0_Entry* unk_30;
    int unk_34;
};

void Unk_11049920(void* Object, int* Flags);

// Unk_110556c0
void Unk_110556c0(UnkType_110556c0* Record, int* Flags)
{
    UnkType_110556c0_Entry* Entry;
    int Index;

    Entry = Record->unk_30;
    for ( Index = 0; Index < Record->unk_34; Index++, Entry++ )
    {
        Unk_11049920(Entry->unk_0, Flags);
    }
}
