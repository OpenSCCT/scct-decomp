// versus_leaf_08efa0.cpp -- the function at file offset 0x8efa0, VA 0x1098efa0, 29 bytes. It returns
// the item at the index in its argument of the array at +0x240, or null when the index is not below
// the count at +0x244.
// The class and method names are invented; the offset and the bytes come from the binary.

class UnkItem_1098efa0;

class UnkType_1098efa0
{
public:
    UnkItem_1098efa0 *UnkFunc_1098efa0(int Index);

private:
    unsigned char unk_00[0x240];    // not read by this function
    UnkItem_1098efa0 **unk_240;
    int unk_244;
};

// UnkType_1098efa0::UnkFunc_1098efa0
UnkItem_1098efa0 *UnkType_1098efa0::UnkFunc_1098efa0(int Index)
{
    if ( Index < unk_244 )
    {
        return unk_240[Index];
    }
    return 0;
}
