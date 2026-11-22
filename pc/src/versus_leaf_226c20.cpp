// versus_leaf_226c20.cpp -- returns false, ignoring its 2 arguments, at file offset 0x226c20 (VA 0x10b26c20).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b26c20
{
public:
    bool TestFalse2(int Unused1, int Unused2);
};

// UnkType_10b26c20::TestFalse2
// The arguments are never read; the function pops 8 bytes (ret 8).
bool UnkType_10b26c20::TestFalse2(int Unused1, int Unused2)
{
    return false;
}
