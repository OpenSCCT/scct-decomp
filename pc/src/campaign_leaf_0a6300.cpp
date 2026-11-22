// campaign_leaf_0a6300.cpp -- one function at file offset 0xa6300, preferred VA 0x109a6300. It
// returns the word at offset 0x2b4 when that word is nonzero. Otherwise it returns the word at
// offset 0x40 of the object that the pointer at offset 0x38 of the object at offset 0x7c
// designates, or 0 when that pointer is null. Its argument is not used. The class and method names
// are invented; the offset and the bytes are the binary's.

struct UnkType_109a6300_Target
{
    unsigned char unk_00[0x40];     // not read by this function
    int unk_40;
};

struct UnkType_109a6300_Mid
{
    unsigned char unk_00[0x38];     // not read by this function
    UnkType_109a6300_Target *unk_38;
};

class UnkType_109a6300
{
public:
    int UnkGetValue(int Unused) const;

private:
    unsigned char unk_00[0x7c];     // not read by this function
    UnkType_109a6300_Mid *unk_7c;
    unsigned char unk_80[0x234];    // not read by this function
    int unk_2b4;
};

// UnkType_109a6300::UnkGetValue
int UnkType_109a6300::UnkGetValue(int Unused) const
{
    if ( unk_2b4 != 0 )
    {
        return unk_2b4;
    }
    if ( unk_7c->unk_38 != 0 )
    {
        return unk_7c->unk_38->unk_40;
    }
    return 0;
}
