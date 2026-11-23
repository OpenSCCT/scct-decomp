// campaign_leaf_768dc0.cpp -- one function at file offset 0x768dc0, preferred VA 0x11068dc0. It
// creates an object of the kind given by the record's word at 0x0 through the function at VA
// 0x11068c90 (kind 0), 0x11068bf0 (kind 1) or 0x11068d40 (kind 2), passing all four arguments on,
// and returns 0 when that succeeds, -1 when it fails or the kind is unknown. The type and function
// names are invented; the addresses are the binary's.

class UnkType_11068dc0_Object;

struct UnkType_11068dc0_Record
{
    int unk_0;
    int unk_4;
};

int Unk_11068c90(UnkType_11068dc0_Object** Object, int Value, UnkType_11068dc0_Record* Record,
                 int Extra);
int Unk_11068bf0(UnkType_11068dc0_Object** Object, int Value, UnkType_11068dc0_Record* Record,
                 int Extra);
int Unk_11068d40(UnkType_11068dc0_Object** Object, int Value, UnkType_11068dc0_Record* Record,
                 int Extra);

// Unk_11068dc0
int Unk_11068dc0(UnkType_11068dc0_Object** Object, int Value, UnkType_11068dc0_Record* Record,
                 int Extra)
{
    switch ( Record->unk_0 )
    {
    case 0:
        if ( Unk_11068c90(Object, Value, Record, Extra) != 0 )
        {
            return -1;
        }
        break;
    case 1:
        if ( Unk_11068bf0(Object, Value, Record, Extra) != 0 )
        {
            return -1;
        }
        break;
    case 2:
        if ( Unk_11068d40(Object, Value, Record, Extra) != 0 )
        {
            return -1;
        }
        break;
    default:
        return -1;
    }
    return 0;
}
