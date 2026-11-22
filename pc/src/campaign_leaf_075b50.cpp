// campaign_leaf_075b50.cpp -- one function at file offset 0x75b50, preferred VA 0x10975b50. It
// returns the word at offset 0xc0 of the object that the pointer at offset 0xc of this object
// designates. The class and struct names are invented; the offset and the bytes are the binary's.

struct UnkType_10975b50_Inner
{
    unsigned char unk_00[0xc0];     // not read by this function
    int unk_c0;
};

class UnkType_10975b50
{
public:
    int UnkGetInner() const;

private:
    unsigned char unk_00[0xc];      // not read by this function
    UnkType_10975b50_Inner *unk_0c;
};

// UnkType_10975b50::UnkGetInner
int UnkType_10975b50::UnkGetInner() const
{
    return unk_0c->unk_c0;
}
