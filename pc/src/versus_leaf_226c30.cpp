// versus_leaf_226c30.cpp -- returns false, ignoring its 3 arguments, at file offset 0x226c30 (VA 0x10b26c30).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b26c30
{
public:
    bool TestFalse3(int Unused1, int Unused2, int Unused3);
};

// UnkType_10b26c30::TestFalse3
// The arguments are never read; the function pops 12 bytes (ret c).
bool UnkType_10b26c30::TestFalse3(int Unused1, int Unused2, int Unused3)
{
    return false;
}
