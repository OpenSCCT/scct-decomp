// versus_leaf_2bae10.cpp -- returns false, ignoring its four arguments, at file offset 0x2bae10 (VA 0x10bbae10).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10bbae10
{
public:
    bool TestFalse4(int Unused1, int Unused2, int Unused3, int Unused4);
};

// UnkType_10bbae10::TestFalse4
// The arguments are never read; the function pops all four (ret 0x10).
bool UnkType_10bbae10::TestFalse4(int Unused1, int Unused2, int Unused3, int Unused4)
{
    return false;
}
