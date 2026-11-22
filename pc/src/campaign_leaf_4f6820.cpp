// campaign_leaf_4f6820.cpp -- one function at file offset 0x4f6820, preferred VA 0x10df6820. A
// constructor: it zeroes a two-word pair at 0x4, an array of twenty such pairs at 0x10 and the
// words at 0x0 and 0xb0. The class, structure and member names are invented; the offsets and the
// bytes are the binary's.

struct UnkPair
{
    UnkPair()
    {
        unk_0 = 0;
        unk_4 = 0;
    }

    int unk_0;
    int unk_4;
};

class UnkType_10df6820
{
public:
    UnkType_10df6820();

    int unk_0;
    UnkPair unk_4;
    int unk_c;
    UnkPair unk_10[20];
    int unk_b0;
};

// UnkType_10df6820::UnkType_10df6820
UnkType_10df6820::UnkType_10df6820()
{
    unk_0 = 0;
    unk_b0 = 0;
}
