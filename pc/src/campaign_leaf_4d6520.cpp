// campaign_leaf_4d6520.cpp -- one function at file offset 0x4d6520, preferred VA 0x10dd6520.
// The constructor builds the member at offset 4, whose inline constructor stores the result of its
// method at 0x10d80c50 at its offset 4 and clears its offset 8. The class, method and member names
// are invented; the offset and the bytes are the binary's.

class UnkType_10d80c50
{
public:
    int unk_0;
    int unk_4;
    int unk_8;

    UnkType_10d80c50()
    {
        unk_4 = Unk_10d80c50();
        unk_8 = 0;
    }

    int Unk_10d80c50();
};

class UnkType_10dd6520
{
public:
    int unk_0;
    UnkType_10d80c50 unk_4;

    UnkType_10dd6520();
};

// UnkType_10dd6520::UnkType_10dd6520
UnkType_10dd6520::UnkType_10dd6520()
{
}
