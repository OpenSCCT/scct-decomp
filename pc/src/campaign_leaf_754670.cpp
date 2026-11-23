// campaign_leaf_754670.cpp -- one function at file offset 0x754670, preferred VA 0x11054670. It
// passes the first word of each 0x1c-byte entry of the array at 0x10 of the record, whose count
// is the word at 0x14, to the function at VA 0x11049880: a result of 2 returns 2 at once, a result
// other than 1 is remembered. It returns 0 when such a result was seen and 1 otherwise. The type
// and function names are invented; the offsets and the callee's address are the binary's.

struct UnkType_11054670_Entry
{
    void* unk_0;
    unsigned char unk_4[0x1c - 0x4];
};

struct UnkType_11054670
{
    unsigned char unk_0[0x10];
    UnkType_11054670_Entry* unk_10;
    int unk_14;
};

int Unk_11049880(void* Object);

// Unk_11054670
int Unk_11054670(UnkType_11054670* Record)
{
    UnkType_11054670_Entry* Entry;
    int Index;
    int Pending;

    Pending = 0;
    Entry = Record->unk_10;
    for ( Index = 0; Index < Record->unk_14; Index++, Entry++ )
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
