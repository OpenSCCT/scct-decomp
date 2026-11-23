// campaign_leaf_4d6950.cpp -- one function at file offset 0x4d6950, preferred VA 0x10dd6950.
// The constructor stores First at offset 0 and Second at offset 4 and copies Third into the member
// at offset 8 with the constructor at 0x10daa830. The class, member and parameter names are
// invented; the offset and the bytes are the binary's.

class UnkType_10dd6950_Member
{
public:
    int unk_0;

    UnkType_10dd6950_Member(const UnkType_10dd6950_Member& Other);
};

class UnkType_10dd6950
{
public:
    int unk_0;
    int unk_4;
    UnkType_10dd6950_Member unk_8;

    UnkType_10dd6950(int First, int Second, const UnkType_10dd6950_Member& Third);
};

// UnkType_10dd6950::UnkType_10dd6950
UnkType_10dd6950::UnkType_10dd6950(int First, int Second, const UnkType_10dd6950_Member& Third)
    : unk_0(First),
      unk_4(Second),
      unk_8(Third)
{
}
