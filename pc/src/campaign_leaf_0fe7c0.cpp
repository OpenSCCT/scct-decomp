// campaign_leaf_0fe7c0.cpp -- one function at file offset 0xfe7c0, preferred VA 0x109fe7c0. It
// returns the element of the array at offset 0x38 at the position of the first element of the
// array at offset 0x44 whose first word equals its argument, or 0 when there is none. The class
// and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109fe7c0_Elem
{
    int unk_00;
    unsigned char unk_04[0x44];     // not read by this function
};

struct UnkType_109fe7c0_Other
{
    unsigned char unk_00[0x3c];     // not read by this function
};

class UnkType_109fe7c0
{
public:
    UnkType_109fe7c0_Other *UnkFindOther(int Key) const;

private:
    unsigned char unk_00[0x38];     // not read by this function
    UnkType_109fe7c0_Other *unk_38;
    unsigned char unk_3c[0x8];      // not read by this function
    UnkType_109fe7c0_Elem *unk_44;
    int unk_48;
};

// UnkType_109fe7c0::UnkFindOther
UnkType_109fe7c0_Other *UnkType_109fe7c0::UnkFindOther(int Key) const
{
    for ( int i = 0; i < unk_48; ++i )
    {
        if ( Key == unk_44[i].unk_00 )
        {
            return unk_38 + i;
        }
    }
    return 0;
}
