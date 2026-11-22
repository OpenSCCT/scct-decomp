// versus_leaf_262ef0.cpp -- returns true, ignoring its two arguments, at file offset 0x262ef0 (VA 0x10b62ef0).
// The class and method names are invented; the offsets and the argument sizes are the binary's.

class UnkType_10b62ef0
{
public:
    bool ReturnsTrueTwo(int Unused1, int Unused2);
};

// UnkType_10b62ef0::ReturnsTrueTwo
// The arguments are never read; the function pops both (ret 8).
bool UnkType_10b62ef0::ReturnsTrueTwo(int Unused1, int Unused2)
{
    return true;
}
