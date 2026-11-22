// campaign_leaf_2fb5d0.cpp -- one function at file offset 0x2fb5d0, preferred VA 0x10bfb5d0. When
// bit 0x1 of the byte at offset 0x444 is set it copies the 12-byte value at offset 0x438 through
// its argument and returns 1; otherwise it returns 0. The class, method and member names are
// invented; the offset and the bytes are the binary's.

struct UnkTriple
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10bfb5d0
{
public:
    unsigned char unk_0[0x438];
    UnkTriple unk_438;
    unsigned char unk_444;

    int Unk_10bfb5d0(UnkTriple& Out);
};

// UnkType_10bfb5d0::Unk_10bfb5d0
int UnkType_10bfb5d0::Unk_10bfb5d0(UnkTriple& Out)
{
    if ( unk_444 & 1 )
    {
        Out = unk_438;
        return 1;
    }
    return 0;
}
