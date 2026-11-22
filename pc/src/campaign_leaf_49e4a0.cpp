// campaign_leaf_49e4a0.cpp -- thiscall at VA 0x10d9e4a0: calls the method at VA 0x10d9e290 on the
// same object with its two arguments and 1, and returns the result. All names are invented.

class UnkType_10d9e4a0
{
public:
    int Unk_10d9e290(int First, int Second, int Count);
    int Unk_10d9e4a0(int First, int Second);
};

// UnkType_10d9e4a0::Unk_10d9e4a0
int UnkType_10d9e4a0::Unk_10d9e4a0(int First, int Second)
{
    return Unk_10d9e290(First, Second, 1);
}
