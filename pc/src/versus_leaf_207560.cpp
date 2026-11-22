// versus_leaf_207560.cpp -- whether the int member at 0x13c of the object is nonzero, at file offset 0x207560 (VA 0x10b07560).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b07560
{
public:
    int TestUnk13C();

private:
    unsigned char unk_00[0x13c];        // not read by TestUnk13C
    int unk_13c;                        // tested by TestUnk13C
};

// UnkType_10b07560::TestUnk13C
int UnkType_10b07560::TestUnk13C()
{
    return unk_13c != 0;
}
