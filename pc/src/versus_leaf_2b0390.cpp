// versus_leaf_2b0390.cpp -- returns the address of the int at Index of the array at 4, at file offset 0x2b0390 (VA 0x10bb0390).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10bb0390
{
public:
    int *GetUnk04Address(int Index);

private:
    unsigned char unk_00[0x4];          // not read by this function
    int *unk_04;                        // array of ints, indexed by Index
};

// UnkType_10bb0390::GetUnk04Address
// The function pops its one argument (ret 4).
int *UnkType_10bb0390::GetUnk04Address(int Index)
{
    return unk_04 + Index;
}
