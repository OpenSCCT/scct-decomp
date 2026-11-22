// campaign_leaf_14b8b0.cpp -- returns 1 when any of the three dwords of this differs from the
// corresponding dword of the argument, otherwise 0. File offset 0x14b8b0, VA 0x10a4b8b0. The class
// and method names are invented; the offsets are the binary's, and the argument type is a guess.

class UnkVec_10a4b8b0
{
public:
    int unk_00;
    int unk_04;
    int unk_08;
};

class UnkType_10a4b8b0
{
public:
    int UnkMethod_10a4b8b0(UnkVec_10a4b8b0 *Other);

private:
    int unk_00;
    int unk_04;
    int unk_08;
};

// UnkType_10a4b8b0::UnkMethod_10a4b8b0
int UnkType_10a4b8b0::UnkMethod_10a4b8b0(UnkVec_10a4b8b0 *Other)
{
    if ( unk_00 != Other->unk_00 || unk_04 != Other->unk_04 || unk_08 != Other->unk_08 )
    {
        return 1;
    }
    return 0;
}
