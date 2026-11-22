// campaign_leaf_14c0e0.cpp -- stores the first argument at offset 0x00 of this, the three dwords of
// the second argument at offset 0x04 and those of the third at offset 0x10, and returns this. File
// offset 0x14c0e0, VA 0x10a4c0e0. The class and method names are invented; the offsets are the
// binary's, and the vector type is a guess.

class UnkVec_10a4c0e0
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10a4c0e0
{
public:
    UnkType_10a4c0e0 *UnkMethod_10a4c0e0(int Value, UnkVec_10a4c0e0 *First, UnkVec_10a4c0e0 *Second);

private:
    int unk_00;
    UnkVec_10a4c0e0 unk_04;
    UnkVec_10a4c0e0 unk_10;
};

// UnkType_10a4c0e0::UnkMethod_10a4c0e0
UnkType_10a4c0e0 *UnkType_10a4c0e0::UnkMethod_10a4c0e0(int Value, UnkVec_10a4c0e0 *First,
                                                       UnkVec_10a4c0e0 *Second)
{
    unk_00 = Value;
    unk_04 = *First;
    unk_10 = *Second;
    return this;
}
