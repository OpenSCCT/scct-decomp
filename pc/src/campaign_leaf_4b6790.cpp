// campaign_leaf_4b6790.cpp -- one function at file offset 0x4b6790, preferred VA 0x10db6790.
// The constructor stores First at offset 0 and Second at offset 4 and builds the member at offset
// 8 from Third with the constructor at 0x10d8af70. The class, member and parameter names are
// invented; the offset and the bytes are the binary's.

class UnkType_10db6790_Member
{
public:
    int unk_0;

    UnkType_10db6790_Member(int Value);
};

class UnkType_10db6790
{
public:
    int unk_0;
    int unk_4;
    UnkType_10db6790_Member unk_8;

    UnkType_10db6790(int First, int Second, int Third);
};

// UnkType_10db6790::UnkType_10db6790
UnkType_10db6790::UnkType_10db6790(int First, int Second, int Third)
    : unk_0(First),
      unk_4(Second),
      unk_8(Third)
{
}
