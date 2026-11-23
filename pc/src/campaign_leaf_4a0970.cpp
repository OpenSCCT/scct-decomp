// campaign_leaf_4a0970.cpp -- one function at file offset 0x4a0970, preferred VA 0x10da0970.
// It passes First and a copy of the 8-byte Second to the method at 0x10d83a90 of the same object.
// The class, structure, method and parameter names are invented; the offset and the bytes are the
// binary's.

struct UnkType_10da0970_Pair
{
    int unk_0;
    int unk_4;
};

class UnkType_10da0970
{
public:
    void Unk_10d83a90(int First, UnkType_10da0970_Pair Second);
    void Unk_10da0970(int First, const UnkType_10da0970_Pair& Second);
};

// UnkType_10da0970::Unk_10da0970
void UnkType_10da0970::Unk_10da0970(int First, const UnkType_10da0970_Pair& Second)
{
    Unk_10d83a90(First, Second);
}
