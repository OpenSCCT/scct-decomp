// campaign_leaf_0b0320.cpp -- one function at file offset 0xb0320, preferred VA 0x109b0320. It
// returns 1 when the word at offset 0x430 is nonzero, and 0 otherwise. The class and method names
// are invented; the offset and the bytes are the binary's.

class UnkType_109b0320
{
public:
    int UnkHas430() const;

private:
    unsigned char unk_00[0x430];    // not read by this function
    int unk_430;
};

// UnkType_109b0320::UnkHas430
int UnkType_109b0320::UnkHas430() const
{
    return unk_430 != 0;
}
