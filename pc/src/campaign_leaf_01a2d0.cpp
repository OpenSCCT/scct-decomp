// campaign_leaf_01a2d0.cpp -- one function at file offset 0x1a2d0, preferred VA 0x1091a2d0. It sets
// the three words at the start of this object to zero and returns this object. The class and method
// names are invented; the offset and the bytes are the binary's.

class UnkType_1091a2d0
{
public:
    UnkType_1091a2d0 *UnkClear();

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_1091a2d0::UnkClear
UnkType_1091a2d0 *UnkType_1091a2d0::UnkClear()
{
    unk_00 = 0;
    unk_04 = 0;
    unk_08 = 0;
    return this;
}
