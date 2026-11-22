// versus_leaf_22fde0.cpp -- returns true, ignoring its argument, at file offset 0x22fde0 (VA 0x10b2fde0).
// The class and method names are invented; the offsets and the argument sizes are the binary's.

class UnkType_10b2fde0
{
public:
    bool ReturnsTrue(int Unused);
};

// UnkType_10b2fde0::ReturnsTrue
// Unused is never read; the function pops its argument (ret 4).
bool UnkType_10b2fde0::ReturnsTrue(int Unused)
{
    return true;
}
