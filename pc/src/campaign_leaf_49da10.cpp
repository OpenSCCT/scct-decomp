// campaign_leaf_49da10.cpp -- thiscall at VA 0x10d9da10: calls the method at VA 0x10d9d700 on the
// same object with its two arguments and 4, and returns the result. All names are invented.

class UnkType_10d9da10
{
public:
    int Unk_10d9d700(int First, int Second, int Count);
    int Unk_10d9da10(int First, int Second);
};

// UnkType_10d9da10::Unk_10d9da10
int UnkType_10d9da10::Unk_10d9da10(int First, int Second)
{
    return Unk_10d9d700(First, Second, 4);
}
