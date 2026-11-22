// campaign_leaf_2f1c10.cpp -- a member function at VA 0x10bf1c10 that returns 1 when the member at
// VA 0x10bee910, given the same two arguments, returns non-zero, and 0 otherwise. The class, method
// and parameter names are invented; the addresses are the binary's.

class UnkType_10bf1c10
{
public:
    int Unk_10bee910(int First, int Second);
    int Unk_10bf1c10(int First, int Second);
};

// UnkType_10bf1c10::Unk_10bf1c10
int UnkType_10bf1c10::Unk_10bf1c10(int First, int Second)
{
    return Unk_10bee910(First, Second) != 0;
}
