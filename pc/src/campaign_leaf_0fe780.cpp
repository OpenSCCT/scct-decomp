// campaign_leaf_0fe780.cpp -- one function at file offset 0xfe780, preferred VA 0x109fe780. It
// returns a pointer to the first element of the array at offset 0x44 whose first word equals its
// argument, or 0 when there is none. Elements are 0x48 bytes and the count is at offset 0x48. The
// class and method names are invented; the offset and the bytes are the binary's.

struct UnkType_109fe780_Elem
{
    int unk_00;
    unsigned char unk_04[0x44];     // not read by this function
};

class UnkType_109fe780
{
public:
    UnkType_109fe780_Elem *UnkFind(int Key) const;

private:
    unsigned char unk_00[0x44];     // not read by this function
    UnkType_109fe780_Elem *unk_44;
    int unk_48;
};

// UnkType_109fe780::UnkFind
UnkType_109fe780_Elem *UnkType_109fe780::UnkFind(int Key) const
{
    for ( int i = 0; i < unk_48; ++i )
    {
        if ( Key == unk_44[i].unk_00 )
        {
            return &unk_44[i];
        }
    }
    return 0;
}
