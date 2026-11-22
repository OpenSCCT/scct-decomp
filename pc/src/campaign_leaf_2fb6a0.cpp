// campaign_leaf_2fb6a0.cpp -- one function at file offset 0x2fb6a0, preferred VA 0x10bfb6a0. A
// constructor: it stores its first argument at offset 0, 1 at offset 4, the three 12-byte values
// its next three arguments refer to at offsets 0x8, 0x14 and 0x20, and the word its last argument
// refers to at offset 0x2c. The class and member names are invented; the offset and the bytes are
// the binary's.

struct UnkType_10bfb6a0_Triple
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10bfb6a0
{
public:
    int unk_0;
    int unk_4;
    UnkType_10bfb6a0_Triple unk_8;
    UnkType_10bfb6a0_Triple unk_14;
    UnkType_10bfb6a0_Triple unk_20;
    int unk_2c;

    UnkType_10bfb6a0(int First, const UnkType_10bfb6a0_Triple& Second,
        const UnkType_10bfb6a0_Triple& Third, const UnkType_10bfb6a0_Triple& Fourth,
        const int& Fifth);
};

// UnkType_10bfb6a0::UnkType_10bfb6a0
UnkType_10bfb6a0::UnkType_10bfb6a0(int First, const UnkType_10bfb6a0_Triple& Second,
    const UnkType_10bfb6a0_Triple& Third, const UnkType_10bfb6a0_Triple& Fourth, const int& Fifth)
    : unk_0(First), unk_4(1), unk_8(Second), unk_14(Third), unk_20(Fourth), unk_2c(Fifth)
{
}
