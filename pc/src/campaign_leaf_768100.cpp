// campaign_leaf_768100.cpp -- one function at file offset 0x768100, preferred VA 0x11068100. When
// the 16-byte record its argument points to has 1 at 0x0, 0x10 at 0x4 and 1 or 2 at 0x8, it copies
// the record into this object and returns 1; otherwise it returns 0. The class, method and member
// names are invented; the offset and the bytes are the binary's.

class UnkType_11068100
{
public:
    int Unk_11068100(const UnkType_11068100* Other);

    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

// UnkType_11068100::Unk_11068100
int UnkType_11068100::Unk_11068100(const UnkType_11068100* Other)
{
    int Valid;

    Valid = Other->unk_0 == 1 && Other->unk_4 == 0x10 && ( Other->unk_8 == 1 || Other->unk_8 == 2 );
    if ( !Valid )
    {
        return 0;
    }
    *this = *Other;
    return 1;
}
