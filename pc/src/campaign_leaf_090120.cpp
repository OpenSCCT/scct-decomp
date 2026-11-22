// campaign_leaf_090120.cpp -- one function at file offset 0x90120, preferred VA 0x10990120. It
// returns the word at offset 0x190 when that word is nonzero. Otherwise it returns the word at
// offset 0x40 of the object that the pointer at offset 0x38 of the object at offset 0x7c
// designates, or 0 when that pointer is null. Its argument is not used. The class and struct names
// are invented; the offset and the bytes are the binary's.

struct UnkType_10990120_Target
{
    unsigned char unk_00[0x40];     // not read by this function
    int unk_40;
};

struct UnkType_10990120_Mid
{
    unsigned char unk_00[0x38];     // not read by this function
    UnkType_10990120_Target *unk_38;
};

class UnkType_10990120
{
public:
    int UnkGetValue(int Unused) const;

private:
    unsigned char unk_00[0x7c];     // not read by this function
    UnkType_10990120_Mid *unk_7c;
    unsigned char unk_80[0x110];    // not read by this function
    int unk_190;
};

// UnkType_10990120::UnkGetValue
int UnkType_10990120::UnkGetValue(int Unused) const
{
    if ( unk_190 != 0 )
    {
        return unk_190;
    }
    if ( unk_7c->unk_38 != 0 )
    {
        return unk_7c->unk_38->unk_40;
    }
    return 0;
}
