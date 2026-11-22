// campaign_leaf_678a80.cpp -- one function at file offset 0x678a80, preferred VA 0x10f78a80. It
// stores its second argument at 0x80 of each non-null object among the four pointers at 0x48-0x54
// of its first argument, and at 0x114 of each non-null object among the two rows of four pointers
// at 0x58-0x74. It pops its arguments (stdcall). The class, function and member names are invented;
// the offset and the bytes are the binary's.

struct UnkType_10f78a80_First
{
    unsigned char unk_0[0x80];
    int unk_80;
};

struct UnkType_10f78a80_Second
{
    unsigned char unk_0[0x114];
    int unk_114;
};

struct UnkType_10f78a80
{
    unsigned char unk_0[0x48];
    UnkType_10f78a80_First* unk_48;
    UnkType_10f78a80_First* unk_4c;
    UnkType_10f78a80_First* unk_50;
    UnkType_10f78a80_First* unk_54;
    UnkType_10f78a80_Second* unk_58[2][4];
};

// Unk_10f78a80
void __stdcall Unk_10f78a80(UnkType_10f78a80* Object, int Value)
{
    int Index;
    int Group;

    if ( Object->unk_48 != 0 )
    {
        Object->unk_48->unk_80 = Value;
    }
    if ( Object->unk_4c != 0 )
    {
        Object->unk_4c->unk_80 = Value;
    }
    if ( Object->unk_50 != 0 )
    {
        Object->unk_50->unk_80 = Value;
    }
    if ( Object->unk_54 != 0 )
    {
        Object->unk_54->unk_80 = Value;
    }
    for ( Index = 0; Index < 4; Index++ )
    {
        for ( Group = 0; Group < 2; Group++ )
        {
            if ( Object->unk_58[Group][Index] != 0 )
            {
                Object->unk_58[Group][Index]->unk_114 = Value;
            }
        }
    }
}
