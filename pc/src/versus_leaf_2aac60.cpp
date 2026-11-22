// versus_leaf_2aac60.cpp -- returns the element at Index of the inline int array at 0, at file offset 0x2aac60 (VA 0x10baac60).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10baac60
{
public:
    int GetUnk00(int Index);

private:
    int unk_00[1];                      // the array's length is not known; GetUnk00 indexes it
};

// UnkType_10baac60::GetUnk00
// The function pops its one argument (ret 4).
int UnkType_10baac60::GetUnk00(int Index)
{
    return unk_00[Index];
}
