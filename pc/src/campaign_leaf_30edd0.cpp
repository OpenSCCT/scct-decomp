// campaign_leaf_30edd0.cpp -- one function at file offset 0x30edd0, preferred VA 0x10c0edd0. When
// bit 0x1 of the byte at offset 0x2cc is set it returns 1 if an entry of the 0x10-byte array at
// offset 0x2b4 (count at 0x2b8) lacks bit 0x1 in its byte at offset 0x8, has a non-zero first word
// and either the value its argument refers to or its byte at offset 0x4 is 2 or the two are equal;
// otherwise 0. The class, method and member names are invented; the offset and the bytes are the
// binary's.

struct UnkType_10c0edd0_Entry
{
    int unk_0;
    unsigned char unk_4;
    unsigned char unk_5[0x8 - 0x5];
    unsigned char unk_8;
    unsigned char unk_9[0x10 - 0x9];
};

class UnkType_10c0edd0
{
public:
    unsigned char unk_0[0x2b4];
    UnkType_10c0edd0_Entry* unk_2b4;
    int unk_2b8;
    unsigned char unk_2bc[0x2cc - 0x2bc];
    unsigned char unk_2cc;

    int Unk_10c0edd0(const int* Value);
};

// UnkType_10c0edd0::Unk_10c0edd0
int UnkType_10c0edd0::Unk_10c0edd0(const int* Value)
{
    if ( !( unk_2cc & 1 ) )
    {
        return 0;
    }
    for ( int i = 0; i < unk_2b8; i++ )
    {
        UnkType_10c0edd0_Entry* Entry = &unk_2b4[i];
        if ( Entry && !( Entry->unk_8 & 1 ) && Entry->unk_0
            && ( *Value == 2 || Entry->unk_4 == 2 || *Value == Entry->unk_4 ) )
        {
            return 1;
        }
    }
    return 0;
}
