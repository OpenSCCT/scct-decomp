// versus_leaf_239fe0.cpp -- replaces the pointer at 0 with the pointer at 4 of the object it names, at file offset 0x239fe0 (VA 0x10b39fe0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

struct UnkNode_10b39fe0
{
    unsigned char unk_00[0x4];
    UnkNode_10b39fe0 *unk_04;                // the next node
};

class UnkType_10b39fe0
{
public:
    UnkType_10b39fe0 &AdvanceUnk00();

private:
    UnkNode_10b39fe0 *unk_00;
};

// UnkType_10b39fe0::AdvanceUnk00
UnkType_10b39fe0 &UnkType_10b39fe0::AdvanceUnk00()
{
    unk_00 = unk_00->unk_04;
    return *this;
}
