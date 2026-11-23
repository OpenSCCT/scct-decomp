// campaign_leaf_755660.cpp -- one function at file offset 0x755660, preferred VA 0x11055660. It
// passes the first word of each 0x10-byte entry of the array at 0x30 of the record, whose count
// is the word at 0x34, to the function at VA 0x11049880: a result of 2 returns 2 at once, a result
// other than 1 is remembered. It returns 0 when such a result was seen and 1 otherwise. The type
// and function names are invented; the offsets and the callee's address are the binary's.

struct UnkType_11055660_Entry
{
    void* unk_0;
    unsigned char unk_4[0x10 - 0x4];
};

struct UnkType_11055660
{
    unsigned char unk_0[0x30];
    UnkType_11055660_Entry* unk_30;
    int unk_34;
};

int Unk_11049880(void* Object);

// Unk_11055660
int Unk_11055660(UnkType_11055660* Record)
{
    UnkType_11055660_Entry* Entry;
    int Index;
    int Pending;

    Pending = 0;
    Entry = Record->unk_30;
    for ( Index = 0; Index < Record->unk_34; Index++, Entry++ )
    {
        switch ( Unk_11049880(Entry->unk_0) )
        {
        case 1:
            break;
        case 2:
            return 2;
        default:
            Pending = 1;
            break;
        }
    }
    if ( Pending != 0 )
    {
        return 0;
    }
    return 1;
}
