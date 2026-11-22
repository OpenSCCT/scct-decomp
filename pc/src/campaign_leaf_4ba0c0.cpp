// campaign_leaf_4ba0c0.cpp -- one function at file offset 0x4ba0c0, preferred VA 0x10dba0c0. A
// constructor: it stores its two words at 0x0 and 0x4 and copies its three-word structure to 0x8.
// The class, structure, member and parameter names are invented; the offsets and the bytes are
// the binary's.

struct UnkTriple_10dba0c0
{
    int unk_0;
    int unk_4;
    int unk_8;
};

class UnkType_10dba0c0
{
public:
    UnkType_10dba0c0(int First, int Second, const UnkTriple_10dba0c0& Third);

    int unk_0;
    int unk_4;
    UnkTriple_10dba0c0 unk_8;
};

// UnkType_10dba0c0::UnkType_10dba0c0
UnkType_10dba0c0::UnkType_10dba0c0(int First, int Second, const UnkTriple_10dba0c0& Third)
{
    unk_0 = First;
    unk_4 = Second;
    unk_8 = Third;
}
