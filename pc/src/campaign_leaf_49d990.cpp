// campaign_leaf_49d990.cpp -- thiscall at VA 0x10d9d990: calls the method at VA 0x10d9d700 on the
// same object with its two arguments and 1, and returns the result. All names are invented.

class UnkType_10d9d990
{
public:
    int Unk_10d9d700(int First, int Second, int Count);
    int Unk_10d9d990(int First, int Second);
};

// UnkType_10d9d990::Unk_10d9d990
int UnkType_10d9d990::Unk_10d9d990(int First, int Second)
{
    return Unk_10d9d700(First, Second, 1);
}
