// campaign_leaf_73ee40.cpp -- one function at file offset 0x73ee40, preferred VA 0x1103ee40. It
// checks every 8-byte entry of the record (the entries at 0x14, their count at 0x18): the object
// that the stdcall function at VA 0x11045de0 finds for the entry's first word is classified by
// the function at VA 0x1103efb0. It returns 2 as soon as one is classified 2, and does the same
// for the object at 0x10 when it is set, returning 0 when that is classified neither 1 nor 2. It
// returns 0 when an entry found nothing or was classified neither 1 nor 2, and 1 otherwise. The
// type and function names are invented; the offsets and the addresses are the binary's.

struct UnkType_1103ee40_Object;

struct UnkType_1103ee40_Entry
{
    int unk_0;
    int unk_4;
};

struct UnkType_1103ee40_Record
{
    unsigned char unk_0[0x10];
    UnkType_1103ee40_Object* unk_10;
    UnkType_1103ee40_Entry* unk_14;
    int unk_18;
};

UnkType_1103ee40_Object* __stdcall Unk_11045de0(int Key);
int Unk_1103efb0(UnkType_1103ee40_Object* Object);

// Unk_1103ee40
int Unk_1103ee40(UnkType_1103ee40_Record* Record)
{
    UnkType_1103ee40_Entry* Entry;
    UnkType_1103ee40_Object* Object;
    int Failed;
    int Index;

    Entry = Record->unk_14;
    Failed = 0;
    for ( Index = 0; Index < Record->unk_18; Index++, Entry++ )
    {
        Object = Unk_11045de0(Entry->unk_0);
        if ( Object != 0 )
        {
            switch ( Unk_1103efb0(Object) )
            {
            case 1:
                continue;
            case 2:
                return 2;
            }
        }
        Failed = 1;
    }
    if ( Record->unk_10 != 0 )
    {
        switch ( Unk_1103efb0(Record->unk_10) )
        {
        case 1:
            break;
        case 2:
            return 2;
        default:
            Failed = 1;
        }
    }
    if ( Failed != 0 )
    {
        return 0;
    }
    return 1;
}
