// versus_leaf_24f5c0.cpp -- sets the pair at 8 and 0xc and returns true when the int at 8 was zero, else false, at file offset 0x24f5c0 (VA 0x10b4f5c0).
// The class, member, node and method names are invented; the offsets, the argument
// sizes and the return convention are the binary's.

class UnkType_10b4f5c0
{
public:
    bool SetPairIfEmpty(int A, int B);

private:
    unsigned char unk_00[0x8];          // not read by this function
    int unk_08;                         // tested and written by SetPairIfEmpty
    int unk_0c;                         // written by SetPairIfEmpty
};

// UnkType_10b4f5c0::SetPairIfEmpty
// The function pops both arguments (ret 8).
bool UnkType_10b4f5c0::SetPairIfEmpty(int A, int B)
{
    if ( unk_08 != 0 )
    {
        return false;
    }
    unk_08 = A;
    unk_0c = B;
    return true;
}
