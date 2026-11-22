// campaign_leaf_4f75f0.cpp -- one function at file offset 0x4f75f0, preferred VA 0x10df75f0. A
// constructor: it stores its two words at 0x0 and 0x4 and copies its four-word structure to 0x8.
// The class, structure, member and parameter names are invented; the offsets and the bytes are
// the binary's.

struct UnkType_10df75f0_Quad
{
    int unk_0;
    int unk_4;
    int unk_8;
    int unk_c;
};

class UnkType_10df75f0
{
public:
    UnkType_10df75f0(int First, int Second, const UnkType_10df75f0_Quad& Third);

    int unk_0;
    int unk_4;
    UnkType_10df75f0_Quad unk_8;
};

// UnkType_10df75f0::UnkType_10df75f0
UnkType_10df75f0::UnkType_10df75f0(int First, int Second, const UnkType_10df75f0_Quad& Third)
{
    unk_0 = First;
    unk_4 = Second;
    unk_8 = Third;
}
