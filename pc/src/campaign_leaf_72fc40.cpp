// campaign_leaf_72fc40.cpp -- one function at file offset 0x72fc40, preferred VA 0x1102fc40. A
// constructor: it zeroes the words at 0x0 and 0x4 and constructs the member at 0x8 with its
// argument and 0 through the constructor at VA 0x10ef9b60. The class names are invented; the
// offsets and the callee's address are the binary's.

class UnkType_1102fc40_Member
{
public:
    UnkType_1102fc40_Member(int First, int Second);

    int unk_0;
};

class UnkType_1102fc40
{
public:
    UnkType_1102fc40(int Value);

    int unk_0;
    int unk_4;
    UnkType_1102fc40_Member unk_8;
};

// UnkType_1102fc40::UnkType_1102fc40
UnkType_1102fc40::UnkType_1102fc40(int Value)
    : unk_0(0), unk_4(0), unk_8(Value, 0)
{
}
