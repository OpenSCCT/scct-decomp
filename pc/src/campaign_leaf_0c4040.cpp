// campaign_leaf_0c4040.cpp -- one function at file offset 0xc4040, preferred VA 0x109c4040. It
// returns 1 when the word at offset 0x31c is nonzero, and 0 otherwise. The class and method names
// are invented; the offset and the bytes are the binary's.

class UnkType_109c4040
{
public:
    int UnkHas31c() const;

private:
    unsigned char unk_00[0x31c];    // not read by this function
    int unk_31c;
};

// UnkType_109c4040::UnkHas31c
int UnkType_109c4040::UnkHas31c() const
{
    return unk_31c != 0;
}
