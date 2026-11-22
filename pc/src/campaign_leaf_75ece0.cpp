// campaign_leaf_75ece0.cpp -- one function at file offset 0x75ece0, preferred VA 0x1105ece0. When
// the 16-byte record its argument points to has a non-zero word at 0x0, 0x10 at 0x4 and 1 or 2 at
// 0x8, it copies the record to 0xc of this object and returns 1; otherwise it returns 0. The class,
// method and member names are invented; the offset and the bytes are the binary's.

struct UnkType_1105ece0_Record
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_1105ece0
{
public:
    int Unk_1105ece0(const UnkType_1105ece0_Record* Record);

    unsigned char unk_0[0xc];
    UnkType_1105ece0_Record unk_c;
};

// UnkType_1105ece0::Unk_1105ece0
int UnkType_1105ece0::Unk_1105ece0(const UnkType_1105ece0_Record* Record)
{
    int Valid;

    Valid = Record->unk_0 != 0 && Record->unk_4 == 0x10 && ( Record->unk_8 == 1 || Record->unk_8 == 2 );
    if ( !Valid )
    {
        return 0;
    }
    unk_c = *Record;
    return 1;
}
