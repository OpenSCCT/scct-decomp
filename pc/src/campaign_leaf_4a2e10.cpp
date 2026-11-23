// campaign_leaf_4a2e10.cpp -- one function at file offset 0x4a2e10, preferred VA 0x10da2e10.
// The constructor builds the member at offset 4 with the constructor at 0x10d8b2d0 and stores
// Value at offset 0. The class, member and parameter names are invented; the offset and the bytes
// are the binary's.

class UnkType_10da2e10_Member
{
public:
    int unk_0;

    UnkType_10da2e10_Member();
};

class UnkType_10da2e10
{
public:
    int unk_0;
    UnkType_10da2e10_Member unk_4;

    UnkType_10da2e10(int Value);
};

// UnkType_10da2e10::UnkType_10da2e10
UnkType_10da2e10::UnkType_10da2e10(int Value)
{
    unk_0 = Value;
}
