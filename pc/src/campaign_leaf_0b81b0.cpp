// campaign_leaf_0b81b0.cpp -- one function at file offset 0xb81b0, preferred VA 0x109b81b0. It
// returns the word at offset 0 of the row, selected by the index in its argument, of the table at
// offset 0x11c of the object at offset 0x80, when that word is nonzero; otherwise the word that
// the pointer at offset 0x28 designates. Rows are 0x80 bytes. The class and method names are
// invented; the offset and the bytes are the binary's.

struct UnkType_109b81b0_Row
{
    int unk_00;
    unsigned char unk_04[0x7c];     // not read by this function
};

struct UnkType_109b81b0_Mid
{
    unsigned char unk_00[0x11c];    // not read by this function
    UnkType_109b81b0_Row *unk_11c;
};

class UnkType_109b81b0
{
public:
    int UnkGetRowValue(int Index) const;

private:
    unsigned char unk_00[0x28];     // not read by this function
    int *unk_28;
    unsigned char unk_2c[0x54];     // not read by this function
    UnkType_109b81b0_Mid *unk_80;
};

// UnkType_109b81b0::UnkGetRowValue
int UnkType_109b81b0::UnkGetRowValue(int Index) const
{
    if ( unk_80->unk_11c != 0 )
    {
        int Value = unk_80->unk_11c[Index].unk_00;
        if ( Value != 0 )
        {
            return Value;
        }
    }
    return *unk_28;
}
