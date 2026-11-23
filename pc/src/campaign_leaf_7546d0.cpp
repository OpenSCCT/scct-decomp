// campaign_leaf_7546d0.cpp -- one function at file offset 0x7546d0, preferred VA 0x110546d0. It
// passes the first word of each 0x1c-byte entry of the array at 0x10 of the record, whose count
// is the word at 0x14, and its second argument to the function at VA 0x11049920. The type and
// function names are invented; the offsets and the callee's address are the binary's.

struct UnkType_110546d0_Entry
{
    void* unk_0;
    unsigned char unk_4[0x1c - 0x4];
};

struct UnkType_110546d0
{
    unsigned char unk_0[0x10];
    UnkType_110546d0_Entry* unk_10;
    int unk_14;
};

void Unk_11049920(void* Object, int* Flags);

// Unk_110546d0
void Unk_110546d0(UnkType_110546d0* Record, int* Flags)
{
    UnkType_110546d0_Entry* Entry;
    int Index;

    Entry = Record->unk_10;
    for ( Index = 0; Index < Record->unk_14; Index++, Entry++ )
    {
        Unk_11049920(Entry->unk_0, Flags);
    }
}
