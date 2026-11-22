// versus_leaf_2a2500.cpp -- returns the float at [Col] of the row at [Row] of the pointer table at 4, at file offset 0x2a2500 (VA 0x10ba2500).
// The class, storage, member and method names are invented; the offsets, the table
// strides and the argument sizes are the binary's.

class UnkType_10ba2500
{
public:
    float GetUnk04Table(int Row, int Col);

private:
    unsigned char unk_00[0x4];          // not read by this function
    float *unk_04[1];                   // the table's length is not known; GetUnk04Table indexes it
};

// UnkType_10ba2500::GetUnk04Table
// Both arguments are popped (ret 8).
float UnkType_10ba2500::GetUnk04Table(int Row, int Col)
{
    return unk_04[Row][Col];
}
