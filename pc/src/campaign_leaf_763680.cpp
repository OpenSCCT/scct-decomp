// campaign_leaf_763680.cpp -- one function at file offset 0x763680, preferred VA 0x11063680. In
// the array of 20-byte entries described by the object at 0x8c (pointer at 0x0, count at 0x4) it
// returns the entry whose first word is its argument; failing that, unless the argument is -1, the
// first entry whose first word is -1; otherwise null. The class, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkType_11063680_Entry
{
    int unk_0;
    unsigned char unk_4[0x14 - 0x4];
};

struct UnkType_11063680_Array
{
    UnkType_11063680_Entry* unk_0;
    int unk_4;
};

class UnkType_11063680
{
public:
    UnkType_11063680_Entry* Unk_11063680(int Key);

    unsigned char unk_0[0x8c];
    UnkType_11063680_Array* unk_8c;
};

// UnkType_11063680::Unk_11063680
UnkType_11063680_Entry* UnkType_11063680::Unk_11063680(int Key)
{
    UnkType_11063680_Entry* Entries;
    UnkType_11063680_Entry* Entry;
    int Index;

    Entries = unk_8c->unk_0;
    Entry = Entries;
    for ( Index = 0; Index < unk_8c->unk_4; Index++, Entry++ )
    {
        if ( Entry->unk_0 == Key )
        {
            return Entry;
        }
    }
    if ( Key != -1 )
    {
        Entry = Entries;
        for ( Index = 0; Index < unk_8c->unk_4; Index++, Entry++ )
        {
            if ( Entry->unk_0 == -1 )
            {
                return Entry;
            }
        }
    }
    return 0;
}
