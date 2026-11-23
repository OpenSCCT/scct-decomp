// campaign_leaf_1b5bc0.cpp -- constructor at VA 0x10ab5bc0 of an array of 4-byte elements (data,
// count, capacity) from two other arrays: it starts empty and adds every element of the first and
// then of the second through the method at VA 0x1098c4f0. The class and member names are invented.

class UnkType_10ab5bc0
{
public:
    UnkType_10ab5bc0(const UnkType_10ab5bc0& First, const UnkType_10ab5bc0& Second);

    void Unk_1098c4f0(const int& Item);

private:
    int* unk_0;
    int unk_4;
    int unk_8;
};

// UnkType_10ab5bc0::UnkType_10ab5bc0
UnkType_10ab5bc0::UnkType_10ab5bc0(const UnkType_10ab5bc0& First, const UnkType_10ab5bc0& Second)
    : unk_0(0), unk_4(0), unk_8(0)
{
    int i;
    for ( i = 0; i < First.unk_4; i++ )
    {
        Unk_1098c4f0(First.unk_0[i]);
    }
    for ( i = 0; i < Second.unk_4; i++ )
    {
        Unk_1098c4f0(Second.unk_0[i]);
    }
}
