// campaign_leaf_0618d0.cpp -- one function at file offset 0x618d0, preferred VA 0x109618d0. It
// returns the pointer stored at offset 0x10 when the size word at offset 0x24 is at least 0x10, and
// otherwise the address of that word, the start of an inline buffer. The class and method names are
// invented; the offset and the bytes are the binary's.

class UnkType_109618d0
{
public:
    void *UnkData();

private:
    unsigned char unk_00[0x10];     // not read by this function
    void *unk_10;                   // pointer, or the first word of the inline buffer
    unsigned char unk_14[0x10];     // rest of the inline buffer, not read by this function
    unsigned int unk_24;            // size, compared with 0x10 unsigned
};

// UnkType_109618d0::UnkData
void *UnkType_109618d0::UnkData()
{
    if ( unk_24 >= 0x10 )
    {
        return unk_10;
    }
    return &unk_10;
}
