// versus_leaf_226c10.cpp -- returns false, ignoring its 1 argument, at file offset 0x226c10 (VA 0x10b26c10).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b26c10
{
public:
    bool TestFalse1(int Unused1);
};

// UnkType_10b26c10::TestFalse1
// The arguments are never read; the function pops 4 bytes (ret 4).
bool UnkType_10b26c10::TestFalse1(int Unused1)
{
    return false;
}
