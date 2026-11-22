// campaign_leaf_08dce0.cpp -- one function at file offset 0x8dce0, preferred VA 0x1098dce0. It
// returns the word at offset 0x40 of the object that the pointer at offset 0x33c designates, or 0
// when that pointer is null. The class and struct names are invented; the offset and the bytes are
// the binary's.

struct UnkType_1098dce0_Target
{
    unsigned char unk_00[0x40];     // not read by these functions
    int unk_40;
};

class UnkType_1098dce0
{
public:
    int UnkGet40() const;

private:
    unsigned char unk_00[0x33c];    // not read by this function
    UnkType_1098dce0_Target *unk_33c;
};

// UnkType_1098dce0::UnkGet40
int UnkType_1098dce0::UnkGet40() const
{
    if ( unk_33c != 0 )
    {
        return unk_33c->unk_40;
    }
    return 0;
}
