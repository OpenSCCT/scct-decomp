// campaign_leaf_0a00c0.cpp -- one function at file offset 0xa00c0, preferred VA 0x109a00c0. It
// returns -1 when the word at offset 0x34 is at least 0x7fff. Otherwise it stores the word plus
// one there and returns the old word. The class and method names are invented; the offset and the
// bytes are the binary's.

class UnkType_109a00c0
{
public:
    int UnkNext();

private:
    unsigned char unk_00[0x34];     // not read by this function
    int unk_34;
};

// UnkType_109a00c0::UnkNext
int UnkType_109a00c0::UnkNext()
{
    if ( unk_34 < 0x7fff )
    {
        int Old = unk_34;
        unk_34 = Old + 1;
        return Old;
    }
    return -1;
}
