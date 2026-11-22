// versus_leaf_2b5ed0.cpp -- clears the int at 0xc unless it is zero or the byte at 0x15 has bit 2 set, at file offset 0x2b5ed0 (VA 0x10bb5ed0).
// The class, member, argument and method names are invented; the offsets, the argument
// sizes and the return convention are the binary's.

class UnkType_10bb5ed0
{
public:
    void ClearUnk0CUnlessFlagged();

private:
    unsigned char unk_00[0xc];          // not read by this function
    int unk_0c;                         // cleared by ClearUnk0CUnlessFlagged
    unsigned char unk_10[0x15 - 0x10];  // not read by this function
    unsigned char unk_15;               // tested by ClearUnk0CUnlessFlagged
};

// UnkType_10bb5ed0::ClearUnk0CUnlessFlagged
void UnkType_10bb5ed0::ClearUnk0CUnlessFlagged()
{
    if ( unk_0c != 0 && !( unk_15 & 2 ) )
    {
        unk_0c = 0;
    }
}
