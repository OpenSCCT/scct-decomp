// versus_leaf_2084d0.cpp -- returns the int member at 0x1a0 of the object, at file offset 0x2084d0 (VA 0x10b084d0).
// The class, member and method names are invented; the offsets and the argument sizes
// are the binary's.

class UnkType_10b084d0
{
public:
    int GetUnk1A0();

private:
    unsigned char unk_00[0x1a0];  // not read by this function
    int unk_1a0;        // read by GetUnk1A0
};

// UnkType_10b084d0::GetUnk1A0
int UnkType_10b084d0::GetUnk1A0()
{
    return unk_1a0;
}
